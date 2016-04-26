#include "CPU.h"

CPU::CPU() {
	
}

void CPU::Init(){
	//Initializing RAM sets 0x0000-0x0800 = 0x00
	ram.Init();
	PS = 0x34;
	SP = 0xFD;
	A = 0x0;
	X = 0x0;
	Y = 0x0;
		/*$4017 = $00(frame irq enabled)
		$4015 = $00(all channels disabled)
		$4000 - $400F = $00(not sure about $4010 - $4013)*/
}

void CPU::Reset(){
	SP -= 0x03;
	PS |= 0x04;
	/*APU was silenced ($4015 = 0)*/
}

void CPU::Cycle(){
	opcode = ram.Read(PC);
	switch (opcode) {
	case 0xA9:
		LDA(Immediate());
	}
}

void CPU::LDA() {
	if (ram.Read(PC + 1) < 0x80)
		PS &= 0b11111110;
	else
		PS |= 0b00000001;
	if (ram.Read(PC + 1) == 0x0)
		PS |= 0b01000000;
	else
		PS &= 0b10111111;

}

uint16_t CPU::read16(uint16_t address) {
	return (uint16_t)ram.Read(address + 1) << 8 | (uint16_t)ram.Read(address);
}

uint8_t CPU::Implied(){
	return 0x0;
}

uint16_t CPU::Immediate(){
	return PC + 1;
}

uint8_t	CPU::Relative(){
	uint16_t tempAddr = ram.Read(PC + 1);
	if (tempAddr < 0x80)
		return PC + 2 + tempAddr;
	else
		return PC + 2 + tempAddr - 0x100;
}

uint8_t	CPU::Accumulator(){
	return 0x0;
}

uint8_t CPU::ZeroPage(){
	return ram.Read(PC + 1) & 0xFF;
}

uint8_t CPU::ZeroPageX(){
	return (ram.Read(PC + 1) + X) & 0xFF;
}

uint8_t CPU::ZeroPageY(){
	return (ram.Read(PC + 1) + Y) & 0xFF;
}

uint16_t CPU::Absolute(){
	return read16(PC + 1);
}

uint16_t CPU::AbsoluteX(){
	return read16(PC + 1) + X;
}

uint16_t CPU::AbsoluteY(){
	return read16(PC + 1) + Y;
}

uint16_t CPU::Indirect(){
	uint16_t tempAddr = read16(PC + 1);
	//Wrap JMP Bug
	if ((tempAddr & 0xFF) == 0xFF)
		return (uint16_t)ram.Read(tempAddr & 0xFF00) << 8 | (uint16_t)ram.Read(tempAddr);
	else
		return read16(tempAddr);
}

uint16_t CPU::IndirectX(){
	return read16((ram.Read(PC + 1) + X) & 0xFF);
	//Bug Implementation?
}

uint16_t CPU::IndirectY(){
	return read16(ram.Read(PC + 1)) + Y;
	//Bug Implementation?
}