#pragma once

#include <stdint.h>
#include "CPUMemoryMap.h"

//Carry, Zero, Interrupt, Decimal, Break, Unused, Overflow, Negative flags
#define CF 1
#define ZF 2
#define IF 3
#define DF 4
#define BF 5
#define UF 6
#define VF 7
#define NF 8

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
	void Push(uint8_t value);
	void Push16(uint16_t value);
	uint8_t Pull();
	uint16_t Pull16();
	bool PagesCrossed(uint16_t addr0, uint16_t addr1);
	void Compare(uint8_t value1, uint8_t value2);
public:
	CPU();
	void Init();
	void Reset();
	void Cycle();

	void SetZ(uint8_t value);
	void SetN(uint8_t value);
	void SetCADC(uint16_t value);
	void SetCSBC(uint16_t value);
	void SetC(uint8_t value);
	void SetC(bool value);
	void SetD(bool value);
	void SetVADC(uint16_t sum, uint8_t value);
	void SetVSBC(uint16_t sum, uint8_t value);
	void SetV(uint8_t value);
	void SetV(bool value);
	void SetB(bool value);
	void SetI(bool value);
	bool GetBit(uint8_t value, int bit);

	// Instructions
	void ADC(uint16_t address);
	void AND(uint16_t address);
	void ASL(uint16_t address);	
	void BCC(uint16_t address);
	void BCS(uint16_t address);
	void BEQ(uint16_t address);
	void BIT(uint16_t address);
	void BMI(uint16_t address);
	void BNE(uint16_t address);
	void BPL(uint16_t address);
	void BRK(uint16_t address);
	void BVC(uint16_t address);
	void BVS(uint16_t address);
	void CLC(uint16_t address);
	void CLD(uint16_t address);
	void CLI(uint16_t address);
	void CLV(uint16_t address);
	void CMP(uint16_t address);
	void CPX(uint16_t address);
	void CPY(uint16_t address);
	void DEC(uint16_t address);
	void DEX(uint16_t address);
	void DEY(uint16_t address);
	void EOR(uint16_t address);
	void INC(uint16_t address);
	void INX(uint16_t address);
	void INY(uint16_t address);
	void JMP(uint16_t address);
	void JSR(uint16_t address);
	void LDA(uint16_t address);
	void LDX(uint16_t address);
	void LDY(uint16_t address);
	void LSR(uint16_t address);
	void NOP(uint16_t address);
	void ORA(uint16_t address);
	void PHA(uint16_t address);
	void PHP(uint16_t address);
	void PLA(uint16_t address);
	void PLP(uint16_t address);
	void ROL(uint16_t address);
	void ROR(uint16_t address);
	void RTI(uint16_t address);
	void RTS(uint16_t address);
	void SBC(uint16_t address);
	void SEC(uint16_t address);
	void SED(uint16_t address);
	void SEI(uint16_t address);
	void STA(uint16_t address);
	void STX(uint16_t address);
	void STY(uint16_t address);
	void TAX(uint16_t address);
	void TAY(uint16_t address);
	void TSX(uint16_t address);
	void TXA(uint16_t address);
	void TXS(uint16_t address);
	void TYA(uint16_t address);


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