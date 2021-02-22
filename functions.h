void showMatrix(const bool matrix[][6][6], unsigned long int startTime) {
  return;
}

void getSpectrum(int spectrum[]) {
  return;
}




// !!! FOR DEBUGGING ONLY !!!
int analogRead(int pin) {
  return 1024;
}



int getVolume() {
  // Read the value of the volume knob
  int knob_reading = analogRead(VolumePin) - VOLUME_MIN_READING;
  
  // We should probably make a state variable to make to sure the value of the knob isn't noisy

  // Normalize the reading and return
  return round((double)knob_reading / VOLUME_INCREMENT_AMOUNT);
}


void normSpectrum(int InSpectrum[], int OutSpectrum[]) {
    OutSpectrum[0] = InSpectrum[0];
    
    for (int arr_index = 1, segment = 5, data_index = 0; arr_index < 36; arr_index++) {
        // If we've calculated all of the filler channels between two channels, reset and move to the next two channels
        if (segment == 0) {
            segment = NUM_FILLER_CHANNELS;
            OutSpectrum[arr_index] = InSpectrum[data_index + 1];
            data_index++;
        }
        // Otherwise, calculate the filler channel
        else {
            OutSpectrum[arr_index] = round(((float)segment / (7 - 1))*InSpectrum[data_index] + 
                                     (1.0 - (float)segment / (7 - 1))*InSpectrum[data_index + 1]);
            segment--;
        }
    }
  return;
}


void makeSpectrumMatrix(bool matrix[][6][6], int spectrum[]) {
  for (int i = 0; i < 36; i++) {
    // Find the mathing index in the freq placement array
    int row, col;
    bool break_all(false);
    for (row = 0; !break_all && row < 6; row++) {
      for (col = 0; !break_all && col < 6; col++) {
        if (FREQ_PLACEMENT[row][col] == i + 1) {
          break_all = true;
          row--; col--;
        }
      }
    }
    // Turn on led's until the freq threshold is not met
    for (int layer = 0; layer < 6; layer++) {
      if (spectrum[i] >= FREQ_THRESHOLDS[layer])
        matrix[layer][row][col] = true;
      else
        break;
    }
  }
  return;
}


void makeVolumeMatrix(bool matrix[][6][6], int volume) {
  return;
}
