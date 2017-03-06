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
    case 10:
      // Todos apagados
      PORTB = B000000;
      digitalWrite(5, LOW);
      break;
    case 11:
      // Todos encendidos
      PORTB = B111111;
      digitalWrite(5, HIGH);
      break;
    case 12:
      // Solo segmento superior
      PORTB = B000001;
      digitalWrite(5, LOW);
      break;
    case 13:
      // Solo segmento inferior
      PORTB = B001000;
      digitalWrite(5, LOW);
      break;
    default:
      PORTB = B111111;
      digitalWrite(5, LOW);
      break;
  }
}

void displayControl(){
  noInterrupts();
  
  // Control de muestra
  if(disp == 0){
    if(help == false) displayS(count%10, 'u');
    else displayS(count, 'u');
    disp++;
  }else if(disp == 1){
    if(help == false) displayS(count/10, 'd');
    else displayS(count, 'd');
    disp++;
  }else{
    displayS(0, 'c');
    disp = 0;
  }

  interrupts();
}
