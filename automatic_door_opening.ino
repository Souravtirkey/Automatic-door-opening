#define sensorPin A0 // for PIR sensor 

#define G_led 8 // Green Led
#define R_led 9 // Red Led

#define in1 2  
#define in2 3  

int set_timer=5;

int sensor =0;
int seconds =0;
int flag=0;
long delay_Start;

void setup()
{ 
Serial.begin(9600);

pinMode(sensorPin, INPUT); 

pinMode(R_led,OUTPUT); 
pinMode(G_led,OUTPUT); 

//motor pin
pinMode(in1,OUTPUT); 
pinMode(in2,OUTPUT); 

digitalWrite(in1, LOW); // Door Open 
digitalWrite(in2, HIGH);// Door Close 
delay(2000); 
digitalWrite(in1, LOW); // Door Open 
digitalWrite(in2, LOW); // Door Close 
}

void loop(){
sensor = digitalRead(sensorPin);

if(sensor==1)
{ 
Serial.println("Motion detected!");
digitalWrite(R_led, HIGH); 
digitalWrite(G_led, HIGH); 

if(flag==0){
digitalWrite(in1, HIGH); 
digitalWrite(in2, LOW);  
delay(2000); 
digitalWrite(in1, LOW); 
digitalWrite(in2, LOW); 
}

seconds=0;
flag=1;
delay_Start = millis(); // set start time
}else{ // pin state change: 1 -> 0
Serial.println("Motion stopped!");
digitalWrite(G_led, LOW); // LED Turn Off. 
}

if((flag==1) && (millis()- delay_Start) > 999){ 
seconds = seconds+1;  
delay_Start = millis(); // set start time
}

if(seconds>set_timer){
digitalWrite(R_led, LOW); // LED Turn Off.   

digitalWrite(in1, LOW); // Door Open 
digitalWrite(in2, HIGH);// Door Close 
delay(2000); 
digitalWrite(in1, LOW); // Door Open 
digitalWrite(in2, LOW); // Door Close 
flag=0;
seconds=0; 
}

delay(100);
}