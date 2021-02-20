#include "functions.h"
#include "constants.h"
#include <math.h>

// Declare Volume Variables
int LastVolume, LastChange;


void setup() {
  // **Set PinModes**
  // Transistor Pins
  pinMode(Layer1, OUTPUT);
  pinMode(Layer2, OUTPUT);
  pinMode(Layer3, OUTPUT);
  pinMode(Layer4, OUTPUT);
  pinMode(Layer5, OUTPUT);
  pinMode(Layer6, OUTPUT);

  // Shift Register Pins
  pinMode(ShiftDataPin,  OUTPUT);
  pinMode(ShiftLatchPin, OUTPUT);
  pinMode(ShiftClockPin, OUTPUT);

  // MSGEQ7 Pins
  pinMode(AnalyserReset,  OUTPUT);
  pinMode(AnalyserStrobe, OUTPUT);

  // **Initialize the Volume Variables**
  LastVolume = getVolume();
  LastChange = -1 * VOLUME_LINGERING_TIME - 1;
}


void loop() {
  //Record the Time at Which We Start the Loop
  unsigned long int StartTime = micros();

  //Read Data From the MSGEQ7 Circuit
  int TempSpectrum[7] = {0},
      OutSpectrum[36] = {0};
  getSpectrum(TempSpectrum);
  normSpectrum(TempSpectrum, OutSpectrum);

  // Build the Matrix and Send it to the Cube
  bool OutMatrix[6][6][6] = {0};
  makeSpectrumMatrix(OutMatrix, OutSpectrum);
  showMatrix(OutMatrix, StartTime);


  //Check if the Volume Knob has Changed
  while ( abs(LastVolume - getVolume()) > VOLUME_CHANGE_THRESHOLD || 
          milis() < LastChange + VOLUME_LINGERING_TIME) {
    
    LastVolume = getVolume();
    LastChange = milis();

    bool VolumeMatrix[6][6][6] = {0};
    makeVolumeMatrix(VolumeMatrix, LastVolume);
    showMatrix(VolumeMatrix, StartTime);

    StartTime = micros();
  }
}
