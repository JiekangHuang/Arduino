<<<<<<< HEAD
﻿void setup()
{
=======
﻿#include "DHT/dht.h"

#define dht_pin 8

dht DHT;

void setup()
{
	Serial.begin(9600);
	delay(500);
	Serial.print("***Electropeak***\n\n");
>>>>>>> 534b9e43658fd8682ac836b7f7f72ac293c9a799
}

void loop()
{
<<<<<<< HEAD
=======
	DHT.read11(dht_pin);

	Serial.print("humidity = ");
	Serial.print(DHT.humidity);
	Serial.print("%  ");
	Serial.print("temperature = ");
	Serial.print(DHT.temperature);
	Serial.println("C  ");

	delay(3000);
>>>>>>> 534b9e43658fd8682ac836b7f7f72ac293c9a799
}