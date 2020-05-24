#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCBoards.h>
#include <SLIPEncodedSerial.h>
SLIPEncodedSerial SLIPSerial(Serial);


// Valores dos bototes/potenciometros
int button0State = 0, button0Statef = 0, button0Send = 1;
int pot0State = 1;
int button1State = 0, button1Statef = 0, button1Send = 1;
int pot1State = 1;
int button2State = 0, button2Statef = 0, button2Send = 1;
int pot2State = 1;
int button3State = 0, button3Statef = 0, button3Send = 1;
int pot3State = 1;
int button4State = 0, button4Statef = 0, button4Send = 1;
int pot4State = 1;

// Portas dos botoes e potenciometros
const int button0Pin = 2; 
const int pot0Pin = A0; 
const int button1Pin = 3; 
const int pot1Pin = A4;
const int button2Pin = 4; 
const int pot2Pin = A3;
const int button3Pin = 5; 
const int pot3Pin = A2;
const int button4Pin = 6; 
const int pot4Pin = A1;

void setup() {
  SLIPSerial.begin(115200); 
  // Configurando pinos de entrada
  pinMode(button0Pin, INPUT);
  pinMode(pot0Pin, INPUT);
  pinMode(button1Pin, INPUT);
  pinMode(pot1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(pot2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(pot3Pin, INPUT);
  pinMode(button4Pin, INPUT);
  pinMode(pot4Pin, INPUT);
}

void loop() {
  // Lendo os botoes e potenciometros:
  button0Statef = digitalRead(button0Pin); 
  pot0State = analogRead(pot0Pin);
  button1Statef = digitalRead(button1Pin);
  pot1State = analogRead(pot1Pin);
  button2Statef = digitalRead(button2Pin);
  pot2State = analogRead(pot2Pin);
  button3Statef = digitalRead(button3Pin);
  pot3State = analogRead(pot3Pin);
  button4Statef = digitalRead(button4Pin);
  pot4State = analogRead(pot4Pin);


  // Mudando os estados das mensagens OSC dos botoes, caso tenham sido apertados
  if (button0Statef && !button0State) {
    if(button0Send) {
      button0Send = 0;
    } else {
      button0Send = 1;
    }
  }
  if (button1Statef && !button1State) {
    if(button1Send) {
      button1Send = 0;
    } else {
      button1Send = 1;
    }
  }
  if (button2Statef && !button2State) {
    if(button2Send) {
      button2Send = 0;
    } else {
      button2Send = 1;
    }
  }
  if (button3Statef && !button3State) {
    if(button3Send) {
      button3Send = 0;
    } else {
      button3Send = 1;
    }
  }
  if (button4Statef && !button4State) {
    if(button4Send) {
      button4Send = 0;
    } else {
      button4Send = 1;
    }
  }


  // Enviando um bundle com os estados dos botoes e potenciometros
  OSCBundle bndl;

  bndl.add("/botao/0").add((uint16_t) button0Send);
  bndl.add("/pot/0").add((uint16_t) pot0State);
  bndl.add("/botao/1").add((uint16_t) button1Send);
  bndl.add("/pot/1").add((uint16_t) pot1State);
  bndl.add("/botao/2").add((uint16_t) button2Send);
  bndl.add("/pot/2").add((uint16_t) pot2State);
  bndl.add("/botao/3").add((uint16_t) button3Send);
  bndl.add("/pot/3").add((uint16_t) pot3State);
  bndl.add("/botao/4").add((uint16_t) button4Send);
  bndl.add("/pot/4").add((uint16_t) pot4State);
  
  SLIPSerial.beginPacket();  
  bndl.send(SLIPSerial); // send the bytes to the SLIP stream
  SLIPSerial.endPacket(); // mark the end of the OSC Packet
  bndl.empty(); // empty the bundle to free room for a new one



 
  button0State = button0Statef;
  button1State = button1Statef;
  button2State = button2Statef;
  button3State = button3Statef;
  button4State = button4Statef;
  delay(10);

}
