#ifndef BIT_MASK_UTIL_
#define BIT_MASK_UTIL_

#include <iostream>
#include <concepts>
#include <type_traits>

namespace BitMaskUtil
{
	template<typename _Tp>
	concept boolean_testable = std::convertible_to<_Tp, bool>;

	bool isBitInBitMask(uint32_t t_bitMask, uint32_t t_requiredBit);

	template<std::integral Number>
	uint8_t getSizeOfInt(Number t_number) {
		if (std::is_same<Number, uint8_t>::value || std::is_same<Number, int8_t>::value)
			return 0x8;
		else if (std::is_same<Number, uint16_t>::value || std::is_same<Number, int16_t>::value)
			return 0x10;
		else if (std::is_same<Number, uint32_t>::value || std::is_same<Number, int32_t>::value)
			return 0x20;
		else if (std::is_same<Number, uint64_t>::value || std::is_same<Number, int64_t>::value)
			return 0x40;
		else
			return 0;
	}

	template<std::integral Return, boolean_testable... Values>
	Return createBitMask(Values&&... t_values) {
		size_t m_index = 0;
		uint64_t m_tempBitMask = 0;
		for (auto& m_iterator : { t_values... }) {
			m_tempBitMask |= (m_iterator << m_index);
			++m_index;
		}
		//return (((... | (uint64_t)(t_values<<m_index), m_index++));
	}
};

#endif