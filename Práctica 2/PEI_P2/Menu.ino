void Menu(){
  Serial.print("\nOpciones:\n");
  Serial.print("1. Guardar dato en una posicion de memoria\n");
  Serial.print("2. Leer una posicion de memoria\n");
  Serial.print("3. Inicializar memoria a un valor\n");
  Serial.print("4. Mostrar contenido de los 128 bytes\n");
  Serial.print("5. Inicilizar memoria a un valor(Page Write)\n");
  Serial.print("6. Mostrar contenido de los 128 bytes(Sequential Read) (NO IMPLEMENTADO)\n");
  Serial.print("7. Modificar zona de memoria");
  while(Serial.available() <= 0);
  int option = Serial.parseInt();
  Command(option);
}

void Command(int option){
  switch(option){
    case 1:{
      Serial.print("\n---- Guardar dato en una posicion de memoria ----\n");
      Serial.print("Introduzca un dato a almacenar (0-255): ");
      while(Serial.available() == 0);
      int data = Serial.parseInt();
      Serial.print(data);
      Serial.print("\nIntroduzca una direccion de memoria(0-127): ");
      while(Serial.available() == 0);
      int dir = Serial.parseInt();
      Serial.print(dir);
      Store(dir, data);
      Serial.print("\n----------------\n");
      break;
    }
    case 2:{
      Serial.print("\n---- Leer una posicion de memoria ----\n");
      Serial.print("Introduzca una direccion de memoria(0-127): ");
      while(Serial.available() == 0);
      int dir = Serial.parseInt();
      Serial.println(dir);
      Serial.print("El dato contenido en la posicion es: ");
      Serial.print(Read(dir));
      Serial.print("\n----------------\n");
      break;
    }
    case 3:{
      Serial.print("\n---- Inicializar memoria a un valor ----\n");
      Serial.print("Introduzca un dato a inicializar (0-255): ");
      while(Serial.available() == 0);
      int data = Serial.parseInt();
      Serial.print(data);
      IniMem(data);
      Serial.print("\n----------------\n");
      break;
    }
    case 4:{
      Serial.print("\n---- Mostrar contenido de los 128 bytes ----\n");
      Serial.print("Posicion:Valor\n");
      ReadMem();
      Serial.print("\n----------------\n");
      break;
    }
    case 5:{
      Serial.print("\n---- Inicilizar memoria a un valor(Page Write) ----\n");
      Serial.print("Introduzca un dato a inicializar (0-255): ");
      while(Serial.available() == 0);
      int data = Serial.parseInt();
      Serial.print(data);
      IniMemPW(data);
      Serial.print("\n----------------\n");
      break;
    }
    case 6:{
      Serial.print("\n---- Mostrar contenido de los 128 bytes(Sequential Read) ----\n");
      SeqRead();
      //ReadMemSQ();
      Serial.print("\n----------------\n");
      break;
    }
    case 7:{
      Serial.print("\n---- Modificar zona de memoria ----\n");
      Serial.print("Introduzca una posicion minima(0-127): ");
      while(Serial.available() == 0);
      int minPos = Serial.parseInt();
      Serial.print(minPos);
      Serial.print("\nIntroduzca una posicion maxima(min-127): ");
      while(Serial.available() == 0);
      int maxPos = Serial.parseInt();
      Serial.print(maxPos);
      if(minPos > maxPos){
        Serial.print("\nError en los datos introducidos");
        Serial.print("\n----------------\n");
        break;
      }
      modMem(minPos, maxPos);
      Serial.print("\n----------------\n");
      break;
    }
    default:
      Serial.print("\n---- Opcion no valida ----\n");
      break;
  }
}
