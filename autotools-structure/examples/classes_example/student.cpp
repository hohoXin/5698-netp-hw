/*
 * [2020] Northeastern University - Network Programming
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/


#include "student.h"
#include <sstream>

Student::Student(const std::string& name, 
  const std::string& surname,  
  const std::string& account, 
  unsigned int id) :
m_name{name},
m_surname{surname},
m_account{account},
m_id{id}
{

}

Student::~Student() {
  
}

std::string Student::getName() const 
{
  return m_name;
}

std::string Student::getSurname() const
{
  return m_surname;
}

unsigned int Student::getId() const
{
  return m_id;
}

std::string Student::getAccount() const 
{
  return m_account;
}

void Student::setName(const std::string& name)
{
  this->m_name = name; // it is not necessary to use this
}

void Student::setSurname(const std::string& sn)
{
  m_surname = sn;
}

void Student::setId(unsigned int m_id)
{
  this->m_id = m_id; // it is necessary to use this
  // as the choice of the name of the argument is 
  // unfortunate and shadows that of the member variable
}

void Student::setAccount(const std::string& acc) {
  m_account = acc;
}


std::ostream&
operator<<(std::ostream& out, const Student& p)
{
  out << p.getName() << " " << p.getSurname() << " " 
      << p.getId() << " " << p.getAccount();
  return out;
}
 