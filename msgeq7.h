class MSGEQ7 {
public:
    void getSpectrum();
    void makeSpectrumMatrix();
    void queueMatrix(Multiplexer);
private:
    void normSpectrum();

    int rawReadings[7] = {0};
    int normedReadings[36] = {0};
    bool spectrumMatrix[6][6][6] = {0};
};

void MSGEQ7::getSpectrum() {
    int temp[] = {0, 100, 200, 300, 400, 500, 600};
    for (int i = 0; i < 7; i++) {
        rawReadings[i] = temp[i];
    }
    return;
}

void MSGEQ7::normSpectrum() {
    normedReadings[0] = rawReadings[0];

    for (int arr_index = 1, segment = 5, data_index = 0; arr_index < 36; arr_index++) {
        // If we've calculated all of the filler channels between two channels, reset and move to the next two channels
        if (segment == 0) {
            segment = NUM_FILLER_CHANNELS;
            normedReadings[arr_index] = rawReadings[data_index + 1];
            data_index++;
        }
        // Otherwise, calculate the filler channel
        else {
            normedReadings[arr_index] = round(((float)segment / (7 - 1))*rawReadings[data_index] +
                                              (1.0 - (float)segment / (7 - 1))*rawReadings[data_index + 1]);
            segment--;
        }
    }
    return;
}

void MSGEQ7::makeSpectrumMatrix() {
    // We must normalize the raw readings before making the spectrum matrix
    normSpectrum();

    for (int i = 0; i < 36; i++) {
        // Find the mathing index in the freq placement array
        int row, col;
        bool break_all(false);
        for (row = 0; !break_all && row < 6; row++) {
            for (col = 0; !break_all && col < 6; col++) {
                if (FREQ_PLACEMENT[row][col] == i + 1) {
                    break_all = true;
                    row--;
                    col--;
                }
            }
        }
        // Turn on led's until the freq threshold is not met
        for (int layer = 0; layer < 6; layer++) {
            if (normedReadings[i] >= FREQ_THRESHOLDS[layer])
                spectrumMatrix[layer][row][col] = true;
            else
                break;
        }
    }
    return;
}

void MSGEQ7::queueMatrix(Multiplexer output) {
    output.setMatrix(spectrumMatrix);
    return;
}