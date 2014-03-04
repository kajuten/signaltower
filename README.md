# signaltower

ATmega8 is the interface between the control of the signals/railway switches and the communication to rpi-central in a model railroad project

## Components

- ### Signal API

- ### Railway switch API

- ### RF12 chip API

	- communication via SPI

	- connected Pins:

		ATmega 8 PCB  |     | RF12
------------: |:-----:| :---
3.3V		  | ----> | VDD
PD2			  | <---- | NIRQ
MOSI 		  | ----> | SDI
GND			  | ----> | GND
MISO 		  | <---- | SDO
CLK  		  | ----> | SCK
SS			  | ----> | nSEL

## Model Railroad description

**Goal:** a self-made model railroad which can be controlled via a PC

- Train components and casings are 3D printed
- PCB self-made
- Central Raspberry Pi connected to WIFI
- Communication from RPi-central to the signal-towers via RF12 chip [TRX433S][RF12]
- MySQL database hosted on Raspberry Pi
- Signal towers are controlled by an ATmega8 which is connected with a RF12 chip ([see signaltower project][signaltower])
- Another Raspberry Pi with a camera module is in every train which is connected via a 3G dongle to the internet ([see RPi-train project][RPi-train])

[RF12]: http://www.matrixmultimedia.com/resources/files/datasheets/RF%20Solutions%20Transciever.pdf
[signaltower]: https://github.com/kajuten/signaltower
[RPi-train]: https://github.com/kajuten/rpi-train