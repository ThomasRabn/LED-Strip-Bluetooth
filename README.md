# LED-Strip-Bluetooth

## The Project

LEDs strips are cool. But they are not cool enough to be bought as it is. This is why I made my own Arduino program to control a LEDs strip composed of 60 RGB LEDs thanks to an Arudino Uno board and a Bluetooth sensor. The master version uses the `FastLed` library and is made to control a 60 LEDs strip.

## Functionnalities

There are numerous functionalities:
- Luminosity control (more light, less light)
- Solid colors
- Bicolor gradients
- Rainbow gradient
- 'Disco' effect: colors moving from one side to the other
- 'Changing' mode: solid color changing in time
- Speed control: faster or slower 'Disco' and 'Changing' modes

## How to install

- Download or clone the repository
- Open the .ino file in the Arduino IDE
- Upload the code to an Arduino Uno board
- Make sure to connect all the LEDs strip's pins and the Bluetooth sensor's pins to the good Arduino pins
- Connect the Arduino and/or the lights to a real power source (**at least 1 amp**)
- Download a serial Bluetooth app on your phone (eg: `Serial Bluetooth Terminal` on Android)
- Connect to the Bluetooth sensor and a text message that is understandable to it (eg: `rainbow`)
- The LED strip should turn on and work depending on what you sent

# Author

Thomas RABIAN - thomas.rabian@protonmail.com
