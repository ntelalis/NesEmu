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
	//ASL Instructions
	case 0x0A:
		ASL(Accumulator());
		PC += 1;
		cycles += 2;
		break;
	case 0x06:
		ASL(ZeroPage());
		PC += 2;
		cycles += 5;
		break;
	case 0x16:
		ASL(ZeroPageX());
		PC += 2;
		cycles += 6;
		break;
	case 0x0E:
		ASL(Absolute());
		PC += 3;
		cycles += 6;
		break;
	case 0x1E:
		ASL(AbsoluteX());
		PC += 3;
		cycles += 7;
		break;
	//BCC Instruction
	case 0x90:
		BCC(Relative());
		PC += 2;
		cycles += 2;
		break;
	//BCS Instruction
	case 0xB0:
		BCS(Relative());
		PC += 2;
		cycles += 2;
		break;
	//BEQ Instruction
	case 0xF0:
		BEQ(Relative());
		PC += 2;
		cycles += 2;
		break;
	//BIT Instruction
	case 0x24:
		BIT(ZeroPage());
		PC += 2;
		cycles += 3;
		break;
	case 0x2C:
		BIT(Absolute());
		PC += 3;
		cycles += 4;
		break;
	//BMI Instruction
	case 0x30:
		BMI(Relative());
		PC += 2;
		cycles += 2;
		break;
	//BNE Instruction
	case 0xD0:
		BNE(Relative());
		PC += 2;
		cycles += 2;
		break;
	//BPL Instruction
	case 0x10:
		BPL(Relative());
		PC += 2;
		cycles += 2;
		break;
	//BRK Instruction
	case 0x00:
		BRK(Implied());
		PC += 1;
		cycles += 7;
		break;
	//BVC Instruction
	case 0x50:
		BVC(Relative());
		PC += 2;
		cycles += 2;
		break;
	//BVS Instruction
	case 0x70:
		BVS(Relative());
		PC += 2;
		cycles += 2;
		break;
	//CLC Instruction
	case 0x18:
		CLC(Implied());
		PC += 1;
		cycles += 2;
		break;
	//CLD Instruction
	case 0xD8:
		CLC(Implied());
		PC += 1;
		cycles += 2;
		break;
	//CLI Instruction
	case 0x58:
		CLC(Implied());
		PC += 1;
		cycles += 2;
		break;
	//CLV Instruction
	case 0xB8:
		CLC(Implied());
		PC += 1;
		cycles += 2;
		break;
	//CMP Instructions
	case 0xC9:
		CMP(Immediate());
		PC += 2;
		cycles += 2;
		break;
	case 0xC5:
		CMP(ZeroPage());
		PC += 2;
		cycles += 3;
		break;
	case 0xD5:
		CMP(ZeroPageX());
		PC += 2;
		cycles += 4;
		break;
	case 0xCD:
		CMP(Absolute());
		PC += 3;
		cycles += 4;
		break;
	case 0xDD:
		CMP(AbsoluteX());
		PC += 3;
		cycles += 4;
		break;
	case 0xD9:
		CMP(AbsoluteY());
		PC += 3;
		cycles += 4;
		break;
	case 0xC1:
		CMP(IndirectX());
		PC += 2;
		cycles += 6;
		break;
	case 0xD1:
		CMP(IndirectY());
		PC += 2;
		cycles += 5;
		break;
	//CPX Instructions
	case 0xE0:
		CPX(Immediate());
		PC += 2;
		cycles += 2;
		break;
	case 0xE4:
		CPX(ZeroPage());
		PC += 2;
		cycles += 3;
		break;
	case 0xEC:
		CPX(Absolute());
		PC += 3;
		cycles += 4;
		break;
	//CPY Instructions
	case 0xC0:
		CPY(Immediate());
		PC += 2;
		cycles += 2;
		break;
	case 0xC4:
		CPY(ZeroPage());
		PC += 2;
		cycles += 3;
		break;
	case 0xCC:
		CPY(Absolute());
		PC += 3;
		cycles += 4;
		break;
	//DEC Instructions
	case 0xC6:
		DEC(ZeroPage());
		PC += 2;
		cycles += 5;
		break;
	case 0xD6:
		DEC(ZeroPageX());
		PC += 2;
		cycles += 6;
		break;
	case 0xCE:
		DEC(Absolute());
		PC += 3;
		cycles += 6;
		break;
	case 0xDE:
		DEC(AbsoluteX());
		PC += 3;
		cycles += 7;
		break;
	//DEX Instruction
	case 0xCA:
		DEX(Implied());
		PC += 1;
		cycles += 2;
		break;
	case 0x88:
		DEY(Implied());
		PC += 1;
		cycles += 2;
		break;
	//EOR Instructions
	case 0x49:
		EOR(Immediate());
		PC += 2;
		cycles += 2;
		break;
	case 0x45:
		EOR(ZeroPage());
		PC += 2;
		cycles += 3;
		break;
	case 0x55:
		EOR(ZeroPageX());
		PC += 2;
		cycles += 4;
		break;
	case 0x4D:
		EOR(Absolute());
		PC += 3;
		cycles += 4;
		break;
	case 0x5D:
		EOR(AbsoluteX());
		PC += 3;
		cycles += 4;
		break;
	case 0x59:
		EOR(AbsoluteY());
		PC += 3;
		cycles += 4;
		break;
	case 0x41:
		EOR(IndirectX());
		PC += 2;
		cycles += 6;
		break;
	case 0x51:
		EOR(IndirectY());
		PC += 2;
		cycles += 5;
		break;
	//INC Instructions
	case 0xE6:
		INC(ZeroPage());
		PC += 2;
		cycles += 5;
		break;
	case 0xF6:
		INC(ZeroPageX());
		PC += 2;
		cycles += 6;
		break;
	case 0xEE:
		INC(Absolute());
		PC += 3;
		cycles += 6;
		break;
	case 0xFE:
		INC(AbsoluteX());
		PC += 3;
		cycles += 7;
		break;
	//INX Instruction
	case 0xE8:
		INX(Implied());
		PC += 1;
		cycles += 2;
		break;
	//INY Instruction
	case 0xC8:
		INY(Implied());
		PC += 1;
		cycles += 2;
		break;
	//JMP Instructions
	case 0x4C:
		JMP(Absolute());
		PC += 3;
		cycles += 3;
		break;
	case 0x6C:
		JMP(Indirect());
		PC += 3;
		cycles += 5;
		break;
	//JSR Instruction
	case 0x20:
		JSR(Absolute());
		PC += 3;
		cycles += 6;
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

void CPU::SetC(uint8_t value) {
	if (value & 0x80 == 0)
		PS &= ~(1 << CF);
	else
		PS |= 1 << CF;
}

void CPU::SetC(bool value) {
	if (value)
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

void CPU::SetV(uint8_t value) {
	if(value & 0x40 == 0)
		PS &= ~(1 << VF);
	else
		PS |= 1 << VF;
}

void CPU::SetB(bool value) {
	if (value)
		PS |= 1 << BF;
	else
		PS &= ~(1 << BF);
}
void CPU::SetD(bool value) {
	if (value)
		PS |= 1 << DF;
	else
		PS &= ~(1 << DF);
}

void CPU::SetI(bool value) {
	if (value)
		PS |= 1 << IF;
	else
		PS &= ~(1 << IF);
}

void CPU::SetV(bool value) {
	if (value)
		PS |= 1 << VF;
	else
		PS &= ~(1 << VF);
}


bool CPU::GetBit(uint8_t value, int bit) {
	return (value & (1 << bit)) != 0;
}

// Instructions

void CPU::ADC(uint16_t address) {
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

void CPU::ASL(uint16_t address) {
	if (address == -1) {
		CPU::SetC(A);
		A <<= 1;
		CPU::SetN(A);
		CPU::SetZ(A);
	}
	else {
		uint8_t value = ram.Read(address);
		CPU::SetC(value);
		value <<= 1;
		ram.Write(address, value);
		CPU::SetN(value);
		CPU::SetZ(value);
	}
}

void CPU::BCC(uint16_t address) {
	if (CPU::GetBit(PS, CF) == 0) {
		if (PagesCrossed(PC, address))
			cycles += 2;
		else
			cycles += 1;
		PC += address;
	}
}

void CPU::BCS(uint16_t address) {
	if (CPU::GetBit(PS, CF) == 1) {
		if (PagesCrossed(PC, address))
			cycles += 2;
		else
			cycles += 1;
		PC += address;
	}
}

void CPU::BEQ(uint16_t address) {
	if (CPU::GetBit(PS, ZF) == 1) {
		if (PagesCrossed(PC, address))
			cycles += 2;
		else
			cycles += 1;
		PC += address;
	}
}

void CPU::BIT(uint16_t address) {
	uint8_t value = ram.Read(address);
	CPU::SetZ(A & value);
	CPU::SetV(value);
	CPU::SetN(value);
}

void CPU::BMI(uint16_t address) {
	if (CPU::GetBit(PS, NF) == 1) {
		if (PagesCrossed(PC, address))
			cycles += 2;
		else
			cycles += 1;
		PC += address;
	}
}

void CPU::BNE(uint16_t address) {
	if (CPU::GetBit(PS, ZF) == 0) {
		if (PagesCrossed(PC, address))
			cycles += 2;
		else
			cycles += 1;
		PC += address;
	}
}

void CPU::BPL(uint16_t address) {
	if (CPU::GetBit(PS, NF) == 0) {
		if (PagesCrossed(PC, address))
			cycles += 2;
		else
			cycles += 1;
		PC += address;
	}
}

void CPU::BRK(uint16_t address) {
	CPU::SetB(true);
	CPU::Push16(PC);
	CPU::Push(PS);
	CPU::SetI(true);
	PC = CPU::read16(0xFFFE);
}

void CPU::BVC(uint16_t address) {
	if (GetBit(PS, VF) == 0) {
		if (PagesCrossed(PC, address))
			cycles += 2;
		else
			cycles += 1;
		PC += address;
	}
}

void CPU::BVS(uint16_t address) {
	if (GetBit(PS, VF) == 1) {
		if (PagesCrossed(PC, address))
			cycles += 2;
		else
			cycles += 1;
		PC += address;
	}
}

void CPU::CLC(uint16_t address) {
	CPU::SetC(false);
}

void CPU::CLD(uint16_t address) {
	CPU::SetD(false);
}

void CPU::CLI(uint16_t address) {
	CPU::SetI(false);
}

void CPU::CLV(uint16_t address) {
	CPU::SetV(false);
}

void CPU::CMP(uint16_t address) {
	CPU::Compare(A, ram.Read(address));
}

void CPU::CPX(uint16_t address) {
	CPU::Compare(X, ram.Read(address));
}

void CPU::CPY(uint16_t address) {
	CPU::Compare(Y, ram.Read(address));
}

void CPU::DEC(uint16_t address) {
	uint8_t value = ram.Read(address) - 1;
	CPU::SetZ(value);
	CPU::SetN(value);
	ram.Write(address, value);
}

void CPU::DEX(uint16_t address) {
	X--;
	CPU::SetZ(X);
	CPU::SetN(X);
}

void CPU::DEY(uint16_t address) {
	Y--;
	CPU::SetZ(Y);
	CPU::SetN(Y);
}

void CPU::EOR(uint16_t address) {
	A ^= ram.Read(address);
	CPU::SetZ(A);
	CPU::SetN(A);
}

void CPU::INC(uint16_t address) {
	uint8_t value = ram.Read(address) + 1;
	CPU::SetZ(value);
	CPU::SetN(value);
	ram.Write(address, value);
}

void CPU::INX(uint16_t address) {
	X++;
	CPU::SetZ(X);
	CPU::SetN(X);
}

void CPU::INY(uint16_t address) {
	Y++;
	CPU::SetZ(Y);
	CPU::SetN(Y);
}

void CPU::JMP(uint16_t address) {
	PC = read16(address);
}

void CPU::JSR(uint16_t address) {
	CPU::Push16(PC-1);
	PC = address;
}

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

// Addressing Modes

uint16_t CPU::Implied(){
	return -1;
}

uint16_t CPU::Accumulator() {
	return -1;
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
		return PC + tempAddr;
	else
		return PC + tempAddr - 0x100;
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

void CPU::Push(uint8_t value) {
	ram.Write(0x100 | (uint16_t)SP, value);
	SP--;
}

uint8_t CPU::Pull() {
	SP++;
	return ram.Read(0x100 | (uint16_t)SP);
}

void CPU::Push16(uint16_t value) {
	CPU::Push((uint8_t)(value >> 8));
	CPU::Push((uint8_t)(value & 0xFF));
}

uint16_t CPU::Pull16() {
	return ((uint16_t)CPU::Pull()) << 8 | (uint16_t)CPU::Pull();
}

// Helper function which checks if high byte has been altered
bool CPU::PagesCrossed(uint16_t addr0, uint16_t addr1) {
	return (addr0 & 0xFF00 != addr1 & 0xFF00);
}

void CPU::Compare(uint8_t value1, uint8_t value2) {
	uint8_t result = value1 - value2;
	CPU::SetZ(result);
	CPU::SetN(result);
	if (value1 >= value2)
		CPU::SetC(true);
	else
		CPU::SetC(false);

}