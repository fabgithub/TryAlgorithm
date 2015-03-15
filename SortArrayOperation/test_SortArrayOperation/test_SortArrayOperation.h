//
//  test_SortArrayOperation.h
//  SortArrayOperation
//
//  Created by liyoudi on 20131114.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#ifndef SortArrayOperation_testSortArrayOperation_h
#define SortArrayOperation_testSortArrayOperation_h

#include <cxxtest/TestSuite.h>
#include <list>
#include <stdio.h>
#include <iostream>

#include "SortArrayOperation.h"

#define MyTEST_SortArrayOperation(arr, elemCount, result) \
    { \
        TS_ASSERT_EQUALS(SortOperation(arr, elemCount), result); \
    }

class test_SortArrayOperation : public CxxTest::TestSuite
{
public:
    void testBasicSequence(void)
    {
        TS_ASSERT(true);
        int b[] = {3,2,1};
        MyTEST_SortArrayOperation(b, sizeof(b) / sizeof(int), 1);
        int a[] = {2,3,1};
        MyTEST_SortArrayOperation(a, sizeof(a) / sizeof(int), 2);
    }
};

#endif
