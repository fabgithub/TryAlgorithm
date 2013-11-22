//
//  SmallestOperation.cpp
//  SmallestOperation
//
//  Created by liyoudi on 20131115.
//  Copyright (c) 2013年 liyoudi. All rights reserved.
//

#include "SmallestOperation.h"

#include <set>
#include <map>
#include <list>
#include <vector>
#include <string>

typedef std::list<const char *> RoadPath;
class RoadPathLess
{
public:
    bool operator () (const RoadPath &r1, const RoadPath &r2) const
    {
        if (r1.size() < r2.size())
            return true;
        if(r1.size() > r2.size())
            return false;
        return r1 < r2;
    }
};

typedef std::set<RoadPath, RoadPathLess> RoadSet;
typedef std::vector<const char *> WordVector;
typedef std::set<const char *> WordSet;
typedef std::map<const char *, WordSet> ChangeWordSet;

void GenerateGraph(const WordVector &wdVector, ChangeWordSet &cws)
{
    size_t i = 0, j = 0;
    int nDiffCount = 0;
    const char *szFirst = NULL;
    const char *szSecond = NULL;
    for (i = 0; i < wdVector.size(); i++)
    {
        for (j = i + 1; j < wdVector.size(); ++j)
        {
            szFirst = wdVector[i];
            szSecond = wdVector[j];
            nDiffCount = 0;
            for (;nDiffCount <= 1 && *szFirst && *szSecond; ++szFirst, ++szSecond)
            {
                if (*szFirst != *szSecond)
                {
                    ++nDiffCount;
                }
            }
            if (nDiffCount == 1 && !(*szFirst) && !(*szSecond))
            {
                cws[wdVector[i]].insert(wdVector[j]);
                cws[wdVector[j]].insert(wdVector[i]);
            }
        }
    }
}

std::ostream & operator << (std::ostream &os, ChangeWordSet &cws)
{

    ChangeWordSet::const_iterator citerCWS;
    WordSet::const_iterator citerWS;
    for (citerCWS = cws.begin(); citerCWS != cws.end(); ++citerCWS)
    {
        os << citerCWS->first << " ->" << std::endl << "\t";
        for (citerWS = citerCWS->second.begin(); citerWS != citerCWS->second.end(); ++citerWS)
        {
            os << (*citerWS) << ", ";
        }
        os << std::endl;
    }
    return os;
}

std::ostream & operator << (std::ostream &os, const RoadSet &rdSet)
{
    RoadSet::const_iterator iterSet = rdSet.begin();
    for (;iterSet != rdSet.end() ; ++iterSet)
    {
        RoadPath::const_iterator iterPath = iterSet->begin();
        for (; iterPath != iterSet->end();++iterPath)
        {
            os << (*iterPath) << " -> ";
        }
        os << std::endl;
    }
    return os;
}

void innerGetRoadSet(RoadPath &curRoad, WordSet &curWordSet, const char *szTo, const ChangeWordSet &cws, RoadSet &rdSet)
{
    const char *szLastWord = curRoad.back();
    if (szLastWord == szTo)
    {
        rdSet.insert(curRoad);
        return ;
    }
    ChangeWordSet::const_iterator iterFound = cws.find(szLastWord);
    if(iterFound == cws.end())
    {
        std::cout << "不应该到此.";
    }
    else
    {
        WordSet::const_iterator citerWord = iterFound->second.begin();
        for (; citerWord != iterFound->second.end(); ++citerWord)
        {
            if (curWordSet.find((*citerWord)) == curWordSet.end())
            {
                WordSet tmpWordSet = curWordSet;
                RoadPath tmpRoad = curRoad;
                tmpWordSet.insert(*citerWord);
                tmpRoad.push_back(*citerWord);
                innerGetRoadSet(tmpRoad, tmpWordSet, szTo, cws, rdSet);
            }
        }
    }
}
void GetRoadSet(const char *szFrom, const char *szTo, const ChangeWordSet &cws, RoadSet &rdSet)
{
    rdSet.clear();
    if (strcmp(szFrom, szTo) == 0)
    {
        return ;
    }
    std::list<const char *> searchStack;
    RoadPath curPath;
    WordSet  curWordSet;
    curPath.push_back(szFrom);
    innerGetRoadSet(curPath, curWordSet, szTo, cws, rdSet);
}

void GetDictVector(const char *szDic[], int nDicCount, const char *szFrom, const char *szTo, WordVector &dictVector)
{
    WordSet wdSet;
    wdSet.insert(szFrom);
    wdSet.insert(szTo);
    for (int i = 0; i < nDicCount; ++i)
    {
        wdSet.insert(szDic[i]);
    }
    dictVector.clear();
    WordSet::iterator iter = wdSet.begin();
    for (; wdSet.end() != iter; ++iter)
    {
        dictVector.push_back(*iter);
    }
}

int SmallestOperation(const char *szDic[], int nDicCount, const char *szFrom, const char *szTo)
{
    WordVector wdVector;
    GetDictVector(szDic, nDicCount, szFrom, szTo, wdVector);
    ChangeWordSet cws;
    GenerateGraph(wdVector, cws);
    std::cout << std::endl;
    std::cout << cws << std::endl;

    RoadSet rdSet;
    GetRoadSet(szFrom, szTo, cws, rdSet);
    std::cout << rdSet << std::endl;
    return 0;
}

using namespace std;

vector<vector<string>> findLadders(string start, string end, set<string>& dict)
{
    set<string> tmpDict = dict;
    WordVector wdVector;
    tmpDict.insert(start);
    tmpDict.insert(end);
    set<string>::iterator iterWord = tmpDict.begin();
    for (; iterWord != tmpDict.end(); ++iterWord)
    {
        wdVector.push_back(iterWord->c_str());
    }
    const char *szFrom = tmpDict.find(start)->c_str();
    const char *szTo = tmpDict.find(end)->c_str();
    ChangeWordSet cws;
    GenerateGraph(wdVector, cws);
//    std::cout << std::endl;
//    std::cout << cws << std::endl;

    RoadSet rdSet;
    GetRoadSet(szFrom, szTo, cws, rdSet);
//    std::cout << rdSet << std::endl;
    //
    vector<vector<string> >retPathVec;
    RoadSet::iterator iterRD = rdSet.begin();
    size_t nMinSize = 0;
    for (; iterRD != rdSet.end(); ++iterRD)
    {
        if (nMinSize > 0 && nMinSize < iterRD->size()) {
            break;
        }
        nMinSize = iterRD->size();
        vector<string> path;
        RoadPath::const_iterator iterPath = iterRD->begin();
        for (; iterPath != iterRD->end(); ++iterPath)
        {
            path.push_back(*iterPath);
        }
        retPathVec.push_back(path);
    }
    return retPathVec;
}
