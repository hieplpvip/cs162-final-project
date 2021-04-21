#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <string>
#include "Vector.h"

namespace CSVParser {
  enum ParseError {
    Success,
    ImproperQuote,
    UnpairedQuote,
    UnclosedQuote,
  };

  ParseError parseLine(std::string line, Vector<std::string> &values);
  std::string writeLine(const Vector<std::string> &values);
};

#endif
