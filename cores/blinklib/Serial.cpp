/*

  A very simplified serial port built to look like Arduino's Serial class.

  This serial port lives on the service port on new boards. It is really intended for debugging.

  The port always runs at a fixed 1M baud. Dev Candy Adapter boards and cables are available to
  connect to a USB port and then use the Arduino IDE's serial monitor to interact with your tile.

*/

//#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include "sp.h"

#include "Serial.h"

#include "ArduinoTypes.h"


// Public Methods //////////////////////////////////////////////////////////////

void ServicePortSerial::begin(void)
{

  sp_serial_init();

}

void ServicePortSerial::end()
{
    // TODO: Is there any reason to turn off the serial port? Power?

}

// We only use the 1 byte hardware buffer

int ServicePortSerial::available(void) {

    if (sp_serial_rx_ready()) {
        return(1);
    } else {
        return(0);
    }

}

int ServicePortSerial::read(void)
{
  if (!sp_serial_rx_ready()) {
    return -1;
  } else {
    return sp_serial_rx();
  }
}

// We don't implement flush because it would require adding a flag to remember if we ever sent.
// This is because the hardware only gives us a bit that tells us when a tx completes, not if
// no TX was ever started. Ardunio does this with the `_writen` flag.
// If you can convince me that we really need flush, LMK and it can be added.

size_t ServicePortSerial::write(uint8_t c)
{

  sp_serial_tx(c);

  return(1);

}

// Block until all pending transmits complete

void ServicePortSerial::flush(void)
{
    sp_serial_flush();
}