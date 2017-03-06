// Configuración zumbador
int freq = 200;
int dur = 50;
// Variables del 7 segmento
int unit = 0;
int dozen = 0;
int temp[2] = {0, 0};
int disp = 0;
boolean change = false;
// Variables teclado
boolean mode = false; // Modo adicional
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
  if(mode){
    TestTeclas();
    if(digitalRead(18) == LOW && digitalRead(19) == LOW){
      mode = false;
      unit = 0;
      dozen = 0;
    }else if(digitalRead(18) == LOW){
      if(dozen == 18){
        temp[0] = unit;
        unit = 18;
        dozen = temp[1];
      }else{
        temp[1] = dozen;
        dozen = 18;
        unit = temp[0];
      }
      delay(200);
    }else if(digitalRead(19) == LOW){
      // Aqui falta el blink
      int i = 0;
      blk:
      if(dozen == 18){
        temp[0] = unit;
        unit = 18;
        dozen = temp[1];
      }else{
        temp[1] = dozen;
        dozen = 18;
        unit = temp[0];
      }
      i++;
      delay(500);
      
      if(i < 6) goto blk;
    }
  }else if(digitalRead(18) == LOW && digitalRead(19) == LOW){
    unit = 0;
    dozen = 0;
    zumba();
    delay(100);
  }else if(digitalRead(18) == LOW){
    unit--;
    zumba();
    delay(100);
  }else if(digitalRead(19) == LOW){
    unit++;
    zumba();
    delay(100);
  }
}
