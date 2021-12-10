#define OFFMODE 1
#define ONMODE 0

const byte trafficLight[3] = {13,12,11}; //신호등 핀
int lightTime[3] = {6,2,6}; //신호등 유지시간
unsigned long timeVal = 0; //이전시간
int indexVal = 0;

char ch;
int state = OFFMODE;

void setup() {
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  Serial.begin(9600);
  
  for(int i=0;i<3;i++){
    pinMode(trafficLight[i], OUTPUT);
    }  
      //초기상태
    digitalWrite(trafficLight[indexVal], HIGH); //녹색등
    digitalWrite(7,HIGH);
}

void loop() {
  
  if(Serial.available()){
    ch = Serial.read();
  }
  if(millis()-timeVal>=lightTime[indexVal]*1000){ //신호등 동작 trafficLight[3]순서대로
    digitalWrite(trafficLight[indexVal], LOW);  //이전등 끄기
    
    digitalWrite(6,LOW);
    delay(1000);
    digitalWrite(7,HIGH);
    delay(100);
    indexVal++; //신호등위치 증
    if(indexVal==3)indexVal=0; // 신호등위치가 3이 되면 다시 0으로 처음위치로 돌아감
    digitalWrite(trafficLight[indexVal], HIGH); //새로운등 켜기
    delay(100);
    digitalWrite(6,HIGH);
    digitalWrite(7,LOW);
    timeVal=millis();
    
  }
  if(ch=='1'){
    state=ONMODE;
  }else{
    state=OFFMODE;
  }
  
  if(state==ONMODE){
    digitalWrite(11,HIGH); // 초록불 지속시간 증가
    delay(6000);
  }else{
//  OFFMODE 
    digitalWrite(trafficLight[indexVal], HIGH);
    
    if(millis()-timeVal>=lightTime[indexVal]*1000){   //신호등 동작 trafficLight[3]순서대로
    digitalWrite(trafficLight[indexVal], LOW);  //이전등 끄기
    indexVal++; //신호등위치 증가
    if(indexVal==3)indexVal=0; // 신호등위치가 3이 되면 다시 0으로 처음위치로 돌아감
    digitalWrite(trafficLight[indexVal], HIGH); //새로운 등 켜기
    timeVal=millis();
  }
  }
}
