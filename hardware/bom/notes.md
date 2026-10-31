# bom notes (messy)

- hall sensors: a3144 works but needs pullup. ss49e is analog and smoother, maybe rev2. magnet polarity matters!! standardize it
- ws2812 at 64 leds draws a lot. 5v rail needs to handle ~4A worst case. usb alone no. rev1 probably underpowered if i forget, add external 5v
- esp32 devkit pins: check which gpios are strapping pins before routing (0,2,5,12,15)
- jlcpcb assembly: mark dnp for anything hand soldered. check basic vs extended parts or cry at checkout
- row connectors: keep identical for all 8 rows so i dont mix them up
