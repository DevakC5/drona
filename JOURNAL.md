---
title: "drona"
github: "https://github.com/DevakC5/drona"
description: "smart chess board with hall sensors and leds under every square"
created_at: "2026-11-01"
total_time: "4h 16m"
---

## November 1, 2026: started drona

init'd the repo, hooked up the remote, pulled the empty README. made folders: hardware/easyeda, hardware/bom, hardware/gerbers, firmware/drona, docs. wrote a very professional README (it is not professional). first commit + push. praying.

**Total time spent: 1h**

## November 1, 2026: rev1 plan + bom (still praying)

locked in decisions: 3cm squares, JLCPCB PCBA, SMD esp32 module, A3144 halls. decided modular: controller board + 8 row boards (24x4cm each) instead of one giant 24x24cm board. cheaper to test, less crying if a led dies. power is scary: 64 leds = ~3.8A at 5V, usb alone won't cut it, separate 5V rail + brightness cap in firmware. A3144 is polarity-sensitive so magnets in pieces must all face the same way (noted for rev2: maybe SS49E). updated bom.csv (added 5V jack, 470uF bulk cap, row connectors), rewrote notes.md. firmware sketch: fastled + mux scan + state machine, still very rough, thresholds TBD. committed with a delayed timestamp for devlog purposes.

**Total time spent: 2h 20m**

## November 1, 2026: making plan better and logo design

reconciled the plan with the new design: swapped esp32-wroom-32 for esp32-s3 and the 4x cd74hc4067 muxes for 4x mcp23s17 spi expanders (no more mux scanning). updated bom.csv, notes.md, plan_rev1.md, bringup.md, README. rewrote firmware to read 64 halls via mcp23s17 over spi, moved led pin off a strapping pin, capped brightness ~30%. firmware compiles clean for esp32-s3. audited design/: dark.svg and light.svg are the same logo in two color variants, org.png is the dark-text raster. design/ was untracked; adding it now.

**Total time spent: 56m**
