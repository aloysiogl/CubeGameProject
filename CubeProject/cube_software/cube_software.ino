//Definições
#define clk 8
#define latch 10
#define data 9
//Variáveis
int rrain;
byte shift[4];
boolean led[125];
boolean connection = 0;

//Código
void setup(){
  pinMode(latch,OUTPUT);  //Definição dos pinos dos Shift Registers
  pinMode(data,OUTPUT);   
  pinMode(clk,OUTPUT);      
  Serial.begin(115200);
}
void loop(){
  Connecting1_(850);
  Connecting2_(850);
 // space(10000);
  if (isConnected()) 
   connection = 1;
  while (connection){
      readSerial();
      exe_led(1);
  }
}
//Veryfies connection
int isConnected(){
    bool validation = 0;
    char reading;
    char key[11] = {'c','o','n','n','e','c','t','i','o','n','\0'};
    if (Serial.available() > 0){
      for (int i = 0; i < 10; i++){
         while (!(Serial.available() > 0))
         {}
         validation = 1;
         reading = Serial.read();
         if (key[i] != reading){
            validation = 0;
            break;
         }
      }
      Serial.print(key);
      Connecting1_(850);
      Connecting2_(850);
    }
    return validation;
}
//Reads data afeter connection is established
static bool readSerial(){
  byte reading;  //Stores the reading
  if (Serial.available() > 0){
    for (int i = 0; i < 16; i++){
        while (!(Serial.available() > 0)) //This part is needed to prevent jumping chars
        {}
        if (i%3 == 2)
          exe_led(1);
        reading = Serial.read();
        for (int j = 0; j < 8; j++){      //This part is responsible for reading the input to the led matrix
          led[8*i + j] = reading%2;
          reading >>=1;
          if (i == 15 && j == 4)          //Ensures reading finishes at position 124
              break;
        }
    }
    Serial.print(1);
    return 1;
  }
}
static void exe_led(int duration){
  //Mantém o frame no tempo desejado
  unsigned long counter = millis() + duration; 
  while(counter >= millis()){
    //Acende a camada de leds
    digitalWrite(latch,0);  
    shift[3] = B00000011;
    for (byte i = 0; i < 25; i++){
    if (i < 8){ 
    bitWrite(shift[0], i, !led[i]);
    }
    if (i >= 8 & i < 16){ 
    bitWrite(shift[1], i-8, !led[i]);
    }
    if (i >= 16 & i < 24){ 
    bitWrite(shift[2], i-16, !led[i]);
    }
    if (i == 24){ 
    bitWrite(shift[3], 0, !led[i]);
    }
    }
    exe();
    digitalWrite(latch,0);  
    shift[3] = B00000101;
    for (byte i = 0; i < 25; i++){
    if (i < 8){ 
    bitWrite(shift[0], i, !led[i+25]);
    }
    if (i >= 8 & i < 16){ 
    bitWrite(shift[1], i-8, !led[i+25]);
    }
    if (i >= 16 & i < 24){ 
    bitWrite(shift[2], i-16, !led[i+25]);
    }
    if (i == 24){ 
    bitWrite(shift[3], 0, !led[i+25]);
    }
    }
    exe();
    digitalWrite(latch,0);
    shift[3] = B00001001;
    for (byte i = 0; i < 25; i++){
    if (i < 8){ 
    bitWrite(shift[0], i, !led[i+50]);
    }
    if (i >= 8 & i < 16){ 
    bitWrite(shift[1], i-8, !led[i+50]);
    }
    if (i >= 16 & i < 24){ 
    bitWrite(shift[2], i-16, !led[i+50]);
    }
    if (i == 24){ 
    bitWrite(shift[3], 0, !led[i+50]);
    }
    }
    exe();
    digitalWrite(latch,0);
    shift[3] = B00010001;
    for (byte i = 0; i < 25; i++){
    if (i < 8){ 
    bitWrite(shift[0], i, !led[i+75]);
    }
    if (i >= 8 & i < 16){ 
    bitWrite(shift[1], i-8, !led[i+75]);
    }
    if (i >= 16 & i < 24){ 
    bitWrite(shift[2], i-16, !led[i+75]);
    }
    if (i == 24){ 
    bitWrite(shift[3], 0, !led[i+75]);
    }
    }
    exe();
    digitalWrite(latch,0);
    shift[3] = B00100001;
    for (byte i = 0; i < 25; i++){
    if (i < 8){ 
    bitWrite(shift[0], i, !led[i+100]);
    }
    if (i >= 8 & i < 16){ 
    bitWrite(shift[1], i-8, !led[i+100]);
    }
    if (i >= 16 & i < 24){ 
    bitWrite(shift[2], i-16, !led[i+100]);
    }
    if (i == 24){ 
    bitWrite(shift[3], 0, !led[i+100]);
    }
    }
    exe();  
  }
}
static void exe(){
  //Escreve a saída e fecha o pin latch
  shiftOut(data, clk, MSBFIRST, shift[3]);
  shiftOut(data, clk, MSBFIRST, shift[2]);
  shiftOut(data, clk, MSBFIRST, shift[0]);
  shiftOut(data, clk, MSBFIRST, shift[1]);
  digitalWrite(latch,1);
}

void module(unsigned long layer, byte layerNumber)
{
  for (byte k = 0; k < 25; k++)
  {
    led[k+(layerNumber-1)*25] = layer%2;
    layer = layer/2;
  }
}  
void a(unsigned int duration){
//Mantém o frame no tempo desejado
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){  
   led[0+25*l]=!led[0+25*l];
   led[1+25*l]=!led[1+25*l];
   led[2+25*l]=!led[2+25*l];
   led[8+25*l]=!led[8+25*l];
   led[14+25*l]=!led[14+25*l];
   led[18+25*l]=!led[18+25*l];
   led[20+25*l]=!led[20+25*l];
   led[21+25*l]=!led[21+25*l];
   led[22+25*l]=!led[22+25*l];
   led[7+25*l]=!led[7+25*l];
   led[12+25*l]=!led[12+25*l];
   led[17+25*l]=!led[17+25*l];
   exe_led(100);
}
}
}
void rain (unsigned int duration){
  unsigned long counter = millis() + duration;
  while (counter >= millis()){
    for(int i = 0;i < 25;i++){
      boolean rrain = 0;
      if (random(1, 25) == 8) {
        rrain = 1;
      }
      led[i] = led[i + 25];
      led[i + 25] = led[i + 50];
      led[i + 50] = led[i + 75];
      led[i + 75] = led[i + 100];
      led[i + 100] = rrain;
    }
    exe_led(100);
  }
  //Limpeza
  for (int k=0; k <125;k++){
    led[k]=0;  }
}
void space (unsigned int duration){
  unsigned long counter = millis() + duration;
  boolean rrain = 0;
  int tamanho = random(1,3);
  int aul = random(0,24);
  while (counter >= millis()){
    int aux; 
    if (!tamanho){
          aux = aul%5 + (aul/5)*25+(aul/25)*5 + 20;
          led[aux] = 0;
          aul = random(0,24);
          tamanho = random(1,3);
    }
    else  {
      aux = aul%5 + (aul/5)*25+(aul/25)*5 + 20;
      led[aux] = 1;
      tamanho--;
    }
    for(int i = 0; i < 100;i++){
      int k = i%5 + ((i%25)/5)*25+(i/25)*5;
      led[k] = led[k + 5];
      if (i%5 == 4)
        exe_led(8);
    }
  }
  
  //Limpeza
 // for (int k=0; k <125;k++){
 //   led[k]=0;  }
}

void snake1 (unsigned int duration){
  for (int k=0; k <125;k++)
    led[k]=0; 
//Acende o led inicial
  const int siZe = 3;
  byte LedHead = random(125);
  byte Size[125];
  while (true)
  {
    switch (random(1,7))
    {
      case 1:
      if (LedHead%5 != 4)
      {
        LedHead += 1;
      }
      break;
      case 2:
      if (LedHead%5 !=0)
      {
        LedHead -= 1;
      }
      break;
      case 3:
      if (LedHead%25 < 20)
      {
        LedHead += 5;
      }
      break;
      case 4:
      if (LedHead%25 >= 5)
      {
        LedHead -= 5;
      }
      break;
      case 5:
        if (LedHead <= 100)
        {
        LedHead += 25;
        }
      break;
      case 6:        
        if (LedHead >= 25)
        {
        LedHead -= 25;
        }
      break;
    }
    byte *Size = new byte[siZe];
    for (byte i = 1; i < siZe; i++)
    {
       int k = Size[i];
       int j = Size[i-1]; 
       Size[i-1] = k;
       Size[i] = j;
    }
    Size[siZe-1] = LedHead;
    for (byte i = 0; i < siZe; i++)
    {
      led[Size[i]] = true;
    }
    led[0]=0;
    exe_led(200);
    for (byte i = 0; i < siZe; i++)
    {
      led[Size[i]] = false;
    }
    delete[] Size;
  }
}
void snake (unsigned int duration){
  unsigned long counter = duration + millis();
  led[12] = 1;
  int hist[8];
  hist[0] = 12;
  byte toPrint = 1;
  byte toDelet = 2;
  byte head[] = {0, 2, 2};
  while (counter >= millis()){
    byte to_true = 0;
    while (to_true == 0){
      int actpos = (25*head[0] + 5*head[1] + head[2]);
      int direc = random(1, 7);
      if (direc == 1 && head[0] != 0 && led[actpos - 25] == 0){
        led[actpos - 25] = 1;
        to_true = 1;
        hist[toPrint] = actpos - 25;
        toPrint += 1;
        head[0] -= 1;
      }
      else if(direc == 2 && head[0] != 4 && led[actpos + 25] == 0){
        led[actpos + 25] = 1;
        to_true = 1;
        hist[toPrint] = actpos + 25;
        toPrint += 1;
        head[0] += 1;
      }
      else if(direc == 3 && head[1] != 0 && led[actpos - 5] == 0){
        led[actpos - 5] = 1;
        to_true = 1;
        hist[toPrint] = actpos - 5;
        toPrint += 1;
        head[1] -= 1;
      }
      else if(direc == 4 && head[1] != 4 && led[actpos + 5] == 0){
        led[actpos + 5] = 1;
        to_true = 1;
        hist[toPrint] = actpos + 5;
        toPrint += 1;
        head[1] += 1;
      }
      else if(direc == 5 && head[2] != 0 && led[actpos - 1] == 0){
        led[actpos - 1] = 1;
        to_true = 1;
        hist[toPrint] = actpos - 1;
        toPrint += 1;
        head[2] -= 1;
      }
      else if(direc == 6 && head[2] != 4 && led[actpos + 1] == 0){
        led[actpos + 1] = 1;
        to_true = 1;
        hist[toPrint] = actpos + 1;
        toPrint += 1;
        head[2] += 1;
      }
    }
    if (toPrint == 8){
      toPrint = 0;
    }
    led[hist[toDelet]] = 0;
    toDelet += 1;
    if (toDelet == 8){
      toDelet = 0;
    } 
    exe_led(200);
  }

}
//Alphabet
void A_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {20, 45, 70, 96, 122, 98, 74, 49, 24, 71, 72, 73, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void B_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {120, 95, 70, 45, 20, 21, 22, 49, 72, 71, 98, 122, 121, 73, 23, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void C_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {120, 95, 70, 45, 20, 21, 22, 23, 121, 122, 123, 24, 124, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void D_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {120, 95, 70, 45, 20, 21, 22, 23, 122, 121, 123, 99, 74, 49, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void E_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {120, 95, 70, 45, 20, 21, 22, 23, 71, 72, 121, 122, 123, 124, 73, 24, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void F_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {120, 95, 70, 45, 20, 71, 72, 121, 122, 123, 124, 73, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
       /* if (l > 0)
        {
          led[posLed[k]-5*l]=!led[posLed[k]-5*l];
          led[posLed[k]-5*(l-1)]=!led[posLed[k]-5*(l-1)];
        }
        else
        {
          led[posLed[k]]=!led[posLed[k]];
          led[posLed[k]-20]=0;
        }
       */ 
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void G_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {124, 123, 122, 121, 120, 95, 70, 45, 20, 21, 22, 23, 24, 49, 74, 73, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void H_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {120, 95, 70, 45, 20, 71, 72, 73, 124, 99, 74, 99, 49, 24, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void I_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {121, 122, 123, 97, 72, 47, 21, 22, 23, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void K_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {20, 45, 70, 95, 120, 71, 72, 98, 123, 48, 24, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void L_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {20, 45, 70, 95, 120, 21, 22, 23, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void M_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {20, 45, 70, 95, 120, 96, 72, 98, 124, 99, 74, 49, 24, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void N_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {20, 45, 70, 95, 120, 96, 72, 48, 124, 99, 74, 49, 24, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void O_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {95, 70, 45, 21, 22, 23, 49, 74, 99, 121, 122, 123, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void P_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {20, 45, 70, 95, 120, 121, 122, 123, 99, 71, 72, 73, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void Q_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {95, 70, 45, 21, 22, 23, 49, 74, 99, 121, 122, 123, 24, 72, 48, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void R_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {20, 45, 70, 95, 120, 121, 122, 123, 99, 71, 72, 73, 48, 24, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void S_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {120, 121, 122, 123, 124, 95, 70, 71, 72, 73, 74, 49, 20, 21, 22, 23, 24, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void T_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {120, 121, 122, 123, 124, 97, 72, 47, 22, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void U_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {120, 95, 70, 45, 20, 21, 22, 23, 24, 49, 74, 99, 124, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void V_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {120, 95, 71, 46, 22, 73, 48, 124, 99, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void W_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {20, 45, 70, 95, 120, 46, 72, 48, 24, 49, 74, 99, 124, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void X_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {72, 20, 46, 48, 24, 120, 96, 98, 124, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void Y_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {72, 47, 22, 120, 96, 98, 124, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void Z_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {120, 121, 122, 123, 124, 98, 72, 46, 20, 21, 22, 23, 24, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void ex1_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {122, 97, 72, 22, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void ex2_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {121, 96, 71, 21, 123, 98, 73, 23, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void ex3_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {122, 97, 72, 22, 120, 95, 70, 20, 124, 99, 74, 24, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void ex5_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {122, 97, 72, 22, 120, 95, 70, 20, 124, 99, 74, 24, 121, 96, 71, 21, 123, 98, 73, 23, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void S2_(unsigned int duration){
//Mantém o frame no tempo desejado
byte posLed[] = {121, 123, 95, 96, 97, 98, 99, 71, 72, 73, 47, 0};
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 5; l++){
      for (byte k = 0; posLed[k] != 0; k++)
      {
        led[posLed[k]-5*l]=!led[posLed[k]-5*l];
      }   
      exe_led(100);
   }
 }
}
void __(unsigned int duration){
  for (int k=0; k <125;k++)
  led[k]=0; 
  unsigned long counter = millis() + duration; 
  while(counter >= millis()){
 }
}
void each_one(unsigned int duration)
{
for (byte k = 0; k < 2; k++)
{
for (byte m = 0, t = 0; m < 5; m++, t = !t)
{  
 if (t == 0)
 { 
    for (byte j = 0, r = 0; j < 5; j++, r = !r)
    {
      for(byte i = 0; i < 5; i++)
      {
        if (r == 0)
        {
          led[i+5*j+25*m]=!led[i+5*j+25*m];
          exe_led(duration);
        }
        else
        {
          led[4-i+5*j+25*m]=!led[4-i+5*j+25*m];
          exe_led(duration);  
        }  
      }
    }
 } 
 if (t == 1)
 {
    for (byte j = 0, r = 0; j < 5; j++, r = !r)
    {
      for(byte i = 0; i < 5; i++)
      {
        if (r == 0)
        {
          led[-5*j-i+(25*m+24)]=!led[-5*j-i+(25*m+24)];
          exe_led(duration);
        }
        else
        {
          led[-4+i-5*j+25*m+24]=!led[-4+i-5*j+25*m+24];
          exe_led(duration);  
        }  
      }
    }
 }
}
}
}
void stars(unsigned int duration)
{
  unsigned long counter = millis() + duration; 
  while(counter >= millis())
  {
    byte i = random(0,125);
    led[i] = 1;
    exe_led(random(30,61)); 
    led[i] = 0;
    exe_led(random(100,201));
    
  }
}
void cube(unsigned int duration)
{
unsigned long counter = millis() + duration; 
while(counter >= millis())
{  
module(4096,3);
exe_led(100);
module(0,3);
exe_led(100);
module(473536,4);
module(469440,3);
module(473536,2);
exe_led(100);
module(0,4);
module(0,3);
module(0,2);
exe_led(100);
module(33554431,1);
module(33080895,2);
module(33080895,3);
module(33080895,4);
module(33554431,5);
exe_led(100);
module(0,1);
module(0,2);
module(0,3);
module(0,4);
module(0,5);
exe_led(100);
module(473536,4);
module(469440,3);
module(473536,2);
exe_led(100);
module(0,4);
module(0,3);
module(0,2);
exe_led(100);
}
}  
void wave (unsigned long duration){
   unsigned long counter_wave = duration + millis();
   for (int i = 0; i < 125; i++){
      led[i] = 0;
   }
   int x = random(125);
   boolean *temp = new boolean[x+1];
   temp[x] = 1;
   led[x] = 1;
   exe_led(200);
   while (counter_wave > millis()){
      for (int i = 0; i < 125; i++){
         switch(temp[i]){
            case 0:
               break;
            case 1:
               led[i] = 0;
               led[i + 25] = 1;
               led[i - 25] = 1;
               led[i + 5] = 1;
               led[i - 5] = 1;
               led[i + 1] = 1;
               led[i - 1] = 1;
               break;
         }
      }
      for (int i = 0; i < 125; i++){
         temp[i] = led[i];
      }
      exe_led(200);
   }
  delete[] temp; 
}
void All(unsigned int duration){
//Mantém o frame no tempo desejado
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
   for(int l=0; l < 124; l++){
      led[l]=1;
      }   
      exe_led(duration);
   }
 }
void Connecting1_(unsigned int duration){
//Mantém o frame no tempo desejado
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
  for(int j = 0; j < 5; j++){
   for(int i = 0; i < 25; i++){
      led[i+j*25]=1;
      }
      exe_led(50);
   if (j != 4)
    for(int i = 0; i < 25; i++){
        led[i+j*25]=0;
    }
  }
  exe_led(150);
  for(int j = 4; j >= 0; j--){
   for(int i = 0; i < 25; i++){
      led[i+j*25]=1;
      }
      exe_led(50);
    if (j != 0)
      for(int i = 0; i < 25; i++){
         led[i+j*25]=0;
      }
  }
  exe_led(200);
 }
}
void Connecting2_(unsigned int duration){
//Mantém o frame no tempo desejado
unsigned long counter = millis() + duration; 
 while(counter >= millis()){
  for(int j = 0; j < 5; j++){
   for(int i = 0; i < 25; i++){
      led[i%5+(i/5)*25+j*5]=1;
      }
      exe_led(50);
   if (j != 4)
    for(int i = 0; i < 25; i++){
        led[i%5+(i/5)*25+j*5]=0;
    }
  }
  exe_led(150);
  for(int j = 4; j >= 0; j--){
   for(int i = 0; i < 25; i++){
      led[i%5+(i/5)*25+j*5]=1;
      }
      exe_led(50);
    if (j != 0)
      for(int i = 0; i < 25; i++){
          led[i%5+(i/5)*25+j*5]=0;
      }
  }
  exe_led(200);
 }
 //for(int l=0; l < 124; l++)
  //    led[l]=0;
}
void batata(unsigned int duration)
{
  unsigned long counter = millis() + duration; 
  while(counter >= millis())
  {
    for (int i = 0; i < 24; i++)
    {
      led[(((i/5)*25)+(i%5))] = 1;
    }
    exe_led(5000);
    for (int j = 0; j < 5; j ++)
    {
        led[100+j] = 0;
        led[105+j] = 1;
    }
    exe_led(200);
    for (int i = 0; i<5; i++)
    {
      led[105+i] = 0;
      led[75+i] = 0;
      led[50+i] = 0;
      led[85+i] = 1;
      led[55+i] = 1;
    }
    exe_led(200);
    
  }
}
 /*static void readSerial(){
  byte reading;  //Stores the reading
  bool isActive; //Stores the led state
  while(Serial.available() > 0){
    reading = Serial.read();
    isActive = (reading & 128) > 0;    //Will be > 0 if reading last byte = 1
    if (isActive) reading ^= 128;      //Will remove last bit if this bit is 1
    if (reading >= 125) reading = 0;   //Reading can't be >= 125
    led[reading] = isActive; 
  }
  exe_led(1);
}
*/
