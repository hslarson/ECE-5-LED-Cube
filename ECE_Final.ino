#include <math.h>

#include "constants.h"
#include "multiplexer.h"
#include "msgeq7.h"
#include "volume.h"

// Create Class Objects
Multiplexer   cube;
MSGEQ7        analyzer;
VolumeControl knob;

// Declare Timing Variable
unsigned long int StartTime = micros();

// Declare a function to handle subtasks
void subtasks(bool);


void setup() {
    // **Open the Serial Port**
    if (DEBUG) Serial.begin(9600);

    // **Set PinModes**
    // Transistor Pins
    for (int layer = 0; layer < 6; layer++) {
        pinMode(LAYER_PINS[layer], OUTPUT);
    }

    // Shift Register Pins
    pinMode(ShiftLatchPin, OUTPUT);
    pinMode(ShiftDataPin,  OUTPUT);
    pinMode(ShiftClockPin, OUTPUT);

    // MSGEQ7 Pins
    pinMode(AnalyzerReset, OUTPUT);
    pinMode(AnalyzerStrobe,OUTPUT);
    pinMode(AnalyzerData,  INPUT);

    // **Initialize Volume Class**
    knob.checkVolume(1);
}


void loop() {
    // Reset State Variables
    bool finished_drawing_cube = 0,
         finished_subtask = 0;

    // Reset the subtask handler
    subtasks(true);

    while (!finished_drawing_cube) {
        // Do one subtask before drawing each layer
        if (!finished_subtask) {
            subtasks(false);
            finished_subtask = true;
        }

        // Attempt to show the layers on a preset interval
        else if (abs(micros() - StartTime) / (int)LAYER_SHOW_TIME) {
            StartTime = micros();
            finished_subtask = false;

            if (cube.nextLayer())
                finished_drawing_cube = true;
        }
    }
}


void subtasks (bool reset) {
    static int task = 0;
    static bool mode = MODE_SPECTRUM;

    if (reset) {
        task = 0;
        return;
    }

    switch (task) {

    // Check the state of the volume know
    case 0:
        // Switch into volume mode if there have been changes in the volume knob
        if (knob.checkVolume())
            mode = MODE_VOLUME;
        else
            mode = MODE_SPECTRUM;

        if (DEBUG) {
            Serial.print("Draw Mode: ");
            Serial.print((mode ? "Spectrum\n" : "Volume\n"));
        }
        break;

    // Collect data (if necessary)
    case 1:
        // Read data from the MSGEQ7 circuit
        if (mode == MODE_SPECTRUM)
            analyzer.getSpectrum();

        break;

    // Construct the matrix
    case 2:
        if (mode == MODE_SPECTRUM)
            analyzer.makeSpectrumMatrix();
        else
            knob.makeVolumeMatrix();
        break;

    // Queue the matrix to be shown
    case 3:
        if (mode == MODE_SPECTRUM)
            analyzer.queueMatrix(cube);
        else
            knob.queueMatrix(cube);
        break;
    };

    task++;
    return;
}
