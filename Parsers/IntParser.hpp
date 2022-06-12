/******************************************************************************
 * @ingroup   CommandLine
 * @file      CmdLine/Parsers/IntParser.hpp
 * @author    Anton Tkachenko
 * @brief     CLI Tools Parsers - Parser class for argument of a=b kind,
 *            where 'b' part is an integer
 * @date      2021/12/17
 * @copyright TM Software, 2021
 *            github.com/avt82/lib_CmdLine
 *            Will require: github.com/avt82/lib_Utilities (soon)
 *****************************************************************************/

#if !defined(COMMONTOOLS_CMDLINE_INTEGER_PARSERS_PARSER_HPP_)
#define COMMONTOOLS_CMDLINE_INTEGER_PARSERS_PARSER_HPP_

#include <string>
#include <initializer_list>
#include <functional>
#include <stdexcept>
#include "CmdLine/Parsers/StringParser.hpp"

namespace cmdline {

  // TODO: should be template for integer types
  class IntParser: public StringParser {
  public:
    // callback functor type
    typedef std::function<cmdline::Parser::RetVal(const int value)> IntAction;

    // Constructor #1 - callback
    IntParser(std::initializer_list<std::string> list, IntAction intAction):
      cmdline::StringParser(list, [intAction](const std::string &value) {
        size_t idx = 0;
        try {
          // TODO: that's the bottle-neck for template;
          // should be changed after utils::stringToInt will be implemented
          int res = std::stoi(value, &idx, 0);
          if((idx > 0) && (idx == value.length())) return intAction(res);
        }
//        catch(const std::invalid_argument &e) {
//          return cmdline::Parser::RetVal::error;
//        }
//        catch(const std::out_of_range &e) {
//          return cmdline::Parser::RetVal::error;
//        }
        catch(...) {
//          return cmdline::Parser::RetVal::error;
        }
        return cmdline::Parser::RetVal::error;
      }) { }

    // Constructor #2 - reference to variable
    IntParser(std::initializer_list<std::string> list, int &var):
      IntParser(list, [&var](const int value) {
        var = value;
        return cmdline::Parser::RetVal::parsed;
      }) { }

    // Constructor #3 - reference to variable and min/max values
    IntParser(std::initializer_list<std::string> list, int &var, const int min, const int max):
      IntParser(list, [&var, min, max](const int value) {
        if((value < min) && (value > max)) return cmdline::Parser::RetVal::error;
        var = value;
        return cmdline::Parser::RetVal::parsed;
      }) { }

  protected:

  private:

  };

}

#endif // COMMONTOOLS_CMDLINE_INTEGER_PARSERS_PARSER_HPP_
