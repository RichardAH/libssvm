// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <iostream>

//#include "easyloggingpp/easylogging++.h"

#define LOG(X) std::cout

namespace SSVM {
namespace Log {

void passEasyloggingppArgs(int Argc, char *Argv[]);
void setErrorLoggingLevel();

//extern el::base::type::StoragePointer elStorage;
//extern el::base::debug::CrashHandler elCrashHandler;

} // namespace Log
} // namespace SSVM
