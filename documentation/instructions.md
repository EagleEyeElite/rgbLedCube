led panel:
https://www.youtube.com/watch?v=6TpQfvCegF8

also: to stop a led from lighing also the led above, i used black paint at the bottom of the led

my mistakes:
- I tested the leds just with 3V / multimeter without checking volt threspoint
- didnt test with tlc controller, some leds dont light up.

Fix broken Leds:
Issues:
	-When powered with 3 or more Volts led Turns on
	-Multimeter shows ~60 Ohms accross in both directions
	-Forword drop Voltage is 1.1V
	-TLC cant turn it on or only at higher current
-Fix: (exact reason unkown):
	-Warning: once TLC can already turn LED at high current on, its very close to break the Led
	-if the Led is at 3/5V on, but dimmer than other Leds its broken for good! 

	-put shortly 3V across with instant Voltage drop with current increase, if it doesn't help, go up to 5V
	-check if Issues remain
	-be very carefully once TLC is able to power it a bit, its close to breaking for good!
	-repeat until Ohms go into kilo ohms and forward drop Valage is normle


current PCB has some flaws: checkout board/notes/specs & mistakes.md

