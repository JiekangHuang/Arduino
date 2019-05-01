#pragma once
#include <Arduino.h>
class L298N
{
private:
	byte EA, IA, EB, IB, L, R;  //pin
	bool ea, ia, eb, ib;
	byte lsp, rsp;
	const byte def_sp_L = 150;
	const byte def_sp_R = 155;

public:
	L298N(byte, byte, byte, byte, byte, byte);
	~L298N();
	void Forward();
	void Backward();
	void T_left();
	void T_right();
	void stop();
	void Updata();
	void L_stop();
	void R_stop();
	void set_speed(byte);
};
