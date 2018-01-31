#ifndef POLYVARIANT_TEST_HPP
#define POLYVARIANT_TEST_HPP

#include <array>
#include "gtest/gtest.h"
#include "infra/PolyVariant.hpp"
#include "stdio.h"

namespace sx
{
	struct dummy
	{
	public:
		dummy(uint32_t w, uint32_t d)
		{}

		uint64_t mem1;
		uint32_t mem2;
		// 4 bytes padding
	};

	struct B : public dummy
	{
		B() : dummy(1, 2) {}
	};

	struct C : public B
	{
		long b;
	};
	
	struct D {};
	//static_assert(PolyVariant<uint32_t>::Size == 4);
	static_assert(PolyVariant<dummy, dummy>::Size == 16);
	static_assert(PolyVariant<dummy, C, B>::Size == 24);


	TEST(PolyVariantTest, Get)
	{
		PolyVariant<dummy, C, B> wat;
		const C& c = wat;
		//static_assert(PolyVariant<)
	}
}

#endif