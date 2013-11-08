//
//  testBigNumSuit.h
//  NonDisplayNumber
//
//  Created by liyoudi on 20131107.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#ifndef NonDisplayNumber_testBigNumSuit_h
#define NonDisplayNumber_testBigNumSuit_h


#include <cxxtest/TestSuite.h>
#include <list>
#include <iostream>
#include <sstream>

#include "JxBigNum.h"

#define TEST_BIGNUM_OP(n1, n2, op, resStr) \
    TS_ASSERT_EQUALS( (JxBigNum(n1) op JxBigNum(n2)).ToString(), resStr );

namespace CxxTest
{
    CXXTEST_TEMPLATE_INSTANTIATION
    class ValueTraits<JxBigNum>
    {
        std::string mstrValue;
    public:
        ValueTraits(const JxBigNum& m) { mstrValue = m.ToString(); }
        const char *asString() const { return mstrValue.c_str(); }
    };
};

int GetEsp()
{
    __asm
    {
        pop ebx
        pop ebp
        mov eax, ebp
        ret
    }
}

#define ShowEsp() \
{\
    /*std::cout << "show Esp in " << __FUNCTION__ << " is " << GetEsp() << std::endl; */\
}


class testStdListSuit : public CxxTest::TestSuite
{
public:
    void testAddition(void)
    {
        ShowEsp();
        TEST_BIGNUM_OP(0xFFFFFFF0, 0xFFFFFFFF, +, "0x00000001ffffffef");
        TEST_BIGNUM_OP(0xFFFFFFFF, 0xFFFFFFFF, +, "0x00000001fffffffe");
        TEST_BIGNUM_OP(1, 0xFFFFFFFF, +, "0x0000000100000000");
        TEST_BIGNUM_OP(0, 0xFFFFFFFF, +, "0xffffffff");
        TEST_BIGNUM_OP(0xFFFFFFFF, 0xFFFFFFFF, +, "0x00000001fffffffe");
        TEST_BIGNUM_OP(0, 0, +, "0x00000000");
        TEST_BIGNUM_OP(0, 1, +, "0x00000001");
        TEST_BIGNUM_OP(1, 0, +, "0x00000001");
        TEST_BIGNUM_OP(1, 1, +, "0x00000002");
    }
    void testSub(void)
    {
        TEST_BIGNUM_OP(0xFFFFFFF0, 0xFFFFFFFF, -, "-0x0000000f");
        TEST_BIGNUM_OP(0xFFFFFFFF, 0xFFFFFFFF, -, "0x00000000");
        TEST_BIGNUM_OP(1, 0xFFFFFFFF, -, "-0xfffffffe");
        TEST_BIGNUM_OP(0, 0xFFFFFFFF, -, "-0xffffffff");
        TEST_BIGNUM_OP(0, 0, -, "0x00000000");
        TEST_BIGNUM_OP(0, 1, -, "-0x00000001");
        TEST_BIGNUM_OP(1, 0, -, "0x00000001");
        TEST_BIGNUM_OP(1, 1, -, "0x00000000");
        ShowEsp();
    }
    void testMul(void)
    {
        TEST_BIGNUM_OP(0, 1, *, "0x00000000");
        TEST_BIGNUM_OP(1, 0, *, "0x00000000");
        TEST_BIGNUM_OP(1, 1, *, "0x00000001");
        TEST_BIGNUM_OP(0xFFFFFFF0, 0xFFFFFFFF, *, "0xffffffef00000010");
        TEST_BIGNUM_OP(0xFFFFFFFF, 0xFFFFFFFF, *, "0xfffffffe00000001");
        TEST_BIGNUM_OP(1, 0xFFFFFFFF, *, "0xffffffff");
        TEST_BIGNUM_OP(0, 0xFFFFFFFF, *, "0x00000000");
        ShowEsp();
   }
    void testDiv(void)
    {
        ShowEsp();
    }
    void testMod(void)
    {
        ShowEsp();
    }
    void testMixOp(void)
    {
        ShowEsp();
        JxBigNum num(0xFFFFFFFE);
        JxBigNum ori = num;
        num += ori;
        num += ori;
        num += ori;
        num -= ori;
        num -= ori;
        num -= ori;
        TS_ASSERT_EQUALS(num, ori);
        JxBigNum tmp(0xFFFFFFFd);
        TEST_BIGNUM_OP(num, 2, +, (tmp + 3).ToString());
        TEST_BIGNUM_OP(num, 2, +, "0x0000000100000000");
    }

    void tearDown()
    {
        ShowEsp();
    }
};

#endif
