const int readSDA = 2;
const int readSCL = 3;
const int writeSDA = 4;
const int writeSCL = 5;

void setup() {
  Serial.begin(9600);

  pinMode(readSDA, INPUT);
  pinMode(readSCL, INPUT);

  pinMode(writeSDA, OUTPUT);
  pinMode(writeSCL, OUTPUT);

  digitalWrite(writeSDA, HIGH);
  digitalWrite(writeSCL, HIGH);
}

void loop() {
  Menu();
}

// Envia bits de dirección del dispositivo
void SDevDir(){
  // Dir: 1010000
  EBit1();
  EBit0();
  EBit1();
  EBit0();
  EBit0();
  EBit0();
  EBit0();
}
