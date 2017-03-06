void control(){
 displayControl();
 if(!mode)keypadControl();
}

void zumba(){
  noTone(3);
  tone(4, freq, dur);
  delay(dur);
  tone(3, 10);
}

void swap(int i){
  dozen = unit;
  unit = i;
}

