This is a short guide on how to assemble a laser cut box with two NES ports and a pro micro.

Dimensions
===
86mm x 63mm x 26mm


Parts list
===

| Item                          | Count  | Cost  | Link   |
| -----                         | -------| ------| ------ |
| 3mm plywood/acrylic (A4)      | 1      | $6    |        |
| 20mm m3 standoff              | 5      | -     |        |
| m3 nut                        | 7      | $5    | [Link](https://www.ebay.com.au/itm/M3-Hex-Column-Male-Female-Black-Standoff-Spacers-Screw-Nut-Box-Kit-Nylon-A1F/252337488786)        |
| m3 screw, 10mm                | 5      | -     |        |
| m3 screw, 20mm                | 2      | $1    | [Link](https://www.ebay.com.au/itm/M2-M2-5-M3-Black-Nylon-Pan-Head-Screws-Phillips-Machine-Bolts-Plastic-Round/222643401951)       |
| microusb port panel mount     | 1      | $1.09 | [Link](https://www.ebay.com.au/itm/USB-2-0-Micro-USB-Male-To-Female-Panel-Mount-Extension-Adapter-Cable-30cm-50cm/253356879959)      |
| cherry mx (compatible) switch | 1      | $0.30 |        |
| LED                           | 2      | $1    | [Link](https://www.jaycar.com.au/red-3mm-led-40mcd-round-diffused/p/ZD0100)|
| Resistor(TODO)                | 2      | $1    |        |
| Cat5 wire for wires (30cm)    | 1      | $1    |        |
| Pro micro clone               | 1      | $5    |        |
| NES Ports (Female)            | 2      | $5    | [Link](https://www.aliexpress.com/item/Hight-quality-Replacement-Parts-90-Degree-7-Pin-Connector-female-for-NES-console-Socket/32827549549.html)

Tools list
===
* Soldering iron
* Laser cutting services, where you can engrave 1.5mm deep
* Screwdriver
* Wire strippers
* Flush cutters
* Heatshrink

Cut the case
===
* Laser cut the files provided. You'll want to engrave at 1.5mm for the areas that will mount to the NES Ports, since they are designed to fit on 1.5mm steel.
* They should all fit together nicely.
* Test the nes ports (gently!). If they aren't going to fit, modify the design files. The plastic nubs are VERY sensitive,
don't break them!

Soldering
===
1. Shorten the panel mount connector, to roughly 2-3 cm. Use flush cutters to strip away the ribbing from the cable, enabling it to be bent 90°. This involves cutting the middle section out of the cable, and re-soldering / re-heatshrinking
2. If you ordered 90° NES Female panel connectors, use flush cutters to shorten the connections and bend them back to straight. Solder these (using Cat5) to the microcontroller. Look at source code for which exact ports.
![NES connector](https://github.com/alex-ong/LaglessNESUSB/blob/master/Software/Images/nes.png)
3. TODO: Solder LEDs/resistors/cherry switch

Assembly
===
1. Put standoffs into the base of the case, using nuts from the other side to hold them in place.
2. Put nes ports in case, snapping them in.
3. Screw in MicroUSB port into back panel
4. Plug MicroUSB extension into the pro micro.
5. Cram everything together. 
6. Screw the 5 screws in.


