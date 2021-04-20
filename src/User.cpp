#include "Global.h"

User::User() {}
User::User(string id) : user_id(id) {}

string User::getID() {
  return user_id;
}

string User::genUserID() {
  std::stringstream ss;
  ss << std::setw(6) << std::setfill('0') << (all_user.size() + 1);
  return ss.str();
}

void User::createStaffUser() {
  throw "Not implemented yet!";
}

User *User::createStudentUser(const string &username, const string &password, Student *st) {
  User *u = new User();
  u->user_id = genUserID();
  u->username = username;
  u->password = password;
  u->role = UserRole::STUDENT;
  u->pStudent = st;
  all_user.push_back(u);
  return u;
}

void User::loadFromStream(std::istream &f) {
  string _user_id;
  getline(f, _user_id);
  assert(_user_id == user_id);

  getline(f, username);
  getline(f, password);
  f >> role;
  f.ignore();

  if (role == UserRole::STUDENT) {
    string student_id;
    getline(f, student_id);
    pStudent = nullptr;
    for (auto st : all_student) {
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
