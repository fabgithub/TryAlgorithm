//
//  JxBigNum.cpp
//  NonDisplayNumber
//  大数,实现运算操作. this is in master branch
//  added in tata branch.
//  add in second branch.
//  add in TryAlgotithm first branch.
//  add some text in tata second times.
//  Created by liyoudi on 20131107.
//  add in second branch second times.
//  add in third branch
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//
// add in forth branch.
//
// add in forth branch twice.
//
// add in forth branch 3 times.
//

// add in fifth branch.

// add in fifth branch twice.

// add in fifth branch 3 times.

// add feathure in sixth branch.

// add in fifth branch twice.

// add in fifth branch 3 times.

// add feathure in first branch.

// add feathure in seventh branch.

// add in second branch.

#include "JxBigNum.h"
#include <sstream>

JxBigNum::JxBigNum():mbSign(false)
{
    mNums.push_front(0);
}

JxBigNum::JxBigNum(const char *szNum):mbSign(false)
{
    InitWithStr(szNum ? szNum : "0");
}
JxBigNum::JxBigNum(const std::string &strNum):mbSign(false)
{
    InitWithStr(strNum.empty() ? "0" : strNum.c_str());
}

JxBigNum::JxBigNum(int n)
{
    if (n < 0) {
        mbSign = true;
        n = -n;
    }
    else
    {
        mbSign = false;
    }
    mNums.push_back(n);
}
JxBigNum::JxBigNum(unsigned int n)
: mbSign(false)
{
    mNums.push_back(n);
}
JxBigNum::JxBigNum(const JxBigNum &n)
: mNums(n.mNums), mbSign(n.mbSign)
{}
void JxBigNum::CutHighZero()
{
    while (mNums.size() > 1 && mNums.back() == 0)
    {
        mNums.pop_back();
    }
}
JxBigNum & JxBigNum::AddOrSub(const JxBigNum &num, bool bAdd)
{
    unsigned int tmp;
    int bOverflow = 0;
    NumberList::iterator iOri;
    NumberList::const_iterator iNum;
    iOri = mNums.begin();
    iNum = num.mNums.begin();
    for (;iOri != mNums.end() && iNum != num.mNums.end();++iOri, ++iNum)
    {
        if(bAdd)
        {
            (*iOri) += (*iNum) + bOverflow;
            bOverflow = ((*iOri) < (*iNum)) ? 1 : 0;
        }
        else
        {
            tmp = (*iOri);
            (*iOri) -= (*iNum) + bOverflow;
            bOverflow = ((*iOri) > tmp) ? 1 : 0;
        }
    }
    if(iOri == mNums.end() && iNum == num.mNums.end())
    {
    }
    else if (iOri == mNums.end())
    {
        for (; iNum != num.mNums.end();++iNum)
        {
            if(bAdd)
            {
                tmp = (*iNum) + bOverflow;
                bOverflow = (tmp < (*iNum)) ? 1 : 0;
                mNums.push_back(tmp);
            }
            else
            {

            }
        }
    }
    else if(iNum == num.mNums.end())
    {
        for (;bOverflow && iOri != mNums.end(); ++iOri)
        {
            if(bAdd)
            {
                (*iOri) += bOverflow;
                bOverflow = ((*iOri) < 1) ? 1 : 0;
            }
            else
            {
                if((*iOri) >= 1)
                {
                    bOverflow = 0;
                }
                (*iOri) -= 1;
            }
        }
    }
    if(bOverflow)
    {
        if (bAdd)
            mNums.push_back(1);
        else
        {
            mbSign = true;
            for (iOri = mNums.begin(); mNums.end() != iOri; ++iOri)
            {
                (*iOri) = ~(*iOri);
            }
            *mNums.begin() += 1;
        }
    }
    CutHighZero();
    return *this;
}

JxBigNum JxBigNum::Pow(const JxBigNum &nTimes) const
{
    JxBigNum result(1);
    JxBigNum tmpTimes = nTimes;
    JxBigNum tmpPower = *this;
    while (tmpTimes > 0)
    {
        if (tmpTimes % 2 == 1) {
            result *= tmpPower;
        }
        tmpTimes /= 2;
        tmpPower *= tmpPower;
    }
    return result;
}

int JxBigNum::Compare (const JxBigNum &num) const
{
    if (mNums.size() > num.mNums.size()) {
        return 1;
    }
    else if (mNums.size() < num.mNums.size())
    {
        return -1;
    }
    int res = 0;
    NumberList::const_reverse_iterator riMe, riNum;
    riMe = mNums.rbegin();
    riNum = num.mNums.rbegin();
    for (; riMe != mNums.rend(); ++riMe, ++riNum)
    {
        if((*riMe) > (*riNum))
        {
            res = 1;
        }
        else if((*riMe) < (*riNum))
        {
            res = -1;
        }
        if(res)
        {
            break;
        }
    }
    return res;
}

bool JxBigNum::operator == (const JxBigNum &num) const
{
    return Compare(num) == 0;
}
bool JxBigNum::operator != (const JxBigNum &num) const
{
    return Compare(num) != 0;
}
bool JxBigNum::operator >= (const JxBigNum &num) const
{
    return Compare(num) >= 0;
}
bool JxBigNum::operator <= (const JxBigNum &num) const
{
    return Compare(num) <= 0;
}
bool JxBigNum::operator > (const JxBigNum &num) const
{
    return Compare(num) > 0;
}
bool JxBigNum::operator < (const JxBigNum &num) const
{
    return Compare(num) < 0;
}
bool JxBigNum::operator ! () const
{
    return Compare(0) != 0;
}

JxBigNum JxBigNum::operator - () const
{
    return 0 - (*this);
}


JxBigNum & JxBigNum::operator = (const JxBigNum &num)
{
    mbSign = num.mbSign;
    mNums = num.mNums;
    return *this;
}

JxBigNum & JxBigNum::operator += (const JxBigNum &num)
{
    AddOrSub(num, true);
    return *this;
}

JxBigNum & JxBigNum::operator -= (const JxBigNum &num)
{
    AddOrSub(num, false);
    return *this;
}

JxBigNum & JxBigNum::operator *= (const JxBigNum &num)
{
    (*this) = (*this) * num;
    return *this;
}

JxBigNum & JxBigNum::operator /= (const JxBigNum &num)
{
    (*this) = (*this) / num;
    return *this;
}

JxBigNum & JxBigNum::operator %= (const JxBigNum &num)
{
    (*this) = (*this) % num;
    return *this;
}

JxBigNum & JxBigNum::operator >>= (unsigned int nShiftCount)
{
    (*this) = (*this) >> nShiftCount;
    return *this;
}

JxBigNum & JxBigNum::operator <<= (unsigned int nShiftCount)
{
    (*this) = (*this) << nShiftCount;
    return *this;
}

std::string JxBigNum::ToString() const
{
    std::stringstream ss;
    ss << *this;
    return ss.str();
}

JxBigNum JxBigNum::GetBigNum(unsigned int n)
{
    JxBigNum tmp(n);
    return tmp;
}

JxBigNum JxBigNum::MultiUI(unsigned int n1, unsigned int n2)
{
    unsigned int s11, s12, s21, s22;
    s11 = n1 & 0xFFFF;
    s12 = (n1 & 0xFFFF0000) >> 16;
    s21 = n2 & 0xFFFF;
    s22 = (n2 & 0xFFFF0000) >> 16;

    unsigned int m11 = s11 * s21;
    unsigned int m12 = s11 * s22;
    unsigned int m21 = s12 * s21;
    unsigned int m22 = s12 * s22;
    JxBigNum low = JxBigNum(m11) + JxBigNum( (m12 & 0xFFFF) << 16 ) + JxBigNum( (m21 & 0xFFFF) << 16 );
    JxBigNum high ( (m12 & 0xFFFF0000) >> 16 );
    high += JxBigNum( (m21 & 0xFFFF0000) >> 16 );
    high += JxBigNum(m22);
    high.mNums.push_front(0);
    return low + high;
}

JxBigNum operator >> (const JxBigNum &num, unsigned int nShiftCount)
{
    JxBigNum res;
    int nCutCount = nShiftCount / 32;
    nShiftCount %= 32;
    JxBigNum::NumberList::const_iterator iterNum;
    iterNum = num.mNums.begin();
    for (int i = 0; i < nCutCount && iterNum != num.mNums.end(); i++)
    {
        ++iterNum;
    }
    if(iterNum != num.mNums.end())
    {
        unsigned int tmp = 0;
        res.mNums.clear();
        for (; iterNum != num.mNums.end();++iterNum)
        {
            tmp = (*iterNum);
            if(!res.mNums.empty())
            {
                res.mNums.back() |= tmp << (32 - nShiftCount);
            }
            res.mNums.push_back(tmp >> nShiftCount);
        }
    }
    res.CutHighZero();
    return res;
}

JxBigNum operator << (const JxBigNum &num, unsigned int nShiftCount)
{
    JxBigNum res;
    int nCutCount = nShiftCount / 32;
    nShiftCount %= 32;
    JxBigNum::NumberList::const_iterator iterNum;
    iterNum = num.mNums.begin();
    res.mNums.clear();
    for (int i = 0; i < nCutCount; i++)
    {
        res.mNums.push_back(0);
    }
    if(iterNum != num.mNums.end())
    {
        unsigned int tmp = 0;
        for (; iterNum != num.mNums.end();++iterNum)
        {
            if (nShiftCount)
            {
                res.mNums.push_back(tmp >> (32 - nShiftCount));
                tmp = (*iterNum);
                res.mNums.back() |= tmp << nShiftCount;
            }
            else
            {
                res.mNums.push_back(*iterNum);
            }
        }
        unsigned int aaa = tmp >> (32 - nShiftCount);
        if (nShiftCount && aaa)
        {
            res.mNums.push_back(tmp >> (32 - nShiftCount));
        }
    }
    res.CutHighZero();
    return res;
}

JxBigNum operator + (const JxBigNum &num1, const JxBigNum &num2)
{
    JxBigNum tmp(num1);
    return tmp.AddOrSub(num2, true);
}

JxBigNum operator - (const JxBigNum &num1, const JxBigNum &num2)
{
    JxBigNum tmp(num1);
    return tmp.AddOrSub(num2, false);
}

JxBigNum operator * (const JxBigNum &num1, const JxBigNum &num2)
{
    JxBigNum tmp(0), res(0);
    int nOutPos = 0, nInPos = 0, i = 0;
    JxBigNum::NumberList::const_iterator iter1, iter2;
    iter1 = num1.mNums.begin();
    iter2 = num2.mNums.begin();
    nOutPos = 0;
    for (; iter1 != num1.mNums.end(); ++iter1, ++nOutPos)
    {
        nInPos = nOutPos;
        for (iter2 = num2.mNums.begin(); iter2 != num2.mNums.end(); ++iter2, ++nInPos)
        {
            tmp = JxBigNum::MultiUI(*iter1, *iter2);
            for (i = 0; i < nInPos; ++i) {
                tmp.mNums.push_front(0);
            }
            res += tmp;
//            std::cout << "tmp is " << tmp << ", res is " << res << std::endl;
        }
    }
    res.CutHighZero();
    return res;
}

JxBigNum operator / (const JxBigNum &num1, const JxBigNum &num2)
{
    JxBigNum tmp;
    JxBigNum nMin = 1, nMax = num1;
    JxBigNum nShang = 0;
    int nCmpRes = num1.Compare(num2);
    if (nCmpRes <= 0) {
        return (nCmpRes < 0) ? 0 : 1;
    }
    else if (num1 * num2 == num1) {
        return num2;
    }
    else if(num2 == num1)
    {
        return num1;
    }
    // 使用折半查找法来试商
    while (nMin <= nMax)
    {
        nShang = ((nMax - nMin) >> 1) + nMin;
        tmp = num2 * nShang;
//        std::cout << "num1 (" << num1 << "), " << num2 << " * nShang = " << tmp << ", nShange = " << nShang << ", nMin = " << nMin << ", nMax = " << nMax << std::endl;
        if (tmp  == num1) {
            break;
        }
        else if(tmp < num1)
        {
            if (num1 - tmp < num2)
            {
//                std::cout << "num1 - tmp = " << num1 << " - " << tmp << " = " << num1 - tmp << ", num2 = " << num2 << std::endl;
                break;
            }
            nMin = nShang + 1;
        }
        else
        {
            if(tmp - num1 < num2)
            {
                nShang -= 1;
                break;
            }
            nMax = nShang - 1;
        }
    }
    if(nMin > nMax)
    {
        // 不应该出现
        std::cout << "不应该出现在此." << std::endl;
    }
    return nShang;
}

JxBigNum operator % (const JxBigNum &num1, const JxBigNum &num2)
{
    JxBigNum tmp(num1);
    tmp = num1 / num2;
    tmp = num1 - num2 * tmp;
    return tmp;
}

std::ostream & operator << (std::ostream &os, const JxBigNum &num)
{
    JxBigNum::NumberList::const_reverse_iterator riter = num.mNums.rbegin();
    if(num.mbSign)
    {
        os << "-";
    }
    os << "0x";
    bool bCutZero = true;
    char szBuffer[20] = "";
    char *sz = szBuffer;
    for (; riter != num.mNums.rend(); ++riter)
    {
        sz = szBuffer;
        sprintf(sz, "%08x", (*riter));
        while (bCutZero && *sz == '0')
        {
            sz++;
        }
        if (bCutZero && *sz)
        {
            bCutZero = false;
        }
        os << sz;
    }
    if (!(*sz)) {
        os << "0";
    }
    return os;
}

void JxBigNum::InitWithStr(const char *szNum)
{
    mNums.clear();
    mNums.push_front(0);
    if (!szNum || !szNum[0]) {
        return ;
    }
    unsigned int nPos = 0;
    unsigned int nJinZhi = 10;
    if (szNum[nPos] == '-')
    {
        mbSign = true;
        ++nPos;
    }
    if (szNum[nPos] == '+')
    {
        mbSign = false;
        ++nPos;
    }
    if (szNum[nPos] == '0' && (szNum[1 + nPos] == 'x' || szNum[1 + nPos] == 'X'))
    {
        nJinZhi = 16;
        nPos += 2;
    }
    szNum += nPos;
    if (nJinZhi == 16)
    {
        for (;*szNum;++szNum)
        {
            if (*szNum <= 0 || (!isalnum(*szNum))) {
                break;
            }
            (*this) *= nJinZhi;
            if(*szNum >= '0' && *szNum <= '9')
            {
                (*this) += *szNum - '0';
            }
            else if(*szNum >= 'A' && *szNum <= 'F')
            {
                (*this) += *szNum - 'A' + 10;
            }
            else if(*szNum >= 'a' && *szNum <= 'f')
            {
                (*this) += *szNum - 'a' + 10;
            }
        }
    }
    else if(nJinZhi == 10)
    {
        for (;*szNum;++szNum)
        {
            if (*szNum < '0' || *szNum > '9') {
                break;
            }
            (*this) *= nJinZhi;
            (*this) += *szNum - '0';
        }
    }
}