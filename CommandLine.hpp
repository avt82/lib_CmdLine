/******************************************************************************
 * @ingroup   CommandLine
 * @file      CmdLine/CommandLine.hpp
 * @author    Anton Tkachenko
 * @brief     CLI Tools - Main class to process the command line
 * @date      2021/12/16
 * @copyright TM Software, 2021
 *            github.com/avt82/lib_CmdLine
 *****************************************************************************/

#if !defined(COMMONTOOLS_COMMANDLINE_CMDLINE_HPP_)
#define COMMONTOOLS_COMMANDLINE_CMDLINE_HPP_

#include <vector>
#include <string>
#include <initializer_list>
#include "CmdLine/CommandLineArguments.hpp"
#include "CmdLine/Parsers/Container.hpp"
#include "CmdLine/Parsers/Composite.hpp"
#include "CmdLine/Parsers/Parser.hpp"

namespace cmdline {

  class CommandLine: public cmdline::ParserComposite {
  public:
    // no sense to create class w/o argc-argv
    CommandLine() = delete;
    // Possible side-effects on copy/move, but it's not needed
    CommandLine(const CommandLine&) = delete;
    CommandLine(const CommandLine&&) = delete;

    // Constructors
    CommandLine(const int argc, const char* const argv[]):
      CommandLine(argc, argv, {}) { }
    CommandLine(const int argc, const char* const argv[], std::initializer_list<cmdline::Parser *const> list):
      cmdline::ParserComposite(list), arguments(argc, argv) { }

    // Destructor
    ~CommandLine() { }

    // the processing function
    // TODO: improve, EnumParser duplication
    bool process() {
      return this->arguments.process(
          [this](const std::string &arg) {
        return this->parsers.evaluate(arg);
      });
    }

    // forwards to CommandLineArguments
    // TODO: naming
    std::string getMyFullName() const { return arguments.getMyFullName(); }
    std::string getMyShortName() const { return arguments.getMyShortName(); }
    size_t getArgsCount() const { return arguments.getArgsCount(); }
    std::string getCurrentArgument() const { return arguments.getCurrentArgument(); }

  protected:
    cmdline::CommandLineArguments arguments;

  private:

  };

}

#endif // COMMONTOOLS_COMMANDLINE_CMDLINE_HPP_
