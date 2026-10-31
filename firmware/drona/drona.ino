// drona - smart chess board firmware
// esp32 + 64 ws2812 + hall sensors via mux
// hackclub stardance 2026

#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    64
#define MUX_S0      16
#define MUX_S1      17
#define MUX_S2      18
#define MUX_S3      19
#define MUX_SIG     34   // adc input

CRGB leds[NUM_LEDS];

enum State { IDLE, LIFTED, PLACED };
State state = IDLE;

int lastSquare = -1;

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(60);

  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
  pinMode(MUX_S3, OUTPUT);

  // all leds off on boot
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  Serial.println("drona boot ok");
}

// read one channel of the mux
int readMux(int ch) {
  digitalWrite(MUX_S0, ch & 1);
  digitalWrite(MUX_S1, (ch >> 1) & 1);
  digitalWrite(MUX_S2, (ch >> 2) & 1);
  digitalWrite(MUX_S3, (ch >> 3) & 1);
  delayMicroseconds(50);
  return analogRead(MUX_SIG);
}

// scan all 64 hall sensors, return square index with piece present (or -1)
int scanBoard() {
  for (int i = 0; i < 64; i++) {
    int v = readMux(i % 16);  // todo: handle 2 muxes / row select
    if (v < 2000) return i;   // threshold TBD, calibrate on real board
  }
  return -1;
}

void loop() {
  int sq = scanBoard();

  if (state == IDLE && sq != -1) {
    lastSquare = sq;
    leds[sq] = CRGB::Red;
    FastLED.show();
    state = LIFTED;
    Serial.print("lifted: "); Serial.println(sq);
  } else if (state == LIFTED && sq == -1) {
    // piece put back or moved; for now just reset
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    state = IDLE;
    Serial.println("idle");
  }

  delay(50);
}
```

Wait, the scanBoard only uses one mux with 16 channels but 64 squares. This is a prototype sketch with a todo. That's realistic for a first sketch. Good.

Let me also create docs/bringup.md and docs/photos/.gitkeep.<|end|><|start|> assistant to=write<|channel|>analysis <|constrain|>xml<|message|><rfl:parameter name="path">
D:\Projects\drona\docs\bringup.md