//
//  ReverseMapString.cpp
//  ReverseMapString
//
//  Created by liyoudi on 20140723.
//  Copyright (c) 2014年 liyoudi. All rights reserved.
//

#include "ReverseMapString.h"


/***
 题目详情:
 这是个字符串问题。我们的字符串只包含大写字母。我们定义一个字母和它13位以后的字母互补。即A与N互补，B与O互补，C与P互补……，我们需要找一个字符串的两个不重叠的子串，其中一个和另外一个的翻转全互补。另外，因为我们的问题来自生物学，所以我们允许这两个字符串的一个可以删掉两个字符（注意：仅允许一个字符串删掉任意位置的两个字符，另外一个必须全部互补上）。我们的目的是求最长的反向互补子串的长度。
 输入格式：
 多组数据，每组数据一行，有一个字符串。每个字符串长度不超过2000，只有大写英文字母组成。
 输出格式：
 每组数据输出一行包含一个整数，表示最长的反向互补子串长度。
 答题说明:

 输入样例
 ABCD
 ABCDQOPN
 ABON
 输出样例：
 0
 2
 2
 解释：
 第一个样例，没有互补的子串。
 第二个样例，AB和NO互补，所以反向互补子串的时候我们可以选择NPO，删掉一个P即可。
 第三个样例，AB与ON反向互补。
  */

int ReverseMapString(const std::string &strInput)
{
    return 0;
}