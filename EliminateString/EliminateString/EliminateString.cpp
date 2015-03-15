//
//  EliminateString.cpp
//  EliminateString
//
//  Created by liyoudi on 20131122.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#include "EliminateString.h"

#include <string>
#include <map>
#include <list>

int EliminateString(const char *szStr)
{
    int nResult = 0;
    // 统计个数
    typedef std::list<char> CharList;
    CharList cl;
    typedef std::map<char, int> CharCount;
    CharCount cc;
    cc['a'] = 0;
    cc['b'] = 0;
    cc['c'] = 0;
    while (*szStr)
    {
        cl.push_back(*szStr);
        if (cc.find(*szStr) == cc.end())
        {
            cc[*szStr] = 0;
        }
        cc[*szStr]++;
        szStr++;
    }
    if (cc.size() != 3)
    {
        return -1;
    }
    // 开始消除
    bool bCutSome = true;
    while (bCutSome)
    {
//        CharList::iterator iterCur, iterNext;
//        for (iterCur = cl.begin(); iterCur != cl.end(); iterCur = iterNext)
//        {
//            iterNext = iterCur;
//            ++iterNext;
//            //
//
//        }
        std::multimap<int, CharCount::iterator> countCharMap;
        CharCount::iterator iter;
        for (iter = cc.begin(); iter != cc.end(); ++iter)
        {
            countCharMap.insert(std::make_pair(iter->second, iter));
        }
        std::multimap<int, CharCount::iterator>::iterator iterOther, itwo, ithree;
        iterOther = countCharMap.begin();
        if(iterOther->second->second == 0)
        {
            itwo = iterOther;
            ++itwo;
            ithree = itwo;
            ++ithree;
            if (itwo->second->second == 0)
            {
                return ithree->second->second;
            }
        }
        iterOther->second->second++;
        ++iterOther;
        iterOther->second->second--;
        ++iterOther;
        iterOther->second->second--;
    }
    return nResult;
}
