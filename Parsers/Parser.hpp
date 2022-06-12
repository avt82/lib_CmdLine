/******************************************************************************
 * @ingroup   CommandLine
 * @file      CmdLine/Parsers/Parser.hpp
 * @author    Anton Tkachenko
 * @brief     CLI Tools Parsers - Base class for command line parser
 * @date      2021/12/16
 * @copyright TM Software, 2021
 *            github.com/avt82/lib_CmdLine
 *****************************************************************************/

#if !defined(COMMONTOOLS_CMDLINE_PARSERS_PARSER_HPP_)
#define COMMONTOOLS_CMDLINE_PARSERS_PARSER_HPP_

#include <string>
#include <vector>
#include <initializer_list>
#include <functional>

namespace cmdline {

  class Parser {
  public:
    // return value type for processing functions
    enum class RetVal { ignored, parsed, partially, error };
    // callback functor type
    typedef std::function<RetVal(const std::string &arg, const std::string &item)> Action;

    // Possible side-effects on copy/move, but it's not needed
    Parser() = delete;
    Parser(const Parser&) = delete;
    Parser(const Parser&&) = delete;
    // Constructor
    Parser(std::initializer_list<std::string> list, Action action) : action(action) {
      for(auto const &it: list) this->list.push_back(it);
    }

    // Destructor
    virtual ~Parser() = default;

    // the processing function
    // TODO: naming, improve
    virtual cmdline::Parser::RetVal evaluate(const std::string &arg) {
      for(auto &it: this->list) {
        if(arg.rfind(it, 0) != std::string::npos) {
          auto const ret = this->action(arg, it);
          if(ret != cmdline::Parser::RetVal::ignored) return ret;
        }
      }
      return cmdline::Parser::RetVal::ignored;
    }

  protected:
    std::vector<std::string> list;
    Action action;

  private:
  };

}

#endif // COMMONTOOLS_CMDLINE_PARSERS_PARSER_HPP_
