# Course Registration System

### At the beginning of a school year, an academic staff member will:

- [] Create a new school year (e.g. `2020-2021`)
- [] Create classes for freshmen (e.g. `20CTT1`, `20CTT2`)
- [] Add freshmen to created classes (Student ID, First name, Last name, Gender, Date of Birth, Social ID)
- [] Import students information from CSV instead of manual input

### At the beginning of a semester, an academic staff member will:

- [] Create a new semester. There are 3 semesters in a school year: 1 (Fall), 2 (Summer), 3 (Autumn). The newly-created semester will be the default semester for all actions below.
- [] Create a course registration session
- [] Add a course: course id, course name, teacher name, number of credits, maximum number of students in that course (default 50), sessions (MON / TUE / WED / THU / FRI / SAT, S1 (07:30), S2 (09:30), S3(13:30), S4 (15:30))
- [] Update course information
- [] Delete a course

### When a course registration session is active, a student can:

- [] Enroll in a course. If that course conflicts with enrolled courses, he/she can not enroll in it. He/she can enroll in at most 5 courses in a semester.
- [] Un-enroll from a course from
- [] View enrolled courses

### When a course registration session is close, a student still can:

- []View list of his/her courses. He/she will study these courses in this semester.

### At any time, an academic staff member can:

- [] View list of classes
- [] View list of students in a class
- [] View list of courses
- [] View list of students in a course

### At the end of a semester, an academic staff member can:

- [] Export list of students in a course to a CSV file
- [] Import the scoreboard of a course. A scoreboard must have the following columns: Student ID, Full Name, Total Mark, Final Mark, Midterm Mark, Other Mark. An academic staff member will export the list of students in a course, send the CSV file to the teacher, the teacher will enter student results in this file, send it back to the staff, and the staff will import the scoreboard to the system.
- [] View the scoreboard of a course
- [] Update a student's score
- [] View the scoreboard of a class, (including final marks of all courses in the semester, GPA in this semester, and the overall GPA)

### When the scoreboard has been published by a staff member, a student can:

- [] View his/her scoreboard

## Technical requirements

1. Written in C++.
2. Only text files or binary files are allowed. Database is not allowed.
3. Only dynamic arrays or linked lists are allowed.
4. `char[]`, `char*`, and `string` are allowed.
5. Use Github to manage your source code. Each member must have at least 20 commits spreading across at least 15 days.
