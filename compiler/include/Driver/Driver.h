#ifndef ARVCC_DRIVER_H
#define ARVCC_DRIVER_H

#include "Diag/Diagnostic.h"
#include "Driver/DriverOption.h"
#include "Option/ArgList.h"
#include "Option/OptTable.h"

using namespace arvcc::Diag;

namespace arvcc {
namespace driver {

class Compilation;
class Driver {

private:
  // The path the driver executable was invoked
  // from the command line
  std::string Dir;

  DiagnosticEngine &Diags;

  // command line arguments
  std::vector<const char *> Args;

  // parsed arguments
  std::unique_ptr<opt::InputArgList> CLOptions;

public:
  Driver(DiagnosticEngine &diags, const char **args, int argc) : Diags(diags) {
    if (1 == argc)
      Diags.DiagError("no Input files");
    for (int i = 0; i < argc; i++)
      Args.push_back(args[i]);
  }

public:
  // Construct a Compilation object for a
  // command line arguments vector
  Compilation *BuildCompilation();

  // Execute a compilation according to
  // command line arguments
  int ExecuteCompilation(Compilation &C);

  // Compiler Frontend
  int ExecuteCC1Tool();

  //
  const opt::OptTable &getOpts() const { return getDriverOptionTable(); }

  opt::InputArgList ParseArgStrings(bool ContainsError);

  bool HasCC1Tool();
};

} // namespace driver
} // namespace arvcc

#endif
