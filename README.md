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
