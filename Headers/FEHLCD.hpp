/// \file
/// \brief A sanitized version of `FEHLCD.h`.
///
/// This header should always be preferred to the `FEHLCD.h` provided by the simulator library.
///
/// \author Will Blankemeyer

#pragma once

// Bypass inclusion of `LCDColors.h` by `FEHLCD.h`.
//
// `LCDColor.h` defines 141 (!!!) macros with common names such as `WHITE` and `BLACK`. This is
// quite problematic, particularly for our color type `Color` (defined in `screen.hpp`) that defines
// static data members including `WHITE` and `BLACK`. We need to prevent the preprocessor from
// naively replacing these names with the numeric literal definitions given in `LCDColor.h`,---but
// how?
//
// Luckily for us, the simulator library uses traditional `#include` guards in its header files, so
// we can define the guard macro for `LCDColors.h` and *then* include `FEHLCD.h`. While this is a
// fragile setup, the project Makefile locks the simulator library to a specific Git commit hash, so
// there shouldn't be any risk of breakage unless that commit hash is changed.
#define LCDCOLORS_H

#include <FEHLCD.h>

#undef LCDCOLORS_H
