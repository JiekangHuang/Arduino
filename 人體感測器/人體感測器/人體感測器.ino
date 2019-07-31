/*
 Name:		人體感測器.ino
 Created:	2019/6/25 下午 12:53:37
 Author:	s2862
*/

#include "esp8266 key.h"
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid = "Arduino";
const char* pass = "xup6y3pp3150";

String str = "/btn?key=fu.y3xup6&id=";

HTTPClient http;

void line(String mess)
{
	http.begin("csu-arduino.herokuapp.com", 80, str + mess);
	int httpCode = http.GET();
	if (httpCode > 0) {
		// 在序列埠監控視窗顯示送出的數據
		Serial.printf("HTTP code: %d\n", httpCode);

		if (httpCode == 200) {
			String payload = http.getString();
			// 顯示遠端伺服器的回應

			Serial.println(payload);
		}
	}
	else {
		Serial.println("HTTP connection ERROR!");
	}
}

void setup()
{
	Serial.begin(9600);
	WiFi.begin(ssid, pass);

	Serial.println("");
	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}
	Serial.println("Wi-Fi ready...");
}

void loop()
{
	bool val = digitalRead(D0);
	if (val)
	{
		line("find");
		delay(5000);
	}
}