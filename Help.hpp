/******************************************************************************
 * @ingroup   CommandLine
 * @file      CmdLine/Help.hpp
 * @author    Anton Tkachenko
 * @brief     CLI Tools - Classes to show the help screen
 * @date      2022/06/06
 * @copyright TM Software, 2022
 *            github.com/avt82/lib_CmdLine
 *****************************************************************************/

#if !defined(COMMONTOOLS_COMMANDLINE_HELP_HPP_)
#define COMMONTOOLS_COMMANDLINE_HELP_HPP_

#include <string>
#include <initializer_list>

namespace cmdline {

  class HelpElement {
  public:
  protected:
  private:
  };

  class Help {
  public:
    // no sense to create class w/o argc-argv
    Help() = delete;
    // Possible side-effects on copy/move, but it's not needed
    Help(const Help&) = delete;
    Help(const Help&&) = delete;

    // Constructor
    Help(const int argc) { }

    // Destructor
    ~Help() { }

  protected:

  private:

  };

}

#endif // COMMONTOOLS_COMMANDLINE_HELP_HPP_
