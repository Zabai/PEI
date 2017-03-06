void control(){
 displayControl();
 keypadControl();
}

void zumba(){
  noTone(3);
  tone(4, freq, dur);
  delay(dur);
  tone(3, 10);
}
