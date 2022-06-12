/******************************************************************************
 * @ingroup   CommandLine
 * @file      CmdLine/Parsers/EnumParser.hpp
 * @brief     CLI Tools Parsers - Class for argument of a=b with various options
 *            for 'b' part - could be another parser set.
 *            for single variable.
 * @date      2022/06/11
 * @copyright TM Software, 2022
 *            github.com/avt82/lib_CmdLine
 *****************************************************************************/

#if !defined(COMMONTOOLS_CMDLINE_ENUMERATION_PARSERS_PARSER_HPP_)
#define COMMONTOOLS_CMDLINE_ENUMERATION_PARSERS_PARSER_HPP_

#include <string>
#include <vector>
#include <initializer_list>
#include "CmdLine/Parsers/Container.hpp"
#include "CmdLine/Parsers/Composite.hpp"
#include "CmdLine/Parsers/Parser.hpp"
#include "CmdLine/Parsers/BoolParser.hpp"
#include "CmdLine/Parsers/StringParser.hpp"

namespace cmdline {

  class EnumParser: public cmdline::StringParser, public cmdline::ParserComposite {
  public:
    // Constructor
    EnumParser(std::initializer_list<std::string> list, std::initializer_list<Parser *const> parsers):
      cmdline::StringParser(list, [this](const std::string &value) {
          if(!this->parsers.evaluate(value)) return cmdline::Parser::RetVal::error;
          return cmdline::Parser::RetVal::parsed;
      }), cmdline::ParserComposite(parsers) { }

  protected:

  private:

  };

}

#endif // COMMONTOOLS_CMDLINE_ENUMERATION_PARSERS_PARSER_HPP_
