#include <HardwareSerial.h>

HardwareSerial LINSerial(1);
const long BAUD_RATE = 19200;
const int RX_PIN = 8;
const int TX_PIN = 9;

const int MAX_DATA_BYTES = 8;

enum SnifferState {
  WAITING_FOR_ID,
  READING_DATA,
  READING_CHECKSUM
};

SnifferState currentState = WAITING_FOR_ID;
byte currentID;
byte dataBytes[MAX_DATA_BYTES];
int dataByteCount = 0;
byte checksum;

byte messageLengths[64] = {0};

byte calculateChecksum(byte id, const byte* data, int length) {
  unsigned int sum = 0;
  sum += id;
  for (int i = 0; i < length; i++) {
    sum += data[i];
  }
  return (~(sum & 0xFF));
}

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
  Serial.println("--- LIN Bus Smart Sniffer (XIAO ESP32-C3) ---");
  Serial.print("Monitoring LIN bus at ");
  Serial.print(BAUD_RATE);
  Serial.println(" bps.");
  Serial.print("Using Hardware Serial on TX:");
  Serial.print(TX_PIN);
  Serial.print(", RX:");
  Serial.print(RX_PIN);
  Serial.println(".");

  LINSerial.begin(BAUD_RATE, SERIAL_8N1, TX_PIN, RX_PIN, true);
  delay(100);

  Serial.println("\nWaiting for LIN messages...");
  Serial.println("--------------------------------------------------");
}

void loop() {
  if (LINSerial.available()) {
    byte incomingByte = LINSerial.read();

    switch (currentState) {
      case WAITING_FOR_ID:
        currentID = incomingByte;
        dataByteCount = 0;
        currentState = READING_DATA;
        
        Serial.printf("\nID: %02X, Data: ", currentID);
        break;

      case READING_DATA:
        dataBytes[dataByteCount] = incomingByte;
        Serial.printf("%02X ", incomingByte);
        dataByteCount++;

        if (dataByteCount >= MAX_DATA_BYTES) {
          currentState = READING_CHECKSUM;
        }
        break;

      case READING_CHECKSUM:
        checksum = incomingByte;
        Serial.printf("Checksum: %02X ", checksum);
        
        currentState = WAITING_FOR_ID;
        break;
    }
  }
}
