#include <TheThingsNetwork.h>
#include <TheThingsMessage.h>

// Set your AppEUI and AppKey
const char *appEui = "70B3D57ED003E946";
const char *appKey = "7496BDF1964B5928E5A83533499528A9";

#define loraSerial Serial3
#define debugSerial Serial
#define loraResetPin 40


// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_US915

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup()
{
  debugSerial.begin(9600);
  loraSerial.begin(57600);
    
  pinMode(loraResetPin, OUTPUT);
  digitalWrite(loraResetPin, HIGH);
  delay(2000);
  digitalWrite(loraResetPin, LOW);

  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
}

void loop()
{
  debugSerial.println("-- LOOP");

  String payload = "T_35_C;H_95_%";
  byte buffer[payload.length() + 1];

  payload.getBytes(buffer, payload.length() + 1);

  // Send it off
  ttn.sendBytes(buffer, sizeof(buffer));

  delay(10000);
}
