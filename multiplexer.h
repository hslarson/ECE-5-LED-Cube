class Multiplexer {
public:
    static void setMatrix(bool[][6][6], bool);
    static bool nextLayer();

private:
    static bool matrix[6][6][6];
    static bool newMatrix[6][6][6];
    static short currentLayer, lastLayer;

    static short outputData[6];
    static void constructData(int);
    static void sendToCube();
};

bool Multiplexer::matrix[6][6][6] = {{{0}}};
bool Multiplexer::newMatrix[6][6][6] = {{{0}}};
short Multiplexer::currentLayer = 0, Multiplexer::lastLayer = 0;
short Multiplexer::outputData[6] = {0};


void Multiplexer::setMatrix(bool inMatrix[][6][6], bool mode) {

    // Mode 0 takes a brand new matrix and queues it to be shown
    if (!mode)
      memcpy(&newMatrix[0][0][0], &inMatrix[0][0][0], (6*6*6)*sizeof(bool));
    
    // Mode 1 sets the display matrix to some new matrix (presumably newMatrix)
    else
      memcpy(&matrix[0][0][0], &inMatrix[0][0][0], (6*6*6)*sizeof(bool));
    
    return;
}

bool Multiplexer::nextLayer() {

    // Build the data array for the current layer
    constructData(currentLayer);

    if (DEBUG) {
      Serial.print("Layer ");
      Serial.print(currentLayer);
      Serial.print(": ");

      for (int num : outputData) {
        Serial.print(num);
        Serial.print(" ");
      }
      Serial.println("");
    }

    // Send the data to the shift registers and turn on the current layer
    sendToCube();

    // Update the state variables and return true if we're returning to the bottom
    lastLayer = currentLayer;
    if (currentLayer == 5) {
        currentLayer = 0;
        setMatrix(newMatrix, true);
        return true;
    }
    else {
        currentLayer++;
        return false;
    }
}

void Multiplexer::constructData(int layer) {
    // Place the bits of data into the data array based on the pin configuration setting
    bool temp_data[48] = {0};
    for (short r = 0; r < 6; r++) {
        for (short c = 0; c < 6; c++) {
            temp_data[PIN_CONFIGURATION[r][c] - 1] = matrix[layer][r][c];
        }
    }

    // Convert the binary array we just created into an array of integers
    for (short sr = 0, arr_pos = 0; sr < 6; sr++) {
        // For each byte int the private data array, convert it to an int and save it to the output array
        short out_num = 0;
        for (int b = 7; b >= 0; b--) {
            out_num += temp_data[arr_pos] * pow(2, b);
            arr_pos++;
        }
        outputData[sr] = out_num;
    }

    return;
}

void Multiplexer::sendToCube() {
    // Send the the data to the shift registers
    digitalWrite(ShiftLatchPin, LOW);
    for (short i = 6; i > 0; i--) {
        SPI.transfer(outputData[i]);
    }
    // Update the layer transistors and display the output of the shift registers
    digitalWrite(LAYER_PINS[lastLayer], LOW);
    digitalWrite(ShiftLatchPin, HIGH);
    digitalWrite(LAYER_PINS[currentLayer], HIGH);

    return;
}
