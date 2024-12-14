#include <AccelStepper.h>

unsigned long lastTime = 0;




////////////////////////////////


//////////////////////////////// q1 /////////////////////////////////////
int q1distance = -10;  // El valor de q1 corresponde a la coordenada Z

const int q1stepPin = 2;
const int q1dirPin = 5;

AccelStepper q1Motor(1, q1stepPin, q1dirPin);

///// Transformacion a posicion deseada en mm
double q1DistanceToSteps = 200/2;
int q1position = q1distance*q1DistanceToSteps; 


//////////////////////////////// q2 ///////////////////////////////////

const int q2stepPin = 3;
const int q2dirPin = 6;

AccelStepper q2Motor(1, q2stepPin, q2dirPin);

/////// Transformacion a posicion deseada en grados
double q2AngleToSteps = (200.0/360.0)*(62.0/20.0);


int q2angle = 0;
int q2position = q2angle*q2AngleToSteps;


//////////////////////////////// q3 ///////////////////////////////////

const int q3stepPin = 4;
const int q3dirPin = 7;

AccelStepper q3Motor(1, q3stepPin, q3dirPin);

/////// Transformacion a posicion deseada en grados
double q3AngleToSteps = (200.0/360.0)*(62.0/20.0);

int q3angle = 0;
int q3position = (q2angle + q3angle)*q3AngleToSteps; //(q2angle + q3angle)


void setup() {

  q1Motor.setMaxSpeed(1000);
  q1Motor.setAcceleration(200);
  q1Motor.setCurrentPosition(0);
  ////Orden de movimiento
  q1Motor.moveTo(q1position);


  q2Motor.setMaxSpeed(200);
  q2Motor.setAcceleration(100);
  q2Motor.setCurrentPosition(0);
  ////Orden de movimiento
  q2Motor.moveTo(q2position);

  q3Motor.setMaxSpeed(200);
  q3Motor.setAcceleration(100);
  q3Motor.setCurrentPosition(0);
  ////Orden de movimiento
  q3Motor.moveTo(q3position);

}

void loop() {

  q1Motor.run();
  q2Motor.run();
  q3Motor.run();

}
