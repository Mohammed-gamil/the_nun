#include "Medochi_DHT11.h"


DHT11::DHT11(int pin) : _pin(pin) {
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, HIGH);
}

int DHT11::readRawData(byte data[5]) {
	delay(500);
	startSignal() ;
    unsigned long timeout_start = millis();

	while (digitalRead(_pin) == HIGH) {
		if (millis() - timeout_start > 1000)
		{
		  Serial.println(millis());
		  Serial.println(timeout_start) ; 
		  return 2;
		}
	  }
	
	if(digitalRead(_pin) == LOW) {
		delayMicroseconds(80);
		for(int i = 0 ;i < 5;i++) {
			Serial.println("i am before read bytes");
			data[i] = readByte();
		}
	} else {
		Serial.println("no man please no");
		delay(15) ; 
	}
	if(data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF) ) {
		return 0 ;
	}else {
		Serial.println("You got fucked");
	}
}
byte DHT11::readByte(){
	byte value = 0 ;
	for(int i = 0 ; i < 8 ; i++){
		while(digitalRead(_pin) == LOW) Serial.println("i am low");
		delayMicroseconds(30);
		if(digitalRead(_pin) == HIGH){
			Serial.println("i Changed the value");
			value |= (1 << (7-i)) ;
		}
		while (digitalRead(_pin) == HIGH) Serial.println("i am high")  ;
	}
	return value ;
}

void DHT11::startSignal() {
	Serial.println("i started starting") ; 
	pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
    delay(18);
    digitalWrite(_pin, HIGH);
    delayMicroseconds(40);
    pinMode(_pin, INPUT);
	Serial.println("i Finished starting") ; 
}

int DHT11::readTemperature(){
	byte data[5] ; 
	int error = readRawData(data) ; 
	if( error == 0 ) {
		return data[2];
	} else if (error == 1) {
		Serial.println("#### you ");
	} else if (error == 2) {
		Serial.println("Man really !!");
	}
}
int DHT11::readHumidity(){
	byte data[5] ;
	int error = readRawData(data) ; 
	if( error == 0 ) {
		return data[0];
	} 
}


