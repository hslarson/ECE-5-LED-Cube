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
    for (int layer = 0; layer < 6; layer++) {
        pinMode(LAYER_PINS[layer], OUTPUT);
    }

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

    while (!finished_drawing_cube || !finished_subtasks) {
		// If the subtasks haven't been completed, do one
		if (!finished_subtasks) {
			if (subtasks(false))
				finished_subtasks = true;

			// If we're waiting on the subtasks to start a new iteration, don't bother checking the timer for the layers
			if (finished_drawing_cube)
				continue;
			
		}
		// Try to show the layers on a preset interval
        else if ((int)abs(micros() - StartTime) / (int)LAYER_SHOW_TIME) {
            if (cube.nextLayer())
                finished_drawing_cube = true;
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
		// Handle any changes in the volume knob
        if (volume.checkVolume())
            volume.showVolume(cube);
        break;
    case 1:
		// Read data from the MSGEQ7 circuit
        analyser.getSpectrum();
        break;
    case 2:
		// Output the spectrum data to the cube
        analyser.makeSpectrumMatrix();
        analyser.queueMatrix(cube);
        break;

	// Return true if all tasks have been completed
    default:
        return true;
    };

    task++;
    return false;
}