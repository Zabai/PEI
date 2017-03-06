// Configuración zumbador
int freq = 200;
int dur = 50;
// Variables del 7 segmento
int unit = 0;
int dozen = 0;
int disp = 0;
// Variables teclado
boolean pulsed = false;
boolean ast = false;

void setup() {
  Serial.begin(9600);
  
  // Pines de salida de segmento (PDB)
  DDRB = B111111;

  // Pines entrada botones y teclado
  DDRC = B000000;
  PORTC = B111111;
  
  // Pines salida decodificador
  DDRD = B11111000;

  //Interrupciones
  attachInterrupt(0, control, RISING);
  tone(3, 10);
}

void loop() {
  if(digitalRead(18) == LOW && digitalRead(19) == LOW){
    unit = 0;
    dozen = 0;
    zumba();
  }else if(digitalRead(18) == LOW){
    unit--;
    zumba();
  }else if(digitalRead(19) == LOW){
    unit++;
    zumba();
  }
  delay(100);
}
