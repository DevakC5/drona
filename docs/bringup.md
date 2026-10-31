# bringup checklist (rev1)

first power:
- [ ] check 5v and 3.3v rails with no load
- [ ] esp32 boots, serial prints "drona boot ok"
- [ ] ws2812 chain lights up, no flicker
- [ ] hall sensor reads change when magnet brought near

known problems to check:
- ws2812 current draw at full white
- mux crosstalk between channels
- hall sensor threshold (analog values vary a lot)

if magic smoke appears: unplug and cry
