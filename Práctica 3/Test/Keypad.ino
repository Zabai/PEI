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
      ast = false;
    }
  }
  
}


void MuestraTecla(){
   // Primera fila
  if(digitalRead(17) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
    swap(1);
    Serial.print("EL 1\n");
  }else if(digitalRead(17) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
    swap(2);
    Serial.print("EL 2\n");
  }else if(digitalRead(17) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
    swap(3);
    Serial.print("EL 3\n");
  }
    
  // Segunda fila
  if(digitalRead(16) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
    swap(4);
    Serial.print("EL 4\n");
  }else if(digitalRead(16) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
    swap(5);
    Serial.print("EL 5\n");
  }else if(digitalRead(16) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
    swap(6);
    Serial.print("EL 6\n");
  }
  
  // Tercera fila
  if(digitalRead(15) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
    swap(7);
    Serial.print("EL 7\n");
  }else if(digitalRead(15) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
    swap(8);
    Serial.print("EL 8\n");
  }else if(digitalRead(15) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
    swap(9);
    Serial.print("EL 9\n");
  }
  
  // Cuarta fila
  if(digitalRead(14) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
    swap(11);
    Serial.print("EL *\n");
  }else if(digitalRead(14) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
    swap(0);
    Serial.print("EL 0\n");
  }else if(digitalRead(14) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
    swap(12);
    Serial.print("EL #\n");
  }
}
