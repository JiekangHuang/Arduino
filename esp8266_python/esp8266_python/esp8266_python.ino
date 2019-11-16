/*
	This sketch demonstrates how to set up a simple HTTP-like server.
	The server will set a GPIO pin depending on the request
	  http://server_ip/gpio/0 will set the GPIO2 low,
	  http://server_ip/gpio/1 will set the GPIO2 high
	server_ip is the IP address of the ESP8266 module, will be
	printed to Serial when the module is connected.
*/

#include "OTA.h"
#include "esp8266 key.h"

#define SW_SPEED D6
#define SW_OFF D7
#define LED D4

WiFiServer server(80);

bool st = false;
String mess = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";

void setup() {
	Serial.begin(115200);

	pinMode(LED, OUTPUT);
	pinMode(SW_SPEED, OUTPUT);
	pinMode(SW_OFF, OUTPUT);
	digitalWrite(LED, HIGH);
	digitalWrite(SW_SPEED, LOW);
	digitalWrite(SW_OFF, LOW);

	OTA();

	server.begin();
	Serial.println("Server started !!");
}

void loop()
{
	String res;
	ArduinoOTA.handle();
	WiFiClient client = server.available();
	if (!client)
		return;

	Serial.println("new client");
	while (!client.available())
		delay(1);

	String req = client.readStringUntil('\r');
	Serial.println(req);
	client.flush();

	int val;
	if (req.indexOf("/gpio/0") != -1)
	{
		if (st == false)
		{
			val = 0;
			for (int i = 0; i < 1; i++)
			{
				digitalWrite(SW_SPEED, HIGH);
				delay(100);
				digitalWrite(SW_SPEED, LOW);
				delay(100);
			}
			st = true;
			res = mess + "IOT Electric Fan is open !";
		}
		else
			res = mess + "電風扇已經開了喔 ~ !";
	}
	else if (req.indexOf("/gpio/1") != -1)
	{
		if (st == true)
		{
			val = 1;
			digitalWrite(SW_OFF, HIGH);
			delay(100);
			digitalWrite(SW_OFF, LOW);
			st = false;
			res = mess + "IOT Electric Fan is close !";
		}
		else
			res = mess + "電風扇已經關了喔 ~ !";
	}
	else
	{
		Serial.println("invalid request");
		client.stop();
		return;
	}
	digitalWrite(LED, val);

	client.flush();

	client.print(res);
	delay(1);
	Serial.println("Client disonnected");
}