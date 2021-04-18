#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
using namespace std;

class Student;

class User {
public:
  enum UserRole {
    STAFF = 1,
    STUDENT = 2
  };

  string user_id;
  string username;
  string password;
  UserRole role;
  Student *pStudent;

  User();
  User(string id);

  string getID();

  static void createUser();
  static bool logIn();
  static void logOut();

  void loadFromStream(std::istream &f);
  void writeToStream(std::ostream &f);
};

istream &operator>>(istream &f, User::UserRole &role);

#endif
