#include <math.h>  // Necesario para funciones matemáticas como sqrt() y atan2()
#include <AccelStepper.h>

int contador = 0;

// Coordenadas de los puntos de destino (en cm)
const int p1_x = 0;  // Coordenada X del primer punto
const int p1_y = 15;  // Coordenada Y del primer punto
const int p1_z = 12;  // Coordenada Z del primer punto

const int p2_x = 0;  // Coordenada X del segundo punto
const int p2_y = -15;  // Coordenada Y del segundo punto
const int p2_z = 12;  // Coordenada Z del segundo punto

// Longitudes de los eslabones del robot
const double l1 = 10.5;  // Longitud del primer eslabón (en cm)
const double l2 = 13.5;  // Longitud del segundo eslabón (en cm)

// Variables para almacenar los resultados de la cinemática inversa
double q1, q2, q3;
double q1_prev = 0, q2_prev = 0, q3_prev = 0;  // Para almacenar las posiciones anteriores

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

// Función para calcular la cinemática inversa
void calcularCinematicaInversa(int x, int y, int z) {
  // Cálculo de q1
  q1 = z * 10;  // El valor de q1 corresponde a la coordenada Z

  // Cálculo de C3
  double C3 = (pow(x, 2) + pow(y, 2) - pow(l1, 2) - pow(l2, 2)) / (2 * l1 * l2);

  // Verificar si C3 está en el rango [-1, 1]
  if (C3 < -1.0) {
    C3 = -1.0;
  }
  if (C3 > 1.0) {
    C3 = 1.0;
  }
  double S3 = sqrt(1 - pow(C3, 2));
  // Cálculo de S3 y q3

  if (contador > 0){
    S3 = -S3;
  };
  contador = contador + 1;
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

  // Configuración de motores
  q1Motor.setMaxSpeed(1000);
  q1Motor.setAcceleration(200);
  q1Motor.setCurrentPosition(0);

  q2Motor.setMaxSpeed(200);
  q2Motor.setAcceleration(100);
  q2Motor.setCurrentPosition(0);

  q3Motor.setMaxSpeed(200);
  q3Motor.setAcceleration(100);
  q3Motor.setCurrentPosition(0);

  // Calcular cinemática inversa para el primer punto
  calcularCinematicaInversa(p1_x, p1_y, p1_z);
  
  // Mover al primer punto
  q1Motor.moveTo(q1 * q1DistanceToSteps);
  q2Motor.moveTo(q2 * q2AngleToSteps);
  q3Motor.moveTo(q3 * q3AngleToSteps);
}

void loop() {
  // Mover de forma continua a los motores hasta alcanzar el primer punto
  q1Motor.run();
  q2Motor.run();
  q3Motor.run();

  // Una vez alcanzado el primer punto, calcular la cinemática inversa para el segundo punto
  if (!q1Motor.isRunning() && !q2Motor.isRunning() && !q3Motor.isRunning() && contador == 1) {
    calcularCinematicaInversa(p2_x, p2_y, p2_z);

    // Calcular las diferencias incrementales de las posiciones
    double delta_q1 = q1 - q1_prev;
    double delta_q2 = q2 - q2_prev;
    double delta_q3 = q3 - q3_prev;

    // Mover al segundo punto de manera incremental
    q1Motor.moveTo(q1_prev * q1DistanceToSteps + delta_q1 * q1DistanceToSteps);
    q2Motor.moveTo(q2_prev * q2AngleToSteps + delta_q2 * q2AngleToSteps);
    q3Motor.moveTo(q3_prev * q3AngleToSteps + delta_q3 * q3AngleToSteps);

    // Actualizar las posiciones previas
    q1_prev = q1;
    q2_prev = q2;
    q3_prev = q3;
  }
}
