/******************************************************************************
 * @ingroup   CommandLine
 * @file      CmdLine/Parsers/StringParser.hpp
 * @author    Anton Tkachenko
 * @brief     CLI Tools Parsers - Parser class for argument of a=b kind, where
 *            the 'b' part is a string. Base class for complex parsers.
 * @date      2021/12/17
 * @copyright TM Software, 2021
 *            github.com/avt82/lib_CmdLine
 *****************************************************************************/

#if !defined(COMMONTOOLS_CMDLINE_STRING_PARSERS_PARSER_HPP_)
#define COMMONTOOLS_CMDLINE_STRING_PARSERS_PARSER_HPP_

#include <string>
#include <initializer_list>
#include <functional>
#include "CmdLine/Parsers/Parser.hpp"

namespace cmdline {

  class StringParser: public Parser {
  public:
    // callback functor type
    typedef std::function<cmdline::Parser::RetVal(const std::string &value)> StringAction;

    // Constructor #1 - callback implementation
    StringParser(std::initializer_list<std::string> list, StringAction stringAction):
      cmdline::Parser(list, [stringAction](const std::string &arg, const std::string &item) {
        return stringAction(arg.substr(item.length(), std::string::npos));
      }) { }

    // Constructor #1 - reference to variable
    StringParser(std::initializer_list<std::string> list, std::string &var):
      StringParser(list, [&var](const std::string &value) {
        var = value;
        return cmdline::Parser::RetVal::parsed;
      }) { }

  protected:

  private:

  };

}

#endif // COMMONTOOLS_CMDLINE_STRING_PARSERS_PARSER_HPP_
