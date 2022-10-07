/*
 * [2020] Northeastern University - Network Programming
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/

#include <sstream>
#include "course.h"

namespace School {

std::string Course::default_room {""};

Course::Course(const std::string& teacher)
	:   m_studentNames{}, 
		m_teacher{teacher},
		m_room{default_room},
		m_is_valid{},
		m_students_string_cache{""}
{

}

int
Course::getNumberOfStudents() const
{
	return m_studentNames.size();
}

StudentList
Course::getStudentNames() const
{
	return m_studentNames;
}

std::string 
Course::getTeacherName() const
{
	return m_teacher;
}

void
Course::setTeacherName(const std::string& teacher)
{
	m_teacher = teacher;
}

Course&
Course::addStudent(const Student& student)
{
	m_studentNames.push_back(student);
	m_is_valid = false;
	return *this;
}

Course&
Course::addMultipleStudents(const StudentList& student)
{
	m_studentNames.insert(
		std::end(m_studentNames), std::begin(student), std::end(student));
	m_is_valid = false;
	return *this;
}

std::string
Course::studentsToString() const
{
	if(m_is_valid)
	{
		return m_students_string_cache;
	}

	// this code is not executed if the cache is valid
	updateCache();
	return m_students_string_cache;
}

void
Course::setDefaultRoom(const std::string& room)
{
	default_room = room;
}

void 
Course::updateCache() const
{
	// this is an example on how to use stringstreams
	// to concatenate strings
	std::stringstream ss {};
	for(auto student : m_studentNames)
	{
		ss << student << ", ";
	}

	m_students_string_cache = ss.str();
	m_is_valid = true;
}

}
