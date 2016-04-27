#pragma once

#include <stdint.h>
#include "CPUMemoryMap.h"

//Carry, Zero, Interrupt, Decimal, Break, Unused, Overflow, Negative flags
#define CF 8
#define ZF 7
#define IF 6
#define DF 5
#define BF 4
#define UF 3
#define VF 2
#define NF 1

class CPU {
private:

	RAM ram;

	//Registers
	uint16_t PC;							//Program counter 16-bit
	uint8_t SP, A, X, Y, PS;				//Stack Pointer,Acumulator,X & Y Register, Processor Status Register 8-bit

	//Counters
	long int cycles;
	uint8_t opcode;

	uint16_t read16(uint16_t address);
	bool PagesCrossed(uint16_t addr0, uint16_t addr1);
public:
	CPU();
	void Init();
	void Reset();
	void Cycle();

	void SetZ(uint8_t value);
	void SetN(uint8_t value);
	void SetC(uint16_t value);
	void SetV(uint16_t sum, uint8_t value);
	bool GetBit(uint8_t value, int bit);

	void LDA(uint16_t address);
	void LDX(uint16_t address);
	void LDY(uint16_t address);
	void ADC(uint16_t address);
	void AND(uint16_t address);

	
	

	//Addressing modes
	uint16_t Implied();
	uint16_t Immediate();
	uint16_t Relative();
	uint16_t Accumulator();
	uint16_t ZeroPage();
	uint16_t ZeroPageX();
	uint16_t ZeroPageY();
	uint16_t Absolute();
	uint16_t AbsoluteX();
	uint16_t AbsoluteY();
	uint16_t Indirect();
	uint16_t IndirectX();
	uint16_t IndirectY();
};