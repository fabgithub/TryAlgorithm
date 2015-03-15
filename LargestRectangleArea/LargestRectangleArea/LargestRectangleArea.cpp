//
//  LargestRectangleArea.cpp
//  LargestRectangleArea
//
//  Created by liyoudi on 20131127.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#include "LargestRectangleArea.h"

#include <vector>
#include <map>

class HeightInfo
{
    
};

int LargestRectangleArea(int *nHightArr, int nCount)
{
    int nMaxArea = nHightArr[0], tmpArea = 0;
    int nMaxHeight = 1;
    int i = 0, j = 0, k = 0;
    if(nCount <= 0)
        return 0;
    for (i = 0; i < nCount; i++)
    {
        k = i + 1;
        for (j = nHightArr[i];j >= nMaxHeight;--j)
        {
            for (; ; k++)
            {
                if (j > nHightArr[k] || k >= nCount)
                {
                    tmpArea = (k - i) * j;
                    if (tmpArea > nMaxArea)
                    {
                        nMaxArea = tmpArea;
                    }
                    break;
                }
            }
        }
        nMaxHeight = nHightArr[i];
    }
    return nMaxArea;
}
