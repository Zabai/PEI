void displayS(int digit, char type){
  if(type == 'u'){
    digitalWrite(6, 0);
    digitalWrite(7, 0);
  }else if(type == 'd'){
    digitalWrite(6, 0);
    digitalWrite(7, 1);
    
  }else{
    digitalWrite(6, 1);
    digitalWrite(7, 0);
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
    case 11:
      // 'A' mayúscula
      PORTB = B110111;
      digitalWrite(5, HIGH);
    case 12:
      // 'U' mayúscula
      PORTB = B111110;
      digitalWrite(5, LOW);
    default:
      PORTB = B111111;
      digitalWrite(5, LOW);
      break;
  }
}

void displayControl(){
  noInterrupts();
  
  if(disp == 0){
    displayS(unit, 'u');
    disp++;
  }else if(disp == 1){
    displayS(dozen, 'd');
    disp++;
  }else{
    displayS(0, 'c');
    disp = 0;
  }
  
  if(unit == 10){
    unit = 0;
    dozen++;
    if(dozen == 10){
      dozen = 0;
    }
  }else{
    if(unit < 0){
    unit = 9;
    dozen -= (dozen == 0)? -9 : 1;
    }
  }
  interrupts();
}
