/*
 Name:		esp8266.ino
 Created:	2019/8/4 下午 06:39:03
 Author:	s2862
*/
#include "OTA.h"
#include "esp8266_key.h"
#include <Temboo.h>
#include <Bridge.h>
#include "Google_Info.h"
#include "TembooAccount.h"

long int pre_time = 0;
long int cur_time = 0;
bool val = false;

boolean success = false;

void setup()
{
	Serial.begin(9600);
	OTA();
	pinMode(D4, OUTPUT);
	Serial.begin(9600);
	pre_time = millis();
	Bridge.begin();
}

void loop()
{
	/*
	ArduinoOTA.handle();
	cur_time = millis();
	if (cur_time - pre_time >= 1000)
	{
		Serial.println("Holle !");
		pre_time = cur_time;
		digitalWrite(D4, val);
		val = !val;
	}
	*/
	if (!success)
	{
		Serial.println("Running SendAnEmail...");

		TembooChoreo SendEmailChoreo;

		// invoke the Temboo client
		// NOTE that the client must be reinvoked, and repopulated with
		// appropriate arguments, each time its run() method is called.
		SendEmailChoreo.begin();

		// set Temboo account credentials
		SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
		SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
		SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);

		// identify the Temboo Library choreo to run (Google > Gmail > SendEmail)
		SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");

		// set the required choreo inputs
		// see https://www.temboo.com/library/Library/Google/Gmail/SendEmail/
		// for complete details about the inputs for this Choreo

		// the first input is your Gmail email address
		SendEmailChoreo.addInput("Username", GMAIL_USER_NAME);
		// next is your Gmail App-Specific password.
		SendEmailChoreo.addInput("Password", GMAIL_PASSWORD);
		// who to send the email to
		SendEmailChoreo.addInput("ToAddress", TO_EMAIL_ADDRESS);
		// then a subject line
		SendEmailChoreo.addInput("Subject", "Arduino Yun Email 測試 !!");

		// next comes the message body, the main content of the email
		SendEmailChoreo.addInput("MessageBody", "真酷!!");

		// tell the Choreo to run and wait for the results. The
		// return code (returnCode) will tell us whether the Temboo client
		// was able to send our request to the Temboo servers
		unsigned int returnCode = SendEmailChoreo.run();

		// a return code of zero (0) means everything worked
		if (returnCode == 0) {
			Serial.println("Success! Email sent!");
			success = true;
		}
		else {
			// a non-zero return code means there was an error
			// read and print the error message
			while (SendEmailChoreo.available()) {
				char c = SendEmailChoreo.read();
				Serial.print(c);
			}
		}
		SendEmailChoreo.close();

		// do nothing for the next 60 seconds
		delay(60000);
	}
}