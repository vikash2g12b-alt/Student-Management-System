#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LENGTH 50
#define FILE_NAME "students.txt"

// Structure to store student details
struct Student {
    char name[NAME_LENGTH];
    int rollNumber;
    float marks;
};

// Function prototypes
void addStudent(struct Student students[], int *count);
void viewStudents(const struct Student students[], int count);
void searchStudent(const struct Student students[], int count);
void loadStudents(struct Student students[], int *count);
int saveStudents(const struct Student students[], int count);
void clearInputBuffer(void);

int main(void) {
    // Array of structures to store student records in memory
    struct Student students[MAX_STUDENTS];
    int studentCount = 0;
    int choice = 0;

    // Load existing student records from file at startup
    loadStudents(students, &studentCount);

    do {
        // Display Menu
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student by Roll Number\n");
        printf("4. Exit\n");
        printf("=====================================\n");
        printf("Enter your choice: ");

        // Read choice and handle invalid non-integer inputs
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a valid number (1-4).\n");
            clearInputBuffer();
            continue;
        }

        // Handle menu options
        switch (choice) {
            case 1:
                addStudent(students, &studentCount);
                break;
            case 2:
                viewStudents(students, studentCount);
                break;
            case 3:
                searchStudent(students, studentCount);
                break;
            case 4:
                printf("\nThank you for using the Student Management System. Goodbye!\n");
                break;
            default:
                printf("\nInvalid choice! Please select an option between 1 and 4.\n");
                break;
        }
    } while (choice != 4);

    return 0;
}

// Function to clear standard input buffer (handles leftover newline or invalid chars)
void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        // Discard characters until newline or end-of-file
    }
}

// Function to load student records from students.txt into memory
void loadStudents(struct Student students[], int *count) {
    *count = 0;

    // Open file in read mode
    FILE *file = fopen(FILE_NAME, "r");
    if (file == NULL) {
        // If file does not exist (e.g. first run), start with empty list safely
        printf("Note: File '%s' not found. Starting with an empty student list.\n", FILE_NAME);
        return;
    }

    int roll;
    char name[NAME_LENGTH];
    float marks;

    // Read records while within maximum capacity
    while (*count < MAX_STUDENTS) {
        // Parse format: RollNumber|Name|Marks
        // %49[^|\n] reads student name with spaces while stopping at '|' or newline
        int matched = fscanf(file, "%d|%49[^|\n]|%f\n", &roll, name, &marks);
        if (matched == EOF) {
            break;
        }

        if (matched == 3) {
            // Validate marks range (0 to 100)
            if (marks < 0.0f || marks > 100.0f) {
                printf("Warning: Skipping Roll No %d ('%s') due to invalid marks (%.2f).\n", roll, name, marks);
                continue;
            }

            // Check for duplicate roll numbers already loaded
            int isDuplicate = 0;
            for (int i = 0; i < *count; i++) {
                if (students[i].rollNumber == roll) {
                    isDuplicate = 1;
                    break;
                }
            }
            if (isDuplicate) {
                printf("Warning: Skipping duplicate Roll No %d ('%s') found in file.\n", roll, name);
                continue;
            }

            // Store validated record into array
            students[*count].rollNumber = roll;
            strncpy(students[*count].name, name, NAME_LENGTH - 1);
            students[*count].name[NAME_LENGTH - 1] = '\0';
            students[*count].marks = marks;
            (*count)++;
        } else {
            // Malformed or incomplete record: skip invalid line safely
            printf("Warning: Malformed record found in '%s'. Skipping invalid line.\n", FILE_NAME);
            int ch;
            while ((ch = fgetc(file)) != '\n' && ch != EOF) {
                // Discard characters until end of line
            }
        }
    }

    // Check if additional records exist beyond MAX_STUDENTS
    if (*count >= MAX_STUDENTS) {
        int ch = fgetc(file);
        if (ch != EOF) {
            printf("Warning: Maximum capacity (%d) reached. Remaining records in file were not loaded.\n", MAX_STUDENTS);
        }
    }

    // Safely close the file
    fclose(file);

    if (*count > 0) {
        printf("Successfully loaded %d student record(s) from '%s'.\n", *count, FILE_NAME);
    }
}

// Function to save all student records from memory to students.txt
int saveStudents(const struct Student students[], int count) {
    // Open file in write mode ("w" creates or overwrites with current full list)
    FILE *file = fopen(FILE_NAME, "w");
    if (file == NULL) {
        printf("\nError: Unable to open file '%s' for saving!\n", FILE_NAME);
        return 0; // Indicate failure
    }

    // Write every student record to file
    for (int i = 0; i < count; i++) {
        if (fprintf(file, "%d|%s|%.2f\n", students[i].rollNumber, students[i].name, students[i].marks) < 0) {
            printf("\nError: Failed to write data for student '%s' (Roll No: %d) to file!\n", 
                   students[i].name, students[i].rollNumber);
            fclose(file);
            return 0; // Indicate failure
        }
    }

    // Safely close the file and check for close error
    if (fclose(file) != 0) {
        printf("\nError: Failed to close file '%s' properly after saving!\n", FILE_NAME);
        return 0; // Indicate failure
    }

    return 1; // Indicate success
}

// 1. Add Student
void addStudent(struct Student students[], int *count) {
    // Check if the system has reached maximum capacity
    if (*count >= MAX_STUDENTS) {
        printf("\nError: Maximum capacity reached (%d students). Cannot add more students.\n", MAX_STUDENTS);
        return;
    }

    int rollNo;
    printf("\n--- Add New Student ---\n");
    printf("Enter Roll Number: ");
    if (scanf("%d", &rollNo) != 1) {
        printf("Error: Invalid roll number! Roll number must be an integer.\n");
        clearInputBuffer();
        return;
    }

    // Check for duplicate roll number
    for (int i = 0; i < *count; i++) {
        if (students[i].rollNumber == rollNo) {
            printf("Error: A student with Roll Number %d already exists! Duplicate roll numbers are not allowed.\n", rollNo);
            return;
        }
    }

    // Assign validated roll number
    students[*count].rollNumber = rollNo;

    // Read student name (allows spaces, e.g., "Rahul Sharma")
    printf("Enter Student Name: ");
    scanf(" %49[^\n]", students[*count].name);

    // Read marks and validate range (0 to 100)
    printf("Enter Marks (0 - 100): ");
    if (scanf("%f", &students[*count].marks) != 1) {
        printf("Error: Invalid marks format! Please enter a valid numeric value.\n");
        clearInputBuffer();
        return;
    }

    if (students[*count].marks < 0.0f || students[*count].marks > 100.0f) {
        printf("Error: Marks must be between 0 and 100. Student was not added.\n");
        return;
    }

    // Increment student count in memory
    (*count)++;

    // Automatically save all student records to file
    if (saveStudents(students, *count)) {
        printf("Success: Student '%s' (Roll No: %d) added and saved to '%s' successfully!\n", 
               students[*count - 1].name, students[*count - 1].rollNumber, FILE_NAME);
    } else {
        printf("Warning: Student '%s' was added to memory, but could NOT be saved to '%s'!\n", 
               students[*count - 1].name, FILE_NAME);
    }
}

// 2. View All Students
void viewStudents(const struct Student students[], int count) {
    printf("\n--- All Students List ---\n");

    // Display message if no students exist
    if (count == 0) {
        printf("No students found. Please add a student first.\n");
        return;
    }

    // Display formatted table header
    printf("------------------------------------------------------------\n");
    printf("%-10s %-30s %-10s\n", "Roll No", "Name", "Marks");
    printf("------------------------------------------------------------\n");

    // Print each student record
    for (int i = 0; i < count; i++) {
        printf("%-10d %-30s %-10.2f\n", 
               students[i].rollNumber, 
               students[i].name, 
               students[i].marks);
    }

    printf("------------------------------------------------------------\n");
    printf("Total Students: %d\n", count);
}

// 3. Search Student by Roll Number
void searchStudent(const struct Student students[], int count) {
    printf("\n--- Search Student ---\n");

    if (count == 0) {
        printf("No students found in the system to search.\n");
        return;
    }

    int searchRoll;
    printf("Enter Roll Number to search: ");
    if (scanf("%d", &searchRoll) != 1) {
        printf("Error: Invalid roll number input.\n");
        clearInputBuffer();
        return;
    }

    // Linear search for the roll number
    int foundIndex = -1;
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == searchRoll) {
            foundIndex = i;
            break;
        }
    }

    // Display result
    if (foundIndex != -1) {
        printf("\nStudent Found:\n");
        printf("-----------------------------------\n");
        printf("Roll Number : %d\n", students[foundIndex].rollNumber);
        printf("Name        : %s\n", students[foundIndex].name);
        printf("Marks       : %.2f\n", students[foundIndex].marks);
        printf("-----------------------------------\n");
    } else {
        printf("Student not found.\n");
    }
}
