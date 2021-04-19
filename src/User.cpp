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
  throw "Not implemented yet!";
}

void User::writeToStream(std::ostream &f) {
  throw "Not implemented yet!";
}
