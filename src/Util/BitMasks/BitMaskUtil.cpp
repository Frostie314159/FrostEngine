#include "BitMaskUtil.hpp"

bool BitMaskUtil::isBitInBitMask(uint32_t t_bitMask, uint32_t t_requiredBit) {
	return (t_bitMask & t_requiredBit) == t_requiredBit;
}