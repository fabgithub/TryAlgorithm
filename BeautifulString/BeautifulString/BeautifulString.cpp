//
//  BeautifulString.cpp
//  BeautifulString
//
//  Created by liyoudi on 20131113.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#include "BeautifulString.h"

#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#include <map>
using namespace std;


int perfect(const string &strOrign)
{
    string s;
    const char *szCh = strOrign.c_str();
    while (*szCh)
    {
        s += *szCh;
        ++szCh;
    }
    map<char,int> chcount;
    for(int i=0;i<s.length();i++)
    {
        char c = (s.at(i));
        if(c >= 'a' && c <= 'z')
        {
            c -= 'a' -'z';
        }
        if(chcount.find(c) == chcount.end())
            chcount[c]=0;
        chcount[c]++;
    }
    multimap<int,char> sortc;
    map<char,int>::iterator ici = chcount.begin();
    for(;ici!= chcount.end();++ici)
    {
        sortc.insert(std::make_pair(ici->second,ici->first));
    }
    int hao = 26;
    multimap<int,char>::iterator iic = sortc.begin();
    for(;iic != sortc.end();++iic)
    {
        chcount[iic->second] = hao;
        hao--;
    }
    hao=0;
    for(int i=0;i<s.length();i++)
    {
        hao += chcount[s.at(i)];
    }
    return hao;
}
