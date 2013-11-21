//
//  ReverseNumber.cpp
//  ReverseNumber
//
//  Created by liyoudi on 20131121.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#include "ReverseNumber.h"


int reverse(int n)
{
    bool bLessZero = false;
    if (n < 0) {
        n = -n;
        bLessZero = true;
    }
    int nRes = 0;
    while (n > 0)
    {
        nRes *= 10;
        nRes += n % 10;
        n /= 10;
    }
    if (bLessZero) {
        nRes = -nRes;
    }
    return nRes;
}
