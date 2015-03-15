//
//  test_TwentyFourGame.h
//  TwentyFourGame
//
//  Created by liyoudi on 20131114.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#ifndef TwentyFourGame_testTwentyFourGame_h
#define TwentyFourGame_testTwentyFourGame_h

#include <cxxtest/TestSuite.h>
#include <list>
#include <stdio.h>
#include <iostream>

#include "TwentyFourGame.h"

class test_TwentyFourGame : public CxxTest::TestSuite
{
public:
    void testBasicSequence(void)
    {
        double aa = (8/3.0);
        std::cout << 8.0/(3-aa) << std::endl;
//        TS_ASSERT_EQUALS(8.0/(3-aa), 24);
        TS_ASSERT_EQUALS(can24(1, 13, 1, 13), 1);
        TS_ASSERT_EQUALS(can24(8, 3, 8, 3), 1);
        TS_ASSERT_EQUALS(can24(1, 1, 1, 10), 0);
        TS_ASSERT_EQUALS(can24(1, 1, 1, 11), 1);
        TS_ASSERT_EQUALS(can24(6, 6, 6, 6), 1);
        TS_ASSERT_EQUALS(can24(5, 5, 5, 1), 1);
    }
};

#endif
