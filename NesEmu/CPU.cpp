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
	//ADC Instructions
	case 0x69:
		ADC(Immediate());
		PC += 2;
		cycles += 2;
		break;
	case 0x65:
		ADC(ZeroPage());
		PC += 2;
		cycles += 3;
		break;
	case 0x75:
		ADC(ZeroPageX());
		PC += 2;
		cycles += 4;
		break;
	case 0x6D:
		ADC(Absolute());
		PC += 3;
		cycles += 4;
		break;
	case 0x7D:
		ADC(AbsoluteX());
		PC += 3;
		cycles += 4;
		break;
	case 0x79:
		ADC(AbsoluteY());
		PC += 3;
		cycles += 4;
		break;
	case 0x61:
		ADC(IndirectX());
		PC += 2;
		cycles += 6;
		break;
	case 0x71:
		ADC(IndirectY());
		PC += 2;
		cycles += 5;
		break;
	//AND Instructions
	case 0x29:
		AND(Immediate());
		PC += 2;
		cycles += 2;
		break;
	case 0x25:
		AND(ZeroPage());
		PC += 2;
		cycles += 3;
		break;
	case 0x35:
		AND(ZeroPage());
		PC += 2;
		cycles += 4;
		break;
	case 0x2D:
		AND(Absolute());
		PC += 3;
		cycles += 4;
		break;
	case 0x3D:
		AND(AbsoluteX());
		PC += 3;
		cycles += 4;
		break;
	case 0x39:
		AND(AbsoluteY());
		PC += 3;
		cycles += 4;
		break;
	case 0x21:
		AND(IndirectX());
		PC += 2;
		cycles += 6;
		break;
	case 0x31:
		AND(IndirectY());
		PC += 2;
		cycles += 5;
		break;
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
		cycles += 4;
		break;
	case 0xB9:
		LDA(AbsoluteY());
		PC += 3;
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
		cycles += 4;
		break;
	}
}

// Set/Unset & Read Processor Status Register bits

void CPU::SetZ(uint8_t value) {
	if (value == 0x0)
		PS |= 1 << ZF;
	else
		PS &= ~(1 << ZF);
}

void CPU::SetN(uint8_t value) {
	if (value & 0x80 == 0)
		PS &= ~(1 << NF);
	else
		PS |= 1 << NF;
}

void CPU::SetC(uint16_t value) {
	if (value > 0xFF)
		PS |= 1 << CF;
	else
		PS &= ~(1 << CF);
}

void CPU::SetV(uint16_t sum, uint8_t value) {
	if ((A ^ value) & 0x80 == 0 && (A ^ sum) & 0x80 != 0)
		PS |= 1 << VF;
	else
		PS &= ~(1 << VF);
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
	uint8_t addr = ram.Read(address);
	uint16_t sum = A + addr + GetBit(PS, CF);
	if (GetBit(PS, DF) && false) {
		//TODO (Decimal mode doesnt work in NES 6502)
	}
	else {
		CPU::SetV(sum,addr);
		CPU::SetC(sum);
		A = sum;
		CPU::SetN(A);
		CPU::SetZ(A);
	}
}

void CPU::AND(uint16_t address) {
	A &=ram.Read(address);
	CPU::SetN(A);
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
	uint16_t addr = read16(PC + 1) + (uint16_t)X;
	if (PagesCrossed(addr - (uint16_t)X, addr))
		cycles++;
	return addr;
}

uint16_t CPU::AbsoluteY(){
	uint16_t addr = read16(PC + 1) + (uint16_t)Y;
	if (PagesCrossed(addr - (uint16_t)Y, addr))
		cycles++;
	return addr;
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
	return read16(((uint16_t)ram.Read(PC + 1) + (uint16_t)X) & 0xFF);
}

uint16_t CPU::IndirectY(){
	uint16_t addr = read16((uint16_t)ram.Read(PC + 1)) + (uint16_t)Y;
	if (PagesCrossed(addr - (uint16_t)Y, addr))
		cycles++;
	return addr;
}

// Helper function that returns an address from 2 consecutive memory addresses (Little Endian)
uint16_t CPU::read16(uint16_t address) {
	return (uint16_t)ram.Read(address + 1) << 8 | (uint16_t)ram.Read(address);
}

// Helper function which checks if high byte has been altered
bool CPU::PagesCrossed(uint16_t addr0, uint16_t addr1) {
	return (addr0 & 0xFF00 != addr1 & 0xFF00);
}