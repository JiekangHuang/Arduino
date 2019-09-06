#include "DHT/dht.h"

#define dht_pin 8

dht DHT;

void setup()
{
	Serial.begin(9600);
	delay(500);
	Serial.print("***Electropeak***\n\n");
}

void loop()
{
	DHT.read11(dht_pin);

	Serial.print("humidity = ");
	Serial.print(DHT.humidity);
	Serial.print("%  ");
	Serial.print("temperature = ");
	Serial.print(DHT.temperature);
	Serial.println("C  ");

	delay(3000);
}