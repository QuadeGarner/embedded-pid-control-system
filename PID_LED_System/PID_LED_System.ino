class VituralMotor{
  private:
    double position = 100;
    double velocity = 0.0;
    double acceleration;
    double const MASS = 1;
    const double DAMPING = 0.1; // FRICTION: amount of resistance
    const double POWER_SCALING = 5.0 ;// motor strength
  public:
    void update(double inputPower, double DELTA_T){
      double force = (inputPower * POWER_SCALING) - (velocity * DAMPING);
      acceleration = force / MASS;
      velocity +=(acceleration * DELTA_T);  // velocity = acceleration time the amount of time

      position += velocity * DELTA_T ; // update the posistion based on the velocity and how much time has passed

    }
    double getPosition(){return position;}
    double getVelocity(){return velocity;}


};
int const potPin = A0;
int const portKP = A1;
int const portKD = A3;
VituralMotor vm;
int KD;
int KP;
double kP;
double kD;
double error = 0;
double currentPos;
double lastError = 0;
double target;
double derviative;
double power;
long currentTime;
long lastTime = 0;
long delta_t = 0; 
double dd_t = 0;


void setup() {
  // put your setup code here, to run once:
  analogReadResolution(12);
  Serial.begin(9600);
  for(int i = 3 ; i < 7; i++){
    pinMode(i, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int potVal = analogRead(potPin);
  KP = analogRead(portKP);
  KD = analogRead(portKD);
  kP = ((double)KP / 4095) * 1; 
  kD = ((double)KD / 4095) * 0.35;
 
  
  
  target = (double)map(potVal, 0, 4095, 0, 179);
  //Serial.print("target: "+ String(target)+"\n");
  //Serial.print("Error: " + String(error) +"\n");
  //Serial.print("CurrentPos: " + String(currentPos)+ "\n");
  //Serial.print("kP: " + String(kP)+ "\n");
  //Serial.print("kD: " + String(kD)+ "\n");
  currentTime = millis();
  currentPos = vm.getPosition();
  delta_t = currentTime - lastTime;
  dd_t = delta_t / 1000.0;
  lastTime = currentTime;
  if (dd_t > 0.0015){
    error = target - currentPos;
    // clamp delta_t if to big
    if(dd_t > 0.25){
      dd_t = 0.25;
    }
    double rawDerivate = (error - lastError) / dd_t;
    lastError = error;
    derviative = (0.1*rawDerivate) + (0.9 * derviative);
    power = (error * kP) + (derviative * kD);
    if(power > 1.0 ){
      power = 1.0;
    }
    if(power < -1.0){
      power = -1.0;
    }
    if( power < 0.05 && power > 0) {
      power = 0.05;
    }else if( power > -0.05 && power < 0){
      power = -.05;
    }
    vm.update(power, dd_t);
  }
  if( error <=-100){
      // Left redLight
      digitalWrite(7, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
  }else if ( (error > -100) && (error <=  -25)){
    // left yellow light
    digitalWrite(7, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
  } else if ((error < 25 )  && (error > -25) ){
    // green light
    digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, LOW);
  }else if ( (error >= 25) &&(error < 100) ){
    //  right yellow light
    digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
  } else {
  // right Red Light
    digitalWrite(7, LOW);
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
  }

}

