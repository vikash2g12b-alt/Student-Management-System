# Student Management System with File Handling in C

A beginner-friendly, menu-driven **Student Management System** developed in C with persistent storage using standard **File Handling**. This project is specifically designed for first-year B.Tech students (Cyber Security / Computer Science) to master core programming fundamentals including:
- **Structures (`struct`)** and **Arrays of Structures**
- **File Handling in C (`fopen`, `fprintf`, `fscanf`, `fclose`)**
- **Data Persistence** across program executions
- **Input Validation & Error Handling** (preventing duplicate keys, range checking, buffer safety)
- **Modular Function Design**

---

## 📌 Features

### Core Management Features
1. **Add Student**:
   - Takes input for Roll Number, Full Name (supports spaces), and Marks.
   - Validates that marks are between `0` and `100`.
   - Prevents duplicate roll numbers.
   - Enforces maximum capacity of `100` students (`MAX_STUDENTS`).
   - Automatically saves all records to `students.txt` upon successful addition.

2. **View All Students**:
   - Displays all loaded student records in a clean, tabular format (`Roll No`, `Name`, `Marks`).
   - Displays a helpful message if no student records exist.
   - Displays the total student count.

3. **Search Student by Roll Number**:
   - Searches for a student by roll number using linear search.
   - Displays student name, roll number, and marks if found.
   - Displays `Student not found.` if the roll number does not match.

4. **Exit Program**:
   - Displays a friendly exit message and terminates safely.

### File Handling & Persistence Features
1. **Automatic Data Loading (`loadStudents`)**:
   - Automatically reads saved records from `students.txt` when the program starts.
   - Restores student records and updates `studentCount`.
   - Handles the case where `students.txt` does not exist on the first run without crashing.
   - Safely parses records and handles malformed or incomplete records without crashing.
   - Validates loaded records against duplicate roll numbers, marks range, and capacity limits.

2. **Automatic Data Saving (`saveStudents`)**:
   - Automatically saves all currently loaded student records to `students.txt` whenever a new student is added.
   - Ensures data safety by writing all current records (not just the new student).
   - Verifies file open and write operations and reports any failures clearly.

---

## 📁 File Storage Details (`students.txt`)

- **File Name**: `students.txt`
- **Location**: In the same directory as the executable.
- **Format**: Pipe-delimited plain text (`<RollNumber>|<Name>|<Marks>`), one record per line.
- **Example content**:
  ```text
  101|Rahul Sharma|85.00
  102|Priya Verma|92.50
  ```

---

## 📚 Understanding File Handling in C

Standard C file I/O functions from `<stdio.h>` are used for persistent storage:

| Function | Purpose in this Project |
| :--- | :--- |
| `fopen()` | Opens a file stream with a specified mode: `"r"` (read mode in `loadStudents`) or `"w"` (write mode in `saveStudents`). Returns a `FILE*` pointer, or `NULL` if opening fails. |
| `fscanf()` | Formatted file input. Reads data from `students.txt` using the format specifier `"%d\|%49[^\|\n]\|%f\n"`. This safely captures names with spaces while isolating delimiters and numbers. |
| `fprintf()` | Formatted file output. Writes student records line-by-line into `students.txt` in the format `"%d\|%s\|%.2f\n"`. |
| `fclose()` | Closes an open file stream, ensuring that all cached buffers are flushed to disk and operating system file handles are released. |

---

## 💻 Prerequisites

- **C Compiler**: GCC (via MinGW / MSYS2 on Windows, or standard GCC on Linux/macOS).
- **Terminal**: PowerShell, Command Prompt, or VS Code integrated terminal.

Verify GCC installation:
```bash
gcc --version
```

---

## 🛠️ Compilation and Execution Instructions

### Step 1: Open Terminal
Navigate to the project folder:
```powershell
cd "d:\New Era\Student Management System"
```

### Step 2: Compile the Program
Compile using `gcc`:
```bash
gcc -Wall -Wextra student_management.c -o student_management
```

### Step 3: Run the Program
- **On Windows**:
  ```powershell
  .\student_management.exe
  ```
- **On Linux / macOS**:
  ```bash
  ./student_management
  ```

---

## 🧪 Sample Usage & Test Cases

### Test Case 1: First Run (File Not Found)
When `students.txt` does not exist yet:
```text
Note: File 'students.txt' not found. Starting with an empty student list.

===== STUDENT MANAGEMENT SYSTEM =====
1. Add Student
2. View All Students
3. Search Student by Roll Number
4. Exit
=====================================
Enter your choice: 
```

### Test Case 2: Adding a Student & Saving
```text
Enter your choice: 1

--- Add New Student ---
Enter Roll Number: 101
Enter Student Name: Rahul Sharma
Enter Marks (0 - 100): 88.50
Success: Student 'Rahul Sharma' (Roll No: 101) added and saved to 'students.txt' successfully!
```
*`students.txt` is created with:*
```text
101|Rahul Sharma|88.50
```

### Test Case 3: Duplicate Roll Number Check
```text
Enter your choice: 1

--- Add New Student ---
Enter Roll Number: 101
Error: A student with Roll Number 101 already exists! Duplicate roll numbers are not allowed.
```

### Test Case 4: Re-opening Program (Data Persistence)
Restart `student_management.exe`:
```text
Successfully loaded 1 student record(s) from 'students.txt'.

===== STUDENT MANAGEMENT SYSTEM =====
1. Add Student
2. View All Students
3. Search Student by Roll Number
4. Exit
=====================================
Enter your choice: 2

--- All Students List ---
------------------------------------------------------------
Roll No    Name                           Marks     
------------------------------------------------------------
101        Rahul Sharma                   88.50     
------------------------------------------------------------
Total Students: 1
```

### Test Case 5: Searching for a Loaded Student
```text
Enter your choice: 3

--- Search Student ---
Enter Roll Number to search: 101

Student Found:
-----------------------------------
Roll Number : 101
Name        : Rahul Sharma
Marks       : 88.50
-----------------------------------
```

### Test Case 6: Handling Malformed Records Safely
If `students.txt` contains invalid lines:
```text
Warning: Malformed record found in 'students.txt'. Skipping invalid line.
Warning: Skipping duplicate Roll No 101 ('Duplicate Roll') found in file.
Warning: Skipping Roll No 104 ('Invalid Marks') due to invalid marks (120.00).
Successfully loaded 2 student record(s) from 'students.txt'.
```

### Test Case 7: File Write Failure (Read-Only Safety)
If the file cannot be opened for writing (e.g., permissions or read-only):
```text
Error: Unable to open file 'students.txt' for saving!
Warning: Student 'Test Student' was added to memory, but could NOT be saved to 'students.txt'!
```

---

## ⚠️ Known Limitations
1. **Fixed Array Capacity**:
   - The system supports up to 100 students (`MAX_STUDENTS 100`). Records beyond 100 are ignored to prevent buffer overflows.
2. **Sequential Linear Search**:
   - Search uses linear search ($O(n)$ time complexity), which is simple and ideal for up to 100 records.
3. **Delimiter Restriction**:
   - The pipe symbol (`|`) is used as a delimiter. Student names cannot contain the `|` character.
