use std::io::{self, prelude::*};
use std::process;

use named_pipe::PipeClient;

fn main() {
    // Read the command-line argument
    let args: Vec<String> = std::env::args().collect();
    if args.len() != 2 {
        eprintln!("Usage: sender <message_file>");
        process::exit(1);
    }
    let message_file = &args[1];

    // Open the signal pipe for communication with the receiver process
    let mut signal_pipe = match PipeClient::connect("\\\\.\\pipe\\signal_pipe") {
        Ok(pipe) => pipe,
        Err(err) => {
            eprintln!("Error connecting to signal pipe: {}", err);
            process::exit(1);
        }
    };

    // Send a signal to the receiver process to indicate readiness
    let signal_buffer = [1u8];
    match signal_pipe.write_all(&signal_buffer) {
        Ok(_) => println!("Signal sent to Receiver process"),
        Err(err) => {
            eprintln!("Error sending signal: {}", err);
            process::exit(1);
        }
    }

    // Read user input and perform actions
    loop {
        println!("Enter 'send' to send a message or 'exit' to quit:");
        let mut input = String::new();
        io::stdin()
            .read_line(&mut input)
            .expect("Failed to read input");

        match input.trim() {
            "exit" => break,
            "send" => {
                // Read the message from the user
                let mut message = String::new();
                println!("Enter the message to send:");
                io::stdin()
                    .read_line(&mut message)
                    .expect("Failed to read input");

                // Truncate the message to a maximum length of 20 characters
                message = message.trim().chars().take(20).collect();

                // Open the message file and write the message
                let mut file = match std::fs::OpenOptions::new().append(true).open(message_file) {
                    Ok(file) => file,
                    Err(err) => {
                        eprintln!("Error opening message file: {}", err);
                        process::exit(1);
                    }
                };
                if let Err(err) = writeln!(file, "{}", message) {
                    eprintln!("Error writing message: {}", err);
                    process::exit(1);
                }
                println!("Message sent");
            }
            _ => println!("Invalid command"),
        }
    }
}
