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
  getline(f, _user_id);
  assert(_user_id == user_id);

  getline(f, username);
  getline(f, password);
  f >> role;

  if (role == UserRole::STUDENT) {
    string student_id;
    getline(f, student_id);
    pStudent = nullptr;
    for (auto st : Global::all_student) {
      if (st->student_id == student_id) {
        pStudent = st;
        break;
      }
    }
    assert(pStudent != nullptr);
  }
}

void User::writeToStream(std::ostream &f) {
  f << user_id << '\n';
  f << username << '\n';
  f << password << '\n';
  f << role << '\n';

  if (role == UserRole::STUDENT) {
    f << pStudent->student_id << '\n';
  }
}

istream &operator>>(istream &f, User::UserRole &role) {
  int _role;
  f >> _role;
  role = static_cast<User::UserRole>(_role);
  return f;
}
