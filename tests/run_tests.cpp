#include <cassert>
#include <iostream>
#include <string>
#include "../src/libs/CSVParser.h"
#include "../src/libs/Vector.h"

using namespace std;

int main() {
  // Test Vector
  {
    Vector<int> values;
    for (int i = 0; i < 100; ++i) {
      values.push_back(i);
      assert(values.size() == i + 1);
    }

    for (int i = 0; i < 100; ++i) {
      assert(values[i] == i);
    }

    for (int i = 99; i >= 0; --i) {
      assert(values.back() == i);
      values.pop_back();
    }

    for (int i = 0; i < 100; ++i) {
      values.push_back(i);
    }
    values.erase(50);
    assert(values.size() == 99);

    for (int i = 50; i < 99; ++i) {
      assert(values[i] == i + 1);
    }

    values.clear();
    assert(values.empty());

    // copy constructor
    Vector<int> A(1, 1), B = A;
    B[0] = 2;
    assert(A[0] == 1);
    assert(B[0] == 2);

    cout << "Vector passed\n";
  }

  // Test CSVParser
  {
    Vector<string> values;
    string line = "\"Joan \"\"the bone\"\", Anne\",Jet,\"9th, at Terrace plc\",Desert City,CO,00123";
    assert(CSVParser::parseLine(line, values) == CSVParser::ParseError::Success);
    assert(values.size() == 6);
    assert(values[0] == "Joan \"the bone\", Anne");
    assert(values[1] == "Jet");
    assert(values[2] == "9th, at Terrace plc");
    assert(values[3] == "Desert City");
    assert(values[4] == "CO");
    assert(values[5] == "00123");

    string line2 = CSVParser::writeLine(values);
    assert(line2 == line);

    string fields[6];
    assert(CSVParser::parseLineToArgs(line,
                                      fields[0],
                                      fields[1],
                                      fields[2],
                                      fields[3],
                                      fields[4],
                                      fields[5]) == CSVParser::ParseError::Success);
    assert(fields[0] == "Joan \"the bone\", Anne");
    assert(fields[1] == "Jet");
    assert(fields[2] == "9th, at Terrace plc");
    assert(fields[3] == "Desert City");
    assert(fields[4] == "CO");
    assert(fields[5] == "00123");

    string line3 = CSVParser::writeArgsToLine(fields[0],
                                              fields[1],
                                              fields[2],
                                              fields[3],
                                              fields[4],
                                              fields[5]);
    assert(line3 == line);

    cout << "CSVParser passed\n";
  }

  return 0;
}
