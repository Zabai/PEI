/*  Métodos:
 *   -void Start(): Secuencia de Start
 *   -void Stop(): Secuancia de Stop
 *   -void EBit0(): Envia bit 0
 *   -void EBit1(): Envia bit 1
 *   -boolean RBit(): Recibe un bit
 */

void Start(){
  check:
  digitalWrite(writeSDA, HIGH);
  digitalWrite(writeSCL, HIGH);
  
  int sda = digitalRead(readSDA);
  int scl = digitalRead(readSCL);
  if(sda != 1 || scl != 1) goto check;
  
  digitalWrite(writeSDA, LOW);
  digitalWrite(writeSCL, HIGH);
  
  digitalWrite(writeSDA, LOW);
  digitalWrite(writeSCL, LOW);
}

void Stop(){
  digitalWrite(writeSDA, LOW);
  digitalWrite(writeSCL, LOW);
  
  digitalWrite(writeSDA, LOW);
  digitalWrite(writeSCL, HIGH);
  
  digitalWrite(writeSDA, HIGH);
  digitalWrite(writeSCL, HIGH);
  
  digitalWrite(writeSDA, HIGH);
  digitalWrite(writeSCL, HIGH);
}

void EBit0(){
  digitalWrite(writeSDA, LOW);
  digitalWrite(writeSCL, LOW);

  digitalWrite(writeSDA, LOW);
  digitalWrite(writeSCL, HIGH);

  digitalWrite(writeSDA, LOW);
  digitalWrite(writeSCL, HIGH);

  digitalWrite(writeSDA, LOW);
  digitalWrite(writeSCL, LOW);
}

void EBit1(){
  digitalWrite(writeSDA, HIGH);
  digitalWrite(writeSCL, LOW);

  digitalWrite(writeSDA, HIGH);
  digitalWrite(writeSCL, HIGH);

  digitalWrite(writeSDA, HIGH);
  digitalWrite(writeSCL, HIGH);

  digitalWrite(writeSDA, HIGH);
  digitalWrite(writeSCL, LOW);
}

boolean RBit(){
  digitalWrite(writeSDA, HIGH);
  digitalWrite(writeSCL, LOW);

  digitalWrite(writeSDA, HIGH);
  digitalWrite(writeSCL, HIGH);

  while(digitalRead(readSCL) != HIGH) digitalWrite(writeSCL, HIGH);
  int sda = digitalRead(readSDA);
  
  digitalWrite(writeSDA, HIGH);
  digitalWrite(writeSCL, LOW);
  
  return sda;  
}
