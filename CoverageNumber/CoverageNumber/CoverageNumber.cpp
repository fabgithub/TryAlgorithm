//
//  CoverageNumber.cpp
//  CoverageNumber
//
//  Created by liyoudi on 20131115.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#include "CoverageNumber.h"
// 1000000000
int CoverageNumber(int a, int b, int x, int y)
{
    if (!(a > 0 && a <= b && x > 0 && x <= y) || y < a)
    {
        return 0;
    }

    int nResult = 0;
    if (y < a)
    {
        return 0;
    }
    if (x < a)
    {
        x = a;
    }
    if (b >= 2 * a - 1) {
        return y - x + 1;
    }
    int nMinFromY = ((b - 1) / (b - a)) * a;
    if (nMinFromY <= x)
    {
        nResult += y - x + 1;
        return nResult;
    }
    if(y >= nMinFromY)
    {
        nResult += y - nMinFromY;
        y = nMinFromY;
    }
    int nDist = b - a;
    int xModA = x % a;
    int xPos = (x) / a;
    int xLastPos = y / a;
//    int begin = (xPos) * a;
    if (xModA <= xPos * nDist) {
        if(y > xPos * b)
            nResult += xPos * (nDist) - xModA + 1;
        else
            nResult += y - x + 1;
    }
    for (++xPos; xPos < xLastPos; ++xPos) {
        nResult += xPos * nDist + 1;
    }
    if(xPos <= xLastPos)
    {
        int yModA = y % a;
        if(yModA > xPos * nDist)
        {
            nResult += xPos * nDist + 1;
        }
        else
        {
            nResult += yModA + 1;
        }
    }
    return nResult;
}
