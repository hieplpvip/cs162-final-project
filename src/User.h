#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using std::string;

class Student;

class User {
public:
  enum UserRole {
    STAFF,
    STUDENT
  };

  string user_id;
  string username;
  string password;
  UserRole role;
  Student *pStudent;

  User();
  User(string id);

  static void createUser();
  static bool logIn();
  static void logOut();

  static User *loadFromStream(std::istream &f);
  void writeToStream(std::ostream &f);
};

#endif
