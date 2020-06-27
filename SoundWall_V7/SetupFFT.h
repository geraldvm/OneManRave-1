#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "noiseFloor.h"

AudioInputI2S            i2s1;           //xy=246,249
AudioMixer4              mixer1;         //xy=538,168
AudioMixer4              mixer2;         //xy=538,168
AudioAnalyzeFFT1024      Lfft;        //xy=843,366
AudioAnalyzeFFT1024      Rfft;        //xy=843,366

AudioConnection          patchCord1(i2s1, 0, mixer1, 0);
AudioConnection          patchCord2(i2s1, 1, mixer2, 0);

AudioConnection          patchCord3(mixer1, Lfft);
AudioConnection          patchCord4(mixer2, Rfft);
AudioControlSGTL5000     audioShield;    //xy=493,607

const int myInput = AUDIO_INPUT_LINEIN;
bool readFFT = false;


void SetupFFT(){

  AudioMemory(24);
  // Enable the audio shield and set the output volume.
  audioShield.enable();
  audioShield.inputSelect(myInput);
  audioShield.volume(2.5);
  mixer1.gain(0, 2.5);
  mixer2.gain(0, 2.5);
  Lfft.windowFunction(AudioWindowHanning1024);
  Rfft.windowFunction(AudioWindowHanning1024);
}
