#ifndef BASE_DEBUG_DEBUGGER_H
#define BASE_DEBUG_DEBUGGER_H

#include "base/base_export.h"

namespace base {
namespace debug {
	BASE_EXPORT void BreakDebugger();
	BASE_EXPORT bool BeingDebugged();
}  // namespace debug
}  // namespace base

#endif  // BASE_DEBUG_DEBUGGER_H
