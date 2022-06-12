/******************************************************************************
 * @ingroup   CommandLine
 * @file      CmdLine/Parsers/Composite.hpp
 * @author    Anton Tkachenko
 * @brief     CLI Tools Parsers - Inherit this class to use a parsers container
 * @date      2022/06/11
 * @copyright TM Software, 2022
 *            github.com/avt82/lib_CmdLine
 *****************************************************************************/

#if !defined(COMMONTOOLS_CMDLINE_PARSERS_COMPOSITION_HPP_)
#define COMMONTOOLS_CMDLINE_PARSERS_COMPOSITION_HPP_

#include <initializer_list>
#include "CmdLine/Parsers/Parser.hpp"
#include "CmdLine/Parsers/Container.hpp"

namespace cmdline {

  class ParserComposite {
  public:
    // Possible side-effects on copy/move, but it's not needed
    ParserComposite(const ParserComposite&) = delete;
    ParserComposite(const ParserComposite&&) = delete;
    // Constructor
    ParserComposite(std::initializer_list<Parser *const> parsers):
      parsers(parsers) { }

    // add single parser - forward to container
    void add(cmdline::Parser *const pParser) { this->parsers.add(pParser); }
    // add multiple parsers - forward to container
    void add(std::initializer_list<cmdline::Parser *const> list) { this->parsers.add(list); }

  protected:
    cmdline::ParserContainer parsers;

  private:

  };

}

#endif // COMMONTOOLS_CMDLINE_PARSERS_COMPOSITION_HPP_
