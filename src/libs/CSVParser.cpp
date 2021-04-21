#include "CSVParser.h"
using namespace std;

namespace CSVParser {
  namespace {
    const char COMMA = ',';
    const char QUOTE = '"';

    enum ParseState {
      Initial,
      Data,
      Quote,
      QuoteInQuote
    };
  }

  ParseError parseLine(const string &line, Vector<string> &values) {
    string value = "";
    auto state = ParseState::Initial;

    for (char c : line) {
      switch (state) {
        case ParseState::Initial: {
          switch (c) {
            case COMMA:
              values.push_back("");
              break;
            case QUOTE:
              state = ParseState::Quote;
              break;
            default:
              value += c;
              state = ParseState::Data;
              break;
          }
          break;
        }
        case ParseState::Data: {
          switch (c) {
            case COMMA:
              values.push_back(value);
              value = "";
              state = ParseState::Initial;
              break;
            case QUOTE:
              return ParseError::ImproperQuote;
            default:
              value += c;
              break;
          }
          break;
        }
        case ParseState::Quote: {
          switch (c) {
            case QUOTE:
              state = ParseState::QuoteInQuote;
              break;
            default:
              value += c;
              break;
          }
          break;
        }
        case ParseState::QuoteInQuote: {
          switch (c) {
            case COMMA:
              values.push_back(value);
              value = "";
              state = ParseState::Initial;
              break;
            case QUOTE:
              value += c;
              state = ParseState::Quote;
              break;
            default:
              return ParseError::UnpairedQuote;
          }
          break;
        }
      }
    }

    switch (state) {
      case ParseState::Initial:
      case ParseState::Data:
      case ParseState::QuoteInQuote:
        values.push_back(value);
        break;
      case ParseState::Quote:
        return ParseError::UnpairedQuote;
    }

    return ParseError::Success;
  }

  string writeLine(const Vector<string> &values) {
    string line = "";
    bool first = true;
    for (const string &value : values) {
      if (first) {
        first = false;
      } else {
        line += COMMA;
      }

      bool enclosed = false;
      for (char c : value) {
        if (c == COMMA || c == QUOTE) {
          enclosed = true;
        }
      }

      if (!enclosed) {
        line += value;
      } else {
        string escaped = "";
        escaped += QUOTE;
        for (char c : value) {
          if (c == QUOTE) {
            escaped += QUOTE;
            escaped += QUOTE;
          } else {
            escaped += c;
          }
        }
        escaped += QUOTE;
        line += escaped;
      }
    }

    return line;
  }
};
