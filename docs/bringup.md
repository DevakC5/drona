# bringup checklist (rev1)

first power:
- [ ] check 5v and 3.3v rails with no load
- [ ] esp32-s3 boots, serial prints "drona boot ok"
- [ ] ws2812 chain lights up, no flicker
- [ ] hall sensor reads change when magnet brought near (mcp23s17 gpio)

known problems to check:
- ws2812 current draw at full white
- mcp23s17 spi addressing (haen) with 4 devices on one cs
- a3144 threshold / active-low polarity (magnet present = low)
- pullups on mcp23s17 gppu

if magic smoke appears: unplug and cry
