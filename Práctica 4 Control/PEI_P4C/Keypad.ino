void keypadControl(){
  if(digitalRead(14) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
    ast = true;
    Serial.print("EL *\n");
  }
  
  if(ast){
    // Primera fila
    if(digitalRead(17) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
      freq = 400;
      Serial.print("EL 1\n");
      ast = false;
    }else if(digitalRead(17) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
      freq = 600;
      Serial.print("EL 2\n");
      ast = false;
    }else if(digitalRead(17) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
      freq = 800;
      Serial.print("EL 3\n");
      ast = false;
    }
    
    // Segunda fila
    if(digitalRead(16) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
      freq = 1000;
      Serial.print("EL 4\n");
      ast = false;
    }else if(digitalRead(16) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
      freq = 1200;
      Serial.print("EL 5\n");
      ast = false;
    }else if(digitalRead(16) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
      freq = 1400;
      Serial.print("EL 6\n");
      ast = false;
    }
    
    // Tercera fila
    if(digitalRead(15) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
      freq = 1600;
      Serial.print("EL 7\n");
      ast = false;
    }else if(digitalRead(15) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
      freq = 1800;
      Serial.print("EL 8\n");
      ast = false;
    }else if(digitalRead(15) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
      freq = 2000;
      Serial.print("EL 9\n");
      ast = false;
    }
    
    // Cuarta fila menos el asterisco
    if(digitalRead(14) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
      freq = 200;
      Serial.print("EL 0\n");
      ast = false;
    }else if(digitalRead(14) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
      Serial.print("EL #\n");
      mode = true;
      unit = 0;
      dozen = 18;
      ast = false;
    }
  }
}

void TestTeclas(){
  // Primera fila
  if(digitalRead(17) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
    unit = (unit == 18)? unit : 11;
    dozen = (dozen == 18)? dozen : 11;
    Serial.print("EL 1\n");
  }else if(digitalRead(17) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
    unit = (unit == 18)? unit : 12;
    dozen = (dozen == 18)? dozen : 12;
    Serial.print("EL 2\n");
  }else if(digitalRead(17) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
    unit = (unit == 18)? unit : 13;
    dozen = (dozen == 18)? dozen : 13;
    Serial.print("EL 3\n");
  }

  // Segunda fila
  if(digitalRead(16) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
    unit = (unit == 18)? unit : 14;
    dozen = (dozen == 18)? dozen : 14;
    Serial.print("EL 4\n");
  }else if(digitalRead(16) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
    unit = (unit == 18)? unit : 15;
    dozen = (dozen == 18)? dozen : 15;
    Serial.print("EL 5\n");
  }else if(digitalRead(16) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
    unit = (unit == 18)? unit : 16;
    dozen = (dozen == 18)? dozen : 16;
    Serial.print("EL 6\n");
  }

  // Tercera fila
  if(digitalRead(15) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
    unit = (unit == 18)? unit : 17;
    dozen = (dozen == 18)? dozen : 17;
    Serial.print("EL 7\n");
  }else if(digitalRead(15) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
    zumbaTecla(1);
    Serial.print("EL 8\n");
  }else if(digitalRead(15) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
    zumbaTecla(2);
    Serial.print("EL 9\n");
  }

  // Cuarta fila
  if(digitalRead(14) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
    zumbaTecla(3);
    Serial.print("EL *\n");
  }else if(digitalRead(14) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
    zumbaTecla(4);
    Serial.print("EL 0\n");
  }else if(digitalRead(14) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
    zumbaTecla(5);
    Serial.print("EL #\n");
  }
}
