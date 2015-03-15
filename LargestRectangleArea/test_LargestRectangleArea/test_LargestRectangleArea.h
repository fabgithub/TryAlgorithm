//
//  test_LargestRectangleArea.h
//  LargestRectangleArea
//
//  Created by liyoudi on 20131114.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#ifndef LargestRectangleArea_testLargestRectangleArea_h
#define LargestRectangleArea_testLargestRectangleArea_h

#include <cxxtest/TestSuite.h>
#include <list>
#include <stdio.h>
#include <iostream>
#include <string>

#include "LargestRectangleArea.h"

class test_LargestRectangleArea : public CxxTest::TestSuite
{
public:
    void testBasicSequence(void)
    {
        {
            int nHightArr[] = {1};
            TS_ASSERT_EQUALS(LargestRectangleArea(nHightArr, sizeof(nHightArr) / sizeof(int)), 1);
        }
        {
            int nHightArr[] = {2,1,5,6,2,3};
            TS_ASSERT_EQUALS(LargestRectangleArea(nHightArr, sizeof(nHightArr) / sizeof(int)), 10);
        }
        {
            int nHightArr[] = {2,1,6,5,2,3};
            TS_ASSERT_EQUALS(LargestRectangleArea(nHightArr, sizeof(nHightArr) / sizeof(int)), 10);
        }
        {
            int nHightArr[] = {2,1,3,1,2,3};
            TS_ASSERT_EQUALS(LargestRectangleArea(nHightArr, sizeof(nHightArr) / sizeof(int)), 6);
        }
    }
};

#endif
