#include "Student.h"
#include "Global.h"
#include <iostream>
using namespace std;
void Student::createStudent()
{
  Student *student = new Student;
  cout << "Input student ID:";
  cin >> student->student_id;
  cout << "Input student first name:";
  cin >> student->firstName;
  cout << "Input student last name:";
  cin >> student->lastName;
  cout << "Input student date of birth";
  cin >> student->dateOfBirth;
  cout << "Input student gender:";
  cin >> student->gender;
  cout << "Input student social ID:";
  cin >> student->socialID;
  cout << "Input student class ID";
  string stuClass;
  cin >> stuClass;
  for (int i = 0; i < Global::all_class.size(); i++)
    if (Global::all_class[i]->class_id == stuClass)
    {
      Global::all_class[i]->pStudents.push_back(student);
      student->pClass = Global::all_class[i];
      Global::all_class[i]->numberOfStudent++;
      break;
    }
  cout << "How many course that student enrolled:";
  cin >> student->numberOfEnrolledCourse;
  for (int i = 0; i < student->numberOfEnrolledCourse; i++)
  {
    cout << "Input the " << i << " enrolled course ID:";
    string enrolledCourse;
    cin >> enrolledCourse;
    for (int j = 0; j < Global::all_course.size(); i++)
      if (Global::all_course[i]->course_id == enrolledCourse)
      {
        Global::all_course[i]->numberOfStudent++;
        if (Global::all_course[i]->numberOfStudent <= Global::all_course[i]->maxNumberOfStudent && Course::checkConflict(Global::all_course[i], student->pEnrolledCourses))
        {
          Global::all_course[i]->pStudents.push_back(student);
          student->pEnrolledCourses.push_back(Global::all_course[i]);
        }
        else
        {
          cout << "Cannot enroll due to full slot or time conflict";
          Global::all_course[i]->numberOfStudent--;
        }
        break;
      }
  }
  Global::all_student.push_back(student);
}
void Student::showStudent()
{
for (int i = 0; i < Global::all_student.size(); i++)
    {
        cout << "Student ID:  "<<Global::all_student[i]->student_id;
        cout << "First name:  "<<Global::all_student[i]->firstName;
        cout << "Last name:  "<<Global::all_student[i]->lastName;
        cout << "Gender:  "<<Global::all_student[i]->gender;
        cout << "Date of birth:  "<<Global::all_student[i]->dateOfBirth;
        cout << "SocialID:  "<<Global::all_student[i]->socialID<<endl;
    }
}