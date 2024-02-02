#include <Servo.h>
#include <IRremote.h>

const int pirPin = 2;     // Pin del sensor PIR
const int servoPin = 9;   // Pin del servo

Servo servo;               // Objeto servo para controlar el servo motor
int pirState = LOW;        // Estado inicial del sensor PIR
int val = 0;               // Variable para almacenar el valor del sensor PIR

const int RECV_PIN = 11;   // Pin del receptor infrarrojo
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(servoPin, OUTPUT);
  servo.attach(servoPin);
  Serial.begin(9600);
  irrecv.enableIRIn();  // Iniciar el receptor infrarrojo
}

void loop() {
  val = digitalRead(pirPin);

  if (val == HIGH) {
    if (pirState == LOW) {
      Serial.println("Movimiento detectado!");
      abrirPuerta();
      pirState = HIGH;
    }
  } else {
    if (pirState == HIGH){
      Serial.println("Sin movimiento");
      cerrarPuerta();
      pirState = LOW;
    }
  }

  if (irrecv.decode(&results)) {
    // Si se recibe una señal infrarroja, ejecutar la función correspondiente
    manejarControlRemoto(results.value);
    irrecv.resume();  // Recibir el próximo valor
  }
}

void abrirPuerta() {
  Serial.println("Abriendo la puerta");
  servo.write(90);
  delay(1000);
}

void cerrarPuerta() {
  Serial.println("Cerrando la puerta");
  servo.write(0);
  delay(1000);
}

void manejarControlRemoto(unsigned long valor) {
  // Función para manejar las diferentes señales del control remoto
  switch (valor) {
    case 0xFF6897:  // Cambia este valor con el código de tu botón
      Serial.println("Botón presionado en el control remoto");
      // Agrega aquí lo que quieres hacer cuando se presiona el botón en el control remoto
      break;
    // Agrega más casos según los códigos de tus botones del control remoto
  }
}
