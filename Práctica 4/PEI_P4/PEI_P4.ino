
// 7 Segmentos
int count = 0;  // Segundos máximos.
int timer = 0;  // Cada 100 interrupciones es 1 segundo.
int disp = 0;   // Control de unidades, decenas y centenas.

// Teclado
boolean hash = false;
boolean flag = true; // Control pulsación de teclado

// Juego
int secret = 0;   // Nº secreto aleatorio
int choice = -1;  // Input del usuario
int mode = 1;     // Dificultad
int tTimer = 0;   // Tiempo de pulsación de tecla
int score = 0, tries = 0;
boolean help = false;

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
  
  // Semilla aleatoria pero como el analog esta conectado hay que buscar otro método
  //randomSeed(analogRead(0));
}

void loop() {
  // Control de botones
  if(digitalRead(18) == LOW && digitalRead(19) == LOW){
    count = 0;
    delay(200);
    noTone(3);
  }else if(digitalRead(18) == LOW){
    switch(mode){
      case 1:
        mode++;
        Serial.print("Dificultad media: 30s\n");
        break;
      case 2:
        mode++;
        Serial.print("Dificultad difícil: 15s\n");
        break;
      case 3:
        Serial.print("Dificultad fácil: 60s\n");
        mode = 1;
        break;
      default:
        Serial.print("Error con la dificultad.\n");
        break;
    }
  }else if(digitalRead(19) == LOW){
    startGame();
  }
  delay(500);
}
