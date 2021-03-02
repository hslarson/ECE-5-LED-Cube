class Multiplexer {
public:
    void setMatrix(const bool[][6][6], bool);
    bool nextLayer();

private:
    bool matrix[6][6][6] = {0};
    bool newMatrix[6][6][6] = {0};
    int  currentLayer = 0, lastLayer = 0;

    int  outputData[6] = {0};
    void constructData(int);
    void sendData();
};

void Multiplexer::setMatrix(const bool inMatrix[][6][6], bool mode = 0) {
    // Mode 0 takes a brand new matrix and queues it to be shown
    if (!mode) {
        memcpy(&newMatrix[0][0][0], &inMatrix[0][0][0], (6*6*6)*sizeof(bool));
    }

    // Mode 1 sets the display matrix to some new matrix (presumably newMatrix)
    else {
        memcpy(&matrix[0][0][0], &inMatrix[0][0][0], (6*6*6)*sizeof(bool));
    }
    
    return;
}

bool Multiplexer::nextLayer() {
    // Build the data array for the current layer
    constructData(currentLayer);

    // Send the data to the shift registers and turn on the current layer
    sendData();

    // Update the state variables and return true if we're returning to the bottom
    lastLayer = currentLayer;
    if (currentLayer == 5) {
        currentLayer = 0;
        setMatrix(newMatrix, 1);
        return true;
    }
    else {
        currentLayer++;
        return false;
    }
}

void Multiplexer::constructData(int layer) {
    // Place the bits of data into the data array based on the pin configuration setting
    bool data[48] = {0};
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 6; c++) {
            data[PIN_CONFIGURATION[r][c] - 1] = matrix[layer][r][c];
        }
    }

    // Convert the binary array we just created into an array of integers
    for (int sr = 0, arr_pos = 0; sr < 6; sr++) {
        // For each byte int the private data array, convert it to an int and save it to the output array
        int out_num = 0;
        for (int bit = 7; bit >= 0; bit--) {
            out_num += data[arr_pos] * pow(2, bit);
            arr_pos++;
        }
        outputData[sr] = out_num;
    }
    return;
}

void Multiplexer::sendData() {
    return;
    /*
    // Send the the data to the shift registers
    digitalWrite(ShiftLatchPin, LOW);
    for (int i = 6; i > 0; i--) {
        SPI.transfer(formatted_data[i]);
    }
    // Update the layer transistors and display the output of the shift registers
    digitalWrite(LAYER_PINS[lastLayer], LOW);
    digitalWrite(ShiftLatchPin, HIGH);
    digitalWrite(LAYER_PINS[currentLayer], HIGH);

    return;
    */
}