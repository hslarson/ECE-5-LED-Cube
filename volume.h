class VolumeControl {
public:
    VolumeControl();
    bool checkVolume();
    void makeVolumeMatrix();
    void queueMatrix(Multiplexer);

private:
    void getVolume();

    double rawVolume = -1;
    int currentVolume, lastVolume;
    bool recentChange = false; unsigned long lastChange;
    bool volumeMatrix[6][6][6] = {0};
};

// Use a class constructor to initialize lastVolume
VolumeControl::VolumeControl() {
    getVolume();
    lastVolume = currentVolume;
}

bool VolumeControl::checkVolume() {
    // Get the current volume
    getVolume();

    // Check if the volume has changed beyond the threshold
    if ( abs(lastVolume - currentVolume) > VOLUME_CHANGE_THRESHOLD) {
        lastVolume = currentVolume;
        lastChange = millis();
        recentChange = true;
        return 1;
    }

    // Check if we're within the volume lingering period
    if (recentChange && !((int)abs(millis() - lastChange) / VOLUME_LINGERING_TIME))
        return 1; 
    else
        recentChange = false;

    return 0;
}

void VolumeControl::getVolume() {
    // Read the value of the volume knob
    int knob_reading = analogRead(VolumePin);

    // Apply the rolling average filter
    if (rawVolume < 0)
        rawVolume = knob_reading;
    else 
        rawVolume = (double)(VOLUME_AVERAGING_POINTS - 1) / VOLUME_AVERAGING_POINTS * knob_reading
                      + (1.0 / VOLUME_AVERAGING_POINTS) * rawVolume;

    // Normalize the reading
    currentVolume = round(rawVolume / VOLUME_INCREMENT_AMOUNT);

    return;
}

void VolumeControl::makeVolumeMatrix() {
    int num_bars = currentVolume;
    bool break_all = 0;

    // Continue lighting rows until num bars = 0
    for (int col = 5; col >= 0 && !break_all; col--) {
        for (int layer = 0; layer < 6 && !break_all; layer++) {
            
            for(int row = 0; row < 6; row++) {
                volumeMatrix[layer][row][col] = true;
            }

            if (--num_bars <= 0) {
                break_all = true;
            }
        }
    }

    return;
}

void VolumeControl::queueMatrix(Multiplexer output) {
    output.setMatrix(volumeMatrix, 0);
    return;
}
