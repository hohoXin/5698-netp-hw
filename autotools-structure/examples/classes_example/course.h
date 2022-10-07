/*
 * [2020] Northeastern University - Network Programming
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#ifndef H_COURSE
#define H_COURSE

#include <vector>
#include <string>
#include "student.h"

/**
 * The namespace School defines useful names to handle 
 * stuff at a school or university
 */
namespace School
{

using StudentList = std::vector<Student>;

/**
 * The C++ class Course is a user-defined type to represent 
 * a course
 */
class Course {

public: // public interface
	/**
	 * Constructor for a Course object
	 * It is explicit to avoid unwanted implicit conversions
	 * @param a string to represent the teacher for the class, with default empty string
	 */
	explicit Course(const std::string& teacher = "");

	// non-modifying members to inspect a class
	/**
	 * Get the number of students
	 * @return the number of registered students
	 */
	int getNumberOfStudents() const;

	/**
	 * Get the list of students
	 * @return a vector with the students names
	 */
	// using auto is totally unnecessary (do not do it), just to show you it can be done
	auto getStudentNames() const -> StudentList;

	/**
	 * Get the teacher name
	 * @return a string with the teacher name
	 */
	std::string getTeacherName() const;

	/**
	 * Set the teacher name
	 * @param a string with the teacher name
	 */
	void setTeacherName(const std::string& teacher);

	/**
	 * Get the list of students as a string
	 * @return the list of students as a string, with comma-separated values
	 */
	std::string studentsToString() const;

	// modifying functions to change the course
	/**
	 * Add a student
	 * @param a student
	 * @return a reference to the Course object
	 */
	Course& addStudent(const Student& studentName);

	/**
	 * Add multiple students
	 * @param a vector of string with the students' names
	 * @return a reference to the Course object
	 */
	Course& addMultipleStudents(const StudentList& newStudentsNames);

	/**
	 * Set the default room for the class
	 * @param a string with the room name
	 */
	static void setDefaultRoom(const std::string& room);

private: // private members
	/**
	 * Update the string representation of this class
	 */
	void updateCache() const;

	StudentList m_studentNames; /**<names of the students */
	std::string m_teacher {"Michele"}; /**<teacher of the course */
	std::string m_room; /**<room of the course */

	// these members are declared mutable so that 
	// they can be updated even in const functions
	// this can be logically done because they do not
	// represent the status of the object, but just a 
	// property (a cache) that depends on the actual status
	mutable bool m_is_valid; /**<valid cache flag */
	mutable std::string m_students_string_cache; /**<string with names of students */

	// static member
	// let's assume all the computer labs take place - by default - 
	// in a certain room of the department
	// it makes sense to create a default which is the same
	// for all the objects of this class
	static std::string default_room; /**<default room */
};


}; // end of namespace School

#endif // H_COURSE
