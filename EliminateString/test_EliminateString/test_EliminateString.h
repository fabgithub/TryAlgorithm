//
//  test_EliminateString.h
//  EliminateString
//
//  Created by liyoudi on 20131114.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#ifndef EliminateString_testEliminateString_h
#define EliminateString_testEliminateString_h

#include <cxxtest/TestSuite.h>
#include <list>
#include <stdio.h>
#include <iostream>

#include "EliminateString.h"

class test_EliminateString : public CxxTest::TestSuite
{
public:
    void testBasicSequence(void)
    {
        TS_ASSERT_EQUALS(EliminateString("cab"), 2);
        TS_ASSERT_EQUALS(EliminateString("bcab"), 1);
    TS_ASSERT_EQUALS(EliminateString("caaabbaaaaccbbcaacbabacccaccbabbbbbbacbbabacccaabcbaacbcaacababacabaaabbccbcbcaaccbccccaccaaacbaccbbbaaacbcbaabaacaabaabcbaaabbbcccaacbaabbccaacaacabbbcaccaccccbbaabcacaccaacaabbaccabcacaabacaccabcbba"), 2);
    }
};

#endif
