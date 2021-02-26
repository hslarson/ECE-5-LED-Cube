#ifndef constants
#define constants


/*** PIN CONSTANTS ***/
// Transistor Pins
const int Layer1 = 2,
          Layer2 = 3,
          Layer3 = 4,
          Layer4 = 5,
          Layer5 = 6,
          Layer6 = 7;

// Shift Register Pins
// (Since we're using the SPI bus, MOSI(Pin 11) and SCK(Pin 13) correspond to data and clock,  respectively)
const int ShiftLatchPin = 10;

// MSGEQ7 Pins
const int AnalyserData   = 14, //A0
          AnalyserReset  = 8,
          AnalyserStrobe = 9;

// Volume Knob Pin
const int VolumePin = 15; //A1


/*** DISPLAY CONSTANTS ***/
/*
  How to set PIN_CONFIGURATION

  Transistor Array 1:  Transistor Array 2:  Transistor Array 3:
  Out 1: 1             Out 1: 7             Out 1: 13
  Out 2: 2             Out 2: 8             Out 2: 14
  Out 3: 3             Out 3: 9             Out 3: 15
  Out 4: 4             Out 4: 10            Out 4: 16
  Out 5: 5             Out 5: 11            Out 5: 17
  Out 6: 6             Out 6: 12            Out 6: 18

  Transistor Array 4:  Transistor Array 5:  Transistor Array 6:
  Out 1: 19            Out 1: 25            Out 1: 31
  Out 2: 20            Out 2: 26            Out 2: 32
  Out 3: 21            Out 3: 27            Out 3: 33
  Out 4: 22            Out 4: 28            Out 4: 34
  Out 5: 23            Out 5: 29            Out 5: 35  
  Out 6: 24            Out 6: 30            Out 6: 36

  Using the values above, assign integer values to the 2d matrix below
  to denote which output of the shift registers each column is connected to

  The specific pin each "Out" corresponds to is set in SHIFT_REGISTER_CONFIG, here we just care about order

  Note:
    The front of the cube is towards the top of the page
    You are looking at the cube from the top down
*/
const int PIN_CONFIGURATION[][6] = {
  //          ^
  //        Front
  {1,  2,  3,  4,  5,  6 },
  {7,  8,  9,  10, 11, 12},
  {13, 14, 15, 16, 17, 18},
  {19, 20, 21, 22, 23, 24},
  {25, 26, 27, 28, 29, 30},
  {31, 32, 33, 34, 35, 36}
};

// Describes which pins of the shift registers are connected (1 = Connected, 0 = Not Connected)
// To simplify things, the program assumes that each register has the same number of connections (6 each for 6x6x6)
// and that the connections are the same for each register
const bool SHIFT_REGISTER_CONFIG[] = {0, 1, 1, 1, 1, 1, 1, 0};
//                                   Q0 Q1 Q2 Q3 Q4 Q5 Q6 Q7

// Organizes the layer pins so they can be used easily
const int LAYER_PINS[] = {Layer1, Layer2, Layer3, Layer4, Layer5, Layer6};

// The number of times to refresh the cube per second
const int FRAME_RATE = 60;

// The number of microseconds each layer is shown
const double LAYER_SHOW_TIME = 1000000 / FRAME_RATE / 6;


/*** AUDIO ANALYSER CONSTANTS ***/
/*
  How to set FREQ_PLACEMENT

  This array describes which frequency maps to each column

  The range of frequencies spans from 63HZ (Number 1) to 16KHZ (Number 36).
  Fill out the grid similarly to the pin_configuration array (see instructions above).
*/
const int FREQ_PLACEMENT[][6] = {
  //          ^
  //        Front
  {1,  2,  3,  4,  5,  6 },
  {7,  8,  9,  10, 11, 12},
  {13, 14, 15, 16, 17, 18},
  {19, 20, 21, 22, 23, 24},
  {25, 26, 27, 28, 29, 30},
  {31, 32, 33, 34, 35, 36}
};

// This array sets the MINIMUM magnitude (0 - 1023) to light a particular layer of led's
const int FREQ_THRESHOLDS[] = {146, 292, 438, 584, 730, 876};

// Number of new channels we need to create between each real channel
// Always evaluates to 5 but this helps demonstrate where it comes from
const int NUM_FILLER_CHANNELS = round((float)(36 - 7) / (7 - 1));


/*** VOLUME CONSTANTS ***/
// The amount by which the raw volume reading needs to change in order to display the volume (on a scale from 1 - 36)
const int VOLUME_CHANGE_THRESHOLD = 2;

// The analog reading when the knob is at it's lowest point
const int VOLUME_MIN_READING = 456; // <--- Not right, I forgot what I tested it to be

// The amount by which the raw volume reading must change to register as a different reading (1-36)
const double VOLUME_INCREMENT_AMOUNT = (double)(1024 - VOLUME_MIN_READING) / 36;

//The length of time (in miliseconds) the the volume will stay on the cube after no changes are detected
const int VOLUME_LINGERING_TIME = 2000;


#endif
