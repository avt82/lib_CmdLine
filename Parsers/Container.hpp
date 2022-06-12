/******************************************************************************
 * @ingroup   CommandLine
 * @file      CmdLine/Parsers/Container.hpp
 * @author    Anton Tkachenko
 * @brief     CLI Tools Parsers - Contains the parsers and checks for match
 * @date      2022/06/06
 * @copyright TM Software, 2022
 *            github.com/avt82/lib_CmdLine
 *****************************************************************************/

#if !defined(COMMONTOOLS_COMMANDLINE_PARSER_CONTAINER_HPP_)
#define COMMONTOOLS_COMMANDLINE_PARSER_CONTAINER_HPP_

#include <vector>
#include <string>
#include <initializer_list>
#include "CmdLine/Parsers/Parser.hpp"

namespace cmdline {

  class ParserContainer {
  public:
    // Possible side-effects on copy/move, but it's not needed
    ParserContainer(const ParserContainer&) = delete;
    ParserContainer(const ParserContainer&&) = delete;

    // Constructors
    // TODO: consider to delete () constructor
    ParserContainer() { }
    ParserContainer(std::initializer_list<cmdline::Parser *const> list) {
      this->add(list);
    }

    // Destructor
    ~ParserContainer() {
      for(auto &it: this->pParsers) delete it;
    }

    // add single parser
    void add(cmdline::Parser *const pParser) {
      if(pParser != nullptr)
        this->pParsers.push_back(pParser);
    }

    // add multiple parsers
    void add(std::initializer_list<cmdline::Parser *const> list) {
      for(const auto &it: list) this->add(it);
    }

    // go through the parsers
    // TODO: clean-up comments, improve
    bool evaluate(const std::string &arg) {
      size_t cnt = 0;
      for(const auto &parser: this->pParsers) {
        if(parser != nullptr) {
          const auto res = parser->evaluate(arg);

//          switch(res) {
//          case cmdline::Parser::RetVal::ignored:                  break;
//          case cmdline::Parser::RetVal::parsed:     return true;
//          case cmdline::Parser::RetVal::partially:  cnt++;        break;
//          default:                                  return false;
//          }

          switch(res) {
          case cmdline::Parser::RetVal::ignored:            break;
          case cmdline::Parser::RetVal::partially:  cnt++;  break;
          default: return (res == cmdline::Parser::RetVal::parsed);
          }

        }
      }

      return (cnt != 0);
    }

  protected:
    std::vector<cmdline::Parser*> pParsers;

  private:

  };

}

#endif // COMMONTOOLS_COMMANDLINE_PARSER_CONTAINER_HPP_
