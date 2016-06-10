// This #include statement was automatically added by the Particle IDE.
#include "HTU21D/HTU21D.h"
#include "ThingSpeak/ThingSpeak.h"
#include "HC_SR04/HC_SR04.h"

#define ARRAY_SIZE 6


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
unsigned long lastTime = 0UL;
char publishString[64];
int humd;
int tmp;
int state[4] = {0,0,0,0};
int zoneOut[5] = {D7,A4,A5,A6,A7};
TCPClient client;
HC_SR04 rangefinder = HC_SR04(trigPin, echoPin, 2.0,102.0);
HTU21D htu = HTU21D();




void setup() {
pinMode(zoneOut[1], OUTPUT);
pinMode(zoneOut[2], OUTPUT);
pinMode(zoneOut[3], OUTPUT);
pinMode(zoneOut[4], OUTPUT);
digitalWrite(zoneOut[1],HIGH);
digitalWrite(zoneOut[2],HIGH);
digitalWrite(zoneOut[3],HIGH);
digitalWrite(zoneOut[4],HIGH);


EEPROM.get(10, zone1str);
EEPROM.get(30, zone2str);
EEPROM.get(50, zone3str);
EEPROM.get(70, zone4str);
EEPROM.get(90, state);

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

lvlcheck();


};


void loop(){
   runZone(1);
   runZone(2);
   runZone(3);
   runZone(4);
     unsigned long now = millis();
    //Every 30 seconds publish uptime
    if (now-lastTime>30000UL) {
        lastTime = now;
        // now is in milliseconds
        lvlcheck();
        tmp = htu.readTemperature();
        humd = htu.readHumidity();
        if (loops == 4 ){
            Publishzone(1);
            delay(255);
            Publishzone(2);
            delay(255);
            Publishzone(3);
            delay(255);
            Publishzone(4);
            delay(255);
            loops = 0;
        }
        sprintf(publishString,"{\"Tmp\": %u, \"Hum\": %u, \"Lvl\": %u, \"Ltrs\": %u}",tmp,humd,lvl,ltrs);
        Particle.publish("Stats",publishString);
				ThingSpeak.setField(1,lvl);
				ThingSpeak.setField(2,ltrs);
				ThingSpeak.setField(3,htu.readTemperature());
				ThingSpeak.setField(4,htu.readHumidity());
				ThingSpeak.writeFields(channelid, "write api key");

				loops = ++loops;
    }

};


int lvlcheck(){
cm = rangefinder.getDistanceCM();
delay(100);
lvl = 104-cm;
if (lvl > 68.5){
    ltrs = lvl*10 + 600;
}
else { ltrs = lvl * 18.76;}
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

int runZone(int cycle){  //this is our primary time loop
int zoneTorun[ARRAY_SIZE];
    switch(cycle){
        case(1):
        for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zoneTorun[i]=zone1str[i];
    }
        break;
        case(2):
        for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zoneTorun[i]=zone2str[i];
    }
        break;
        case(3):
        for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zoneTorun[i]=zone3str[i];
    }
        break;
        case(4):
        for (i = 0; i < ARRAY_SIZE; i = ++i) {
        zoneTorun[i]=zone4str[i];
    }
        break;
    }

    Days(zoneTorun[4]);

           //we turn things off before we turn them on just in case
        if (days[Time.weekday()] == 1){             //check the day
             Serial.println(Time.weekday());
             Serial.println("today is the day");
             Serial.print("zone ");
             Serial.println(cycle);
             Serial.println(Time.hour());
             Serial.println(zoneTorun[0]);
             Serial.println(Time.minute());
             Serial.println(zoneTorun[1]);
             Serial.println(zoneOut[cycle]);
             if(Time.hour() == zoneTorun[2] && Time.minute()==zoneTorun[3]){
               Serial.print("turning zone ");
               Serial.print(cycle);
               Serial.println(" off");
               digitalWrite(zoneOut[cycle], HIGH);
               Serial.println(zoneOut[cycle]);
               if (state[cycle-1] == 1){Publishzone(cycle);}
               state[cycle-1] = 0;
               EEPROM.put(90, state);

            }
            if(Time.hour() == zoneTorun[0] && Time.minute()==zoneTorun[1]){
                Serial.print("turning zone ");
                Serial.print(cycle);
                Serial.println(" on");
                digitalWrite(zoneOut[cycle], LOW);
                if (state[cycle-1] == 0){Publishzone(cycle);}
                state[cycle-1] = 1;
                Serial.println(zoneOut[cycle]);
                EEPROM.put(90, state);

            }
            }


    }




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
        Particle.publish("Zone1",publishString);
    }
    if (pzone == 2){
        sprintf(publishString,"%u-%u:%u, %u:%u - %u",state[1],zone2str[0],zone2str[1],zone2str[2],zone2str[3],zone2str[4]);
        Particle.publish("Zone2",publishString);
    }
    if (pzone == 3){
        sprintf(publishString,"%u-%u:%u, %u:%u - %u",state[2],zone3str[0],zone3str[1],zone3str[2],zone3str[3],zone3str[4]);
        Particle.publish("Zone3",publishString);
    }
    if (pzone == 4){
        sprintf(publishString,"%u-%u:%u, %u:%u - %u",state[3],zone4str[0],zone4str[1],zone4str[2],zone4str[3],zone4str[4]);
        Particle.publish("Zone4",publishString);
    }


};
