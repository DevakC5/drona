# drona rev1 plan (will probably change 5 times)

ok final-ish decisions, dont @ me:

- square size = 3cm. board = 24x24cm. big but ok
- jlcpcb assembles it (expensive but im lazy and bad at soldering 0402)
- esp32-s3 as smd module soldered down (not removable, rip if it dies)
- a3144 hall sensors (digital, magnet polarity matters!! read the gotcha)

## how many boards

NOT one big board. doing modular:
- 1 small controller board (esp32-s3, power, 4x mcp23s17, connectors)
- 8 row boards, each 8 squares (24x4cm). one row = 8 sensors + 8 leds

why: if one led dies on a 24cm board im crying. also cheaper to test one row first.

jlcpcb charges per design so: controller x5, row board x1 first, test, then x7 more if it doesnt suck.

## block diagram (rough, dont judge)

usb-c (data/prog) -> esp32-s3 -> spi -> 4x mcp23s17 -> hall sensors (64)
5v in -> leds (chained row1->row2->...->row8)
5v -> ams1117 -> 3.3v for esp32-s3

note: no mux scanning. each mcp23s17 reads 16 sensors in parallel over spi.

## parts list (see bom.csv too)

- esp32-s3-wroom-1 x1
- a3144 x64
- ws2812b x64
- mcp23s17 x4
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
3. mux: none. 4 mcp23s17 over one spi bus, one shared cs, hardware addressing via a0-a2. enable haen first.
4. esp32-s3 strapping pins: dont use gpio 0,3,45,46 for important stuff
5. a3144 open-collector: needs pullup. enable gppu on mcp23s17 (active low: magnet present = low)
6. jlcpcb: check if parts are "basic" or "extended". extended = extra fee per design. check early or cry at checkout

## cool features (no screens)

change game modes and settings by moving the white king to different glowing squares on the board. no screen, no buttons. esp32-s3 runs chess logic fully offline.

## build order (dont do everything at once!!)

1. controller board x5. get esp32-s3 + power + one mcp23s17 working. test with jumper wires to 8 sensors.
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
