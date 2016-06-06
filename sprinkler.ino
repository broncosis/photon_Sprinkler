// This #include statement was automatically added by the Particle IDE.
#include "ThingSpeak/ThingSpeak.h"
#include "HC_SR04/HC_SR04.h"


double cm = 0.0;
int trigPin = D4;
int echoPin = D5;
int z1out = D2;
int z2out = D3;
int z3out = D6;
int z4out = D7;
int z5out = TX;
int soil1 = A0;
int lvl;
int ltrs;
int startHour = 0;
int startMinute = 0;
int stopHour = 0;
int stopMinute = 0;
int zOne = 0;
int days =0;
int sprink1day;
int sprink1timeonMin;
int sprink1timeonHr;
int sprink1timeoffMin;
int sprink1timeoffHr;

HC_SR04 rangefinder = HC_SR04(trigPin, echoPin);


void setup() {
Particle.variable("cm", &cm, DOUBLE);
Time.zone(-8);
Serial.begin(9600);
Particle.function("parse",parse);
};

void loop()
{


    if (Time.weekday() == sprink1day){
        if (Time.hour() == sprink1timeonHr){
            if (Time.minute() == sprink1timeonMin){
               lvlcheck();
            };
        };
    };


};

void lvlcheck(){
cm = rangefinder.getDistanceCM();
delay(100);
lvl = 102-cm;
ltrs = lvl*10;
};


int parse(String command){
    char charBuf[30];
    command.toCharArray(charBuf, 30);

    //Begin black magic supplied by @mdma at:
    // https://community.spark.io/t/gpio-control-via-gui/6310/7
    const int value_count = 10;  // the maximum number of values
    int values[value_count];    // store the values here

    char string[25];
    strcpy(string, charBuf);  // the string to split
    int idx = 0;
    for (char* pt=strtok(string, "~"); pt && idx<value_count; pt=strtok(NULL, "~")) {
       values[idx++] = atoi(pt);
    }
    //End black magic.


    startHour = values[0];
    startMinute = values[1];
    stopHour = values[2];
    stopMinute = values[3];
    zOne = values[4];
    days = values[5];

Serial.println(zOne);
Serial.println(startHour);
Serial.println(startMinute);
Serial.println(stopHour);
Serial.println(stopMinute);
Serial.println(days);
return 0;
}
