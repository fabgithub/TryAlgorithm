//
//  JxBigNum.h
//  NonDisplayNumber
//
//  Created by liyoudi on 20131107.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#ifndef __NonDisplayNumber__JxBigNum__
#define __NonDisplayNumber__JxBigNum__

#include <string>
#include <iostream>
#include <list>

class JxBigNum
{
public:
    JxBigNum();
    explicit JxBigNum(const char *szNum);
    explicit JxBigNum(const std::string &strNum);
    JxBigNum(int n);
    JxBigNum(unsigned int n);
    JxBigNum(const JxBigNum &n);
    void InitWithStr(const char *szNum);
    void CutHighZero();
    JxBigNum & AddOrSub(const JxBigNum &num, bool bAdd);

    friend JxBigNum operator >> (const JxBigNum &num1, unsigned int nShiftCount);
    friend JxBigNum operator << (const JxBigNum &num1, unsigned int nShiftCount);

    friend JxBigNum operator + (const JxBigNum &num1, const JxBigNum &num2);
    friend JxBigNum operator - (const JxBigNum &num1, const JxBigNum &num2);
    friend JxBigNum operator * (const JxBigNum &num1, const JxBigNum &num2);
    friend JxBigNum operator / (const JxBigNum &num1, const JxBigNum &num2);
    friend JxBigNum operator % (const JxBigNum &num1, const JxBigNum &num2);

    std::string ToString() const;

    int Compare (const JxBigNum &num) const;
    bool operator == (const JxBigNum &num) const;
    bool operator != (const JxBigNum &num) const;
    bool operator >= (const JxBigNum &num) const;
    bool operator <= (const JxBigNum &num) const;
    bool operator > (const JxBigNum &num) const;
    bool operator < (const JxBigNum &num) const;
    bool operator ! () const;

    JxBigNum operator - () const;

    JxBigNum & operator = (const JxBigNum &num);
    JxBigNum & operator += (const JxBigNum &num);
    JxBigNum & operator -= (const JxBigNum &num);
    JxBigNum & operator *= (const JxBigNum &num);
    JxBigNum & operator /= (const JxBigNum &num);
    JxBigNum & operator %= (const JxBigNum &num);
    JxBigNum & operator >>= (unsigned int nShiftCount);
    JxBigNum & operator <<= (unsigned int nShiftCount);
    static JxBigNum GetBigNum(unsigned int n);

    static JxBigNum MultiUI(unsigned int n1, unsigned int n2);

public:
    typedef std::list<unsigned int> NumberList;
    NumberList mNums;
    bool mbSign;
};

JxBigNum operator >> (const JxBigNum &num1, unsigned int nShiftCount);
JxBigNum operator << (const JxBigNum &num1, unsigned int nShiftCount);

JxBigNum operator + (const JxBigNum &num1, const JxBigNum &num2);
JxBigNum operator - (const JxBigNum &num1, const JxBigNum &num2);
JxBigNum operator * (const JxBigNum &num1, const JxBigNum &num2);
JxBigNum operator / (const JxBigNum &num1, const JxBigNum &num2);
JxBigNum operator % (const JxBigNum &num1, const JxBigNum &num2);
std::ostream & operator << (std::ostream &os, const JxBigNum &num);
#endif /* defined(__NonDisplayNumber__JxBigNum__) */
