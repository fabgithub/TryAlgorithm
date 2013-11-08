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

// add in fifth branch.

// add in fifth branch twice.

// add in fifth branch 3 times.

// add feathure in sixth branch.

// add feathure in first branch.

// add feathure in seventh branch.

#include "JxBigNum.h"
#include <sstream>

JxBigNum::JxBigNum():mbSign(false)
{
    mNums.push_front(0);
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
        res = (*riMe) - (*riNum);
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
    return *this;
}

JxBigNum & JxBigNum::operator /= (const JxBigNum &num)
{
    return *this;
}

JxBigNum & JxBigNum::operator %= (const JxBigNum &num)
{
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

JxBigNum operator >> (const JxBigNum &num1, unsigned int nShiftCount)
{
    JxBigNum res;
    return res;
}

JxBigNum operator << (const JxBigNum &num1, unsigned int nShiftCount)
{
    JxBigNum res;
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
        for (; iter2 != num2.mNums.end(); ++iter2, ++nInPos)
        {
            tmp = JxBigNum::MultiUI(*iter1, *iter2);
            for (i = 0; i < nInPos; ++i) {
                tmp.mNums.push_front(0);
            }
            res += tmp;
        }
    }
    res.CutHighZero();
    return res;
}

JxBigNum operator / (const JxBigNum &num1, const JxBigNum &num2)
{
    JxBigNum tmp(num1);
    return tmp.AddOrSub(num2, false);
}

JxBigNum operator % (const JxBigNum &num1, const JxBigNum &num2)
{
    JxBigNum tmp(num1);
    return tmp.AddOrSub(num2, false);
}

std::ostream & operator << (std::ostream &os, const JxBigNum &num)
{
    JxBigNum::NumberList::const_reverse_iterator riter = num.mNums.rbegin();
    if(num.mbSign)
    {
        os << "-";
    }
    os << "0x";
    for (; riter != num.mNums.rend(); ++riter)
    {
        char sz[20] = "";
        sprintf(sz, "%08x", (*riter));
        os << sz;
    }
    return os;
}
