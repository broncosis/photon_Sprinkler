// This #include statement was automatically added by the Particle IDE.
#include <HC_SR04.h>
#include <HTU21D.h>
#include <ThingSpeak.h>
#include "config.h"
#define ARRAY_SIZE 6

int i =0;  //looping variable
double cm = 0.0;
int trigPin = D4;
int echoPin = D5;
int lvl;
int ltrs;
int loops = 1;
int days[8];
int sprink1day;
int sprink1timeonMin;
int sprink1timeonHr;
int sprink1timeoffMin;
int sprink1timeoffHr;
int startmin;
int stopmin;
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
int soilzone[6] = {0,0,0,0,0,0};
int publish[5] = {0,0,0,0,0};
int toggler[3] = {0,0,0};
byte out = 0B11111111;
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
digitalWrite(soilenable,LOW);


EEPROM.get(10, zone1str);
EEPROM.get(30, zone2str);
EEPROM.get(50, zone3str);
EEPROM.get(70, zone4str);
EEPROM.get(90, state);
EEPROM.get(110, zone5str);

ThingSpeak.begin(client);

Time.zone(TIME_ZONE);

Serial.begin(9600);
Particle.function("parse",parse);

Serial.println("HTU21D test");

	while(! htu.begin()){
	    sprintf(publishString, "{\"Tmp\": HTU21D not found}");
	    Particle.publish("Stats",publishString);
	    delay(2000);
	}
sprintf(publishString, "{\"Tmp\": HTU21D ok}");
	    Particle.publish("Stats",publishString);
//Serial.println("HTU21D OK");
days[0] = 0;


if (state[0]==1){
    digitalWrite(zoneOut[1],LOW);
    out = out - PIN1;
}
else {digitalWrite(zoneOut[1],HIGH);}
if (state[1]==1){
    digitalWrite(zoneOut[2],LOW);
    out = out - PIN2;
    }
else {digitalWrite(zoneOut[2],HIGH);}
if (state[2]==1){
    digitalWrite(zoneOut[3],LOW);
    out = out - PIN3;
    }
else {digitalWrite(zoneOut[3],HIGH);}
if (state[3]==1){
    digitalWrite(zoneOut[4],LOW);
    out = out - PIN4;
    }
else {digitalWrite(zoneOut[4],HIGH);}
if (state[4]==1){
    digitalWrite(zoneOut[5],LOW);
    out = out - PIN5;
    }
else {digitalWrite(zoneOut[5],HIGH);}

Wire.beginTransmission(Addr);
Wire.write(out);
Wire.endTransmission();

lvlcheck();
soilCheck();

};


void loop(){

     unsigned long now = millis();
    //Every 30 seconds publish uptime
    if (now-lastTime>15000UL) {
        lastTime = now;
        // now is in milliseconds
        // code here runs every 15 seconds  every time through
        lvlcheck();
        soilCheck();
        tmp = htu.readTemperature();
        humd = htu.readHumidity();
        if (loops == 1){        //first time through the loop
                Publishzone(1);
								Publishzone(16);
                }
        if (loops == 2){        //second time through the loop
                Publishzone(2);
                }
        if (loops == 3){        //third time through the loop
                Publishzone(3);
								Publishzone(19);
                }
				if (loops == 4){
								Publishzone(4);
				 				}
				if (loops == 5){
								Publishzone(5);
			 					}
				if (loops == 6){
								Publishzone(18);
			 					}
				if (loops == 7){
								Publishzone(17);
								}
				if (loops == 8){        //forteenth time through

                loops = 0;
                publish[0] = 0;
                publish[1] = 0;
                publish[2] = 0;
                publish[3] = 0;
                publish[4] = 0;
                }

		loops = ++loops;
    }
runZone(1);
runZone(2);
runZone(3);
runZone(4);
runZone(5);


};


int parse(String command){
Serial.println("got it");

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
if (values[0] == 2){  //manual control
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
if (values[0] == 3){  // force update of all zones and stats
Publishzone(1);
delay(300);
Publishzone(2);
delay(300);
Publishzone(3);
delay(300);
Publishzone(4);
delay(300);
Publishzone(5);
delay(300);
Publishzone(18);

};
return 0;
};


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

   //too wet don't water
   if (monitor > 0 && monitor < 6){
        if (soilzone[monitor] > 3900){
            zoneTorun[4] = 0 ;
            Serial.print("zone ");
            Serial.print(cycle);
            Serial.println(" does not need water");
            if (loops == 1 ){
                if (publish[cycle - 1] == 0) {
            sprintf(publishString,"%u, no water needed for zone %u",soilzone[monitor],cycle);
            Particle.publish("soil",publishString);
            publish[cycle - 1] + 1;
            }}
        }
        //needs some water cut time in half
    if (soilzone[monitor] > 1200 && soilzone[monitor] < 2200){
        int minmod;
        minmod = stopmin - startmin;
        minmod = minmod / 2;
        stopmin = stopmin - minmod;

     //monitor coments
       if (loops == 1) {
           if (publish[cycle - 1] == 0){
            int newstopmin;
            int newstophour = stopmin / 60;
            int work = newstophour * 60;
            newstopmin = stopmin - work;
        sprintf(publishString,"zone %u - %u,mon %u:%u time off, %u:%u modified %u",cycle,monitor,zoneTorun[2],zoneTorun[3],newstophour,newstopmin,stopmin);
        Particle.publish("soil",publishString);
        publish[cycle - 1] + 1;
           }
        }
    }
    // no changes
     if (soilzone[monitor] < 2800) {
        if (loops == 1 ){
                if (publish[cycle - 1] == 0) {
                    sprintf(publishString,"%u, no adjustmet needed for zone %u",soilzone[monitor],cycle);
                    Particle.publish("soil",publishString);
                     publish[cycle - 1] + 1;
                    }}}
    }


Days(zoneTorun[4]);
              //we turn things off before we turn them on just in case
        if (days[Time.weekday()] == 1){             //check the day
             int realmins = Time.hour();
             realmins = tomin(realmins) + Time.minute();
             // we use try for a extar minute to make sure its off
             if(realmins >= stopmin && realmins <= stopmin + 1){
                 if(state[cycle-1] == 1){
               digitalWrite(zoneOut[cycle], HIGH);
               Publishzone(cycle);
               state[cycle-1] = 0;
               EEPROM.put(90, state);
                 }
            }
            if(realmins >= startmin && realmins <= startmin + 1){
                if(state[cycle-1] == 0){
                digitalWrite(zoneOut[cycle], LOW);
                Publishzone(cycle);
                state[cycle-1] = 1;
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

        };

int Publishzone(int pzone) {

    if (pzone == 1){    // zone 1 publish
        sprintf(publishString,"{\"sta\":%u,\"sth\":%u,\"stm\":%u,\"sph\":%u,\"spm\":%u,\"day\":%u}",state[0],zone1str[0],zone1str[1],zone1str[2],zone1str[3],zone1str[4]);
		Particle.publish("Zone1",publishString);
       // ThingSpeak.setField(1,state[0]);
    //    ThingSpeak.writeFields(THINGSPEAKCHANNEL2, THINGSPEAKWRITEAPI2);
        }
    if (pzone == 2){    // zone 2 publish
        sprintf(publishString,"{\"sta\":%u,\"sth\":%u,\"stm\":%u,\"sph\":%u,\"spm\":%u,\"day\":%u}",state[1],zone2str[0],zone2str[1],zone2str[2],zone2str[3],zone2str[4]);
        Particle.publish("Zone2",publishString);
    //    ThingSpeak.setField(2,state[1]);
     //   ThingSpeak.writeFields(THINGSPEAKCHANNEL2, THINGSPEAKWRITEAPI2);
        }
    if (pzone == 3){    // zone 3 publish
        sprintf(publishString,"{\"sta\":%u,\"sth\":%u,\"stm\":%u,\"sph\":%u,\"spm\":%u,\"day\":%u}",state[2],zone3str[0],zone3str[1],zone3str[2],zone3str[3],zone3str[4]);
        Particle.publish("Zone3",publishString);
      //  ThingSpeak.setField(3,state[2]);
        //ThingSpeak.writeFields(THINGSPEAKCHANNEL2, THINGSPEAKWRITEAPI2);
        }
    if (pzone == 4){    // zone 4 publish
        sprintf(publishString,"{\"sta\":%u,\"sth\":%u,\"stm\":%u,\"sph\":%u,\"spm\":%u,\"day\":%u}",state[3],zone4str[0],zone4str[1],zone4str[2],zone4str[3],zone4str[4]);
        Particle.publish("Zone4",publishString);
       // ThingSpeak.setField(4,state[3]);
    //    ThingSpeak.writeFields(THINGSPEAKCHANNEL2, THINGSPEAKWRITEAPI2);
        }
        // zone five inactive test zone no thing speak data
    if (pzone == 5){    // zone 5 publish
        sprintf(publishString,"{\"sta\":%u,\"sth\":%u,\"stm\":%u,\"sph\":%u,\"spm\":%u,\"day\":%u}",state[4],zone5str[0],zone5str[1],zone5str[2],zone5str[3],zone5str[4]);
        Particle.publish("Zone5",publishString);
        }

    if (pzone == 16){ //thingspeak
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

    if (pzone == 17){    // publish soil info
        sprintf(publishString,"zone 1 %u - zone 2 %u - zone 3 %u - zone 4 %u",soilzone[1],soilzone[2],soilzone[3],soilzone[4]);
        Particle.publish("soil",publishString);
        }

    if (pzone == 18){  //publish stats
        sprintf(publishString,"{\"Tmp\": %u, \"Hum\": %u, \"Lvl\": %u, \"Ltrs\": %u}",tmp,humd,lvl,ltrs);
        Particle.publish("Stats",publishString);

        }

   if (pzone == 19){
            ThingSpeak.setField(1,state[0]);
            ThingSpeak.setField(2,state[1]);
            ThingSpeak.setField(3,state[2]);
            ThingSpeak.setField(4,state[3]);
            ThingSpeak.writeFields(THINGSPEAKCHANNEL2, THINGSPEAKWRITEAPI2);

   }


 };
void soilCheck(){
	if (toggler[0] == 1){
			soilzone[1] = analogRead(soiltest[0]);
    	soilzone[2] = analogRead(soiltest[1]);
    	soilzone[3] = analogRead(soiltest[2]);
    	soilzone[4] = analogRead(soiltest[3]);
    	soilzone[5] = 800;
    	digitalWrite(soilenable, LOW);
			toggler[0] = 0;
			return;
			}
		if (toggler[0] == 0) {
			digitalWrite(soilenable, HIGH);
			toggler[0] = 1;
			return;
		}
};


int tomin(int input){
input = input * 60;
return input;
}

int lvlcheck(){
pinMode(echoPin, OUTPUT); // Then we set echo pin to output mode
digitalWrite(echoPin, LOW); // We send a LOW pulse to the echo pin
delayMicroseconds(200);
pinMode(echoPin, INPUT);
delayMicroseconds(200);

cm = rangefinder.getDistanceCM();
//delay(100);
lvl = 103-cm;
if (lvl > 48){
    ltrs = lvl*11.1 + 600;
}
else {ltrs = lvl * 23.6;}
return lvl;
// barell heigh 68.5  x 18.76  this is calculated for my own setup ( 1 ibc tote and 3 plastic drums on thier side )
};


int ZONEon(int input){
if (input == 1){out = out - PIN1;}
if (input == 2){out = out - PIN2;}
if (input == 3){out = out - PIN3;}
if (input == 4){out = out - PIN4;}
if (input == 5){out = out - PIN5;}

Wire.beginTransmission(Addr);
Wire.write(out);
Wire.endTransmission();

};

int ZONEoff(int input){
if (input == 1){out = out + PIN1;}
if (input == 2){out = out + PIN2;}
if (input == 3){out = out + PIN3;}
if (input == 4){out = out + PIN4;}
if (input == 5){out = out + PIN5;}

Wire.beginTransmission(Addr);
Wire.write(out);
Wire.endTransmission();
};

int sanityCheck(){
    if (lvl <= 10){
        digitalWrite(zoneOut[1], HIGH);
        digitalWrite(zoneOut[2], HIGH);
        digitalWrite(zoneOut[3], HIGH);
        digitalWrite(zoneOut[4], HIGH);
} };
