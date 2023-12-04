# Arduino Resources

This repository is dedicated to learning about Arduino and the ATmega328p
microcontroller. 

## Compiler

There are several ways to obtain the Arduino developement toolchain. The easiest
way is to piggyback on the `avr-gcc` toolchain installed with the Arduino IDE.
On MacOS, you can find the toolchain at `~/Library/Arduino15/packages/arduino/tools`.

However, downloading and installing the `avr-gcc` toolchain in a seperate 
directory allows for better organization and removes the Arduino IDE dependency.

The following toolchain components need to be installed

  1. avr-binutils
  2. avr-gcc
  3. avr-libc
  4. avrdude (for uploading code to the arduino)

A tutorial for installing all these components can be found at (https://www.nongnu.org/avr-libc/user-manual/install_tools.html#path)[https://www.nongnu.org/avr-libc/user-manual/install_tools.html#path]



The code in this repository can be compiled using the `avr-gcc` compiler.

The code in this repository focuses on the using
