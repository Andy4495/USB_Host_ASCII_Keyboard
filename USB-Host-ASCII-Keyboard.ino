#include <hidboot.h>
#include <usbhub.h>
#include <UHS2_gpio.h>

/*
 * USB Host ASCII Keyboard Driver
 * 
 * This sketch implements a simple USB to ASCII keyboard translator. 
 * It uses Serial.print() to output the ASCII character of the key pressed on the keyboard. 
 * ASCII control characters are also supported (e.g. <CTRL>-M prints ASCII 0x0D -- carriage return)
 * It should work with keyboards with or without built-in USB hubs. 
 * An LED/Resistor combo can be connected to the Host Shield output pin 7 (NOT Arduino pin 7) and GND 
 * to indicate that a Keyboard is connected and running. 
 * 
 * Based on USBHIDBootKbd example sketch from USB Host Shield 2.0 Library:  
 *   https://github.com/felis/USB_Host_Shield_2.0
 *   
 * License: GNU General Public License
 *   
 * 1.0 - 04/10/2021 - A.T. - Original 
 * 
 */

#include <SPI.h>

class KbdRptParser : public KeyboardReportParser
{
  protected:
    void OnKeyDown	(uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t key);
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
///  Serial.print("DN ");
///  PrintKey(mod, key);
  uint8_t c = OemToAscii(mod, key);

// Add support for ASCII control characters
  if (mod & 0x11) { // CTRL modifier key pressed
    if (c >= 0x40 && c <= 0x5F) c = c - 0x40;  // Upper case characters
    if (c >= 0x60 && c <= 0x7F) c = c - 0x60;  // Lower case characters
  }

  if (c)
    OnKeyPressed(c);
}

void KbdRptParser::OnKeyPressed(uint8_t key)
{
///  Serial.print("ASCII: ");
///  Serial.println((int)key, HEX);
  Serial.print((char) key);
};

USB     Usb;
USBHub     Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
UHS2_GPIO Gpio(&Usb); 
#define LED_GPIO_PIN 7


KbdRptParser Prs;

void setup()
{
  Serial.begin( 57600 );

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  HidKeyboard.SetReportParser(0, &Prs);
}

void loop()
{
  Usb.Task();

  // Turn on GPIO 0 on Host Shield if USB device connected and running. 
  if ( Usb.getUsbTaskState() == USB_STATE_RUNNING ) Gpio.digitalWrite(LED_GPIO_PIN, HIGH);
  else   Gpio.digitalWrite(LED_GPIO_PIN, LOW);

}
