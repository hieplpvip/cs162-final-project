#include "Class.h"
#include "Global.h"
#include <iostream>
using namespace std;
void Class::createClass()
{
  Class *cls;
  cout << "Input class id:";
  cin >> cls->class_id;
  cout << "Input class name:";
  cin >> cls->class_name;
  Global::all_class.push_back(cls);
}
