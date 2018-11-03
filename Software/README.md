# LaglessNesUSB
## What is this?

*This code is a modified/simplified version of the original from [mcgurk](https://github.com/mcgurk/Arduino-USB-HID-RetroJoystickAdapter). *

*It uses a copy of the Joystick library from MHeironimus [Joystick2](https://github.com/MHeironimus/ArduinoJoystickLibrary/tree/version-1.0/Joystick2)*

Very cheap and quite easy way to connect many non-USB joysticks and gamepads or DIY arcade cabinet controller to almost any machine with USB-port and HID-support. Arduino board with ATmega32u4 chip with help of Joystick-library does all the USB-work.
Tested with Windows and Linux desktop computers and ARM based computers like Raspberry Pi and Orange Pi.


### Supported controllers
- Nintendo Entertainment System controllers (NES)

### Polling rate / latency
- The Software polls the controllers at over 10000hz, and as soon as a difference is detected, sends this to the OS. The device is setup as a 1000hz usb joystick,
so maximal latency is 1ms. This is all handled by the Joystick2 library.

If you use Linux and want to get more than 1 controller with one Arduino, check "Linux and more than one controller with one Arduino"-topic in this same page.

## Short version
- Get ATmega32u4 Arduino board
- Connect joystick or gamepad to Arduino (in most situations soldering is required)
- Install Arduino [IDE](https://www.arduino.cc/en/Main/Software)
- Install Joystick [library](https://github.com/alex-ong/LaglessNESUSB/Software/Joystick2).
- Open sourcecode to Arduino IDE and select controller by commenting and uncommenting and edit pin-numbers (if needed)
- Build, Upload
- Done

## Long version
### What you need

#### Arduino board
Starting point is ATmega32u4 based Arduino board. There is two versions of ATmega32u4, IO-logic with 5V or 3.3V. We need 5V. Arduino Leonardo includes ATmega32u4, but cheapest and smallest ones are named Pro Micro. Arduino Pro Micro and ATmega32u4 are good words to use when searching from Ebay etc. Cheapest starts from about $4.

Example of Arduino Pro Micro:

![Arduino Pro Micro](https://github.com/alex-ong/LaglessNESUSB/raw/master/Software/Images/Arduino_ProMicro.jpg)


#### Computer with Arduino IDE
Arduino IDE works with Windows, OS X and Linux and ARM (beta). If you use small card computer like Rasperry Pi or Orange Pi, you can program adapter even with them (tested with Orange Pi PC and RetrOrangePi 2.0). That way you don't even have to unplug adapter from your emulator/game-platform if you want reprogram adapter.

#### Joystick library for Arduino IDE
I've made a copy from the original source, it is in Software/Joystick2. It is a single .cpp file and .h file. It sets up a 1000hz USB Joystick device. To install the joystick library, copy the folder into your arduino folder.

#### Joystick(s) or gamepad(s) and way to connect them to Arduino
Get some female ports off ali-express, or ebay.

NES-controller wiring:
![NES wiring](https://github.com/alex-ong/LaglessNESUSB/raw/master/Software/Images/nes.png)

### Setup

- Download and install Arduino IDE: https://www.arduino.cc/en/Main/Software

- `Tools->Board->Arduino Leonardo`

  In Arduino IDE you have to select board. In my case some reason "Arduino Leonardo" selections works better than "Arduino/Genuino Micro". With Leonardo-setting RX and TX leds are normally off and blinks when data is transfered to/from USB. With Micro-setting LED's are normally on and they blinks to off when data is transferring. Connect now your board ATmega32u4 through USB, the RX and TX leds should blink (if not, try another USB port).

- `Tools->Port->COMx`

  Arduino IDE shows available COM-ports. In most cases it's biggest numbered COM-port. COM-port number can change when you start to upload program first time (COM-port number can be different after joystick-features are enabled). If this happens, just change COM-port and start upload again. When I tested with RetrOrangePi (Armbian Linux), port was `/dev/ttyACM0`. In Windows environment, do not use any USB HUB, it may interfere with the comunication with ATmega32u4 board.

- Test your programming environment and upload

  You can now test your setup. One basic example is "blink". With this board, it doesn't blink, because there is no led in pin 13. Nevertheless you can use it as a test that your IDE and Arduino works. Select `File -> Examples -> 01.Basics -> Blink` and press `Upload` (Arrow to right -symbol top of code windows). If you get no errors, you are good to go.

- Install joystick library (needed for this controller)

  Copy the Joystick2 folder from Software\Joystick2
  to `%HOMEPATH%\Documents\Arduino\libraries` (Windows) or `~/Arduino/libraries` (Linux). If you have a non-installer verison of Arduino, look for the libraries folder.
  
  After extraction check that you have files `%HOMEPATH%\Documents\Arduino\libraries\Joystick2\Joystick2.h and Joystick2.cpp` or `~/Arduino/libraries/Joystick2/Joystick2.h and Joystick2.cpp`.
  Close and start Arduino IDE again so it searches and finds library.
  
- Load `RetroJoystickAdapter.ino` to Arduino IDE
  If you chose differnt pin numbers to solder to, change them at the top of the file.

- Press Verify / Upload

- If you got the message "all done" and no errors, your done here.

### Time to Enjoy

#### MS Windows
- You should go now to `Control Panel -> All Control Panel Items > Devices and Printers (some Windows versions in Game Controllers)` and try to find `Arduino Leonardo` device. Right click on `Gamepad controller definitions` > double click in one of the options (1st is the controller one, and the 2nd is the controller two) and you can now test the buttons.

##### Notice With Windows!
If you move adapter to other Windows machine, you may have to install the arduino drivers. To have the last updated ones, just download the file `Windows ZIP file for non admin install` from the page https://www.arduino.cc/en/Main/Software. After the download, unzip the folder. Go to the `Computer` > right click > `Manage > Device Manager > Unknown devices` > right click > `Update Driver Software > Browse my computer for software > Browse...` > and try to find the folder `\arduino-1.6.xx\drivers` inside the folder you unziped before. Click `Next` and Windows should install the driver. Arduino would apper as the name `Arduino Leonardo` inside `Ports (COM and LPT)` with an associated COM port (like `COM9` for example).

#### Linux
- Just connect, open your command line and test whit `jstest /dev/input/js0`.

##### Notice With Linux!
Linux usbhid-module doesn't support out of box multiple controllers with one USB without USB-hub-features.

You have to give parameter 
`quirks=0x2341:0x8036:0x40` (first numbers are VID and PID of Arduino) to usbhid-module. 

Here is example how to do it with RetrOrangePi 2.5.2:
- Make backup of `/boot/boot-retro.cmd` and `/boot/boot.scr`
- Edit `/boot/boot-retro.cmd` setenv bootargs -line and add `usbhid.quirks=0x2341:0x8036:0x40` to kernel parameters.
- `sudo mkimage -C none -A arm -T script -d /boot/boot-retro.cmd /boot/boot.scr`
- Reboot
- Check with `cat /proc/cmdline`

Lakka 2.0:
- Remount r/w: `mount -o rw,remount /flash`
- Make backup: `cp /flash/boot.scr /flash/org.boot.scr`
- Make file `/flash/boot.cmd`:
```
setenv machid 1029
setenv bootm_boot_mode sec
setenv bootargs console=ttyS0,115200 boot=/dev/mmcblk0p1 disk=/dev/mmcblk0p2 consoleblank=0 usbhid.quirks=0x2341:0x8036:0x40
fatload mmc 0 0x43000000 script.bin
fatload mmc 0 0x42000000 KERNEL
bootm 0x42000000
```
`mkimage -C none -A arm -O u-boot -T script -n "Lakka Boot" -d /flash/boot.cmd /flash/boot.scr`
- (you need to get mkimage from somewhere (e.g. use Armbian), because it is not included in Lakka)
- Reboot
- Check with `cat /proc/cmdline`

## Misc

### Changing VID/PID so Windows and Linux works without drivers or quirks

Linux problem with multiple controllers are solved with changing VID and PID to something that already has HID_QUIRK_MULTI_INPUT (0x40) activated in kernel.
Here you can see what quirks are activated to different VID/PIDs:
https://github.com/torvalds/linux/blob/master/drivers/hid/usbhid/hid-quirks.c

In these instructions, USB_VENDOR_ID_MOJO 0x8282, USB_DEVICE_ID_RETRO_ADAPTER 0x3201 are used.

Edit `C:\Program Files (x86)\Arduino\hardware\arduino\avr\boards.txt` or in linux `arduino-x.x.xx/hardware/arduino/avr/boards.txt` (close Arduino IDE before editing):
```
# leonardo.build.vid=0x2341
# leonardo.build.pid=0x8036
leonardo.build.vid=0x8282
leonardo.build.pid=0x3201
# leonardo.build.usb_product="Arduino Leonardo"
leonardo.build.usb_product="Retro Joystick Adapter"
```
#### WARNING!
There is possibility that serial port is not recognized after VID/PID change. We have tested with two Windows 10 machine and Linux with no problems. If you "brick" your Arduino, you get it back to life with resetting it rapidly two times in a row (grab a wire and make a shunt with RST->GND, they are located between A3, VCC and RAW) and then upload sketch (example blink.ino) with <b>normal Arduino VID/PID</b>. Be quick, because <b>you have only 8 seconds</b> to start uploading (try to hit `Send` button before make the reset).

### Changing number of buttons in joystick-library
If you want that less than 16 buttons are shown in joystick-settings, edit Joystick.cpp/Joystick2.cpp/Joystick3.cpp "USAGE_MAXIMUM"-line (0x10 = 16). You may to have create new project after that, because all libraries are not recompiled every time and we don't know how to force full recompile.

### Menu for multiple adapter names
Adapter shows as "Arduino Leonardo", but if you want it to show some other name, edit `C:\Program Files (x86)\Arduino\hardware\arduino\avr\boards.txt`. You can even add sub menu to tools-menu by adding these lines (after editing boards.txt, you have to close and reopen Arduino IDE):

```
menu.usb_name=USB Product Name
leonardo.menu.usb_name.leonardo="Leonardo"
leonardo.menu.usb_name.leonardo.build.usb_product="Arduino Leonardo"
leonardo.menu.usb_name.leonardo_1="Genesis 6"
leonardo.menu.usb_name.leonardo_1.build.usb_product="Genesis 6-button adapter"
leonardo.menu.usb_name.leonardo_2="Genesis 3"
leonardo.menu.usb_name.leonardo_2.build.usb_product="Genesis 3-button adapter"
leonardo.menu.usb_name.leonardo_3="NES"
leonardo.menu.usb_name.leonardo_3.build.usb_product="NES-adapter"
leonardo.menu.usb_name.leonardo_4="SNES"
leonardo.menu.usb_name.leonardo_4.build.usb_product="SNES-adapter"
```

### New board to Arduino IDE
If you add new board to Arduino IDE, it survives from Arduino IDE updates. Copy `boards.txt` to `{sketchbook folder}\hardware\retroadapter\avr\`.

Restart Arduino IDE and select Tools -> Board -> Arduino Pro Micro Retroadapter.

It changes VID to 0x8282 and PID to 0x3201 (Keio Retro Adapter).

#### How to reset Arduino (in case of emergency)

https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/troubleshooting-and-faq#ts-revive

