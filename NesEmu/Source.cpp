#include <iostream>
#include <stdint.h>
#include <bitset>

int main() {
	bool bit = true;
	uint8_t byte = 0x81;
	int8_t byte1 = byte & bit;
	std::cout <<std::bitset<8>(byte)<<" "<<bit<<" "<< std::bitset<8>(byte1);
	system("pause");
	return 0;
}