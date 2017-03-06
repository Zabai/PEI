void control(){
 displayControl();
 if(!mode) keypadControl();
}

void zumba(){
  noTone(3);
  tone(4, freq, dur);
  delay(dur);
  tone(3, 10);
}

void zumbaTecla(int i){
  switch(i){
    case 1:
      buzz(500);
      break;
    case 2:
      buzz(750);
      break;
    case 3:
      buzz(1000);
      break;
    case 4:
      buzz(1250);
      break;
    case 5:
      buzz(1500);
      break;
    default:
      Serial.print("Error al zumbar por tecla");
      break;
  }
}

void buzz(int frequency){
  noTone(3);
  tone(4, frequency, 2000);
  delay(2000);
  tone(3, 10);
}

