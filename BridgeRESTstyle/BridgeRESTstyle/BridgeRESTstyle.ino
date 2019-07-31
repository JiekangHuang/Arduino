/*
 Name:		BridgeRESTstyle.ino
 Created:	2019/7/29 上午 04:31:29
 Author:	s2862
*/
#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h>
#include <Servo.h>

YunServer server;
Servo servoLeft;
Servo servoRight;

void setup()
{
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);
	Bridge.begin();
	digitalWrite(13, HIGH);

	servoLeft.attach(11);
	servoRight.attach(10);

	server.listenOnLocalhost();
	server.begin();
}

void loop()
{
	YunClient client = server.accept();

	if (client)
	{
		process(client);
		client.stop();
	}
	delay(50);
}

void process(YunClient client)
{
	String command = client.readStringUntil('/');

	if (command == "action")
		actionCommand(client);
	if (command == "digital")
		digitalCommand(client);
	if (command == "analog")
		analogCommand(client);
	if (command == "mode")
		modeCommand(client);
}

void actionCommand(YunClient client)
{
	String action = client.readStringUntil('\r');

	if (action == "forward")
	{
		servoLeft.writeMicroseconds(1700);
		servoRight.writeMicroseconds(1300);
		client.print(F("Robot moves forward"));
		return;
	}
	if (action == "backward")
	{
		servoLeft.writeMicroseconds(1300);
		servoRight.writeMicroseconds(1700);
		client.print(F("Robot moves backward"));
		return;
	}
	if (action == "turnright")
	{
		servoLeft.writeMicroseconds(1700);
		servoRight.writeMicroseconds(1700);
		client.print(F("Robot turnss right"));
		return;
	}
	if (action == "turnleft")
	{
		servoLeft.writeMicroseconds(1300);
		servoRight.writeMicroseconds(1300);
		client.print(F("Robot turnss left"));
		return;
	}
	if (action == "stop")
	{
		servoLeft.writeMicroseconds(1500);
		servoRight.writeMicroseconds(1500);
		client.print(F("Robot stops"));
		return;
	}
	client.print(F("error: invalid action "));
	client.print(action);
}

void digitalCommand(YunClient client)
{
	int pin, value;

	pin = client.parseInt();
	if (client.read() == '/')
	{
		value = client.parseInt();
		digitalWrite(pin, value);
	}
	else
		value = digitalRead(pin);

	client.print(F("Pin D"));
	client.print(pin);
	client.print(F(" set to digital"));
	client.println(value);

	String key = "D";
	key += pin;
	Bridge.put(key, String(value));
}

void analogCommand(YunClient client)
{
	int pin, value;

	pin = client.parseInt();

	if (client.read() == '/')
	{
		value = client.parseInt();
		analogWrite(pin, value);

		client.print(F("Pin D"));
		client.print(pin);
		client.print(F(" set to analog "));
		client.println(value);

		String key = "D";
		key += pin;
		Bridge.put(key, String(value));
	}
	else
	{
		value = analogRead(pin);

		client.print(F("Pin A"));
		client.print(pin);
		client.print(F(" reads analog "));
		client.println(value);

		String key = "A";
		key += pin;
		Bridge.put(key, String(value));
	}
}

void modeCommand(YunClient client)
{
	int pin;
	pin = client.parseInt();

	if (client.read() != '/')
	{
		client.println(F("error"));
		return;
	}

	String mode = client.readStringUntil('\r');

	if (mode == "input")
	{
		pinMode(pin, INPUT);

		client.print(F("Pin D"));
		client.print(pin);
		client.print(F(" configured as INPUT!"));
		return;
	}

	if (mode == "output")
	{
		pinMode(pin, OUTPUT);

		client.print(F("Pin D"));
		client.print(pin);
		client.print(F(" configured as OUTPUT!"));
		return;
	}

	client.print(F("error: invalid mode "));
	client.print(mode);
}