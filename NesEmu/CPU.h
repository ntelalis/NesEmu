#pragma once

#include <stdint.h>
#include "CPUMemoryMap.h"

class CPU {
private:

	RAM ram;

	uint16_t PC;							//Program counter 16-bit
	uint8_t SP, A, X, Y, PS;				//Stack Pointer,Acumulator,X & Y Register, Processor Status Register 8-bit
	bool CF, ZF, IF, DF, BF, UF, VF, NF;	//Carry, Zero, Interrupt, Decimal, Break, Unused, Overflow, Negative flags 1-bit


	int8_t opcode;

	uint16_t read16(uint16_t address);
public:
	CPU();
	void Init();
	void Reset();
	void Cycle();

	void LDA();

	//Addressing modes
	uint8_t Implied();
	uint16_t Immediate();
	uint8_t Relative();
	uint8_t Accumulator();
	uint8_t ZeroPage();
	uint8_t ZeroPageX();
	uint8_t ZeroPageY();
	uint16_t Absolute();
	uint16_t AbsoluteX();
	uint16_t AbsoluteY();
	uint16_t Indirect();
	uint16_t IndirectX();
	uint16_t IndirectY();
};