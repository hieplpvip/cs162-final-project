#include "Global.h"

User::User() {}
User::User(string id) : user_id(id) {}

string User::getID() {
  return user_id;
}

void User::createUser() {
  throw "Not implemented yet!";
}

bool User::logIn() {
  throw "Not implemented yet!";
}

void User::logOut() {
  throw "Not implemented yet!";
}

void User::loadFromStream(std::istream &f) {
  string _user_id;
  f >> _user_id;
  f >> username;
  f >> password;
  f >> role;
  assert(_user_id == user_id);

  if (role == UserRole::STUDENT) {
    string student_id;
    f >> student_id;
    pStudent = nullptr;
    for (auto p : Global::all_student) {
      if (p->student_id == student_id) {
        pStudent = p;
      }
    }
    if (pStudent == nullptr) {
      std::cerr << "[ERROR][User::loadFromStream]: Could not find matching pStudent\n";
    }
  }
}

void User::writeToStream(std::ostream &f) {
  f << user_id << '\n';
  f << username << '\n';
  f << password << '\n';
  f << role << '\n';

  if (role == UserRole::STUDENT) {
    f << role << '\n';
  }
}

istream &operator>>(istream &f, User::UserRole &role) {
  int _role;
  f >> _role;
  role = static_cast<User::UserRole>(_role);
  return f;
}
