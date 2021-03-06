class VolumeControl {
public:
    static bool checkVolume(bool);
    static void makeVolumeMatrix();
    static void queueMatrix(Multiplexer&);

private:
    static void getVolume();

    static double rawVolume;
    static short currentVolume, lastVolume;
    static bool recentChange; 
    static unsigned long lastChange;
    static bool volumeMatrix[6][6][6];
};

double VolumeControl::rawVolume = -1;
short VolumeControl::currentVolume, VolumeControl::lastVolume;
bool VolumeControl::recentChange = false;
unsigned long VolumeControl::lastChange;
bool VolumeControl::volumeMatrix[6][6][6] = {{{0}}};


bool VolumeControl::checkVolume(bool init = false) {
    // Get the current volume
    getVolume();

    if (init) {
      lastVolume = currentVolume;
      return 0;
    }

    // Check if the volume has changed beyond the threshold
    if ( abs(lastVolume - currentVolume) > VOLUME_CHANGE_THRESHOLD ) {
        lastVolume = currentVolume;
        lastChange = millis();
        recentChange = true;
        return 1;
    }

    // Check if we're within the volume lingering period
    if (recentChange && !(abs(millis() - lastChange) / VOLUME_LINGERING_TIME))
        return 1; 
    else
        recentChange = false;

    return 0;
}

void VolumeControl::getVolume() {
    // Read the value of the volume knob
    short knob_reading = analogRead(VolumePin);

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
    short num_bars = currentVolume;
    bool break_all = 0;

    // Continue lighting rows until num bars = 0
    for (short col = 5; col >= 0 && !break_all; col--) {
        for (short layer = 0; layer < 6 && !break_all; layer++) {
            
            for(short row = 0; row < 6; row++) {
                volumeMatrix[layer][row][col] = true;
            }

            if (--num_bars <= 0) {
                break_all = true;
            }
        }
    }

    return;
}

void VolumeControl::queueMatrix(Multiplexer &output) {
    output.setMatrix(volumeMatrix, 0);
    return;
}
