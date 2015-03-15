//
//  test_PalindromeString.h
//  PalindromeString
//
//  Created by liyoudi on 20131114.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#ifndef PalindromeString_testPalindromeString_h
#define PalindromeString_testPalindromeString_h

#include <cxxtest/TestSuite.h>
#include <list>
#include <stdio.h>
#include <iostream>

#include "PalindromeString.h"

class test_PalindromeString : public CxxTest::TestSuite
{
public:
    void testBasicSequence(void)
    {
        TS_ASSERT_EQUALS(palindrome("aaabmccab"), 12);
        TS_ASSERT_EQUALS(palindrome("cab"), 0);
        TS_ASSERT_EQUALS(palindrome("bccab"), 2);
        TS_ASSERT_EQUALS(palindrome("aabccab"), 6);
    }
};

#endif
