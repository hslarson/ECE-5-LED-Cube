#ifndef constants
#define constants


// ** Enable Debug Mode **
#define DEBUG false

/*** PIN CONSTANTS ***/
// Transistor Pins
#define Layer1 8
#define Layer2 7
#define Layer3 6
#define Layer4 3
#define Layer5 5
#define Layer6 4

// Shift Register Pins
#define ShiftClockPin 12
#define ShiftDataPin  11
#define ShiftLatchPin 9

// MSGEQ7 Pins
#define AnalyzerData   A1
#define AnalyzerReset  2
#define AnalyzerStrobe A2

// Volume Knob Pin
#define VolumePin A0


/*** DISPLAY CONSTANTS ***/
/*
  How to set PIN_CONFIGURATION

  Shift Register 1:    Shift Register 2:    Shift Register 3:
  Q0: 1                Q0: 9                Q0: 17             
  Q1: 2                Q1: 10               Q1: 18             
  Q2: 3                Q2: 11               Q2: 19             
  Q3: 4                Q3: 12               Q3: 20             
  Q4: 5                Q4: 13               Q4: 21             
  Q5: 6                Q5: 14               Q5: 22             
  Q6: 7                Q6: 15               Q6: 23             
  Q7: 8                Q7: 16               Q7: 24             

  Shift Register 4:    Shift Register 5:    Shift Register 6:
  Q0: 25               Q0: 33               Q0: 41             
  Q1: 26               Q1: 34               Q1: 42             
  Q2: 27               Q2: 35               Q2: 43             
  Q3: 28               Q3: 36               Q3: 44             
  Q4: 29               Q4: 37               Q4: 45             
  Q5: 30               Q5: 38               Q5: 46             
  Q6: 31               Q6: 39               Q6: 47             
  Q7: 32               Q7: 40               Q7: 48             

  Using the values above, assign integer values to the 2d matrix below
  to denote which output pin of the shift registers each column is connected to

  Note:
    The front of the cube is towards the top of the page
    You are looking at the cube from the top down
*/
const short PIN_CONFIGURATION[][6] = {
  //          ^
  //        Front
  {48, 40, 39, 47, 46, 38},
  {37, 44, 36, 43, 34, 45},
  {30, 24, 42, 35, 31, 32},
  {29, 23,  5, 22, 27, 21},
  {26, 19, 14, 16, 15, 20},
  {18, 13, 10, 12,  8, 11}
};


// Organizes the layer pins so they can be iterated through more easily
const int LAYER_PINS[] = {Layer1, Layer2, Layer3, Layer4, Layer5, Layer6};

// Display modes
#define MODE_SPECTRUM true
#define MODE_VOLUME false

// The number of times to refresh the cube per second
#define FRAME_RATE 60

// The number of microseconds each layer is shown
#define LAYER_SHOW_TIME ((double)1000000/FRAME_RATE/6)


/*** AUDIO analyzer CONSTANTS ***/
/*
  How to set FREQ_PLACEMENT

  [1, 36] : References a location in the normalized frequency array
  [0]     : References the average of all of the raw frequency readings
  [-1, -7]: References a location in the raw frequency array

  Fill out the grid similarly to the pin_configuration array (see instructions above)
  You'll also find several examples below
*/

/*
// Normal
const short FREQ_PLACEMENT[][6] = {
  //          ^
  //        Front
  {1,  2,  3,  4,  5,  6 },
  {7,  8,  9,  10, 11, 12},
  {13, 14, 15, 16, 17, 18},
  {19, 20, 21, 22, 23, 24},
  {25, 26, 27, 28, 29, 30},
  {31, 32, 33, 34, 35, 36}
};
*/


// 90-Degree Rotated
const short FREQ_PLACEMENT[][6] = {
  //          ^
  //        Front
  {31, 25, 19, 13, 7,  1},
  {32, 26, 20, 14, 8,  2},
  {33, 27, 21, 15, 9,  3},
  {34, 28, 22, 16, 10, 4},
  {35, 29, 23, 17, 11, 5},
  {36, 30, 24, 18, 12, 6}
};


/*
// Sprial
const short FREQ_PLACEMENT[][6] = {
  //          ^
  //        Front
  {1,  2,  3,  4,  5,  6 },
  {20, 21, 22, 23, 24, 7 },
  {19, 32, 33, 34, 25, 8 },
  {18, 31, 36, 35, 26, 9 },
  {17, 30, 29, 28, 27, 10},
  {16, 15, 14, 13, 12, 11}
};
*/

/*
// Blocks
const short FREQ_PLACEMENT[][6] = {
  //          ^
  //        Front
  {-1,-1,  -2,-2,  -3,-3},
  {-1,-1,  -2,-2,  -3,-3},
  {-1,-1,  -2,-2,  -3,-3},
  
  {-5,-5,  -6,-6,  -7,-7},
  {-5,-5,  -6,-6,  -7,-7},
  {-5,-5,  -6,-6,  -7,-7}
};
*/

// Use this to set the index of each of the raw frequency readings in the normed array
// More Space = Greater "Resolution";
const short PRIMARY_FREQ_LOCATIONS[] = {0, 6, 12, 18, 24, 30, 35};
const short PRIMARY_FREQ_LOCATIONS_ASCENDING[] = {0, 6, 12, 18, 24, 30, 35}; // A sorted version of the previous array to make interpolation faster

// This array sets the MINIMUM magnitude (0 - 1023) to light a particular layer of led's
// const short FREQ_THRESHOLDS[] = {0 , 29, 78, 94, 130, 276};
const short FREQ_THRESHOLDS[] = {146, 292, 438, 584, 730, 876};

// How many points to consider in the rolling average
#define FREQ_AVERAGING_POINTS 4


/*** VOLUME CONSTANTS ***/
// The amount by which the raw volume reading needs to change in order to display the volume (on a scale from 1 - 36)
#define VOLUME_CHANGE_THRESHOLD 2

// How many points to consider in the rolling average
#define VOLUME_AVERAGING_POINTS 4

// The amount by which the raw volume reading must change to register as a different reading (1-36)
#define VOLUME_INCREMENT_AMOUNT ((double)1023/36)

//The length of time (in milliseconds) the volume will stay on the cube after no changes are detected
#define VOLUME_LINGERING_TIME 2000


#endif
