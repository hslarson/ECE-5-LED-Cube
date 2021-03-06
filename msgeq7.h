class MSGEQ7 {
public:
    static void getSpectrum();
    static void makeSpectrumMatrix();
    static void queueMatrix(Multiplexer&);
private:
    static void normSpectrum();
    static short averageReading;

    static short rawReadings[7];
    static short normedReadings[36];
    static bool spectrumMatrix[6][6][6];
};

short MSGEQ7::averageReading = -1;
short MSGEQ7::rawReadings[7] = {0};
short MSGEQ7::normedReadings[36] = {0};
bool MSGEQ7::spectrumMatrix[6][6][6] = {{{0}}};

void MSGEQ7::getSpectrum() {
    short tempReadings[7] = {0};

    // Reset the Chip
    digitalWrite(AnalyserReset, HIGH);
    delayMicroseconds(100);
    digitalWrite(AnalyserReset, LOW);
    
    // Read Data from the Chip
    for (short x = 0; x < 7; x++){
        digitalWrite(AnalyserStrobe, LOW);
        
        // Allow the Output to Settle
        delayMicroseconds(35);
        
        // Save reading
        tempReadings[x] = analogRead(AnalyserData);
        
        digitalWrite(AnalyserStrobe, HIGH);
        
        // Wait Before Strobing Again (unless this is the last reading)
        if (x < 6)
          delayMicroseconds(100);
    }
    
    // Apply the rolling average filter to the data we colloected
    for (short i = 0; i < 7; i++) {
        rawReadings[i] = round((double)(FREQ_AVERAGING_POINTS - 1) / FREQ_AVERAGING_POINTS * rawReadings[i]
                             + (1.0 / FREQ_AVERAGING_POINTS) * tempReadings[i]);
    }

    if (DEBUG) {
      /*
      for (int temp : tempReadings) {
        Serial.print(temp);
        Serial.print(' ');
      } Serial.println("");
      
      for (int raw : rawReadings) {
        Serial.print(raw);
        Serial.print(' ');
      } Serial.println("\n");
      */
    }

    // Calculate the average of the readings we just found
    short sum = 0;
    for (short num : rawReadings) {
        sum += num;
    }
    averageReading = round((double)sum / 7);

    return;
}

void MSGEQ7::normSpectrum() {
    // Distribute the raw readings into the normed array
    for (short i = 0; i < 7; i++) {
        normedReadings[PRIMARY_FREQ_LOCATIONS[i]] = rawReadings[i];
    }

    short data_pos = 0;
    short left_index, right_index;
    short left_data, right_data;
    while (data_pos < 6) {
        // Set the left and right indicies and get the array values 
        left_index  = PRIMARY_FREQ_LOCATIONS_ASCENDING[data_pos];
        right_index = PRIMARY_FREQ_LOCATIONS_ASCENDING[data_pos + 1];

        left_data  = normedReadings[left_index];
        right_data = normedReadings[right_index];

        // Create a function in the form y=mx+b that inperpolates the data between the left and right indices
        double m = (double)(right_data - left_data) / (right_index - left_index);
        double b = (-m * left_index) + left_data;

        // Perform the interpolation
        for (short x = left_index + 1; x < right_index; x++) {
            normedReadings[x] = round( m*x+b );
        }

        // Move to the next set of points
        data_pos++;
    }
    
    return;
}

void MSGEQ7::makeSpectrumMatrix() {
    // We must normalize the raw readings before making the spectrum matrix
    normSpectrum();

    // For each row/column in the freq_placement array calculate the number of LED's to 
    // turn on based on the specified index in the normalized array
    for (short row = 0; row < 6; row++) {
        for (short col = 0; col < 6; col++) {
            short data_index = FREQ_PLACEMENT[row][col], reading;

            // Handle the special case where the index is less than or equal to 0
            if (data_index < 0)
                reading = rawReadings[-1*data_index - 1];
            else if (data_index == 0)
                reading = averageReading;
            else
                reading = normedReadings[data_index - 1];

            // Turn on LED's until the freq threshold is not met
            for (short layer = 0; layer < 6; layer++) {
                if (reading >= FREQ_THRESHOLDS[layer])
                    spectrumMatrix[layer][row][col] = true;
                else
                    break;
            }
        }
    }

    return;
}

void MSGEQ7::queueMatrix(Multiplexer &output) {    
    output.setMatrix(spectrumMatrix, 0);
    return;
}
