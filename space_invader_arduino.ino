//read encoder
#include <Encoder.h>

Encoder encoder(0, 1);
double currentAngle = 0;
double currentPressure = 0;
float desiredAngle = 0.0;

int sensorPin = A4;   
int sensorValue = 0; 
float Vout=0;
float currentPressyre=0;
int offset=0;

void setup() {
  encoder.write(0); //zero out encoder
  Serial.begin(115200); //9600?
  //pressure sensor setup
    int i=0;
    int sum=0;
    offset=0;
    for(i=0;i<10;i++)
    {
         sensorValue = analogRead(sensorPin)-512;
         sum+=sensorValue;
    }
    offset=sum/10.0;
}

void loop() {
  updateCurrentAngle();

  //readSerial();
  
  
  updateCurrentPressure();
  Serial.print((float)currentAngle, 2);
  Serial.print(",");
  Serial.println((float)currentPressure, 2);
  delay(20);
}

void updateCurrentAngle() {
  int pos = encoder.read();
  currentAngle = (-270.0/2875.0) * pos; //max angle range divided by raw encoder range
  //Serial.print("current angle: ");
  //Serial.println((float)currentAngle, 2);

}

void updateCurrentPressure() {

    //Serial.println("Ok");
    //while(1)
    //{
       sensorValue = analogRead(sensorPin)-offset; 
       Vout=(5*sensorValue)/1024.0;
       currentPressure=(Vout-2.5) * 1000;          
       //delay(1000);   
    //}
    //Serial.print("pressure val: ");
    //Serial.println((float)currentPressure, 2);
    delay(20);

}

void readSerial() {
  String incoming;
  if (Serial.available() > 0) {
    incoming = Serial.readStringUntil('\n');
    desiredAngle = incoming.toFloat();
    //Serial.println(incoming.toFloat(), 2);
  }
}
