class Multiplexer {
public:
    void setMatrix(const bool[][6][6], bool);
    bool nextLayer();

private:
    bool matrix[6][6][6] = {0};
    bool newMatrix[6][6][6] = {0};
    int  currentLayer = 0, lastLayer = 0;

    bool data[48] = {0};
    int  outputData[6] = {0};
    void constructData(int layer);
    void sendData();
    void bin2int();
};

void Multiplexer::setMatrix(const bool inMatrix[][6][6], bool mode = 0) {
    for (int l = 0; l < 6; l++) {
        for (int r = 0; r < 6; r++) {
            for (int c = 0; c < 6; c++) {
                // Mode 0 takes a brand new matrix and queues it to be shown
                if (!mode)
                    newMatrix[l][r][c] = inMatrix[l][r][c];
                // Mode 1 sets the display matrix to some new matrix (presumably newMatrix)
                else
                    matrix[l][r][c] = inMatrix[l][r][c];
            }
        }
    }
}

bool Multiplexer::nextLayer() {
    // Build the data array for the current layer
    constructData(currentLayer);
    bin2int();

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
    // Save the 36 bits of real data to a temporary array based on the pin configuration setting
    bool temp_data[36] = {0};
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 6; c++) {
            temp_data[PIN_CONFIGURATION[r][c] - 1] = matrix[layer][r][c];
        }
    }

    // Create a 48 bit array from the 36 bit array based on shift register config
    int temp_arr_pos = 0, out_arr_pos = 0;
    for (int sr = 0; sr < 6; sr++) {
        for (int bit = 0; bit < 8; bit++) {
            if (SHIFT_REGISTER_CONFIG[bit]) {
                data[out_arr_pos + bit] = temp_data[temp_arr_pos];
                temp_arr_pos++;
            }
        }
        out_arr_pos += 8;
    }
    return;
}

void Multiplexer::bin2int() {
    for (int sr = 0, arr_pos = 0; sr < 6; sr++) {
        // For each byte int the private data array, convert it to an int and save it to the output array
        int out_num = 0;
        for (int bit = 7; bit >= 0; bit--) {
            out_num += data[arr_pos] * pow(2, bit);
            arr_pos++;
        }
        outputData[sr] = out_num;
    }
}

void Multiplexer::sendData() {
    return;
    /*
    // Send the the data to the shift registers
    digitalWrite(ShiftLatchPin, LOW);
    for (int i = 0; i < 6; i++) {
        SPI.transfer(formatted_data[i]);
    }
    // Update the layer transistors and display the output of the shift registers
    digitalWrite(LAYER_PINS[lastLayer], LOW);
    digitalWrite(ShiftLatchPin, HIGH);
    digitalWrite(LAYER_PINS[currentLayer], HIGH);

    return;
    */
}