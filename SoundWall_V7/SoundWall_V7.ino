


float levels[2][16];



#include "SetupFFT.h"
#include "ReadFFT.h"

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Initializing");
  SetupFFT();  
}

void loop() {
   if (ReadFFT()) {    // reads left and right channles, returns true if they were read and false if the buffer was not ready to read.  
                      // runs in 6 micros if there is something in the buffer and even less if the buffer is not ready to read
  for (int i = 0; i <= 15; i++) {
    Serial.printf("%.3f:%.3f,", levels[L][i],levels[R][i]);
      }
  }
}
