#include <SPI.h>

// Define pin for Chip Select (CS)
const int CS_PIN = 10;
const int EN_PIN = 4;

// 0x30 0x00 is the command word for reading Sensor ID, used for detecting if the Acconeer is present
const uint8_t READ_ID_COMMAND[] = {0x30, 0x00};  // Replace with actual ID read command
const uint8_t RESPONSE_LENGTH = 4;  // Adjust this to match the expected length of the response

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  
  // Initialize SPI
  SPI.begin();
  
  // Configure Chip Select pin as OUTPUT
  pinMode(CS_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  
  // Set CS pin high to start communication (idle state)
  digitalWrite(CS_PIN, HIGH);
  digitalWrite(EN_PIN, HIGH);
  
  // Setup SPI settings (Mode 0, 1 MHz clock speed, MSB first)
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));

  // Give sensor time to initialize
  delay(100);
  
  // Attempt to read sensor ID
  readSensorID();
  digitalWrite(EN_PIN, LOW);
}

void readSensorID() {
  byte response[RESPONSE_LENGTH] = {0};

  // Start SPI communication (CS Low)
  digitalWrite(CS_PIN, LOW);
  
  // Send command to read ID
  for (int i = 0; i < sizeof(READ_ID_COMMAND); i++) {
    SPI.transfer(READ_ID_COMMAND[i]);
  }
  
  // Receive the response (ID)
  for (int i = 0; i < RESPONSE_LENGTH; i++) {
    response[i] = SPI.transfer(0x00);  // Send dummy byte to clock out the response
  }

  // End SPI communication (CS High)
  digitalWrite(CS_PIN, HIGH);
  
  // Print the received ID
  Serial.print("Sensor ID: ");
  for (int i = 0; i < RESPONSE_LENGTH; i++) {
    Serial.print("0x");
    Serial.print(response[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}


void loop() {
  // Do nothing in the loop for now
}

