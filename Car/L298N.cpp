#include "L298N.h"

L298N::L298N(byte EA, byte IA, byte EB, byte IB, byte L, byte R)
{
	ea = ia = eb = ib = false;

	lsp = def_sp_L + 0;
	rsp = def_sp_R + 0;

	this->EA = EA;
	this->IA = IA;
	this->EB = EB;
	this->IB = IB;
	this->L = L;
	this->R = R;

	pinMode(this->EA, OUTPUT);
	pinMode(this->IA, OUTPUT);
	pinMode(this->EB, OUTPUT);
	pinMode(this->IB, OUTPUT);
	pinMode(this->L, OUTPUT);
	pinMode(this->R, OUTPUT);
}

L298N::~L298N()
{
	Serial.println("L298N::~L298N();");
}

void L298N::Forward()
{
	ea = eb = false;
	ia = ib = true;
	Updata();
}

void L298N::Backward()
{
	ea = eb = true;
	ia = ib = false;
	Updata();
}

void L298N::T_left()
{
	ea = ib = true;
	ia = eb = false;
	Updata();
}

void L298N::T_right()
{
	ea = ib = false;
	ia = eb = true;
	Updata();
}

void L298N::stop()
{
	ea = eb = ia = ib = false;
	Updata();
}

void L298N::Updata()
{
	analogWrite(L, lsp);
	analogWrite(R, rsp);
	digitalWrite(EA, ea);
	digitalWrite(IA, ia);
	digitalWrite(EB, eb);
	digitalWrite(IB, ib);
}

void L298N::set_speed(byte speed)
{
	lsp = rsp = speed;
}