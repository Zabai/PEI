void displayT(int digit, char type){
  if(type == 'u'){
    digitalWrite(6, 0);
    digitalWrite(7, 0);
  }else{
    digitalWrite(6, 0);
    digitalWrite(7, 1);
  }
  switch(digit){
    case 1:
      PORTB = B000110;
      digitalWrite(5, LOW);
      break;
    case 2:
      PORTB = B011011;
      digitalWrite(5, HIGH);
      break;
    case 3:
      PORTB = B001111;
      digitalWrite(5, HIGH);
      break;
    case 4:
      PORTB = B100110;
      digitalWrite(5, HIGH);
      break;
    case 5:
      PORTB = B101101;
      digitalWrite(5, HIGH);
      break;
    case 6:
      PORTB = B111101;
      digitalWrite(5, HIGH);
      break;
    case 7:
      PORTB = B000111;
      digitalWrite(5, LOW);
      break;
    case 8:
      PORTB = B111111;
      digitalWrite(5, HIGH);
      break;
    case 9:
      PORTB = B100111;
      digitalWrite(5, HIGH);
      break;
    default:
      PORTB = B111111;
      digitalWrite(5, LOW);
      break;
  }
}

void displayControl(){
  // No se puede mostrar secuencialmente las unidades y decenas
  if(unit == 10){
    unit = 0;
    dozen++;
    if(dozen == 10){
      dozen = 0;
    }
  }
}

void displayControlT(){
  noInterrupts();
  if(disp == false){
    displayT(unit, 'u');
    disp = true;
  }else{
    displayT(dozen, 'd');
    disp = false;
  }
  if(digitalRead(18) == LOW && digitalRead(19) == LOW){
    unit = 0;
    dozen = 0;
  }else if(digitalRead(18) == LOW){
    unit--;
  }else if(digitalRead(19) == LOW){
    unit++;
    Serial.print("UP\n");
  }
  Serial.print("Interrupción\n");
  interrupts();
}
