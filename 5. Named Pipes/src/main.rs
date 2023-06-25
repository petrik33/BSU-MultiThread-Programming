use std::{
    fs::{self, File, OpenOptions},
    io::Write, mem
};

use std::process::{Command, Stdio};
use std::io::{prelude::*, SeekFrom};
use std::os::windows::io::{AsRawHandle, RawHandle};
use std::sync::{Arc, Mutex};
use std::thread;
use winapi::um::minwinbase::OVERLAPPED;
use winapi::um::winbase;
use winapi::um::winnt::{
    HANDLE,
};

fn main() {
    let mut file = File::create("exchange.bin").expect("Should create file in relative path");

    // Generate a vector of Employee structs for debugging purposes
    let students = debug_generate_students();

    serialize_students(students, &mut file).expect("Should serialize students to file");

    println!("Enter the number of clients:");
    let mut input = String::new();
    std::io::stdin()
        .read_line(&mut input)
        .expect("Should read the number of clients to run");
    let num_clients = input.trim().parse::<usize>().unwrap();

    run_clients(num_clients).expect("Should run client process");
}

fn serve_clients(num_clients: usize) -> std::io::Result<()> {
    // Create a named pipe server for client communication
    let pipe_server = named_pipe::PipeOptions::new("\\\\.\\pipe\\employee_exchange").multiple(&num_clients);

    // Open the file for reading and writing
    let mut file = OpenOptions::new()
        .read(true)
        .write(true)
        .create(true)
        .open("exchange.bin")?;

    // Create a shared mutex to synchronize access to the file
    let mutex = Arc::new(Mutex::new(()));

    // Serve client requests in a loop
    for mut client in pipe_server {
        let mutex_clone = mutex.clone();
        thread::spawn(move || {
            // Read the client request from the named pipe
            let mut request = String::new();
            client.read_to_string(&mut request).unwrap();

            // Split the request into fields
            let fields: Vec<&str> = request.trim().split(',').collect();
            let op = fields[0];
            let record_num = fields[1].parse::<usize>().unwrap();

            // Lock the file if necessary
            let file_handle = file.as_raw_handle() as HANDLE;
            let mut overlapped: OVERLAPPED = Default::default();
            let mut lock_range = unsafe { mem::zeroed::<winapi::um::winnt::LARGE_INTEGER>() };
            let mut unlock_range = unsafe { mem::zeroed::<winapi::um::winnt::LARGE_INTEGER>() };
            let locked =  match op {
                "read" => {
                    // Read the record from the file
                    let mut buf = [0; mem::size_of::<Employee>()];
                    file.seek(SeekFrom::Start((record_num * mem::size_of::<Employee>()) as u64))?;
                    file.read_exact(&mut buf);
    
                    // Send the record to the client
                    client.write_all(&buf)?;
                    client.flush()?;
                }
                "write" => {
                    // Read the new record from the client
                    let mut buf = [0; mem::size_of::<Employee>()];
                    client.read_exact(&mut buf)?;
    
                    // Write the record to the file
                    file.seek(SeekFrom::Start((record_num * mem::size_of::<Employee>()) as u64))?;
                    file.write_all(&buf);
                    file.flush();
                }
                _ => panic!("Invalid operation"),
            };
        });
    }
    
    Ok(())
}

fn run_clients(num_clients: usize) -> std::io::Result<()> {
    for i in 0..num_clients {
        let mut child = Command::new("client")
            .arg(format!("{}", i))
            .stdin(Stdio::null())
            .stdout(Stdio::inherit())
            .stderr(Stdio::inherit())
            .spawn()?;

        child.wait()?;
    }

    Ok(())
}

struct Employee {
    num: i32,         // идентификационный номер сотрудника
    name: [char; 10], // имя сотрудника
    hours: f64,       // количество отработанных часов
}

fn serialize_students(students: Vec<Employee>, file: &mut File) -> std::io::Result<()> {
    for student in students {
        // Convert the student struct to a byte array
        let mut bytes = Vec::new();

        bytes.extend_from_slice(&student.num.to_le_bytes());

        // Convert the name field to a string and encode as UTF-8 bytes
        let name_str: String = student.name.iter().collect();
        let name_bytes = name_str.as_bytes();

        // Extend the byte vector with the UTF-8 bytes and pad with null bytes
        bytes.extend_from_slice(name_bytes);
        bytes.resize(bytes.len() + (10 - name_bytes.len()), 0x00);

        bytes.extend_from_slice(&student.hours.to_le_bytes());

        // Write the byte array to the file
        file.write_all(&bytes)?;
    }
    Ok(())
}

fn debug_generate_students() -> Vec<Employee> {
    vec![
        Employee {
            num: 1,
            name: ['J', 'o', 'h', 'n', ' ', 'D', 'o', 'e', ' ', ' '],
            hours: 40.0,
        },
        Employee {
            num: 2,
            name: ['J', 'a', 'n', 'e', ' ', 'S', 'm', 'i', 't', 'h'],
            hours: 37.5,
        },
        Employee {
            num: 3,
            name: ['B', 'o', 'b', ' ', 'J', 'o', 'n', 'e', 's', ' '],
            hours: 42.5,
        },
    ]
}
