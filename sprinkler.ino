// This #include statement was automatically added by the Particle IDE.
#include "HTU21D/HTU21D.h"
#include "ThingSpeak/ThingSpeak.h"
#include "HC_SR04/HC_SR04.h"
#include "config.h"

#define ARRAY_SIZE 6
#define ZONE1_MONITOR 1
#define ZONE2_MONITOR 2
#define ZONE3_MONITOR 3
#define ZONE4_MONITOR 4
#define ZONE5_MONITOR 5

int i =0;  //looping variable
double cm = 0.0;
int trigPin = D4;
int echoPin = D5;
int lvl;
int ltrs;
int loops = 4;
int days[8];
int sprink1day;
int sprink1timeonMin;
int sprink1timeonHr;
int sprink1timeoffMin;
int sprink1timeoffHr;
int zone1str[ARRAY_SIZE];
int zone2str[ARRAY_SIZE];
int zone3str[ARRAY_SIZE];
int zone4str[ARRAY_SIZE];
int zone5str[ARRAY_SIZE];
unsigned long lastTime = 0UL;
char publishString[64];
int humd;
int tmp;
int state[5] = {0,0,0,0,0};
int zoneOut[6] = {D7,A4,A5,A6,A7,D7};
int soiltest[4] ={A0,A1,A2,A3};
int soilenable = D2;
int soilzone[6];
int publish;
TCPClient client;
HC_SR04 rangefinder = HC_SR04(trigPin, echoPin, 2.0,110.0);
HTU21D htu = HTU21D();




void setup() {
pinMode(soilenable, OUTPUT);
pinMode(zoneOut[1], OUTPUT);
pinMode(zoneOut[2], OUTPUT);
pinMode(zoneOut[3], OUTPUT);
pinMode(zoneOut[4], OUTPUT);
pinMode(zoneOut[5], OUTPUT);
digitalWrite(zoneOut[1],HIGH);
digitalWrite(zoneOut[2],HIGH);
digitalWrite(zoneOut[3],HIGH);
digitalWrite(zoneOut[4],HIGH);
digitalWrite(zoneOut[5],HIGH);
digitalWrite(soilenable,HIGH);


EEPROM.get(10, zone1str);
EEPROM.get(30, zone2str);
EEPROM.get(50, zone3str);
EEPROM.get(70, zone4str);
EEPROM.get(90, state);
EEPROM.get(110, zone5str);

ThingSpeak.begin(client);

Time.zone(-7);

Serial.begin(9600);
Particle.function("parse",parse);

Serial.println("HTU21D test");

	while(! htu.begin()){
	    Serial.println("HTU21D not found");
	    delay(1000);
	}
Serial.println("HTU21D OK");
days[0] = 0;


if (state[0]==1){digitalWrite(zoneOut[1],LOW);}
else {digitalWrite(zoneOut[1],HIGH);}
if (state[1]==1){digitalWrite(zoneOut[2],LOW);}
else {digitalWrite(zoneOut[2],HIGH);}
if (state[2]==1){digitalWrite(zoneOut[3],LOW);}
else {digitalWrite(zoneOut[3],HIGH);}
if (state[3]==1){digitalWrite(zoneOut[4],LOW);}
else {digitalWrite(zoneOut[4],HIGH);}
if (state[4]==1){digitalWrite(zoneOut[5],LOW);}
else {digitalWrite(zoneOut[5],HIGH);}

lvlcheck();
soilCheck();

};


void loop(){
   runZone(1);
   runZone(2);
   runZone(3);
   runZone(4);
   runZone(5);

     unsigned long now = millis();
    //Every 30 seconds publish uptime
    if (now-lastTime>30000UL) {
        lastTime = now;
        // now is in milliseconds
        lvlcheck();
        tmp = htu.readTemperature();
        humd = htu.readHumidity();
       if (loops ==2){
        soilCheck();
        sprintf(publishString,"{\"Tmp\": %u, \"Hum\": %u, \"Lvl\": %u, \"Ltrs\": %u}",tmp,humd,lvl,ltrs);
        Particle.publish("Stats",publishString);
        }

        if (loops == 4 ){
            soilCheck();
            sprintf(publishString,"{\"Tmp\": %u, \"Hum\": %u, \"Lvl\": %u, \"Ltrs\": %u}",tmp,humd,lvl,ltrs);
            Particle.publish("Stats",publishString);
            Publishzone(6);
            delay(300);
            Publishzone(1);
            delay(300);
            Publishzone(2);
            delay(300);
            Publishzone(3);
            delay(300);
            Publishzone(4);
            delay(300);
            Publishzone(5);

            loops = 0;
            publish = 0;

        }
		loops = ++loops;
    }
};


int lvlcheck(){
cm = rangefinder.getDistanceCM();
delay(100);
lvl = 103-cm;
if (lvl > 48){
    ltrs = lvl*11.1 + 600;
}
else {ltrs = lvl * 23.6;}
return lvl;
// barell heigh 68.5  x 18.76  this is calculated for my own setup ( 1 ibc tote and 3 plastic drums on thier side )

};


int parse(String command){
Serial.println("got it");
Serial.print("Hum:"); Serial.println(htu.readHumidity());
Serial.print("Temp:"); Serial.println(htu.readTemperature());
lvlcheck();
Serial.print("CM:");Serial.println(cm);
Serial.print("LvL:");Serial.println(lvl);
Serial.println();

    char charBuf[50];
    command.toCharArray(charBuf, 50);

    //Begin black magic supplied by @mdma at: some what butcherd by me
    // https://community.spark.io/t/gpio-control-via-gui/6310/7
   // const int value_count = ARRAY_SIZE;  // the maximum number of values
    int values[7];    // store the values here

    char string[25];
    strcpy(string, charBuf);  // the string to split
    int idx = 0;
    for (char* pt=strtok(string, "~"); pt && idx<7; pt=strtok(NULL, "~")) {
       values[idx++] = atoi(pt);
    };
    //End black magic.

//    startHour = values[1];
//    startMinute = values[2];
//    stopHour = values[3];
//    stopMinute = values[4];
//    days = values[5];




if (values[0] == 1){
int zOne;
 zOne = values[6];
switch(zOne){
    case(1):
    for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zone1str[i]=values[i+1];
    }
    EEPROM.put(10, zone1str);
    Days(zone1str[4]);
    break;

    case(2):
    for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zone2str[i]=values[i+1];
    }
    EEPROM.put(30, zone2str);
    Days(zone2str[4]);
    break;

    case(3):
    for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zone3str[i]=values[i+1];
    }
    EEPROM.put(50, zone3str);
    Days(zone3str[4]);
    break;

    case(4):
    for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zone4str[i]=values[i+1];
    }
    EEPROM.put(70, zone4str);
    Days(zone4str[4]);
    break;

    case(5):
    for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zone5str[i]=values[i+1];
    }
    EEPROM.put(110, zone5str);
    Days(zone5str[4]);
    break;
}
Publishzone(zOne);
}
if (values[0] == 2){
int mZone;
    mZone = values[1];
        if (values[2]==0){
            Serial.print("manual turning zone ");
            Serial.print(mZone);
            Serial.println(" off");
            digitalWrite(zoneOut[mZone], HIGH);
            Serial.println(zoneOut[mZone]);
            state[mZone-1] = 0;
            EEPROM.put(90, state);
        }
        if(values[2]==1){
            Serial.print("manual turning zone ");
            Serial.print(mZone);
            Serial.println(" on");
            digitalWrite(zoneOut[mZone], LOW);
            state[mZone-1] = 1;
            Serial.println(zoneOut[mZone]);
            EEPROM.put(90, state);
        }
Publishzone(mZone);
}
return 0;
}
int startmin;
int stopmin;
int runZone(int cycle){  //this is our primary time loop
int zoneTorun[ARRAY_SIZE];
int monitor;

    switch(cycle){
        case(1):
        for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zoneTorun[i]=zone1str[i];
        monitor = ZONE1_MONITOR;
    }
        break;
        case(2):
        for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zoneTorun[i]=zone2str[i];
        monitor = ZONE2_MONITOR;
    }
        break;
        case(3):
        for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zoneTorun[i]=zone3str[i];
        monitor = ZONE3_MONITOR;
    }
        break;
        case(4):
        for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zoneTorun[i]=zone4str[i];
        monitor = ZONE4_MONITOR;
    }
        break;
        case(5):
        for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zoneTorun[i]=zone5str[i];
        monitor = ZONE5_MONITOR;
    }
    break;
    }
    startmin = tomin(zoneTorun[0]) + zoneTorun[1];
    stopmin = tomin(zoneTorun[2]) + zoneTorun[3];
   //soil moisture time adjustmets

   if (monitor > 0 && monitor < 6){
        if (soilzone[monitor] > 600){
            zoneTorun[4] = 0 ;
            Serial.print("zone ");
            Serial.print(cycle);
            Serial.println(" does not need water");
            if (loops == 1 && publish == 0) {
            sprintf(publishString,"%u, no water needed ",soilzone[monitor]);
            Particle.publish("soil5",publishString);
            publish + 1;
            }
        }
    if (soilzone[monitor] > 300 && soilzone[monitor] < 600){
        int minmod;
        minmod = stopmin - startmin;
        minmod = minmod / 2;
        stopmin = stopmin - minmod;


       if (loops == 1) {
           if (publish == 0){
            int newstopmin;
            int newstophour = stopmin / 60;
            int work = newstophour * 60;
            newstopmin = stopmin - work;
        sprintf(publishString,"%u,mon %u:%u time off, %u:%u modified %u",monitor,zoneTorun[2],zoneTorun[3],newstophour,newstopmin,stopmin);
        Particle.publish("soil5",publishString);
        publish + 1;
           }
        }
    }

    }


Days(zoneTorun[4]);
              //we turn things off before we turn them on just in case
        if (days[Time.weekday()] == 1){             //check the day
             int realmins = Time.hour();
             realmins = tomin(realmins) + Time.minute();

             if(realmins >= stopmin){
                 if(state[cycle-1] == 1){
               Serial.print("turning zone ");
               Serial.print(cycle);
               Serial.println(" off");
               digitalWrite(zoneOut[cycle], HIGH);
               Serial.println(zoneOut[cycle]);
               Publishzone(cycle);
               state[cycle-1] = 0;
               EEPROM.put(90, state);
                 }
            }
            if(realmins == startmin ){
                if(state[cycle-1] == 0){
                Serial.print("turning zone ");
                Serial.print(cycle);
                Serial.println(" on");
                digitalWrite(zoneOut[cycle], LOW);
                Publishzone(cycle);
                state[cycle-1] = 1;
                Serial.println(zoneOut[cycle]);
                EEPROM.put(90, state);
                }
            }
            }
    };

int Days(int daYs) {
 int y =0;
        byte data = daYs;
            for (byte y=0; y<7; ++y) {
                if (data & (1<<y)) {
                    //Serial.println("day ");
                    //Serial.println(y+1);
                    //Serial.println("HI");
                    days[y+1] = 1;
                } else {
                    //Serial.println("day");
                    //Serial.println(y);
                    //Serial.println("LO");
                    days[y+1] = 0;
                }
            }

        }

int Publishzone(int pzone) {

    if (pzone == 1){
        sprintf(publishString,"%u-%u:%u, %u:%u - %u",state[0],zone1str[0],zone1str[1],zone1str[2],zone1str[3],zone1str[4]);
		//sprintf(publishString,"{\"sta\":%u,\"sth\":%u,\"stm\":%u,\"sph\":%u,\"spm\":%u,\"day\":%u}",state[0],zone1str[0],zone1str[1],zone1str[2],zone1str[3],zone1str[4]);
        Particle.publish("Zone1",publishString);
        ThingSpeak.setField(1,state[0]);
        ThingSpeak.writeFields(THINGSPEAKCHANNEL2, THINGSPEAKWRITEAPI2);
    }
    if (pzone == 2){
        sprintf(publishString,"%u-%u:%u, %u:%u - %u",state[1],zone2str[0],zone2str[1],zone2str[2],zone2str[3],zone2str[4]);
        Particle.publish("Zone2",publishString);
        ThingSpeak.setField(2,state[1]);
        ThingSpeak.writeFields(THINGSPEAKCHANNEL2, THINGSPEAKWRITEAPI2);
    }
    if (pzone == 3){
        sprintf(publishString,"%u-%u:%u, %u:%u - %u",state[2],zone3str[0],zone3str[1],zone3str[2],zone3str[3],zone3str[4]);
        Particle.publish("Zone3",publishString);
        ThingSpeak.setField(3,state[2]);
        ThingSpeak.writeFields(THINGSPEAKCHANNEL2, THINGSPEAKWRITEAPI2);
    }
    if (pzone == 4){
        sprintf(publishString,"%u-%u:%u, %u:%u - %u",state[3],zone4str[0],zone4str[1],zone4str[2],zone4str[3],zone4str[4]);
        Particle.publish("Zone4",publishString);
        ThingSpeak.setField(4,state[3]);
        ThingSpeak.writeFields(THINGSPEAKCHANNEL2, THINGSPEAKWRITEAPI2);
    }
    if (pzone == 5){
        //sprintf(publishString,"%u-%u:%u, %u:%u - %u",state[4],zone5str[0],zone5str[1],zone5str[2],zone5str[3],zone5str[4]);
        sprintf(publishString,"{\"sta\":%u,\"sth\":%u,\"stm\":%u,\"sph\":%u,\"spm\":%u,\"day\":%u}",state[4],zone5str[0],zone5str[1],zone5str[2],zone5str[3],zone5str[4]);
        Particle.publish("Zone5",publishString);
        }

    if (pzone == 6){ //thingspeak
        ThingSpeak.setField(1,lvl);
	      ThingSpeak.setField(2,ltrs);
				ThingSpeak.setField(3,htu.readTemperature());
				ThingSpeak.setField(4,htu.readHumidity());
				ThingSpeak.setField(5,soilzone[1]);
				ThingSpeak.setField(6,soilzone[2]);
				ThingSpeak.setField(7,soilzone[3]);
				ThingSpeak.setField(8,soilzone[4]);
				ThingSpeak.writeFields(THINGSPEAKCHANNEL1, THINGSPEAKWRITEAPI1); 

    }




 };
void soilCheck(){
    digitalWrite(soilenable, LOW);
    soilzone[1] = 100; //analogRead(soiltest[0]);
    soilzone[2] = 280; // analogRead(soiltest[1]);
    soilzone[3] = 200; //analogRead(soiltest[2]);
    soilzone[4] = 205; //analogRead(soiltest[3]);
    soilzone[5] = 500;
    digitalWrite(soilenable, HIGH);

};


int tomin(int input){
input = input * 60;
return input;
}
