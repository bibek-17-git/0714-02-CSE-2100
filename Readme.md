💾 Smart Backup Utility

A modular C-based file backup system built for Advanced Programming Laboratory.
Designed using clean project structure, header abstraction, and Makefile automation.

📌 Overview

Smart Backup Utility is a command-line based backup management system written in C.
It allows users to configure and perform file/directory backups in a structured and maintainable way.

This project demonstrates:

Modular Programming in C

Multi-file project organization

Header file abstraction

Makefile automation

Clean coding style for GitHub projects

📂 Project Structure
smart-backup-utility/
│
├── src/
│   ├── main.c
│   ├── ui.c
│   ├── backup.c
│
├── include/
│   ├── ui.h
│   ├── backup.h
│   └── config.h
│
├── Makefile
├── README.md
├── .gitignore
└── backup_config.txt

🚀 Features

✔ Modular multi-file C project
✔ Separate UI and backup logic
✔ Configurable backup system
✔ Clean folder structure (src/ and include/)
✔ Makefile build automation
✔ Easy to extend

🛠 Technologies Used

C Programming Language

GCC Compiler

GNU Make

Linux / WSL / MinGW environment

⚙️ Build Instructions

Make sure GCC and Make are installed.

🔹 Compile the project

From project root directory:

make


This will generate the executable:

smart-backup-utility

▶️ Run the Program
./smart-backup-utility

🧹 Clean Build Files

To remove object files and executable:

make clean

📄 Configuration

The file backup_config.txt stores backup settings such as:

Source directory

Destination directory

Backup preferences

Edit this file before running the program if needed.

🧠 Module Description
🔹 main.c

Entry point of the program

Initializes the system

Connects UI and backup modules

🔹 ui.c / ui.h

Handles user interaction

Displays menus

Takes user input

🔹 backup.c / backup.h

Core backup logic

File copy operations

Directory processing

🔹 config.h

Macro definitions

Global constants

Configuration declarations

🎯 Learning Outcomes

This project demonstrates:

Multi-file C programming

Header file usage and abstraction

Proper GitHub project organization

Use of Makefile in real projects

Clean coding practices

🔮 Future Improvements

Add timestamp-based automatic backup

Add restore functionality

Add log file system

Add compression (ZIP support)

Add GTK GUI version

📸 Example (Optional)

You may add screenshots here later if you create a GUI version.

👨‍💻 Author

Course: Advanced Programming Laboratory
Project: Smart Backup Utility

📜 License

This project is developed for academic purposes.
