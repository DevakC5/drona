// drona - smart chess board firmware
// esp32-s3 + 64 ws2812 + a3144 halls via 4x mcp23s17 (spi)
// hackclub stardance 2026
//
// led index -> square mapping: snake order
// row0: 0..7  (left->right)
// row1: 15..8 (right->left)
// ... figure out the rest before wiring or cry later
// brightness capped ~30% (75/255) so 5v rail survives
// a3144 is open-collector: magnet present = pin LOW (active low)

#include <SPI.h>
#include <FastLED.h>

#define LED_PIN     14   // safe gpio on esp32-s3 (not a strapping pin)
#define NUM_LEDS    64
#define CS_PIN      10   // shared cs for all 4 mcp23s17
#define SCK_PIN     12
#define MISO_PIN    13
#define MOSI_PIN    11

// mcp23s17 registers (bank 0)
#define MCP_IODIRA  0x00
#define MCP_IODIRB  0x01
#define MCP_IOCON   0x0A
#define MCP_GPPUA   0x0C
#define MCP_GPPUB   0x0D
#define MCP_GPIOA   0x12
#define MCP_GPIOB   0x13

CRGB leds[NUM_LEDS];

enum State { IDLE, LIFTED, PLACED };
State state = IDLE;

int lastSquare = -1;

// --- mcp23s17 helpers (spi, hardware addressing) ---

void mcpWrite(uint8_t dev, uint8_t reg, uint8_t val) {
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x40 | (dev << 1)); // write opcode + hw address
  SPI.transfer(reg);
  SPI.transfer(val);
  digitalWrite(CS_PIN, HIGH);
  SPI.endTransaction();
}

uint8_t mcpRead(uint8_t dev, uint8_t reg) {
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(CS_PIN, LOW);
  SPI.transfer(0x41 | (dev << 1)); // read opcode + hw address
  SPI.transfer(reg);
  uint8_t val = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  SPI.endTransaction();
  return val;
}

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(75); // ~30% cap so 5v rail survives

  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  SPI.begin(SCK_PIN, MISO_PIN, MOSI_PIN, CS_PIN);

  // enable hardware addressing on all devices at once (haen=0 => broadcast)
  mcpWrite(0, MCP_IOCON, 0x08);

  // configure all 4 expanders: inputs with pullups (a3144 open-collector)
  for (uint8_t dev = 0; dev < 4; dev++) {
    mcpWrite(dev, MCP_IODIRA, 0xFF);
    mcpWrite(dev, MCP_IODIRB, 0xFF);
    mcpWrite(dev, MCP_GPPUA,  0xFF);
    mcpWrite(dev, MCP_GPPUB,  0xFF);
  }

  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();

  Serial.println("drona boot ok");
}

// scan all 64 sensors; return first occupied square index, or -1
// device 0 = squares 0-15, device 1 = 16-31, ...
// port a = low 8, port b = high 8; bit low (active low) = piece present
int scanBoard() {
  for (uint8_t dev = 0; dev < 4; dev++) {
    uint8_t a = mcpRead(dev, MCP_GPIOA);
    uint8_t b = mcpRead(dev, MCP_GPIOB);
    for (uint8_t i = 0; i < 8; i++) {
      if (!((a >> i) & 1)) return dev * 16 + i;
      if (!((b >> i) & 1)) return dev * 16 + 8 + i;
    }
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
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    state = IDLE;
    Serial.println("idle");
  }

  delay(50);
}
