
// Here are our magic shared memory links to the BlinkBIOS running up in the bootloader area.
// These special sections are defined in a special linker script to make sure that the addresses
// are the same on both the foreground (this blinklib program) and the background (the BlinkBIOS project compiled to a HEX file)

#include "shared/blinkbios_shared_button.h"
#include "shared/blinkbios_shared_millis.h"
#include "shared/blinkbios_shared_pixel.h"
#include "shared/blinkbios_shared_irdata.h"

#include "blinklib.h"

#include "run.h"

// Here are the actual allocations for the shared memory blocks

// We put each in its own section so that the separately compiled blinkos will be able to find them.

// Note that without the `used` attribute, these blocks get tossed even though they are marked as `KEEP` in the linker script

blinkbios_pixelblock_t      __attribute__ ((section (".ipcram1") , used ))    blinkbios_pixel_block;
blinkbios_millis_block_t    __attribute__ ((section (".ipcram2") , used ))    blinkbios_millis_block;
blinkbios_button_block_t    __attribute__ ((section (".ipcram3") , used ))    blinkbios_button_block;
blinkbios_irdata_block_t    __attribute__ ((section (".ipcram4") , used ))    blinkbios_irdata_block;

// Here is our entry point. We are called by the BlinkBIOS after everything is set up and ready
// Note that this is not a normal startup, we are staring right from flash address 0x000 with no
// vector table at all. We don't need one because all vectors are pointing to the BlinkBIOS
// running up in the bootloader area.

// We will never return, so don't need any of the extra formality, just give me the straight up code

#include <avr/io.h>

extern "C" void mainx(void)  __attribute__ ((used)) __attribute__ ((noreturn));

extern "C" void mainx(void) {

    run();

    __builtin_unreachable();

    // Don't fall off the edge of the earth here!
    // Make sure we stop above!
}
