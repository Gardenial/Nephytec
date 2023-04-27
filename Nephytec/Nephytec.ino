#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <NewPing.h>
#include <SoftwareSerial.h>
#include <Servo.h>

// Inicializa o objeto MPU6050
Adafruit_MPU6050 mpu;

// Inicializa os objetos dos servos
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
Servo servo9;
Servo servo10;

// Define os pinos do sensor HC-SR04
#define TRIGGER_PIN 12
#define ECHO_PIN 13

// Inicializa o objeto do sensor HC-SR04
NewPing sonar(TRIGGER_PIN, ECHO_PIN, 200);

// Inicializa o objeto Bluetooth
SoftwareSerial bluetooth(1, 0); // RX, TX

// Declara as variáveis para armazenar os valores do acelerômetro
float ax, ay, az;
float pitch, roll;

// Declara as variáveis para armazenar os ângulos dos servos
int angle1, angle2, angle3, angle4, angle5, angle6, angle7, angle8, angle9, angle10;

// Declara as variáveis para armazenar a distância medida pelo sensor HC-SR04
int distance;

// Declara a variável para armazenar o comando recebido via Bluetooth
char command;

void updateServos() {
  // Calcula os ângulos dos servos com base nos valores dos ângulos de pitch e roll
  angle1 = constrain((int) (90 - roll - pitch), 0, 180);
  angle2 = constrain((int) (90 - roll + pitch), 0, 180);
  angle3 = constrain((int) (90 + roll - pitch), 0, 180);
  angle4 = constrain((int) (90 + roll + pitch), 0, 180);
  angle5 = constrain((int) (90 - roll - pitch), 0, 180);
  angle6 = constrain((int) (90 - roll + pitch), 0, 180);
  angle7 = constrain((int) (90 + roll - pitch), 0, 180);
  angle8 = constrain((int) (90 + roll + pitch), 0, 180);
  angle9 = constrain((int) (90 - roll), 0, 180);
  angle10 = constrain((int) (90 + roll), 0, 180);

  // Escreve os ângulos nos servos
  servo1.write(angle1);
  servo2.write(angle2);
  servo3.write(angle3);
  servo4.write(angle4);
  servo5.write(angle5);
  servo6.write(angle6);
  servo7.write(angle7);
  servo8.write(angle8);
  servo9.write(angle9);
  servo10.write(angle10);
}

void updateSensor() {
  // Mede a distância com o sensor HC-SR04
  distance = sonar.ping_cm();
}

void processCommand() {
  // Lê o comando enviado via Bluetooth
  if (bluetooth.available() > 0) {
    command = bluetooth.read();

    // Processa o comando
    switch (command) {
      case 'F':
        servo1.write(0);
        servo2.write(0);
        servo3.write(180);
        servo4.write(180);
        servo5.write(0);
        servo6.write(0);
        servo7.write(0);
        servo8.write(180);
        servo9.write(0);
        servo10.write(180);
        break;

      case 'B':
        servo1.write(180);
        servo2.write(180);
        servo3.write(0);
        servo4.write(0);
        servo5.write(180);
        servo6.write(180);
        servo7.write(180);
        servo8.write(180);
        servo9.write(90);
        servo10.write(90);
        break;
      
      case 'L':
        servo1.write(180);
        servo2.write(0);
        servo3.write(180);
        servo4.write(0);
        servo5.write(180);
        servo6.write(0);
        servo7.write(0);
        servo8.write(180);
        servo9.write(45);
        servo10.write(135);
        break;
      
      case 'R':
        servo1.write(0);
        servo2.write(180);
        servo3.write(0);
        servo4.write(180);
        servo5.write(0);
        servo6.write(180);
        servo7.write(180);
        servo8.write(0);
        servo9.write(135);
        servo10.write(45);
        break;
    
      case 'S':
        servo1.write(90);
        servo2.write(90);
        servo3.write(90);
        servo4.write(90);
        servo5.write(90);
        servo6.write(90);
        servo7.write(90);
        servo8.write(90);
        servo9.write(90);
        servo10.write(90);
        break;
      
      default:
        break;
    }

    }
    }
    
    void setup() {
    // Inicializa o monitor serial
    Serial.begin(9600);
    
    // Inicializa o objeto MPU6050
    if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
    delay(10);
    }
    }
    
    // Configura os pinos dos servos
    servo1.attach(2);
    servo2.attach(3);
    servo3.attach(4);
    servo4.attach(5);
    servo5.attach(6);
    servo6.attach(7);
    servo7.attach(8);
    servo8.attach(9);
    servo9.attach(10);
    servo10.attach(11);
    
    // Inicializa o objeto Bluetooth
    bluetooth.begin(9600);
    }
    
    void loop() {
    // Lê os valores do acelerômetro
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    ax = a.acceleration.x;
    ay = a.acceleration.y;
    az = a.acceleration.z;
    
    // Calcula os ângulos de pitch e roll
    roll = atan2(ay, az) * 180.0 / PI;
    pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / PI;
    
    // Atualiza os servos com base nos ângulos de pitch e roll
    updateServos();
    
    // Mede a distância com o sensor HC-SR04
    updateSensor();
    
    // Processa o comando recebido via Bluetooth
    processCommand();
    
    // Imprime os valores de pitch, roll e distância no monitor serial
    Serial.print("Pitch: ");
    Serial.print(pitch);
    Serial.print("\tRoll: ");
    Serial.print(roll);
    Serial.print("\tDistance: ");
    Serial.print(distance);
    Serial.println(" cm");
    
    // Aguarda 50 milissegundos
    delay(50);
    }
