//
//  testCoverageNumber.h
//  CoverageNumber
//
//  Created by liyoudi on 20131115.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#ifndef CoverageNumber_testCoverageNumber_h
#define CoverageNumber_testCoverageNumber_h

#include <cxxtest/TestSuite.h>
#include <list>
#include <stdio.h>
#include <iostream>

#include "CoverageNumber.h"

class testCoverageNumber : public CxxTest::TestSuite
{
public:
    void testCommon(void)
    {
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 2, 65), 17);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 30, 65), 16);

        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 87, 1116), 1026);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 87, 116), 26);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 87, 115), 25);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 87, 114), 25);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 87, 113), 25);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 87, 112), 25);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 87, 111), 25);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 87, 87), 1);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 86, 87), 1);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 85, 87), 1);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 84, 87), 1);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 83, 87), 1);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 82, 87), 1);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 81, 87), 1);
        TS_ASSERT_EQUALS(CoverageNumber(29, 37, 80, 87), 1);

        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 110, 1200), 1090);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 1200), 1143);

        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 1200), 1143);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 200), 143);

        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 108), 51);

        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 107), 50);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 106), 50);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 105), 50);

        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 104), 49);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 103), 48);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 102), 47);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 101), 46);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 100), 45);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 99), 44);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 98), 43);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 97), 42);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 96), 41);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 95), 40);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 94), 39);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 93), 38);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 92), 37);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 91), 36);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 90), 35);

        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 89), 34);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 88), 34);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 87), 34);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 86), 34);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 85), 34);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 84), 34);

        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 78), 28);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 77), 27);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 76), 26);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 75), 25);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 74), 24);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 73), 23);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 72), 22);

        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 71), 21);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 70), 21);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 69), 21);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 68), 21);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 67), 21);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 66), 21);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 65), 21);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 64), 21);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 63), 21);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 55), 13);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 54), 12);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 53), 11);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 52), 11);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 51), 11);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 49), 11);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 48), 11);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 46), 11);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 45), 11);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 44), 11);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 43), 11);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 42), 11);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 36), 5);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 35), 4);
        TS_ASSERT_EQUALS(CoverageNumber(18, 21, 1, 31), 4);


        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 1, 31), 15);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 1, 23), 8);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 1, 22), 8);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 1, 21), 8);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 1, 15), 3);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 1, 14), 3);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 1, 13), 3);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 1, 3), 0);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 7, 50), 34);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 7, 33), 17);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 11, 33), 14);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 20, 33), 10);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 21, 33), 9);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 21, 31), 7);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 21, 32), 8);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 5, 20), 8);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 11, 20), 5);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 10, 20), 6);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 10, 19), 5);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 9, 20), 7);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 3, 20), 8);
        TS_ASSERT_EQUALS(CoverageNumber(8, 10, 7, 20), 8);
    }
};

#endif
