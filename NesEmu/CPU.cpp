#include "CPU.h"

CPU::CPU() {
	cycles = 0;
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
	
	//LDA Instructions
	case 0xA9:
		LDA(Immediate());
		PC += 2;
		cycles += 2;
		break;
	case 0xA5:
		LDA(ZeroPage());
		PC += 2;
		cycles += 3;
		break;
	case 0xB5:
		LDA(ZeroPageX());
		PC += 2;
		cycles += 4;
		break;
	case 0xAD:
		LDA(Absolute());
		PC += 3;
		cycles += 4;
		break;
	case 0xBD:
		LDA(AbsoluteX());
		PC += 3;
		//+1 if pages crossed implement
		cycles += 4;
		break;
	case 0xB9:
		LDA(AbsoluteY());
		PC += 3;
		//+1 if pages crossed implement
		cycles += 4;
		break;
	case 0xA1:
		LDA(IndirectX());
		PC += 2;
		cycles += 6;
		break;
	case 0xB1:
		LDA(IndirectY());
		PC += 2;
		//+1 if pages crossed implement
		cycles += 5;
		break;
	//LDX Instructions
	case 0xA2:
		LDX(Immediate());
		PC += 2;
		cycles += 2;
		break;
	case 0xA6:
		LDX(ZeroPage());
		PC += 2;
		cycles += 3;
		break;
	case 0xB6:
		LDX(ZeroPageY());
		PC += 2;
		cycles += 4;
		break;
	case 0xAE:
		LDX(Absolute());
		PC += 3;
		cycles += 4;
		break;
	case 0xBE:
		LDX(AbsoluteY());
		PC += 3;
		//+1 if pages crossed implement
		cycles += 4;
		break;
	//LDY Instructions
	case 0xA0:
		LDY(Immediate());
		PC += 2;
		cycles += 2;
		break;
	case 0xA4:
		LDY(ZeroPage());
		PC += 2;
		cycles += 3;
		break;
	case 0xB4:
		LDY(ZeroPageX());
		PC += 2;
		cycles += 4;
		break;
	case 0xAC:
		LDY(Absolute());
		PC += 3;
		cycles += 4;
		break;
	case 0xBC:
		LDX(AbsoluteX());
		PC += 3;
		//+1 if pages crossed implement
		cycles += 4;
		break;
	}
}

// Set/Unset & Read Processor Status Register bits

void CPU::SetZ(uint8_t value) {
	if (value == 0x0)
		PS |= 1 << 7;
	else
		PS &= ~(1 << 7);
}

void CPU::SetN(uint8_t value) {
	if (value & 0x80 == 0)
		PS &= ~(1 << 1);
	else
		PS |= 1 << 1;
}

bool CPU::GetBit(uint8_t value, int bit) {
	return (value & (1 << bit)) != 0;
}

// Instructions
void CPU::LDA(uint16_t address) {
	A = ram.Read(address);
	CPU::SetN(A);
	CPU::SetZ(A);
}

void CPU::LDX(uint16_t address) {
	X = ram.Read(address);
	CPU::SetN(X);
	CPU::SetZ(X);
}

void CPU::LDY(uint16_t address) {
	Y = ram.Read(address);
	CPU::SetN(Y);
	CPU::SetZ(Y);
}

void CPU::ADC(uint16_t address) {
	// I am here
	A += (int8_t)ram.Read(address) + GetBit(PS,CF);
	CPU::SetZ(A);
	CPU::SetZ(A);
}

// Addressing Modes

uint16_t CPU::Implied(){
	return 0;
}

uint16_t CPU::Accumulator() {
	return 0;
}

uint16_t CPU::Immediate(){
	return PC + 1;
}

uint16_t CPU::ZeroPage(){
	return (uint16_t)(ram.Read(PC + 1) & 0x00FF);
}

uint16_t CPU::ZeroPageX(){
	return (uint16_t)((ram.Read(PC + 1) + X) & 0x00FF);
}

uint16_t CPU::ZeroPageY(){
	return (uint16_t)((ram.Read(PC + 1) + Y) & 0x00FF);
}

uint16_t CPU::Relative() {
	//Not sure if its ok
	uint16_t tempAddr = (uint16_t)(ram.Read(PC + 1));
	if (tempAddr < 0x80)
		return PC + 2 + tempAddr;
	else
		return PC + 2 + tempAddr - 0x100;
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
	//Not sure if bug implementation is ok
	if ((tempAddr & 0xFF) == 0xFF)
		return (uint16_t)ram.Read(tempAddr & 0xFF00) << 8 | (uint16_t)ram.Read(tempAddr);
	else
		return read16(tempAddr);
}

uint16_t CPU::IndirectX(){
	return read16((ram.Read(PC + 1) + X) & 0xFF);
}

uint16_t CPU::IndirectY(){
	return read16(ram.Read(PC + 1)) + Y;
}

// Helper function that returns an address from 2 consecutive memory addresses (Little Endian)
uint16_t CPU::read16(uint16_t address) {
	return (uint16_t)ram.Read(address + 1) << 8 | (uint16_t)ram.Read(address);
}