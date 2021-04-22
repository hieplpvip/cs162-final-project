# Course Registration System

### At the beginning of a school year, an academic staff member will:

- [x] Create a new school year (e.g. `2020-2021`)
- [x] Create classes for freshmen (e.g. `20CTT1`, `20CTT2`)
- [x] Add freshmen to created classes (Student ID, First name, Last name, Gender, Date of Birth, Social ID)
- [x] Import students information from CSV instead of manual input

### At the beginning of a semester, an academic staff member will:

- [x] Create a new semester. There are 3 semesters in a school year: 1 (Fall), 2 (Spring), 3 (Summer). The newly-created semester will be the default semester for all actions below.
- [x] Create a course registration session
- [x] Add a course: course id, course name, teacher name, number of credits, maximum number of students in that course (default 50), sessions (MON / TUE / WED / THU / FRI / SAT, S1 (07:30), S2 (09:30), S3(13:30), S4 (15:30))
- [x] Update course information
- [x] Delete a course

### When a course registration session is active, a student can:

- [x] Enroll in a course. If that course conflicts with enrolled courses, he/she can not enroll in it. He/she can enroll in at most 5 courses in a semester.
- [x] Un-enroll from a course from
- [x] View enrolled courses

### When a course registration session is close, a student still can:

- [ ] View list of his/her courses. He/she will study these courses in this semester.

### At any time, an academic staff member can:

- [x] View list of classes
- [x] View list of students in a class
- [x] View list of courses
- [x] View list of students in a course

### At the end of a semester, an academic staff member can:

- [x] Export list of students in a course to a CSV file
- [ ] Import the scoreboard of a course. A scoreboard must have the following columns: Student ID, Full Name, Midterm Mark, Final Mark, Other Mark, Total Mark. An academic staff member will export the list of students in a course, send the CSV file to the teacher, the teacher will enter student results in this file, send it back to the staff, and the staff will import the scoreboard to the system.
- [x] View the scoreboard of a course
- [ ] Update a student's score
- [ ] View the scoreboard of a class, (including final marks of all courses in the semester, GPA in this semester, and the overall GPA)

### When the scoreboard has been published by a staff member, a student can:

- [ ] View his/her scoreboard

## Technical requirements

1. Written in C++.
2. Only text files or binary files are allowed. Database is not allowed.
3. Only dynamic arrays or linked lists are allowed.
4. `char[]`, `char*`, and `string` are allowed.
5. Use Github to manage your source code. Each member must have at least 20 commits spreading across at least 15 days.
