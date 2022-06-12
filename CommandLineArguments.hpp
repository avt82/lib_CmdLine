/******************************************************************************
 * @ingroup   CommandLine
 * @file      CmdLine/CommandLineArguments.hpp
 * @author    Anton Tkachenko
 * @brief     CLI Tools - Class that contains argc-argv and iterates through it;
 *            handling executable name
 * @date      2022/06/06
 * @copyright TM Software, 2022
 *            github.com/avt82/lib_CmdLine
 *****************************************************************************/

#if !defined(COMMONTOOLS_COMMANDLINE_ARGUMENTS_HPP_)
#define COMMONTOOLS_COMMANDLINE_ARGUMENTS_HPP_

#include <string>
#include <functional>

namespace cmdline {

  class CommandLineArguments {
  public:
    // no sense to create class w/o argc-argv
    CommandLineArguments() = delete;
    // Possible side-effects on copy/move, but it's not needed
    CommandLineArguments(const CommandLineArguments&) = delete;
    CommandLineArguments(const CommandLineArguments&&) = delete;

    // Constructor
    CommandLineArguments(const int argc, const char* const argv[]):
      cntParams(argc), ppParams(argv), cCurrentArgument(nullptr) { }

    // Destructor
    ~CommandLineArguments() { }

    // the processing function
    bool process(std::function<bool(const std::string &arg)> func) {
      char ** pPtr = (char**)this->ppParams;
      if(pPtr == nullptr) return false;
      pPtr++;
      for(size_t cnt = 1; cnt < this->cntParams; cnt++) {
        this->cCurrentArgument = *pPtr++;
        if(!func(this->cCurrentArgument)) return false;
      }

      this->cCurrentArgument = nullptr;
      return true;
    }

    std::string getMyFullName() const {
      return std::move(std::string(*this->ppParams));
    }

    std::string getCurrentArgument() const {
      if(this->cCurrentArgument == nullptr) return std::move(std::string(""));
      return std::move(std::string(this->cCurrentArgument));
    }

    std::string getMyShortName() const {
      std::string res = this->getMyFullName();
      if(this->getLastFileNameSegment(res, '\\')) return res;
      if(this->getLastFileNameSegment(res, '/')) return res;
      return res;
    }

    size_t getArgsCount() const {
      size_t ret = this->cntParams;
      if(ret > 0) --ret;
      return ret;
    }

  protected:
    const size_t cntParams;
    char const *const *const ppParams;
    char const *cCurrentArgument;

    // TODO: naming
    bool getLastFileNameSegment(std::string &str, const int ch) const {
      const auto pos_u = str.rfind(ch);
      if(pos_u != std::string::npos) {
        str.erase(0, pos_u + 1);
        return true;
      }
      return false;
    }

  private:

  };

}

#endif // COMMONTOOLS_COMMANDLINE_ARGUMENTS_HPP_
