//
//  testSmallestOperation.h
//  testSmallestOperation
//
//  Created by liyoudi on 20131113.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#ifndef SmallestOperation_testSmallestOperation_h
#define SmallestOperation_testSmallestOperation_h


#include <cxxtest/TestSuite.h>
#include <list>
#include <stdio.h>
#include <iostream>
#include "SmallestOperation.h"

class testSmallestOperation : public CxxTest::TestSuite
{
public:
    void testCommon2(void)
    {
        const char *szDic[] = {
            "hot","dot","dog","lot","log"
        };

        TS_ASSERT_EQUALS(SmallestOperation(szDic, sizeof(szDic) / sizeof(const char *), "hit", "cog"), 0);

        set<string> dict;
        for (int i = 0; i < sizeof(szDic) / sizeof(const char *); i++)
        {
            dict.insert(szDic[i]);
        }
        vector<vector<string> > retPathVec;
        retPathVec = findLadders("hit", "cog", dict);
        for (int i = 0; i < retPathVec.size(); ++i)
        {
            for(int j = 0;j < retPathVec[i].size();++j)
            {
                std::cout << retPathVec[i][j] << " -> ";
            }
            std::cout << std::endl;
        }
    }
};
#endif
