// handles a multiplexed 8 segment display
// assumes digit selection for the 8-seg starts on pin 0
// assumes segment selection starts on pin 4

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
  digitalWrite(0, LOW);
  digitalWrite(1, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
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
  int digPin = digit - 1; // pins 0 - 3
  int segPin = segment + 4; // pins 4 - 10
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

void loop() {
  lightDig(1,0);
  lightDig(2,1);
  lightDig(3,2);
  lightDig(4,3);
  
  reset();
  delay(1);
}
