//
//  testLuckNumber.h
//  testLuckNumber
//
//  Created by liyoudi on 20131113.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#ifndef YangHuiExtend_testYangHuiExtend_h
#define YangHuiExtend_testYangHuiExtend_h


#include <cxxtest/TestSuite.h>
#include <list>
#include <stdio.h>
#include <iostream>
#include "LuckNumber.h"

static void PrintPrimeNumList(int nMax)
{
    int nCount = 0;
    for(int i = 2;i < nMax;i++)
    {
        bool bIsPrime = true;
        for (int n = 2; n <= sqrt(i) ; n++)
        {
            if (i % n == 0) {
                bIsPrime = false;
                break;
            }
        }
        if (bIsPrime)
        {
            printf("%3d, ", i);
            nCount++;
            if (nCount % 10 == 0) {
                std::cout << std::endl;
            }
        }
    }
    std::cout << std::endl;
    std::cout << "The sum of primes is " << nCount << std::endl;
}


class testLuckNumber : public CxxTest::TestSuite
{
public:
    void testCommon(void)
    {
//        PrintPrimeNumList(1000);
        TS_ASSERT_EQUALS(lucky(10, 20), 4);
    }
};
#endif
