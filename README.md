What is this?
===
This repository contains two main parts - a hardware folder which includes all the parts required to
make a two player adapter enclosure, and a software folder, arduino code required to create
a lagless adapter.

![heroimage](https://github.com/alex-ong/LaglessNESUSB/raw/master/Hardware/images/case.png)

Why is this lagless?
===
The software leverages [MHeironimus's Joystick2](https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-1.0/Joystick2) library, which creates a 1000hz usb device.
It is a simplified version of [mcgurk](https://github.com/mcgurk/Arduino-USB-HID-RetroJoystickAdapter)'s more universal adapter that polls as quickly as possible (10000hz+)
Total input delay is <1000hz. Pressing two keys at almost the same time will report button presses
2-3 milliseconds apart, in the correct order. This is more accurate than lower usb polling combos,
where pressing two buttons close together will wrap them as sent simultaneously.

 * [Hardware](https://github.com/alex-ong/LaglessNESUSB/tree/master/Hardware)

 * [Software](https://github.com/alex-ong/LaglessNESUSB/tree/master/Software)

Basic instructions
===
 1. Build hardware via laser cutting / screwing, soldering
 2. Flash software from software folder.
 3. Plug in, enjoy!


Future feature list
===

A single button will toggle between nodes, with two LEDs (one for mode, one for output).
Modes could include
 * Flashing an LED when key-down is detected. Use this in combination with a high speed camera to calculate input delay.
 * Auto-fire of arrow keys at 30hz, after a short delay
 * Adding delay to input to do A/B testing on users to detect minimum delay threshold.
 
Testing polling rate / minimum time between keymessages
===
You can use [this tool](https://github.com/alex-ong/UnityInputDelayTester/releases) to ensure that polling rate is 1ms. You can compare with other usb adapters, and your keyboard.
The idea is to strum two keys as close together as possible, without being simultaneous. It will figure out
the minimum time between key messages. Note that some keyboards are advertised as 1000hz, but wrap key events into 5ms polling rates.
This means if you press two keys 1ms apart, they are reported in the same 5ms block with the same timestamp.


Bill of Materials
===
| Electronics                | Cost  | Link                                             |
|----------------------------|-------|--------------------------------------------------|
| Arduino pro micro 5v 16mhz | $3.00 | [link](https://www.aliexpress.com/item/1348800135.html)  |
| Female Nes port            | $2.60 x 2 | [link](https://www.aliexpress.com/i/32827585164.html)    |
| Cabling (Ethernet)         | $0.00 |                                                  |
| Micro usb cable            | $1.00 | [link](https://www.aliexpress.com/item/32996600477.html) |


| Enclosure         | Cost | Link                                             |
|-------------------|------|--------------------------------------------------|
| Laser cut plywood | $3.0 | Todo: upload files as 1.5mm and 3mm              |
| Screws            | $2.0 | Todo                                             |
| Standoffs         | $2.0 | Todo                                             |
| Microusb port     | $1.5 | [link](https://www.aliexpress.com/item/32840345016.html) |

