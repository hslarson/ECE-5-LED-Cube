#ifndef constants
#define constants


/*
  How to set PIN_CONFIGURATION

  Shift Register 1:   Shift Register 2:
    Q0: 0               Q0: 8
    Q1: 1               Q1: 9
    Q2: 2               Q2: 10
    Q3: 3               Q3: 11
    Q4: 4               Q4: 12
    Q5: 5               Q5: 13
    Q6: 6               Q6: 14
    Q7: 7               Q7: 15

  Using the values above, assign integer values to the 2d matrix below
  to denote which pin of the shift registers each column is connected to

  Note:
    The front of the cube is towards the top of the page
    You are looking at the cube from the top down
*/
int PIN_CONFIGURATION[] = {
  //    ^
  //  Front
  {0,  1,  2,  3 },
  {4,  5,  6,  7 },
  {8,  9,  10, 11},
  {12, 13, 14, 15}
};


/*
  How to set FREQ_PLACEMENT

  Frequency Placement (FREQ_PLACEMENT) describes 
  which column of the cube displays each frequency band

  Frequency Range(Hz):
    63-1059:     0
    1060-2055:   1
    2056-3051:   2
    3052-4047:   3
    4048-5043:   4
    5044-6039:   5
    6040-7035:   6
    7036-8031:   7
    8032-9027:   8
    9028-10023:  9
    10024-11019: 10
    11020-12015: 11
    12016-13011: 12
    13012-14007: 13
    14008-15003: 14
    15004-16000: 15

  Fill out the grid similarly to the pin_configuration array (see instructions above)
*/
int FREQ_PLACEMENT[] = {
  //    ^
  //  Front
  {0,  1,  2,  3 },
  {4,  5,  6,  7 },
  {8,  9,  10, 11},
  {12, 13, 14, 15}
};


/*
  How to set FREQ_THRESHOLDS

  This array sets the MAXIMUM magnitude for each layer of led's
  The index of the array represents the number of LED's shown in each column

  Note:
    The first element (index 0) is the magnitude below which no LED's will show
    You don't need to set the maximum magnitude for the 4th led because it's a catch-all
*/
int FREQ_THRESHOLDS[] = {500, 1000, 1500, 2000};  // I don't actually know what the output of getSpectrum looks like so these could be way off


// The amount by which the raw volume reading needs to change in order to display the volume
int VOLUME_CHANGE_THRESHOLD = 64; // Note: set min max and base thresh off this


//The length of time (in miliseconds) the the volume will stay on the cube after no changes are detected
int VOLUME_LINGERING_TIME = 2000;


// The number of times to refresh the cube per second
int FRAME_RATE = 60;


// 
double LAYER_SHOW_TIME = 1 / FRAME_RATE / 6;

// Divide the raw volume reading by this number to get the number of LED's to light up
double VOLUME_NORMALIZING_FACTOR = 1023 / 16;


// 


// **Declare Pin Constants**
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


#endif
