#include <DigiKeyboard.h>
#include <Entropy.h>
#include <SpritzCipher.h>

#define DEBUG 0
#define KEY_SIZE 16

uint32_t seed = 0;
uint32_t old_seed = 1;

uint8_t key[KEY_SIZE]; 

spritz_ctx sc;

void setup() {
  // put your setup code here, to run once:
  #ifdef DEBUG
  DigiKeyboard.sendKeyStroke(0);
  DigiKeyboard.print("START!");
  #endif
  Entropy.initialize();
  
  byte data[3] = {'a','b','c'};
  spritz_setup(&sc, data,sizeof(data));
  addEntropyToSpritz(128);
  #ifdef DEBUG
  DigiKeyboard.println("STARTED!");
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:

  addEntropyToSpritz(1);
  DigiKeyboard.sendKeyStroke(0); 

    unsigned char buf[4];
    for (int j=0; j < 256; j++) {
        uint32_t x = spritz_random32(&sc);
        buf[0] = x >> 24;
        buf[1] = x >> 16;
        buf[2] = x >> 8;
        buf[3] = x;
      for (int i = 0; i < 4; i++) {
        if (isprint(buf[i]))
          DigiKeyboard.print(buf[i]);
      }
    }
}

void addEntropyToSpritz(int amount) {
  for (int j = 0; j < amount % KEY_SIZE + 1; j++) {
    for (int i = 0; i < KEY_SIZE; i++) {
      key[i] = Entropy.randomByte();
    }
    spritz_add_entropy(&sc,key,sizeof(key));
  }
}

