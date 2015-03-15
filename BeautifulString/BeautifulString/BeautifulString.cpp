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
        if ((*szCh) <= 'z' && (*szCh) >= 'a' ) {
            s += (*szCh) - 'a' + 'A';
        }
        else
        {
            s += *szCh;
        }
        ++szCh;
    }
    map<char,int> chcount;
    for(int i=0;i<s.length();i++)
    {
        char c = (s.at(i));
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
    multimap<int,char>::reverse_iterator iic = sortc.rbegin();
    for(;iic != sortc.rend();++iic)
    {
        chcount[iic->second] = hao;
        hao--;
    }
    hao=0;
    for(int i=0;i<s.length();i++)
    {
        hao += chcount[s.at(i)];
    }
    for (map<char,int>::iterator iter = chcount.begin(); iter != chcount.end();++iter)
    {
        std::cout << iter->first << " = " << iter->second << std::endl;
    }
    std::cout << std::endl;
    return hao;
}
