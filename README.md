This repository contains two main parts - a hardware folder which includes all the parts required to
make a two player adapter enclosure, and a software folder, arduino code required to create
a lagless adapter.

The software leverages [MHeironimus's Joystick2](https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-1.0/Joystick2) library, which creates a 1000hz usb device.
It is a simplified version of [mcgurk](https://github.com/mcgurk/Arduino-USB-HID-RetroJoystickAdapter)'s more universal adapter that polls as quickly as possible (10000hz+)
Total input delay is <1000hz. Pressing two keys at almost the same time will report button presses
2-3 milliseconds apart, in the correct order. This is more accurate than lower usb polling combos,
where pressing two buttons close together will wrap them as sent simultaneously.

Hardware (todo: link to hardware)

[Software](https://github.com/alex-ong/LaglessNESUSB/tree/master/Software)

Basic instructions:
 1. Build hardware via laser cutting / screwing, soldering
 2. Flash software from software folder.
 3. Plug in, enjoy!
