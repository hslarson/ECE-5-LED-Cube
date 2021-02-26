class VolumeControl {
public:
    bool checkVolume();
    void showVolume(Multiplexer);
private:
    int getVolume();
    void makeVolumeMatrix();

    int LastVolume = 0, LastChange = millis();
    bool volumeMatrix[6][6][6] = {0};
};

bool VolumeControl::checkVolume() {

    return 0;
}

int VolumeControl::getVolume() {
    // Read the value of the volume knob
    //int knob_reading = analogRead(VolumePin) - VOLUME_MIN_READING;
    int knob_reading = 1000;

    // We should probably make a state variable to make to sure the value of the knob isn't noisy

    // Normalize the reading and return
    int normed_reading = round((double)knob_reading / VOLUME_INCREMENT_AMOUNT);
    return round((float)(LastVolume + normed_reading) / 2);
}

void VolumeControl::makeVolumeMatrix() {

    return;
}