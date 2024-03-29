// handles a multiplexed 8 segment display
// ENSURE digitPin, segmentPin, AND dotsPin ARE SET CORRECTLY!
// there should be 4 digit pins (increasing from digitPin) and 7 segment pins
// to control colon leds, float digits middle 2 digits HIGH, and set dotsPin LOW

int digitPin = 2;
int segmentPin = 7;
int dotsPin = 6;

int digits[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {0,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,0,0,1,1}  // 9
};

void setup() {
  for (int i = 0; i <= 13; i++) {
    pinMode(i, OUTPUT);
  }
  reset();
}

void reset() {
  // set all digits off (LOW)
  for (int p = digitPin; p < digitPin + 4; p++) {
    digitalWrite(p, LOW);
  }
  
  // set all segments off (HIGH)
  for (int p = segmentPin; p < segmentPin + 7; p++) {
    digitalWrite(p, HIGH);
  }
  
  // set all dots off (HIGH)
  digitalWrite(dotsPin, HIGH);
}

void fail() {
  // something is bad, turn off every pin, and infinite loop
  reset();
  while(1) {
    delay(1000);
  }
}

void lightSeg(int digit, int segment) {
  if ((digit < 1) || (digit > 4) || (segment < 0) || (segment > 6)) {
    fail();
  }
  int digPin = digit - 1 + digitPin; // digits are 1-indexed, so subtract 1
  int segPin = segment + segmentPin; // segments are 0 indexed
  digitalWrite(digPin, HIGH);
  digitalWrite(segPin, LOW);
  digitalWrite(digPin, LOW);
  digitalWrite(segPin, HIGH);
}

void lightDig (int digit, int numeral) {
  // digit is which set of segments you want to light up
  // numeral is the number you want to display on those segments
  if ((digit > 4) || (numeral > 9)) {
    fail();
  }
  for (int seg = 0; seg < 7; seg++) {
    if (digits[numeral][seg]) {
      lightSeg(digit, seg);
    }
  }
}

void flashDots() {
  // have to make sure only one dot is on a time to ensure brightness is the same
  digitalWrite(dotsPin, LOW);
  digitalWrite(digitPin + 1, HIGH);
  digitalWrite(digitPin + 1, LOW);
  digitalWrite(digitPin + 2, HIGH);
  digitalWrite(digitPin + 2, LOW);
  digitalWrite(dotsPin, HIGH);
}

void loop() {
  lightDig(1,0);
  lightDig(2,1);
  lightDig(3,2);
  lightDig(4,3);

  if ((millis() %  2000) > 1000) {
    flashDots();
  }
  
  reset();
  delay(1);
}

