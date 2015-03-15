//
//  TwentyFourGame.cpp
//  TwentyFourGame
//
//  Created by liyoudi on 20131126.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#include "TwentyFourGame.h"
#include <string>
#include <sstream>

double Operation(double a, double b, char op)
{
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a * 1.0 / b;
        default:
            break;
    }
    return 0;
}
double Operation(double a, double b, double c, char op1, char op2, int order)
{
    switch (order) {
        case 1:
            return Operation(Operation(a, b, op1), c, op2);
        case 2:
            return Operation(a, Operation(b, c, op2), op1);
        default:
            break;
    }
    return 0;
}

#define OP Operation
#define TEST_RESULT(n) (n >= 23.999 && n <= 24.001)

int Operation(double a, double b, double c, double d, char op1, char op2, char op3)
{
    int retVal = 0;
    std::ostream &ss = std::cout;
    if(TEST_RESULT(OP(OP(OP(a, b, op1), c, op2), d, op3))) // 123
    {
        ss << "((" << a << op1 << b << ")" << op2 << c << ")" << op3 << d << std::endl;
        retVal = 1;
        return 1;
    }
    if(TEST_RESULT(OP(a, OP(b, c, op2), d, op1, op3, 1))) // 213
    {
        ss << "(" << a << op1 << "(" << b << op2 << c << "))" << op3 << d << std::endl;
        retVal = 1;
        return 1;
    }
    if(TEST_RESULT(OP(a, OP(b, c, op2), d, op1, op3, 2))) // 231
    {
        ss << "" << a << op1 << "((" << b << op2 << c << ")" << op3 << d << ")" << std::endl;
        retVal = 1;
        return 1;
    }
    if(TEST_RESULT(OP(OP(a, b, op1), OP(c, d, op3), op2))) // 132, 312
    {
        ss << "(" << a << op1 << b << ")" << op2 << "(" << c << op3 << d << ")" << std::endl;
        retVal = 1;
        return 1;
    }
    if(TEST_RESULT(OP(a, OP(b, OP(c, d, op3), op2), op1))) // 321
    {
        ss << a << op1 << "(" << b << op2 << "(" << c << op3 << d << "))" << std::endl;
        retVal = 1;
        return 1;
    }
    return retVal;
}

int ZuHe(int a, int b, int c, int d)
{
    int retVal = 0;
    char ops[] = "+-*/";
    int op1 = 0, op2 = 0, op3 = 0;
    for (op1 = 0; ops[op1]; ++op1)
    {
        for (op2 = 0; ops[op2]; ++op2)
        {
            for (op3 = 0; ops[op3]; ++op3)
            {
                if(OP(a, b, c, d, ops[op1], ops[op2], ops[op3]))
                {
                    retVal = 1;
                    return 1;
                }
            }
        }
    }
    return retVal;
}
#define TEST_OK(res) {int nn____ = res;if(nn____) return nn____;}
int Order(int a, int b, int c, int d)
{
    int retVal = 0;
    TEST_OK(ZuHe(a, b, c, d));
    TEST_OK(ZuHe(a, b, d, c));
    TEST_OK(ZuHe(a, c, b, d));
    TEST_OK(ZuHe(a, c, d, b));
    TEST_OK(ZuHe(a, d, b, c));
    TEST_OK(ZuHe(a, d, c, b));
    return retVal;
}
int can24(int a, int b, int c, int d)
{
    int retVal = 0;
    TEST_OK(Order(a, b, c, d));
    TEST_OK(Order(b, c, d, a));
    TEST_OK(Order(c, d, a, b));
    TEST_OK(Order(d, a, b, c));
    return retVal;
}
