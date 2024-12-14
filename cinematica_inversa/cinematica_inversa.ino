#include <math.h>  // Necesario para funciones matemáticas como sqrt() y atan2()
#include <AccelStepper.h>

// Coordenadas del extremo del robot
const int x = 5;  // Coordenada X (en cm)
const int y = 10;  // Coordenada Y (en cm)
const int z = 10;  // Coordenada Z (en cm)

// Longitudes de los eslabones del robot
const double l1 = 10.5;  // Longitud del primer eslabón (en cm)
const double l2 = 13.5;  // Longitud del segundo eslabón (en cm)

// Variables para almacenar los resultados de la cinemática inversa
double q1, q2, q3;

// Pines y configuración de motores
const int q1stepPin = 2;
const int q1dirPin = 5;
AccelStepper q1Motor(1, q1stepPin, q1dirPin);

const int q2stepPin = 3;
const int q2dirPin = 6;
AccelStepper q2Motor(1, q2stepPin, q2dirPin);

const int q3stepPin = 4;
const int q3dirPin = 7;
AccelStepper q3Motor(1, q3stepPin, q3dirPin);

// Transformaciones para convertir a pasos
const double q1DistanceToSteps = 200.0 / 2.0;  // Relación para q1 (en mm)
const double q2AngleToSteps = (200.0 / 360.0) * (62.0 / 20.0);  // Relación para q2 (en grados)
const double q3AngleToSteps = (200.0 / 360.0) * (62.0 / 20.0);  // Relación para q3 (en grados)

void calcularCinematicaInversa() {
  // Cálculo de q1
  q1 = z*10;  // El valor de q1 corresponde a la coordenada Z

  // Cálculo de C3
  double C3 = (pow(x, 2) + pow(y, 2) - pow(l1, 2) - pow(l2, 2)) / (2 * l1 * l2);

  // Verificar si C3 está en el rango [-1, 1]
  if (C3 < -1.0) {
    C3 = -1.0;
  }
  if (C3 > 1.0) {
    C3 = 1.0;
  }

  // Cálculo de S3 y q3
  double S3 = sqrt(1 - pow(C3, 2));
  q3 = atan2(S3, C3);  // Ángulo q3 en radianes

  // Cálculo de q2
  q2 = atan2(y, x) - atan2(l2 * sin(q3), l1 + l2 * cos(q3));  // Ángulo q2 en radianes

  // Conversión a grados
  q3 = q3 * 180 / M_PI;
  q2 = q2 * 180 / M_PI;
}

void setup() {
  // Inicialización del monitor serial
  Serial.begin(9600);

  // Calcular cinemática inversa
  calcularCinematicaInversa();

  // Imprimir resultados
  Serial.println("Cálculo de Cinemática Inversa:");
  Serial.print("q1: ");
  Serial.println(q1);
  Serial.print("q2 (grados): ");
  Serial.println(q2);
  Serial.print("q3 (grados): ");
  Serial.println(q3);

  // Configuración de motores
  q1Motor.setMaxSpeed(1000);
  q1Motor.setAcceleration(200);
  q1Motor.setCurrentPosition(0);
  q1Motor.moveTo(q1 * q1DistanceToSteps);

  q2Motor.setMaxSpeed(200);
  q2Motor.setAcceleration(100);
  q2Motor.setCurrentPosition(0);
  q2Motor.moveTo(q2 * q2AngleToSteps);

  q3Motor.setMaxSpeed(200);
  q3Motor.setAcceleration(100);
  q3Motor.setCurrentPosition(0);
  q3Motor.moveTo((q2+q3) * q3AngleToSteps);
}

void loop() {
  q1Motor.run();
  q2Motor.run();
  q3Motor.run();
}