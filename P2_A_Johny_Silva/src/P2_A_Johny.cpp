// Johny Silva Mendes
// PRÁCTICA 2: INTERRUPCIONES
// Objetivo: realizar dos tipos de interrupciones.

// Practica A: interrupción por GPIO

#include <Arduino.h>

struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};

Button button1 = {18, 0, false};

// Función ISR que se ejecutará cuando ocurra la interrupción
void IRAM_ATTR isr() {
  button1.numberKeyPresses += 1;
  button1.pressed = true;
}

//Función SETUP: enseña resultados por pantalla; declara el PIN deseado para la funcionalidad del botón
// Se ejecuta el ISR cuando detecta una caída en el PIN que está conectado el botón. 
void setup() {
  Serial.begin(115200);
  pinMode(button1.PIN, INPUT_PULLUP);
  attachInterrupt(button1.PIN, isr, FALLING);
}

// LOOP: regula la puslacion del boton.
// pulsado: imprime por pantalla el num de veces que ha sido pulsado
// y el estado passa a "no pulsado" 
void loop() {
  if (button1.pressed) {
      Serial.printf("Button 1 has been pressed %u times\n", button1.numberKeyPresses);
      button1.pressed = false;
  }

   // El boton se desactiva tras 1 minuto de inactividad.
   //Detach Interrupt after 1 Minute
  static uint32_t lastMillis = 0;
  if (millis() - lastMillis > 60000) {
    lastMillis = millis();
    detachInterrupt(button1.PIN);
     Serial.println("Interrupt Detached!");
  }
  }