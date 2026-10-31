# drona rev1 plan (will probably change 5 times)

ok final-ish decisions, dont @ me:

- square size = 3cm. board = 24x24cm. big but ok
- jlcpcb assembles it (expensive but im lazy and bad at soldering 0402)
- esp32 as smd module soldered down (not removable, rip if it dies)
- a3144 hall sensors (digital, magnet polarity matters!! read the gotcha)

## how many boards

NOT one big board. doing modular:
- 1 small controller board (esp32, power, muxes, connectors)
- 8 row boards, each 8 squares (24x4cm). one row = 8 sensors + 8 leds

why: if one led dies on a 24cm board im crying. also cheaper to test one row first.

jlcpcb charges per design so: controller x5, row board x1 first, test, then x7 more if it doesnt suck.

## block diagram (rough, dont judge)

usb-c (data/prog) -> esp32 -> 4x mux -> row connectors (hall bus)
5v in -> leds (chained row1->row2->...->row8)
5v -> ams1117 -> 3.3v for esp32

## parts list (see bom.csv too)

- esp32-wroom-32 x1
- a3144 x64
- ws2812b x64
- cd74hc4067 x4
- ams1117-3.3 x1
- usb-c x1 (data + prog)
- 5v power input (barrel jack or screw term) x1
- caps: 100nf x8, one big 100-470uf near led chain start

## power (this is scary)

64 leds at full white = ~3.8A at 5v. usb gives 0.5-0.9A. NOT ENOUGH.
so: separate 5v input for leds. firmware caps brightness to ~30% default.
full white only for testing and crying.

## gotchas

1. a3144 is digital + polarity sensitive. magnets must all face same way in pieces. if someone flips a piece it wont read. (maybe ss49e in rev2)
2. led chain order: snake it. row1 left->right, row2 right->left etc. write down which led index = which square or ull cry later
3. mux: 4 separate sig lines to esp32. dont share one line, too annoying
4. esp32 strapping pins: dont use gpio 0,2,5,12,15 for important stuff
5. jlcpcb: check if parts are "basic" or "extended". extended = extra fee per design. check early or cry at checkout

## build order (dont do everything at once!!)

1. controller board x5. get esp32 + power + one row connector working. test with jumper wires to 8 sensors.
2. row board v1 x1. 8 sensors + 8 leds. check chain, current, thresholds.
3. if v1 sucks, fix -> v2. else order 7 more v1.
4. plug all 8 rows in. tune thresholds. write game logic. (lol)

## rev2 ideas (when rev1 catches fire)

- ss49e instead of a3144
- maybe one big board if money
- enclosure
- piece detection that isnt just magnets (rfid??)
- wireless to phone

## status

plan written. nothing built. praying.
