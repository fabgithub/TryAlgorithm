//
//  testBeautifulString.h
//  BeautifulString
//
//  Created by liyoudi on 20131114.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#ifndef BeautifulString_testBeautifulString_h
#define BeautifulString_testBeautifulString_h


#include <cxxtest/TestSuite.h>
#include <list>
#include <iostream>

#include "BeautifulString.h"

class testBeautifulString : public CxxTest::TestSuite
{
public:
    void testBasicString(void)
    {
        TS_ASSERT_EQUALS(26, perfect("a"));
        TS_ASSERT_EQUALS(52, perfect("aa"));
        TS_ASSERT_EQUALS(75, perfect("abc"));
        TS_ASSERT_EQUALS(101, perfect("abca"));
        TS_ASSERT_EQUALS(153, perfect("abcaaa"));
        TS_ASSERT_EQUALS(176, perfect("abcabcc"));
        TS_ASSERT_EQUALS(202, perfect("abcabccc"));
        TS_ASSERT_EQUALS(227, perfect("abcaabccc"));
        TS_ASSERT_EQUALS(250, perfect("abcaabzccc"));
        TS_ASSERT_EQUALS(250, perfect("abcaabzccc"));
        TS_ASSERT_EQUALS(296, perfect("abcaabzbDccc"));
        TS_ASSERT_EQUALS(348, perfect("abcaaCCbzbDccc"));
    }
};


#endif
