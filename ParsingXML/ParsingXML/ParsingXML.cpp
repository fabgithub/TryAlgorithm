//
//  ParsingXML.cpp
//  ParsingXML
//
//  Created by liyoudi on 20131127.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#include "ParsingXML.h"

void StepSpaces(const std::string &inXml, int &nPos)
{
    for (; nPos < inXml.length(); ++nPos)
    {
        char ch = inXml.at(nPos);
        if (!(ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n'))
        {
            break;
        }
    }
}

int StepToChar(const std::string &inXml, int &nPos, char whichCh, std::string &outStr)
{
    outStr = "";
    int res = -1;
    for (; nPos < inXml.length(); ++nPos)
    {
        char ch = inXml.at(nPos);
        if (ch == whichCh)
        {
            return 0;
        }
        outStr += whichCh;
    }
    return res;
}

int StepHead(const std::string &inXml, int &nPos)
{
    int res = 0;
    StepSpaces(inXml, nPos);
    if(inXml.length() - nPos <= 7)
        return -1;
    std::string strValue;
    if(StepToChar(inXml, nPos, ' ', strValue))
        return -2;
    if(strValue != "<?xml")
        return -3;
    StepSpaces(inXml, nPos);
    if(StepToChar(inXml, nPos, '=', strValue))
        return -4;
    if (strValue != "version")
        return -5;

    StepSpaces(inXml, nPos);
    return res;
}

std::string ParsingXML(const std::string &inXml)
{
    return "";
}
