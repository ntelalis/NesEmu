#include "CPUMemoryMap.h"

RAM::RAM() {
	Init();
}

uint8_t RAM::Read(uint16_t address) {
	if (address < 0x2000) {
		return ram[address & 0x7FF];
	}
	else if (address < 0x4000) {
		return 0; //!!!!!ppuRegs[address & 0x7];
	}
	else if (address < 0x4018) {
		return 0; //!!!!!!!apuRegs[address & 0x17];
	}
	return 0;
}

void RAM::Write(uint16_t address, uint8_t value) {
	if (address < 0x2000) {
		ram[address & 0x7FF] = value;
	}
	else if (address < 0x4000) {
		//ppuRegs!!!![address & 0x7] = value;
	}
	else if (address < 0x4018) {
		//apuRegs!!!![address & 0x17] = value;
	}
}

void RAM::Init() {
	memset(ram, 0x0, sizeof(ram));
}