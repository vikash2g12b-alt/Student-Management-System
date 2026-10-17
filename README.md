# Student Management System in C

A beginner-friendly, menu-driven Student Management System built using C. This project demonstrates core programming concepts such as structures, arrays, modular functions, input validation, and file handling.

Student records are stored in a text file so that data can be loaded again when the program restarts.

## Features

### 1. Add Student
- Add a student's roll number, full name, and marks.
- Supports names containing spaces.
- Validates marks between `0` and `100`.
- Prevents duplicate roll numbers.
- Supports a maximum of 100 students.
- Saves records to `students.txt`.

### 2. View All Students
- Displays all student records in a tabular format.
- Shows the total number of students.
- Displays a message when no records are available.

### 3. Search Student
- Searches for a student using their roll number.
- Displays the student's details when a match is found.
- Displays a message if the student does not exist.

### 4. File Handling
- Loads saved records when the program starts.
- Saves all current records when a student is added.
- Handles a missing data file on the first run.
- Validates loaded records and reports file errors.

## Technologies Used

- **Language:** C
- **Concepts:** Structures, arrays, functions, loops, conditional statements
- **File Handling:** `fopen()`, `fscanf()`, `fprintf()`, `fclose()`
- **Compiler:** GCC

## Project Structure

```text
Student-Management-System/
├── student_management.c
├── students.txt
└── README.md
```

`student_management.exe` may be generated locally when you compile the program. You do not need to commit the executable to GitHub.

## Requirements

- GCC compiler
- VS Code or another code editor
- Terminal or command prompt

Check whether GCC is installed:

```bash
gcc --version
```

## Installation and Execution

### Step 1: Clone the Repository

```bash
git clone https://github.com/vikash2g12b-alt/Student-Management-System.git
cd Student-Management-System
```

### Step 2: Compile the Program

```bash
gcc -Wall -Wextra student_management.c -o student_management
```

### Step 3: Run the Program

**Windows PowerShell:**

```powershell
.\student_management.exe
```

**Linux:**

```bash
./student_management
```

If compilation reports errors, check the compiler output before running the program.

## Data Storage

Student records are stored in `students.txt` using a pipe-delimited format:

```text
101|Rahul Sharma|88.50
102|Priya Verma|92.50
```

Each record contains:

- Roll number
- Student name
- Marks

The program reads these records at startup and saves updated records when a student is added.

**Note:** Use sample data only. Do not commit real students' personal information to a public repository.

## Testing Checklist

Test these scenarios before using the program:

- [ ] Add a new student.
- [ ] View all students.
- [ ] Search for an existing roll number.
- [ ] Search for a nonexistent roll number.
- [ ] Try adding a duplicate roll number.
- [ ] Try marks below `0` or above `100`.
- [ ] Restart the program and check whether records persist.
- [ ] Test the program when `students.txt` does not exist.
- [ ] Test the maximum student capacity.

## Concepts Learned

- Structures and arrays of structures
- Modular function design
- File handling in C
- Data persistence
- Input validation and error handling
- Linear search
- Basic debugging and testing

## Limitations

- Maximum capacity is 100 students.
- Student search uses linear search, with `O(n)` time complexity.
- Student names cannot contain the pipe character (`|`) because it is used as a field separator.
- Records are stored in a plain-text file rather than a database.

## Future Improvements

- Update student details.
- Delete student records.
- Sort students by marks or roll number.
- Replace fixed-size arrays with dynamic memory allocation.
- Add a database such as SQLite.

## Author

Created as a beginner C programming project to practise programming fundamentals and file handling.
