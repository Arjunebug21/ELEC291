// C++ code
//
#define FORWARDS 101
#define BACKWARDS 202
#define STOP 303
#define NOTHING 404

const int pD = 11, pB = 10, pC = 6, pA = 5;
const int forwardPin = 3, backwardPin = 2;
int lastMode = NOTHING;
float lastPWM = 255.0;


void setup()
{
  Serial.begin(9600);
  pinMode(pA, OUTPUT);
  pinMode(pB, OUTPUT);
  pinMode(pC, OUTPUT);
  pinMode(pD, OUTPUT);
  pinMode(forwardPin, INPUT);
  pinMode(backwardPin, INPUT);
  pinMode(A0, INPUT);
  
  lastMode = STOP;
  lastPWM  = 0.0;
  controlDirection(STOP, 0.0);
  Serial.println("SETUP DONE");
}

void loop()
{
  float PWM_val = potChecker();
  int mode = modeCheck();
  if (mode != NOTHING && mode != lastMode){
    controlDirection(mode, PWM_val); 
    lastMode = mode;
    Serial.println("Controlling direction");
  }else if (PWM_val != lastPWM){
  	controlDirection(lastMode, PWM_val);
    Serial.println("CHANGING PWM");
    lastPWM = PWM_val;
  }
  delay(30);
}

float potChecker(){
  int val = analogRead(A0);
  float toPWM = val*(255.0/1023.0);
  return toPWM;
}

int modeCheck(){
  if (digitalRead(forwardPin) == LOW && digitalRead(backwardPin) == LOW){
    Serial.println("STOP1");
    return STOP;
  }else if (digitalRead(forwardPin) == LOW){
    Serial.println("FORWARDS");
    return FORWARDS;
  }else if (digitalRead(backwardPin) == LOW){
    Serial.println("Backwards");
    return BACKWARDS;
  }else{
    Serial.println("NOTHING");
    return NOTHING;
  }
}
  
void controlDirection(int instruction, float rate){
  if (instruction == FORWARDS){
    digitalWrite(pA, LOW);
    digitalWrite(pB, LOW);
    analogWrite(pC, rate);
    analogWrite(pD, rate);
  }else if (instruction == BACKWARDS){
    analogWrite(pA, rate);
    analogWrite(pB, rate);
    digitalWrite(pC, LOW);
    digitalWrite(pD, LOW);
  }else{
    digitalWrite(pA, LOW);
    digitalWrite(pB, HIGH);
    digitalWrite(pC, LOW);
    digitalWrite(pD, HIGH);
  }
}
