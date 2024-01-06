# USB Host ASCII Keyboard

[![Arduino Compile Sketches](https://github.com/Andy4495/USB_Host_ASCII_Keyboard/actions/workflows/arduino-compile-sketches.yml/badge.svg)](https://github.com/Andy4495/USB_Host_ASCII_Keyboard/actions/workflows/arduino-compile-sketches.yml)
[![Check Markdown Links](https://github.com/Andy4495/USB_Host_ASCII_Keyboard/actions/workflows/CheckMarkdownLinks.yml/badge.svg)](https://github.com/Andy4495/USB_Host_ASCII_Keyboard/actions/workflows/CheckMarkdownLinks.yml)

This sketch implements a simple USB to ASCII keyboard translator for use with a USB Host Shield for Arduino. It uses Serial.print() to output the ASCII character of the key pressed on the keyboard. ASCII control characters are also supported (e.g. [CTRL]-M prints ASCII 0x0D -- carriage return).

This setup can be useful for interfacing with retro computer builds that do not support USB.

The sketch has been tested on keyboards with and without built-in USB hubs.

## Optional LED

An LED/Resistor combo can be connected to the Host Shield output pin 7 and GND to indicate that a Keyboard is connected and running. Note that this is using the GPIO available on the [MAX3421E][3] chip, not the Arduino I/O.

## Host Shield Hardware

I used this [generic shield][2] from Amazon, along with a SparkFun [RedBoard][4].

However, any shield based on the [MAX3421E][3] chip along with an Uno-type Arduino should work with this sketch.

For the specific shield that I used, a few hardware configuration changes are necessary to function properly:

- Close the 5V power pad near the "VBUS PWR" silkscreen with a solder blob. Leave the 3.3V pad open. That is, the 5V pad with the "VBUS Power Select" label in this [photo][6].
- Close both the 5V and 3.3V pads near the power pins on the Arduino header connector. That is, the pads labeled "Power Select" in the [photo][6].

If attempting to use an [Arduino Pro][7] instead of an UNO, note that a separate 3.3V regulator is needed, since the Pro does not provide 3.3V power. In additon, the 3.3V "Power Select" pad should be left open (otherwise the Pro will supply 5V to the 3.3V logic on the shield.

## References

- [USB Host Shield Library][1]

## License

The sketch `USB_Host_ASCII_Keyboard.ino` is released under the [GPL-2.0 license][8], as is the sketch it is [based off of][9].

The other files in this repository are released under what is commonly called the [MIT License][100].

See the file [`LICENSE.txt`][101] in this repository.

[1]: https://github.com/felis/USB_Host_Shield_2.0
[2]: https://www.amazon.com/gp/product/B07J2KKGZ4
[3]: https://www.maximintegrated.com/en/products/interface/controllers-expanders/MAX3421E.html
[4]: https://www.sparkfun.com/products/13975
[6]: ./extras/USB-Host-Shield.jpg
[7]: https://www.sparkfun.com/products/10915
[8]: https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html
[9]: https://github.com/felis/USB_Host_Shield_2.0/blob/master/examples/HID/USBHIDBootKbd/USBHIDBootKbd.ino
[100]: https://choosealicense.com/licenses/mit/
[101]: ./LICENSE.txt
[//]: # ([200]: https://github.com/Andy4495/USB_Host_ASCII_Keyboard)
[//]: # ([5]: https://chome.nerpa.tech/arduino_usb_host_shield_projects/)
