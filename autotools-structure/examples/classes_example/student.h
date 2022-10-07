/*
 * [2020] Northeastern University - Network Programming
 * [2019] Signet Lab - Programming for ICT
 * All Rights Reserved.
 * 
 * Authors Filippo Campagnaro and Michele Polese 
*/


#ifndef H_STUDENT
#define H_STUDENT

#include <string>


/**
 * The C++ class Student 
 */
class Student {

public: 
  /**
   * Constructor for a Student object
   * It is explicit to avoid unwanted implicit conversions
   * @param name_ string with the name of the student
   * @param surname_ string with the surname of the student
   * @param account_ string with the dei account
   * @param id_ unique identifier
   */
  Student(const std::string& name, const std::string& surname,  
  	const std::string& account, unsigned int id);

  ~Student();

  /**
   * Get the student name
   * @return a string with the student name
   */
  std::string getName() const;

  /**
   * Get the student name
   * @return a string with the student name
   */
  std::string getSurname() const;

  /**
   * Get the student id
   * @return the student age, in years
   */
  unsigned int getId() const;

  /**
   * Get the student account
   * @return a string with the student account
   */
  std::string getAccount() const;

  /**
   * Set the name
   * @param name string with the name
   */
  void setName(const std::string& name);

  /**
   * Set the surname
   * @param sn string with the surname
   */
  void setSurname(const std::string& sn);

  /**
   * Set the student id
   * @param id the user id
   */
  void setId(unsigned int id);

  /**
   * Set the account
   * @param acc string with the nationality
   */
  void setAccount(const std::string& acc);

private: // private members
  std::string m_name; /**<name of the student*/
  std::string m_surname; /**<surname of the student*/
  std::string m_account; /**<dei account of the student*/
  unsigned int m_id; /**<id of the student*/
};

/**
 * Overload operator<< for the class Student
 * @param out the ostream object
 * @param p the student to print
 * @return a reference to the ostream
 */
std::ostream& operator<<(std::ostream& out, const Student& p);

#endif // H_COURSE
