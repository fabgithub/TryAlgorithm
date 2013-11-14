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
    {\
        JxBigNum tmp1(n1), tmp2(n2); \
        if(#op[0] == '+') tmp1 += tmp2; \
        if(#op[0] == '-') tmp1 -= tmp2; \
        if(#op[0] == '*') tmp1 *= tmp2; \
        if(#op[0] == '/') tmp1 /= tmp2; \
        if(#op[0] == '%') tmp1 %= tmp2; \
        if(#op[0] == '>' && #op[1] == '>') tmp1 >>= n2; \
        if(#op[0] == '<' && #op[1] == '<') tmp1 <<= n2; \
        TS_ASSERT_EQUALS(tmp1.ToString(), resStr ); \
        TS_ASSERT_EQUALS( (JxBigNum(n1) op (n2)), JxBigNum(resStr) ); \
    }

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
    JxBigNum mNum1, mNum2;
    testStdListSuit()
    {
        for (int i = 0; i < 5; i++)
        {
            mNum1 += 0x98765432;
            mNum1 <<= 32;
            mNum2 += 0x23456789;
            mNum2 <<= 32;
        }
    }
public:
    void testAddition(void)
    {
        TS_ASSERT_EQUALS(mNum1.ToString(), "0x987654329876543298765432987654329876543200000000");
        TS_ASSERT_EQUALS(mNum2.ToString(), "0x234567892345678923456789234567892345678900000000");
        
        TEST_BIGNUM_OP(mNum2, 0xFFFFFFFF, +, "0x2345678923456789234567892345678923456789ffffffff");
        TEST_BIGNUM_OP(mNum2 + 0xFFFFFFFF, 1, +, "0x234567892345678923456789234567892345678a00000000");


        TEST_BIGNUM_OP(0xFFFFFFF0, 0xFFFFFFFF, +, "0x1ffffffef");
        TEST_BIGNUM_OP(0xFFFFFFFF, 0xFFFFFFFF, +, "0x1fffffffe");
        TEST_BIGNUM_OP(1, 0xFFFFFFFF, +, "0x100000000");
        TEST_BIGNUM_OP(0, 0xFFFFFFFF, +, "0xffffffff");
        TEST_BIGNUM_OP(0xFFFFFFFF, 0xFFFFFFFF, +, "0x1fffffffe");
        TEST_BIGNUM_OP(0, 0, +, "0x0");
        TEST_BIGNUM_OP(0, 1, +, "0x1");
        TEST_BIGNUM_OP(1, 0, +, "0x1");
        TEST_BIGNUM_OP(1, 1, +, "0x2");
    }
    void testSub(void)
    {
        TEST_BIGNUM_OP(0xFFFFFFF0, 0xFFFFFFFF, -, "-0xf");
        TEST_BIGNUM_OP(0xFFFFFFFF, 0xFFFFFFFF, -, "0x0");
        TEST_BIGNUM_OP(1, 0xFFFFFFFF, -, "-0xfffffffe");
        TEST_BIGNUM_OP(0, 0xFFFFFFFF, -, "-0xffffffff");
        TEST_BIGNUM_OP(0, 0, -, "0x0");
        TEST_BIGNUM_OP(0, 1, -, "-0x1");
        TEST_BIGNUM_OP(1, 0, -, "0x1");
        TEST_BIGNUM_OP(1, 1, -, "0x0");
        ShowEsp();
    }
    void testMul(void)
    {
        TEST_BIGNUM_OP(JxBigNum(0x12345678), 16, *, "0x123456780");
        TEST_BIGNUM_OP(JxBigNum(0x12345678) * 16, 16, *, "0x1234567800");
        TEST_BIGNUM_OP(0x12345, 0x12345, *, "0x14b65f099");
        TEST_BIGNUM_OP(0, 1, *, "0x0");
        TEST_BIGNUM_OP(1, 0, *, "0x0");
        TEST_BIGNUM_OP(1, 1, *, "0x1");
        TEST_BIGNUM_OP(0xFFFFFFF0, 0xFFFFFFFF, *, "0xffffffef00000010");
        TEST_BIGNUM_OP(0xFFFFFFFF, 0xFFFFFFFF, *, "0xfffffffe00000001");
        TEST_BIGNUM_OP(1, 0xFFFFFFFF, *, "0xffffffff");
        TEST_BIGNUM_OP(0, 0xFFFFFFFF, *, "0x0");
        ShowEsp();
   }
    void testShiftRight(void)
    {
        TEST_BIGNUM_OP(0x12345678, 1, >>, "0x91a2b3c");
        TEST_BIGNUM_OP(0x12345678, 2, >>, "0x48d159e");
        TEST_BIGNUM_OP(0x12345678, 3, >>, "0x2468acf");
        TEST_BIGNUM_OP(0x12345678, 4, >>, "0x1234567");
        TEST_BIGNUM_OP(0x12345678, 5, >>, "0x91a2b3");
        TEST_BIGNUM_OP(0x12345678, 6, >>, "0x48d159");
        TEST_BIGNUM_OP(0x12345678, 7, >>, "0x2468ac");
        TEST_BIGNUM_OP(0x12345678, 8, >>, "0x123456");
        TEST_BIGNUM_OP(0x12345678, 9, >>, "0x91a2b");
        TEST_BIGNUM_OP(0x12345678, 27, >>, "0x2");
        TEST_BIGNUM_OP(0x12345678, 28, >>, "0x1");
        TEST_BIGNUM_OP(0x12345678, 29, >>, "0x0");
        TEST_BIGNUM_OP(0x12345678, 32, >>, "0x0");
        TEST_BIGNUM_OP(0x12345678, 33, >>, "0x0");
        ShowEsp();
    }
    void testShiftLeft(void)
    {
        TEST_BIGNUM_OP(0x12345678, 1, <<, "0x2468acf0");
        TEST_BIGNUM_OP(0x12345678, 2, <<, "0x48d159e0");
        TEST_BIGNUM_OP(0x12345678, 3, <<, "0x91a2b3c0");
        TEST_BIGNUM_OP(0x12345678, 4, <<, "0x123456780");
        TEST_BIGNUM_OP(0x12345678, 5, <<, "0x2468acf00");
        TEST_BIGNUM_OP(0x12345678, 6, <<, "0x48d159e00");
        TEST_BIGNUM_OP(0x12345678, 7, <<, "0x91a2b3c00");
        TEST_BIGNUM_OP(0x12345678, 8, <<, "0x1234567800");

        TEST_BIGNUM_OP(0x12345678, 32, <<, "0x1234567800000000");
        TEST_BIGNUM_OP(0x12345678, 33, <<, "0x2468acf000000000");
        TEST_BIGNUM_OP(0x12345678, 34, <<, "0x48d159e000000000");
        TEST_BIGNUM_OP(0x12345678, 35, <<, "0x91a2b3c000000000");
        TEST_BIGNUM_OP(0x12345678, 36, <<, "0x12345678000000000");
        ShowEsp();
    }
    void testDiv(void)
    {
        ShowEsp();
//        TEST_BIGNUM_OP("55", 11, /, "0x5");
        TEST_BIGNUM_OP("0x45160b7a437", 0x10d63af1, /, "0x41a7");
//        return ;
        TEST_BIGNUM_OP(0xFFFFEEA, 0xFEACB, /, "0x101");
        TEST_BIGNUM_OP(123456, 12301, /, "0xa");
        TEST_BIGNUM_OP(8304, 123, /, "0x43");
        TEST_BIGNUM_OP(32, 3, /, "0xa");
        TEST_BIGNUM_OP(100, 10, /, "0xa");
        TEST_BIGNUM_OP("0x123456789f", 0x10, /, "0x123456789");
        TEST_BIGNUM_OP("0x41a7", 0x10d63af1, *, "0x45160b7a437");
        JxBigNum num(rand());
        JxBigNum startValue(num);
        JxBigNum nTmp = rand();
//        std::cout << "num = " << num << ", nTmp = " << nTmp << std::endl;
        int n = 0;
        int nTimes = 10;
        for(n = 0;n < nTimes;n++)
        {
//            std::cout << num << " * " << nTmp;
            num *= nTmp;
//            std::cout << " = " << num << std::endl;
        }
        for(n = 0;n < nTimes;n++)
        {
//            std::cout << num << " / " << nTmp;
            num /= nTmp;
//            std::cout << " = " << num << std::endl;
        }
        TS_ASSERT_EQUALS(startValue, num);
        for(n = 0;n < 10;n++)
        {
            nTmp = rand();
            nTmp << rand() % 117;
            num *= nTmp;
            num /= nTmp;
            TS_ASSERT_EQUALS(num, startValue);
        }
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
        TEST_BIGNUM_OP(num, 2, +, "0x100000000");
        TS_ASSERT_EQUALS(num, (num << 100) >> 100);
        TS_ASSERT_EQUALS(num, (num << 318) >> 318);
        TS_ASSERT_EQUALS(num, (num << 319) >> 319);
        TS_ASSERT_EQUALS(num, (num << 320) >> 320);
        TS_ASSERT_EQUALS(num, (num << 321) >> 321);
    }

    void testStrToBigBun(void)
    {
#define TEST_STR_NUM(str) { JxBigNum tmp(str); TS_ASSERT_EQUALS( tmp.ToString(), str); }
        TEST_STR_NUM("0x0");
        TEST_STR_NUM("0x1");
        TEST_STR_NUM("0x10");
        TEST_STR_NUM("0x1231230000000000");
        TEST_STR_NUM("0x1232300000000000");
    }

    void testPower(void)
    {
#define TEST_POWER(str) { JxBigNum tmp(str); TS_ASSERT_EQUALS( tmp.Pow(10), tmp * tmp * tmp * tmp * tmp * tmp * tmp * tmp * tmp * tmp); }
        TEST_POWER("0x0");
        TEST_POWER("0x1");
        TEST_POWER("0x10");
        TEST_POWER("0x1231230000000000");
        TEST_POWER("0x1232300000000000");
    }

    void tearDown()
    {
        ShowEsp();
//        std::cout << "2 ^ 13 = " << (2 ^ 13) << std::endl;
    }
};

#endif
