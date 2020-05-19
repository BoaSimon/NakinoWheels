# NakinoWheels
An open-source camera control hand-wheels project based on the Kino Wheels project at https://www.kinowheels.com/

I'm just dumping all the files up here right away, but when I've got some time after work today I'll reorganize and make things clear.

STL Files:
The case to print!

NaKinoWheels_UE4.ino
Arduino Sketch which communicates with UE4 over Serial. Requires the UE4Duino2 plugin for Unreal Engine: https://forums.unrealengine.com/community/community-content-tools-and-tutorials/121573-free-windows-only-ue4duino-2-arduino-com-port-communication

NaKinoWheels_KinoSimulator.ino
Arduino Sketch which communicates with the original Kino Wheels Simulator, at https://www.kinowheels.com/simulator/

NaKinoWheels_PPM.ino
Arduino Sketch which outputs PPM from a 3.5mm jack. Good for feeding the Trainer port on any RC Transmitter to send signal to MoVI/Ronin via an S-Bus receiver. I've got a plan to make a simple module that will take the PPM signal and transmit directly through a JR Module to an S-Bus Receiver, but I'll do that when I've got an actual physical production job coming up...

NaKinoController.uasset
The UE4 blueprint for reading Serial signal from the NaKino wheels! It only ticks during runtime, so you won't see anything until you launch PIE.

-- PARTS LIST --
McMaster Carr:
2x Black Aluminum Unthreaded Through-Hole Spoked Hand Wheel, Dished Wheel with Revolving Handle, 6" Diameter, 1/2" Hole
https://www.mcmaster.com/60265K25-60265K25
2x Tapped D-Profile Rotary Shaft, 1045 Carbon Steel, 1/2" Diameter, 6" Long
https://www.mcmaster.com/8017T3-8017T3
2x 	Low-Profile Mounted Sealed Steel Ball Bearing for 1/2" Shaft Diameter
https://www.mcmaster.com/5913K61-5913K61
1x 	Tapered Heat-Set Inserts for Plastic, 8-32 Thread Size, 0.185" Installed Length, Brass, Packs of 100
https://www.mcmaster.com/93365A140-93365A140
1x Zinc-Plated Alloy Steel Hex Drive Flat Head Screw, 8-32 Thread Size, 1/2" Long, Packs of 25
https://www.mcmaster.com/91263A524-91263A524
1x Tapered Heat-Set Inserts for Plastic, 1/4"-20 Thread Size, 0.3" Installed Length, Brass
https://www.mcmaster.com/93365A160-93365A160
1x Tapered Heat-Set Inserts for Plastic, 3/8"-16 Thread Size, 3/8" Installed Length, Brass
https://www.mcmaster.com/93365A290-93365A290

Amazon:
2x 600P/R Rotary Encoder, Aideepen AB 2 Phase Incremental Rotary Encoder 6mm Shaft 5V-24V Wide Voltage
https://www.amazon.com/gp/product/B01MZ4V1XP/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1
1x E-Projects 100EP51210K0 10k Ohm Resistors, 1/2 W, 5% (Pack of 100)
https://www.amazon.com/gp/product/B0185FIOTA/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1
1x ELEGOO MEGA 2560 R3 Board ATmega2560 ATMEGA16U2 + USB Cable Compatible with Arduino IDE, RoHS Compliant
https://www.amazon.com/gp/product/B01H4ZLZLQ/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1
1x Onyehn TRRS 3.5mm Audio Jack Breakout MP3 Stereo Headphone Video Jack Module for Arduino (Pack of 5pcs)
https://www.amazon.com/gp/product/B07L3P93ZD/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1
1x EDGELEC 120pcs Breadboard Jumper Wires 10cm 15cm 20cm 30cm 40cm 50cm 100cm Optional Dupont Wire Assorted Kit Male to Female Male to Male Female to Female Multicolored Ribbon Cable
https://www.amazon.com/gp/product/B07GD1XFWV/ref=ppx_yo_dt_b_asin_title_o01_s01?ie=UTF8&th=1
1x Hornet Tire - 1/4oz Grey Lead Free Adhesive Backed Wheel Weights (48pcs)
https://www.amazon.com/gp/product/B00ZMD8SDG/ref=ppx_yo_dt_b_asin_title_o01_s01?ie=UTF8&psc=1
1x TWTADE / 3pcs wh138 100 ohm Potentiometer Single Turn Rotary Linear Variable Potentiometer +3pcs Black Aluminum Alloy knob
https://www.amazon.com/gp/product/B07DHGHQPQ/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1
