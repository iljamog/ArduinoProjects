// Robo India Tutorial
// Digital Input and Output on LED
// Hardware: NodeMCU

const int RED = 12;
const int GREEN = 13;
const int BLUE = 15;
const int LEDR = 5;
const int LEDG = 4;
const int BTN = 2;
int aeg = 30;


void setup() {
  Serial.begin(38400);
  Serial.print("Hello");
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(BTN, INPUT);
}

void loop() {
  Serial.println(aeg);
  byte button2State = digitalRead(D4);

  if (button2State == HIGH)
  {
    Serial.println("TERE");
    if (aeg > 17) {
      aeg = 17;
    }
  }
  if (aeg > 15) {
    analogWrite(RED, 0);
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 255);
    digitalWrite(LEDR, LOW); // turn the LED on
    digitalWrite(LEDG, HIGH); // turn the LED on
  }
  if (aeg >= 10 && aeg < 16) {
    analogWrite(RED, 0);
    analogWrite(GREEN, 255);
    analogWrite(BLUE, 0);
    delay(500);
    analogWrite(RED, 0);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
  }


  if (aeg < 10 && aeg > 3) {
    analogWrite(RED, 255);
    analogWrite(GREEN, 0);
    analogWrite(BLUE, 0);
    digitalWrite(LEDR, HIGH); // turn the LED on
    digitalWrite(LEDG, LOW); // turn the LED on
  }

  if (aeg <= 3) {
    digitalWrite(LEDR, HIGH); // turn the LED on
    delay(500);
    digitalWrite(LEDR, LOW); // turn the LED on
  } 
  
  delay(1000);
  --aeg;
  if (aeg == 0 || aeg < 0) {
    aeg = 30;
  }
}
