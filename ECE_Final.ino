#include <math.h>
#include <SPI.h>

#include "constants.h"
#include "multiplexer.h"
#include "msgeq7.h"
#include "volume.h"

// Create Class Objects
Multiplexer   cube;
MSGEQ7        analyser;
VolumeControl volume;

// Declare Timing Variable
unsigned long int StartTime = micros();

// Declare a function to handle subtasks
bool subtasks(bool);

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
    pinMode(ShiftLatchPin, OUTPUT);

    // MSGEQ7 Pins
    pinMode(AnalyserReset,  OUTPUT);
    pinMode(AnalyserStrobe, OUTPUT);

    // **Initialize the SPI Bus**
    SPI.begin();
    SPI.beginTransaction(SPISettings(8000000 /* 8MHZ */, LSBFIRST, SPI_MODE0));
}


void loop() {
    // Reset State Variables
    bool finished_drawing_cube = 0,
         finished_subtasks = 0;

    // Reset the subtask handler
    subtasks(true);

    while (!finished_drawing_cube) {
        if ((int)abs(micros() - StartTime) / (int)LAYER_SHOW_TIME) {
            if (cube.nextLayer())
                finished_drawing_cube = true;
        }
        else if (!finished_subtasks && subtasks(false)) {
            finished_subtasks = true;
        }
    }
}

bool subtasks (bool reset) {
    static int task = 0;

    if (reset) {
        task = 0;
        return false;
    }

    switch (task) {
    case 0:
        analyser.getSpectrum();
        break;
    case 1:
        analyser.makeSpectrumMatrix();
        break;
    case 2:
        if (volume.checkVolume())
            volume.showVolume(cube);
        break;

    default:
        return true;
    };

    task++;
    return false;
}