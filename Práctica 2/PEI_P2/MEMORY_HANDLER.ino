/*  Métodos:
 *   -void Store(int dir, int data): Guarda en una posición de memoria(dir) un dato(data)
 *   -int Read(int dir): Lee una posición de memoria(dir)
 *   -void IniMem(int data): Inicializa memoria a un valor(data)
 *   -void ReadMem(): Lectura total de la memoria
 *   -void PageWrite(int dir, int data): Inicializa 1 página de memoria de una dirección(dir) a un valor(data). 1 Página = 16 posiciones de memoria
 *   -void IniMemPW(int data): Inicializa memoria por páginas a un valor(data)
 *   -SeqRead(): Lectura secuencial de memoria
 *   -modMem(): Escribe un 1 si (la posición y contenido es par) o si (la posición y contenido es impar)
 */
 
const int nBit = 8;      // 1 Byte = 8 Bits
const int memCap = 128;  // Capacidad de la memoria
const int pageSize = 16;  // Tamaño de la página

void Store(int dir, int data){
  st:
  Start();

  // Bits de dirección dispositivo
  SDevDir();

  // R/W => En este caso escritura
  EBit0();

  // ACK
  if(RBit() != LOW) goto st;

  // Dirección memoria
  byte dirByte = byte(dir);
  byte mask = B10000000;
  for(int i=0; i < nBit; i++){
    if((dirByte & mask) == mask) EBit1();
    else EBit0();
    dirByte <<= 1;
  }

  // ACK
  if(RBit() != LOW) goto st;

  byte dataByte = byte(data);
  // Escribir dato
  for(int i=0; i < nBit; i++){
      if((dataByte & mask) == mask) EBit1();
      else EBit0();
      dataByte <<= 1;
  }

  // ACK
  if(RBit() != LOW) goto st;

  Stop();
}

int Read(int dir){
  rd:
  Start();

  // Bits de dirección dispositivo
  SDevDir();

  // R/W => En este caso escritura
  EBit0();

  // ACK
  if(RBit() != LOW) goto rd;

  byte dirByte = byte(dir);
  byte mask = B10000000;
  // Dirección memoria
  for(int i=0; i < nBit; i++){
    if((dirByte & mask) == mask) EBit1();
    else EBit0();
    dirByte <<= 1;
  }
  
  // ACK
  if(RBit() != LOW) goto rd;
  
  // Start
  Start();
  
  // Bits de dirección de dispositivo
  SDevDir();
  
  // R/W => En este caso lectura
  EBit1();

  // ACK
  if(RBit() != LOW) goto rd;

  // Leer dato
  byte dataByte = 0;
  for(int i=0; i < nBit; i++){
    if(RBit() == HIGH) dataByte++;
    if(i != 7) dataByte <<= 1; // Para que desplace 8 bits en vez de 9
  }
  
 // ACK
 if(RBit() != HIGH) goto rd;

 Stop();
 return (int) dataByte;
}

void IniMem(int data){
  for(int i = 0; i < memCap; i++){
    Store(i, data);
  }
}

void ReadMem(){
  for(int i = 0; i < memCap; i++){
    Serial.print(i);
    Serial.print(": ");
    if((i+1)%8 == 0 && i!= 0) Serial.println(Read(i), HEX);
    else{
      Serial.print(Read(i), HEX);
      Serial.print("\t\t\t");
    }
  }
}

void PageWrite(int dir, int data){
  pw:
  Start();
  
  // Bits de dirección dispositivo
  SDevDir();
  
  // R/W => En este caso escritura
  EBit0();
  
  // ACK
  if(RBit() != LOW) goto pw;
  
  //Dirección memoria
  byte dirByte = byte(dir);
  byte mask = B10000000;
  for(int i=0; i < nBit; i++){
    if((dirByte & mask) == mask) EBit1();
    else EBit0();
    dirByte <<= 1;
  }
  
  // ACK
  if(RBit() != LOW) goto pw;
  
  // Escribir dato
  byte dataByte = byte(data);
  for(int i = 0; i < pageSize; i++){
    for(int j = 0; j < nBit; j++){
      if((dataByte & mask) == mask) EBit1();
      else EBit0();
      dataByte <<= 1;
    }
    // ACK
    if(RBit() != LOW) goto pw;
    // Restaura dato
    dataByte = byte(data);
  }
  
  Stop();
}

void IniMemPW(int data){
  for(int i = 0; i < memCap/pageSize; i++){
    PageWrite(i*pageSize, data);
  }
}

void SeqRead(){
  sr:
  Start();
  
  // Bits de dirección dispositivo
  SDevDir();
  
  // R/W => En este caso escritura
  EBit0();
  
  // ACK
  if(RBit() != LOW) goto sr;
  
  // Dirección memoria
  for(int i = 0; i < nBit; i++) EBit0();
  
  // ACK
  if(RBit() != LOW) goto sr;
  
  Start();
  
  // Bits de dirección dispositivo
  SDevDir();
  
  // R/W => En este caso lectura
  EBit1();
  
  // ACK
  if(RBit() != LOW) goto sr;
  
  while(RBit() != HIGH){
    byte dataByte = 0;
    for(int i=0; i < nBit; i++){
      if(RBit() == HIGH) dataByte++;
      if(i != 7) dataByte <<= 1; // Para que desplace 8 bits en vez de 9
    }
    Serial.println(dataByte);
  }
  
  Stop();
}

void modMem(int minPos, int maxPos){
  for(int i = minPos; i <= maxPos; i++){
    if((i%2 == 0 && Read(i)%2 == 0) || (i%2 != 0 && Read(i)%2 != 0)){
      Store(i, 1);
    }else{
      Store(i, 0);
    }
  }
  Serial.print("\n");
  ReadMem();
}
