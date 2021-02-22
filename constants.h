#ifndef constants
#define constants


/*** PIN CONSTANTS ***/
// Transistor Pins
const int Layer1 = 13,
          Layer2 = 12,
          Layer3 = 11,
          Layer4 = 10,
          Layer5 = 9,
          Layer6 = 8;

// Shift Register Pins
const int ShiftDataPin  = 7,
          ShiftLatchPin = 6,
          ShiftClockPin = 5;

// MSGEQ7 Pins
const int AnalyserData   = 14, //A0
          AnalyserReset  = 4,
          AnalyserStrobe = 3;

// Volume Knob Pin
const int VolumePin = 15; //A1


/*** DISPLAY CONSTANTS ***/
/*
  How to set PIN_CONFIGURATION

  Transistor Array 1:  Transistor Array 2:  Transistor Array 3:
  Pin 16: 1            Pin 16: 7            Pin 16: 13
  Pin 15: 2            Pin 15: 8            Pin 15: 14
  Pin 14: 3            Pin 14: 9            Pin 14: 15
  Pin 13: 4            Pin 13: 10           Pin 13: 16
  Pin 12: 5            Pin 12: 11           Pin 12: 17
  Pin 11: 6            Pin 11: 12           Pin 11: 18

  Transistor Array 4:  Transistor Array 5:  Transistor Array 6:
  Pin 16: 19           Pin 16: 25           Pin 16: 31
  Pin 15: 20           Pin 15: 26           Pin 15: 32
  Pin 14: 21           Pin 14: 27           Pin 14: 33
  Pin 13: 22           Pin 13: 28           Pin 13: 34
  Pin 12: 23           Pin 12: 29           Pin 12: 35  
  Pin 11: 24           Pin 11: 30           Pin 11: 36

  Using the values above, assign integer values to the 2d matrix below
  to denote which pin of the shift registers each column is connected to

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

// The number of times to refresh the cube per second
const int FRAME_RATE = 60;

// The number of seconds each layer is shown
const double LAYER_SHOW_TIME = 1 / FRAME_RATE / 6;


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
