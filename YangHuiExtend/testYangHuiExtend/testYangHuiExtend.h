//
//  testYangHuiExtend.h
//  YangHuiExtend
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

bool IsOdd(int n, int m);
int FirstNonOddPos(int n);

extern size_t nMaxSetSize;

void TryAll()
{
    nMaxSetSize = 0;
    std::cout << std::endl;
    char szBuf[20] = "";
    int nMax = 15100;
    for (int n = 1; n < nMax; n++)
    {
        sprintf(szBuf, "%03d", n);
        std::cout << szBuf;
        for (int m = 1 - nMax; m <= n - 1; m++)
        {
            if(m >= 1 - n)
            {
                if(IsOdd(n, m))
                {
//                    std::cout << "1";
                }
                else
                {
                    std::cout << "(" << m + n << ")";
                    break;
                }
            }
            else
            {
//                std::cout << "_";
            }
//            std::cout.flush();
        }
        std::cout << std::endl;
    }
    std::cout << "nMaxSetSize is " << nMaxSetSize << std::endl;
}

class testYangHuiExtend : public CxxTest::TestSuite
{
public:
    void testYangHui(void)
    {
//        TS_ASSERT_EQUALS(IsOdd(60, 6), true);
//        for (int i = 99999996; i < 100000000; i++)
        for (int i = 1; i < 1000; i++)
        {
            int pos = FirstNonOddPos(i);
            if (pos < 0)
            {
                continue;
            }
            bool bres = IsOdd(i, pos - i);
            if (bres) {
                TS_ASSERT_EQUALS(false, bres);
            }
        }
//
//        TS_ASSERT_EQUALS(IsOdd(2, -1), true);
//        TS_ASSERT_EQUALS(IsOdd(2, 0), true);
//        TS_ASSERT_EQUALS(IsOdd(2, 1), true);
//
//        TS_ASSERT_EQUALS(IsOdd(3, -2), true);
//        TS_ASSERT_EQUALS(IsOdd(3, -1), false);
//        TS_ASSERT_EQUALS(IsOdd(3, 0), true);
//        TS_ASSERT_EQUALS(IsOdd(3, 1), false);
//        TS_ASSERT_EQUALS(IsOdd(3, 2), true);
//
//        TS_ASSERT_EQUALS(IsOdd(4, -3), true);
//        TS_ASSERT_EQUALS(IsOdd(4, -2), true);
//        TS_ASSERT_EQUALS(IsOdd(4, -1), false);
//        TS_ASSERT_EQUALS(IsOdd(4, 0), true);
//        TS_ASSERT_EQUALS(IsOdd(4, 1), false);
//        TS_ASSERT_EQUALS(IsOdd(4, 2), true);
//        TS_ASSERT_EQUALS(IsOdd(4, 3), true);

        std::cout << "nMaxSetSize is " << nMaxSetSize << std::endl;
//        TryAll();
    }
};
#endif
