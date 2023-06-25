use std::io::{self, prelude::*};
use named_pipe::PipeClient;

#[derive(Debug)]
struct Employee {
    num: i32,         // идентификационный номер сотрудника
    name: [char; 10], // имя сотрудника
    hours: f64,       // количество отработанных часов
}

fn main() -> io::Result<()> {
    // Connect to the named pipe server
    let mut pipe = PipeClient::connect("\\\\.\\pipe\\employee_exchange")?;

    // Start the client loop
    loop {
        // Prompt the user to enter an operation
        println!("Enter an operation (read, write, exit):");
        let mut input = String::new();
        io::stdin().read_line(&mut input)?;
        let operation = input.clone();

        if operation == "exit" {
            break;
        }

        // Prompt the user to enter a record key
        println!("Enter a record key:");
        input.clear();
        io::stdin().read_line(&mut input)?;
        let record_num = input.trim().parse::<usize>().unwrap();

        match operation.trim() {
            "read" => {
                // Send the read request to the server
                let request = format!("read,{}", record_num);
                pipe.write_all(request.as_bytes())?;
                pipe.flush()?;

                // Read the record from the server and print it to the console
                let mut buf = [0; std::mem::size_of::<Employee>()];
                pipe.read_exact(&mut buf)?;
                let record = unsafe { std::mem::transmute::<[u8; std::mem::size_of::<Employee>()], Employee>(buf) };
                println!("Record {}: {:?}", record_num, record);
            }
            "write" => {
                // Send the read request to the server
                let request = format!("read,{}", record_num);
                pipe.write_all(request.as_bytes())?;
                pipe.flush()?;

                // Read the record from the server and print it to the console
                let mut buf = [0; std::mem::size_of::<Employee>()];
                pipe.read_exact(&mut buf)?;
                let record = unsafe { std::mem::transmute::<[u8; std::mem::size_of::<Employee>()], Employee>(buf) };
                println!("Record {}: {:?}", record_num, record);

                // Prompt the user to enter new field values
                println!("Enter new field values:");
                let mut input = String::new();
                io::stdin().read_line(&mut input)?;
                let fields: Vec<&str> = input.trim().split(',').collect();
                let num = fields[0].parse::<i32>().unwrap();
                let name = fields[1].chars().collect::<Vec<char>>();
                let hours = fields[2].parse::<f64>().unwrap();
                let new_record = Employee { num, name: [name[0], name[1], name[2], name[3], name[4], name[5], name[6], name[7], name[8], name[9]], hours };

                // Send the modified record to the server
                let buf = unsafe { std::mem::transmute::<Employee, [u8; std::mem::size_of::<Employee>()]>(new_record) };
                pipe.write_all(&buf)?;
                pipe.flush()?;
            }
            _ => {
                println!("Invalid operation");
            }
        }
    }

    Ok(())
}
