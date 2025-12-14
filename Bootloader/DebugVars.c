#include <stdint.h>

/* All Debug variables in the same area */
__attribute__((section(".debugvars"))) volatile uint32_t dbg_reset = 0;
__attribute__((section(".debugvars"))) volatile uint32_t sysdbg = 0;
__attribute__((section(".debugvars"))) volatile uint32_t maindbg = 0;