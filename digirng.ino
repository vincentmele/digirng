#include <Crypto.h>
#include <RNG.h>
#include <DigiUSB.h>

#define KEYSIZE 32

void setup() {
  // put your setup code here, to run once:
  RNG.begin("NyseionRNG");
  DigiUSB.begin();
}

byte key[KEYSIZE];
bool haveKeys = false;
  
void loop() {
  // put your main code here, to run repeatedly:
  RNG.loop();
  if (DigiUSB.available() && RNG.available(sizeof(key))) {
    RNG.rand(key, sizeof(key));
    for (int i = 0; i < sizeof(key); i++) {
       DigiUSB.write((char)key[i]);
    }
  }
  DigiUSB.delay(10);
}

