#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <sstream>
#include <string>
#include "Vector.h"

using std::string;

namespace CSVParser {
  enum ParseError {
    Success,
    ImproperQuote,
    UnpairedQuote,
    UnclosedQuote,
    InsufficientColumns,
  };

  ParseError parseLine(const string &line, Vector<string> &values);
  string writeLine(const Vector<string> &values);

  template <class... Ts>
  ParseError parseLineToArgs(const string &line, Ts &...args) {
    auto res = ParseError::Success;

    Vector<string> values;
    parseLine(line, values);

    int cur = 0;
    auto lambda = [&](auto &v) {
      if (cur == values.size()) {
        res = ParseError::InsufficientColumns;
        return;
      }
      if constexpr (std::is_same_v<decltype(v), string &>) {
        v = values[cur++];
      } else {
        std::stringstream ss(values[cur++]);
        ss >> v;
      }
    };
    (lambda(args), ...);

    return res;
  }

  template <class... Ts>
  string writeArgsToLine(Ts &...args) {
    Vector<string> values;

    auto lambda = [&](auto &v) {
      std::stringstream ss;
      ss << v;
      values.push_back(ss.str());
    };
    (lambda(args), ...);

    return writeLine(values);
  }
};

#endif
