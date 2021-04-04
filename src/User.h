#ifndef USER_H
#define USER_H

#include <string>
using std::string;

enum UserRole {
	STAFF,
	STUDENT
};

class User {
public:
  int user_id;
  string username;
  string password;
  UserRole role;

  static User createAccount(const string &username, const string &password);

  bool logIn(const string &username, const string &password);
  bool logOut();
};

#endif
