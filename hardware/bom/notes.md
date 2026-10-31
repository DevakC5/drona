# bom notes

- hall sensors: a3144 works but needs pullup. ss49e is analog and smoother, maybe rev2.
- ws2812 at 64 leds draws a lot. 5v rail needs to handle ~4A worst case. rev1 probably underpowered, add external 5v.
- esp32 devkit pins: check which gpios are strapping pins before routing.
- jlcpcb assembly: mark dnp for anything hand soldered.
