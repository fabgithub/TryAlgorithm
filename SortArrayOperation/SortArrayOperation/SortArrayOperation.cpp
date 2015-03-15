//
//  SortArrayOperation.cpp
//  SortArrayOperation
//
//  Created by liyoudi on 20131122.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#include "SortArrayOperation.h"
#include <iostream>
#include <vector>

int SortOperation(const int *arr,int n)
{
    std::vector<int> a;
    int i = 0;
    for (i = 0; i < n; i++)
    {
        if (arr[i] > n || arr[i] <= 0)
        {
            return -2;
        }
        a.push_back(arr[i]);
    }
    int nCount = 0;
    for (i = 0; i < n; i++)
    {
        while (a[i] != (i+1))
        {
            if(a[i] <= 0 || a[i] > n || nCount > 10 * n)
            {
                return -1;
            }
            int tmp = a[i];
            a[i] = a[tmp - 1];
            a[tmp - 1] = tmp;
            nCount++;
        }
    }
    return nCount;
}
