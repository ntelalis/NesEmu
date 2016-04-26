#pragma once

#include <stdint.h>
#include <string.h>

class RAM {

private:
	uint8_t ram[0x800];
public:
	RAM();
	void Init();
	uint8_t Read(uint16_t address);
	void Write(uint16_t address, uint8_t value);
};