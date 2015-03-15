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
#include <sys/time.h>

int TemplateTestestTlsPerformence(int from, int to)
{
    int res = 0;
    timeval tvNow, tvStart;
    gettimeofday(&tvStart, NULL);
    int nTimes = 0;
//    do {
        ++nTimes;
        res = lucky(from, to);
        gettimeofday(&tvNow, NULL);
//    }while (tvNow.tv_sec - tvStart.tv_sec < nSumSeconds);
    double nSec = tvNow.tv_sec - tvStart.tv_sec;
    double nMS  = (tvNow.tv_usec - tvStart.tv_usec) / 1000.0;
    double duration = nSec + nMS / 1000.0;
    std::cout << "used " << duration << " per second." << std::endl;
    return res;
}

class testLuckNumber : public CxxTest::TestSuite
{
public:
    void testCommon(void)
    {
        TS_ASSERT_EQUALS(TemplateTestestTlsPerformence(10, 20), 4);
        TS_ASSERT_EQUALS(TemplateTestestTlsPerformence(10, 200), 4);
//        TS_ASSERT_EQUALS(TemplateTestestTlsPerformence(10000000, 100000000), 4);
    }
};
#endif
