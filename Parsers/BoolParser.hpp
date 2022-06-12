/******************************************************************************
 * @ingroup   CommandLine
 * @file      CmdLine/Parsers/BoolParser.hpp
 * @author    Anton Tkachenko
 * @brief     CLI Tools Parsers - Parser for single action on specified
 *            argument(s); simple match/mismatch check.
 * @date      2021/12/17
 * @copyright TM Software, 2021
 *            github.com/avt82/lib_CmdLine
 *****************************************************************************/

#if !defined(COMMONTOOLS_CMDLINE_BOOLEAN_PARSERS_PARSER_HPP_)
#define COMMONTOOLS_CMDLINE_BOOLEAN_PARSERS_PARSER_HPP_

#include <string>
#include <initializer_list>
#include "CmdLine/Parsers/Parser.hpp"

namespace cmdline {

  template<typename T>
  class BoolParser: public cmdline::Parser {
  public:
    // Constructor
    BoolParser(std::initializer_list<std::string> list, T &var, const T value):
      cmdline::Parser(list, [value, &var](const std::string &arg, const std::string &item) {
        if(arg.length() != item.length()) return cmdline::Parser::RetVal::ignored;
        var = value;
        return cmdline::Parser::RetVal::parsed;
      }) { }

  protected:

  private:

  };

}

#endif // COMMONTOOLS_CMDLINE_BOOLEAN_PARSERS_PARSER_HPP_
