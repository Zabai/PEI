void control(){
 displayControl();
 counterControl();
 keypadControl();
}
void counterControl(){
  // Cada segundo real decrementa el contador
  if(timer != 700) timer++;
  else{
    timer = 0;
    if(count > 0 && !help) count--;
    else if(count == 0) gameOver();
  }

  // Tras una pulsación espera 1s
  if(tTimer != 200)tTimer++;
  else flag = true;    
}

void startGame(){
  Serial.print("Se ha generado un número aleatorio[0-99], intenta adivinarlo.\n");
  // Generación de random
  secret = random(100);
  switch(mode){
    case 1:
      count = 60;
      break;
    case 2:
      count = 30;
      break;
    case 3:
      count = 15;
      break;
     default:
      Serial.print("Error en la dificultad.\n");
      break;
  }
  tone(3, 10);
}

void winGame(){
  Serial.print("Has ganado, tienes ");
  score = count * mode * mode;
  Serial.print(score);
  Serial.print(" puntos. Nº intentos: ");
  Serial.print(tries);
  Serial.print("\n");
  // Parpadeo display + sonido de premio
  int freq = 200;
  for(int i = 0; i < 9; i++){
    noTone(3);
    tone(4, freq, 100);
    delay(150);
    tone(3, 10);
    freq += 200;
  }
  tries = 0;
  noTone(3);
}

void gameOver(){
  Serial.print("Has perdido. Vuelve a intentarlo\n");
  // Parpadeo display + sonido de premio
  int freq = 1800;
  for(int i = 0; i < 4; i++){
    noTone(3);
    tone(4, freq, 100);
    delay(250);
    tone(3, 10);
    freq += 400;
  }
  tries = 0;
  noTone(3);
}

void helpUser(){
  noTone(3);
  tone(4, 1800, 100);
  delay(100);
  tone(3, 10);
  
  int temp = count;
  help = true;
  
  if(choice > secret){
    count = 13;
    // Blink inferior
    for(int i = 0; i < 3; i++){
      if(count == 13) count = 10;
      else count = 13;
      delay(500);
    }
  }else{
    count = 12;
    // Blink superior
    for(int i = 0; i < 3; i++){
      if(count == 12) count = 10;
      else count = 12;
      delay(500);
    }
  }
  count = temp;
  help = false;
}
