#ifndef USER_H
#define USER_H

#include <string>
using std::string;

class Student;

class User {
public:
  enum UserRole {
    STAFF,
    STUDENT
  };

  int user_id;
  string username;
  string password;
  UserRole role;
  Student* pStudent;

  static User* createUser(const string &username, const string &password, const UserRole role);

  bool logIn(const string &username, const string &password);
  bool logOut();
};

#endif
