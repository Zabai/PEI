void keypadControl(){
  if(flag){
    // Primera fila
    if(digitalRead(17) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
      choice = (choice > 0)? choice * 10 + 1 : 1;
      tTimer = 0;
      flag = false;
    }else if(digitalRead(17) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
      choice = (choice > 0)? choice * 10 + 2 : 2;
      tTimer = 0;
      flag = false;
    }else if(digitalRead(17) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
      choice = (choice > 0)? choice * 10 + 3 : 3;
      tTimer = 0;
      flag = false;
    }

    // Segunda fila
    if(digitalRead(16) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
      choice = (choice > 0)? choice * 10 + 4 : 4;
      tTimer = 0;
      flag = false;
    }else if(digitalRead(16) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
      choice = (choice > 0)? choice * 10 + 5 : 5;
      tTimer = 0;
      flag = false;
    }else if(digitalRead(16) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
      choice = (choice > 0)? choice * 10 + 6 : 6;
      tTimer = 0;
      flag = false;
    }

    // Tercera fila
    if(digitalRead(15) == LOW && digitalRead(6) == 0 && digitalRead(7) == 0){
      choice = (choice > 0)? choice * 10 + 7 : 7;
      tTimer = 0;
      flag = false;
    }else if(digitalRead(15) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
      choice = (choice > 0)? choice * 10 + 8 : 8;
      tTimer = 0;
      flag = false;
    }else if(digitalRead(15) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
      choice = (choice > 0)? choice * 10 + 9 : 9;
      tTimer = 0;
      flag = false;
    }

    // Cuarta fila excepto asterisco
    if(digitalRead(14) == LOW && digitalRead(6) == 0 && digitalRead(7) == 1){
      choice = (choice > 0)? choice * 10 : 0;
      tTimer = 0;
      flag = false;
    }else if(digitalRead(14) == LOW && digitalRead(6) == 1 && digitalRead(7) == 0){
      tTimer = 0;
      flag = false;
      tries++;
      Serial.print("Elegiste: ");
      Serial.print(choice);
      Serial.print("\n");
      if(choice == secret){
        // Ganas
        winGame();
      }else{
        // Ayuda de parpadeo inferior
        helpUser();
      }
      choice = -1;
    }
  }
  
}
