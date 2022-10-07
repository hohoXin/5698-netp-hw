/*
 * [2020] Northeastern University - Network Programming
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <iostream>
#include "course.h"

int
main(int argc, char const *argv[])
{
  School::Course::setDefaultRoom("420");
  School::Course ptlc{"Michele"};

  // let's check that there are no students
  std::cout << "Number of students = " 
    << ptlc.getNumberOfStudents() << std::endl;
  // let's try to get the teacher name
  std::cout << "Teacher name = "
    << ptlc.getTeacherName() << std::endl;

  // add students
  ptlc.addStudent({"John","Smith", "smith1", 12355});
  // less efficient way (no need to create the student as lvalue)
  Student student1 {"Jane", "Doe", "doe1", 12375};
  ptlc.addStudent(student1);

  std::cout << "The students are " << ptlc.studentsToString() 
    << std::endl;
  // redefine operator
  School::StudentList new_students {
    {"James", "Doe", "doe1", 12375},
    {"Johnny", "Doe", "doe2", 12375}
  };
  ptlc.addMultipleStudents(new_students);

  std::cout << "The students are " << ptlc.studentsToString() 
    << std::endl;
    
  // create a const class and show that modifiers do not work
  const School::Course ptlc_const{ptlc};

  // this does not compile!
  // ptlc_const.setTeacherName{"someone else"};
  // ptlc_const.addMultipleStudents(new_students);
  // this works, because the function is marked as const
  std::cout << "The students in ptlc_const are " << ptlc_const.studentsToString() 
    << std::endl;

  // with the following calls, we exploit the fact that addStudent
  // returns a self reference to the object on which it was called
  // we can chain multiple calls to addStudent
  

  Student student3 {"Pierre", "Curie", "pcurie", 17775};
  ptlc.addStudent(student3).addStudent(Student{"Peter", "Parker", "parke1", 17775}
  	).addStudent({"Marie", "Curie", "mcurie", 17775});
  std::cout << "The students are (after the multiple calls using self-reference) " 
    << ptlc.studentsToString() << std::endl;

  return 0;
}
