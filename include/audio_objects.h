#ifndef _AUDIO_OBJECTS_H_
#define _AUDIO_OBJECTS_H_

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include "eubit.h"

// GUItool: begin automatically generated code
extern AudioSynthSimpleDrum     drumKick;       //xy=227,104
extern AudioSynthSimpleDrum     drumSnare;      //xy=228,145
extern AudioSynthKarplusStrong  string1;        //xy=229,355
extern AudioSynthSimpleDrum     drumHiHat;      //xy=230,187
extern AudioSynthToneSweep      tonesweep1;     //xy=235,472
extern AudioSynthWaveform       waveform1;      //xy=236,410
extern AudioMixer4              mixerDrum;      //xy=501,113
extern AudioMixer4              mixerMelody;    //xy=518,359
extern AudioMixer4              mixerL;         //xy=721,216
extern AudioMixer4              mixerR;         //xy=726,304
extern AudioOutputI2S           i2s1;           //xy=869,268
// AudioConnection          patchCord1(drumKick, 0, mixerDrum, 0);
// AudioConnection          patchCord2(drumSnare, 0, mixerDrum, 1);
// AudioConnection          patchCord3(string1, 0, mixerMelody, 0);
// AudioConnection          patchCord4(drumHiHat, 0, mixerDrum, 2);
// AudioConnection          patchCord5(tonesweep1, 0, mixerMelody, 2);
// AudioConnection          patchCord6(waveform1, 0, mixerMelody, 1);
// AudioConnection          patchCord7(mixerDrum, 0, mixerL, 0);
// AudioConnection          patchCord8(mixerDrum, 0, mixerR, 0);
// AudioConnection          patchCord9(mixerMelody, 0, mixerL, 1);
// AudioConnection          patchCord10(mixerMelody, 0, mixerR, 1);
// AudioConnection          patchCord11(mixerL, 0, i2s1, 0);
// AudioConnection          patchCord12(mixerR, 0, i2s1, 1);
// GUItool: end automatically generated code

extern eubit_seq_t eubitKick;
extern eubit_seq_t eubitSnare;
extern eubit_seq_t eubitHiHat;
extern eubit_seq_t eubitString;
void setup_audio_objects(void);

#endif
