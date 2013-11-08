//
//  main.cpp
//  NonDisplayNumber
//
//  Created by liyoudi on 20131106.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#include <iostream>
#include "JxBigNum.h"

//1000000007

int nMaxNum = 1000000007;
#define TEST_OP(num1, num2, op) \
    std::cout << JxBigNum(num1) << " " << #op << " " << JxBigNum(num2) << " = " << JxBigNum(num1) op JxBigNum(num2) << std::endl;

int main(int argc, const char * argv[])
{
    JxBigNum num1(0xFFFFFFFFu), num2(0x1);
    TEST_OP(0, 0xFFFFFFFF, +);
    TEST_OP(0, 0, +);
    TEST_OP(num1, num2, +);
    TEST_OP(0, 1, +);
    TEST_OP(1, 0, +);
    TEST_OP(1, 1, +);
    TEST_OP(0, 1, *);
    TEST_OP(1, 0, *);
    TEST_OP(1, 1, *);
    TEST_OP(num1, num2, -);
    TEST_OP(num2, num1, -);
    TEST_OP(num2, num1, *);
    TEST_OP(num1, num2, *);
    std::cout << "1 * 0xFFFFFFFF = " << JxBigNum::MultiUI(1, 0xFFFFFFFF) << std::endl;
    std::cout << "2 * 0xFFFFFFFF = " << JxBigNum::MultiUI(2, 0xFFFFFFFF) << std::endl;
    std::cout << "3 * 0xFFFFFFFF = " << JxBigNum::MultiUI(3, 0xFFFFFFFF) << std::endl;
    return 0;
}

