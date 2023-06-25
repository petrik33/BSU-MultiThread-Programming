use std::io::{self, prelude::*};
use std::process;

use named_pipe::{PipeOptions, PipeServer};

fn main() {
    // Read the command-line arguments
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 3 {
        eprintln!("Usage: receiver <message_file> <num_senders>");
        process::exit(1);
    }
    let message_file = &args[1];
    let num_senders: usize = match args[2].parse() {
        Ok(num) => num,
        Err(_) => {
            eprintln!("Invalid number of senders");
            process::exit(1);
        }
    };

    // Create the signal pipe for receiving readiness signals from senders
    let pipe_options = PipeOptions::new("\\\\.\\pipe\\signal_pipe");

    let signal_pipe = match pipe_options.single() {
        Ok(pipe) => pipe,
        Err(err) => {
            eprintln!("Error creating signal pipe: {}", err);
            process::exit(1);
        }
    };

    // Wait for readiness signals from senders
    let mut signal_buffer = [0u8; 1];
    match signal_pipe.wait() {
        Ok(mut server) => {
            match server.read_exact(&mut signal_buffer[..]) {
                Ok(_) => (),
                Err(err) => {
                    eprintln!("Error receiving signal: {}", err);
                    process::exit(1);
                }
            };
        }
        Err(err) => {
            eprintln!("Error receiving signal: {}", err);
            process::exit(1);
        }
    }
    println!("All senders ready");

    // Read user input and perform actions
    loop {
        println!("Enter 'read' to read a message or 'exit' to quit:");
        let mut input = String::new();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read input");

        match input.trim() {
            "exit" => break,
            "read" => {
                // Open the message file and read the next message
                let mut file = match std::fs::OpenOptions::new().read(true).open(message_file) {
                    Ok(file) => file,
                    Err(err) => {
                        eprintln!("Error opening message file: {}", err);
                        process::exit(1);
                    }
                };

                let mut message = String::new();
                if let Err(err) = file.read_to_string(&mut message) {
                    eprintln!("Error reading message: {}", err);
                    process::exit(1);
                }

                println!("Received message: {}", message.trim());
            }
            _ => println!("Invalid command"),
        }
    }
}
