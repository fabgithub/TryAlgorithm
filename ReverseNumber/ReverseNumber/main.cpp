//
//  main.cpp
//  ReverseNumber
//
//  Created by liyoudi on 20131121.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#include <iostream>

int reverse(int n);
#define TEST_REVERSE(n) std::cout << n << " reverse " << reverse(n) << std::endl;
int main(int argc, const char * argv[])
{

    // insert code here...
    std::cout << "Hello, World!\n";
    TEST_REVERSE(123);
    TEST_REVERSE(-123);
    return 0;
}

