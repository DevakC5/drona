# bom notes (messy)

- hall sensors: a3144 works but needs pullup. ss49e is analog and smoother, maybe rev2. magnet polarity matters!! standardize it. a3144 is open-collector (active low) so pullups live on the mcp23s17 (gppu).
- ws2812 at 64 leds draws a lot. 5v rail needs to handle ~4A worst case. usb alone no. rev1 probably underpowered if i forget, add external 5v
- esp32-s3 strapping pins: avoid gpio 0, 3, 45, 46 for important stuff
- helper chips: 4x mcp23s17 over spi (one cs, hardware addressing via a0-a2). no mux scanning. 16 inputs each = 64 sensors
- mcp23s17: enable haen (hardware address enable) before addressing devices individually. pullups on gppu for a3144
- jlcpcb assembly: mark dnp for anything hand soldered. check basic vs extended parts or cry at checkout
- row connectors: keep identical for all 8 rows so i dont mix them up
