// This program is designed to help you set the PIN_CONFIGURATION array in constants.h
// For each number in the sequence, record the location of the LED that lights up (if any) and add it
// to the array. To move to the next number, just send something to the Arduino via the serial monitor


#define clk 12
#define dat 11
#define lat 10
#define lyr 6

int c = 0;

void setup() {
  Serial.begin(9600);

  pinMode(clk, OUTPUT);
  pinMode(dat, OUTPUT);
  pinMode(lat, OUTPUT);
  pinMode(lyr, OUTPUT);

  digitalWrite(lyr, HIGH);

  for (int r = 0; r < 6; r++) {
    digitalWrite(lat, LOW);
    shiftOut(dat, clk, LSBFIRST, 0); 
    digitalWrite(lat, HIGH);
  }
}

void loop() {
  Serial.println(c + 1);

  digitalWrite(lat, LOW);
  
  digitalWrite(dat, (c++ == 0 ? HIGH : LOW));
  digitalWrite(clk, HIGH);
  delay(1);
  digitalWrite(clk, LOW);
  
  digitalWrite(lat, HIGH);
  
  if (c > 47)
    c = 0;

  // Wait for serial input
  while (!Serial.available()) { delay(10); }
  while(Serial.available()) { Serial.read(); }
}
