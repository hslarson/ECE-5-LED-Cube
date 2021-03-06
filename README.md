### Main Program:

- <b> loop </b>
  - Calls the nextLayer() member  function of the Multiplexer class on a preset interval
  - While we wait for the next layer to be drawn, the loop calls the subtasks() function to perform several smaller tasks required to draw the matrix
- <b>subtasks</b>
  - Each subtask referenced in this function is called once for every complete matrix that is sent to the cube. The function must be reset after every iteration
  - The first step (case 0) is calling the checkVolume() member function of the MSGEQ7 class, this decides whether the subtasks function draws a volume matrix or a spectrum matrix
  - Next, we collect the data required to construct the matrix. This is only required if we are drawing a spectrum matrix
  - Then, we construct the matrix itself. This is handled entirely by the respective classes
  - Lastly, we queue the matrix we just drew, meaning that it will be shown in the next iteration of the loop

### Multiplexer Class:

- <b>setMatrix</b>
  - Uses memcpy to either queue a new matrix or allow the queued matrix to be shown
- <b>nextLayer</b>
  - Handles the drawing of individual layers and the queuing of matrices
  - First, calls the constructData() function to format the data in a way that the registers will understand
  - Then, calls the sendData() function to send the data to the cube
- <b>constructData</b>
  - A helper function for nextLayer() that handles the mapping of output pins and the conversion of the resultant binary array to an integer array
- <b>SendToCube</b>
  - Uses the SPI bus to send the data from the constructData() function to the shift registers

### MSGEQ7 Class:

- <b>getSpectrum</b>
  - Reads data from the MSGEQ7 breakout board using analogRead()
- <b>normSpectrum</b>
  - Takes the array from the getSpectrum() function and converts from 7 channels to 36
- <b>makeSpectrumMatrix</b>
  - Maps each frequency band to a specific column of the cube
  - Applies a threshold to the raw reading to decide how many LED’s to light in each column and constructs a Boolean matrix based on this data
- <b>queueMatrix</b>
  - Calls the setMatrix() member of the Multiplexer class to queue the matrix that was built by the makeSpectrumMatrix() function

### VolumeControl Class:

- <b>checkVolume</b>
  - Uses a timer and the getVolume() function to decide whether or not to draw a volume matrix
- <b>getVolume</b>
  - Reads data from the volume potentiometer and normalizes the reading
  - Creates a running average of the normalized readings
- <b>makeVolumeMatrix</b>
  - Takes the current volume reading and creates a Boolean matrix that displays the volume as front-to-back bars that ascend each column then move from left to right to the next column
- <b>queueMatrix</b>
  - Takes the matrix that was constructed by the makeVolumeMatrix and queues it to be shown on the cube