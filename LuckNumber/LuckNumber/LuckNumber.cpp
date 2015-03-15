//
//  LuckNumber.cpp
//  LuckNumber
//
//  Created by liyoudi on 20131115.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#include "LuckNumber.h"

#include <map>
#include <set>
#include <list>

static int gnSmallPrimeArr[] = {
    2,   3,   5,   7,  11,  13,  17,  19,  23,  29,
    31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
    73,  79
};
static int gnPrimeArr[] = {
      2,   3,   5,   7,  11,  13,  17,  19,  23,  29,
     31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
     73,  79,  83,  89,  97, 101, 103, 107, 109, 113,
    127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
    179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
    233, 239, 241, 251, 257, 263, 269, 271, 277, 281,
    283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
    353, 359, 367, 373, 379, 383, 389, 397, 401, 409,
    419, 421, 431, 433, 439, 443, 449, 457, 461, 463,
    467, 479, 487, 491, 499, 503, 509, 521, 523, 541,
    547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
    607, 613, 617, 619, 631, 641, 643, 647, 653, 659,
    661, 673, 677, 683, 691, 701, 709, 719, 727, 733,
    739, 743, 751, 757, 761, 769, 773, 787, 797, 809,
    811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
    877, 881, 883, 887, 907, 911, 919, 929, 937, 941,
    947, 953, 967, 971, 977, 983, 991, 997
};

static int gnPrimeCount = sizeof(gnPrimeArr) / sizeof(int);

static std::set<int> gPrimeSet;

void InitPrimeSet()
{
    for (int i = 0; i < gnPrimeCount; ++i)
    {
        gPrimeSet.insert(gnPrimeArr[i]);
    }
}

int GetHowmanyNumbers(int n)
{
    int nResult = 0;
    do
    {
        nResult++;
        n = n / 10;
    }while(n);
    return nResult;
}

typedef std::multiset<int> SeperateWay;
class SeperateWayLess
{
public:
    bool operator () (const SeperateWay &sw1, const SeperateWay &sw2)
    {
        if (sw1.size() < sw2.size())
        {
            return true;
        }
        else if(sw1.size() == sw2.size())
        {
            return sw1 < sw2;
        }
        return false;
    }
};

std::ostream & operator << (std::ostream &os, const SeperateWay &sw)
{
    int nSum = 0, nPingFangSum = 0;
    SeperateWay::const_iterator citer = sw.begin();
    for (; sw.end() != citer; ++citer)
    {
        os << (*citer) << ", ";
        nSum += (*citer);
        nPingFangSum += (*citer) * (*citer);
    }
    os << " nSum = " << nSum << ", nPingFangSum = " << nPingFangSum;
    return os;
}

// 打印素数n的各种拆分为nCount份的方案
void PrintSeperateWay(int nPrimeNum, int nCount, std::set<SeperateWay,SeperateWayLess> &seperateSet)
{
    int nIndexArr[20], p1 = 1;
    memset(nIndexArr, 0, sizeof(nIndexArr));

    int nMinNum = nPrimeNum - (nCount - 1) * 9;
    if (nMinNum <= 0)
    {
        nMinNum = 1;
    }
    if (nMinNum > 9)
    {
        return ;
    }

    int nMaxNum = nPrimeNum - (nCount - 1) * nMinNum;
    if (nMaxNum > 9)
    {
        nMaxNum = 9;
    }
    if (nMaxNum <= 0)
    {
        return ;
    }
    for (p1 = 1; p1 <= nCount; p1++)
    {
        nIndexArr[p1] = nMinNum;
    }
    while (true)
    {
        int n = nCount;
        for (;n > 0;--n)
        {
            nIndexArr[n]++;
            if (nIndexArr[n] > nMaxNum)
            {
                nIndexArr[n] = nIndexArr[n - 1];
            }
            else
            {
                break;
            }
        }
        if (n <= 0)
        {
            return ;
        }
        //
        int nSum = 0;
        SeperateWay sw;
        int nPingFangSum = 0;
        for (p1 = 1; p1 <= nCount; p1++)
        {
            nSum += nIndexArr[p1];
            nPingFangSum += nIndexArr[p1] * nIndexArr[p1];
            sw.insert(nIndexArr[p1]);
        }
        if (nSum == nPrimeNum && gPrimeSet.find(nPingFangSum) != gPrimeSet.end())
        {
            seperateSet.insert(sw);
        }
    }
}

int CalcJieCheng(long n)
{
    int res = 1;
    while (n > 0)
    {
        res *= n;
        --n;
    }
    return res;
}

int HowManyLucky(const SeperateWay & way, int from, int to, std::list<int> &fromWei, const std::list<int> & toWei)
{
    std::map<int, long> numCount;
    SeperateWay::const_iterator citer = way.begin();
    for (; citer != way.end(); ++citer)
    {
        if (numCount.find(*citer) == numCount.end())
        {
            numCount[*citer] = 0;
        }
        numCount[*citer]++;
    }
    while (fromWei.size() < toWei.size())
    {
        fromWei.push_front(0);
    }
    numCount[0] = fromWei.size() - way.size();
    //
    int nAllCount = 0;
    while (!fromWei.empty())
    {
        int nMin = fromWei.front();
        int nMax = toWei.front();
        int nProperMaxCount = 0;
        int nProperMinCount = 0;
        int nCopyCount = 1;
        std::map<int, long>::iterator iterC;
        for (iterC = numCount.begin(); iterC != numCount.end(); ++iterC)
        {
            if (iterC->first < nMin)
            {
                nProperMinCount += iterC->second;
            }
            if (iterC->first > nMax)
            {
                nProperMaxCount += iterC->second;
            }
            nCopyCount *= CalcJieCheng(iterC->second);
        }
        nAllCount += CalcJieCheng(fromWei.size()) / nCopyCount;
        
    }
    return nAllCount;
}

int CalcWeiShu(int n, std::list<int> &wei)
{
    int nRes = 0;
    while (n)
    {
        ++nRes;
        wei.push_front(n % 10);
        n /= 10;
    }
    return nRes;
}

int lucky(int x, int y)
{
    if(x > y)
    {
        return 0;
    }
    int nResult = 0;
    InitPrimeSet();
    // 找到和可以是素数的数字组
    // 判断这些数字组的平方和是否是素数
    std::list<int> xWei;
    std::list<int> yWei;
    CalcWeiShu(x, xWei);
    CalcWeiShu(y, yWei);
    int nAllFangAn = 0;
    for (int nCount = 1; nCount <= yWei.size(); ++nCount)
    {
        for (int i = 0; i < sizeof(gnSmallPrimeArr) / sizeof(int); i++)
        {
            std::set<SeperateWay,SeperateWayLess> seperateSet;
            PrintSeperateWay(gnSmallPrimeArr[i], nCount, seperateSet);
            std::set<SeperateWay,SeperateWayLess>::iterator iter = seperateSet.begin();
            int nNO = 1;
            for (; iter != seperateSet.end(); ++iter)
            {
                std::cout << "\t" << nNO++ << ":\t" << (*iter) << std::endl;
                nAllFangAn++;
                HowManyLucky(*iter, x, y, xWei, yWei);
            }
            if (!seperateSet.empty())
            {
//                std::cout << gnSmallPrimeArr[i] << " 分成 " << nCount << " 份有 " << seperateSet.size() << " 种方案." << std::endl;
            }
        }
        std::cout << "分成 <= " << nCount << " 份的方案共有 " << nAllFangAn << " 个." << std::endl;
    }
    return nResult;
}
