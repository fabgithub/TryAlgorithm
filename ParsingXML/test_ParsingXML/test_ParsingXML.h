//
//  test_ParsingXML.h
//  ParsingXML
//
//  Created by liyoudi on 20131114.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#ifndef ParsingXML_testParsingXML_h
#define ParsingXML_testParsingXML_h

#include <cxxtest/TestSuite.h>
#include <list>
#include <stdio.h>
#include <iostream>
#include <string>

#include "ParsingXML.h"

class test_ParsingXML : public CxxTest::TestSuite
{
public:
    void testBasicSequence(void)
    {
        std::string in = "<?xml version=\"1.0\" ?><Books><Book><Name = \"The C++ Programming Language\" Author=\"Bjarne Stroustrup\" /></Book><Book><Name = \"Effective C++\" Author = \"Scott Meyers\" /></Book></Books>";
        std::string out = "Books\r\n\tBook 1\r\n\t\tName:The C++ Programming Language\r\n\t\tAuthor:Bjarne Stroustrup\r\n\tBook 2\r\n\t\tName:Effective C++\r\n\t\tAuthor:Scott Meyers";
        TS_ASSERT_EQUALS(ParsingXML(in), out);
    }
};

#endif
