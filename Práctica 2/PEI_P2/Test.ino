// De int a binario por máscara
void Test1(){
  Serial.print("Introduce un valor decimal: ");
  while(Serial.available() == 0);
  int test = Serial.parseInt();
  Serial.print(test);
  
  Serial.print("\nEn binario es: ");
  byte byt = byte(test);
  byte mask = B10000000;
  for(int i = 0; i < 7; i++){
    if((byt & mask) == mask) Serial.print("1");
    else Serial.print("0");
    byt <<= 1;
  }
  delay(10000);
}

// Pruebas binario
void Test2(){
  byte test = 0;
  test++;
  test <<= 1;
  Serial.println(HIGH);
  Serial.print(test, BIN);
  delay(10000);
}

void Test3(){
  Serial.print("NO FORMAT");       // prints a label
  Serial.print("\t");              // prints a tab

  Serial.print("DEC");  
  Serial.print("\t");      

  Serial.print("HEX");
  Serial.print("\t");  

  Serial.print("OCT");
  Serial.print("\t");

  Serial.print("BIN");
  Serial.println("\t");

  for(int x=0; x< 64; x++){    // only part of the ASCII chart, change to suit

    // print it out in many formats:
    Serial.print(x);       // print as an ASCII-encoded decimal - same as "DEC"
    Serial.print("\t\t");    // prints a tab

    Serial.print(x, DEC);  // print as an ASCII-encoded decimal
    Serial.print("\t");    // prints a tab

    Serial.print(x, HEX);  // print as an ASCII-encoded hexadecimal
    Serial.print("\t");    // prints a tab

    Serial.print(x, OCT);  // print as an ASCII-encoded octal
    Serial.print("\t");    // prints a tab

    Serial.println(x, BIN);  // print as an ASCII-encoded binary
    //                             then adds the carriage return with "println"
    delay(200);            // delay 200 milliseconds
  }
  Serial.println("");      // prints another carriage return
}

void TestStore(){
  for(int i = 0; i < memCap; i++){
    Store(i, i);
  }
}
