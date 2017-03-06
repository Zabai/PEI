int pause = 100;
int unit = 0;
int dozen = 2;
boolean disp = false;

void setup() {
  Serial.begin(9600);
  
  // Pines de salida de segmento (PDB)
  DDRB = B111111;

  // Pines entrada botones y teclado¿?
  DDRC = B000000;
  PORTC = B111111;
  
  // Pines salida decodificador
  DDRD = B11111000;

  //Interrupciones
  attachInterrupt(0, displayControlT, RISING);
  tone(3, 100);
}

void loop() {
  
}
