/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int main( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_testStdListSuit_init = false;
#include "/work/ShareForWin/SourceCode/Test/TryAlg/NonDisplayNumber/NonDisplayNumber/testBigNumSuit.h"

static testStdListSuit suite_testStdListSuit;

static CxxTest::List Tests_testStdListSuit = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_testStdListSuit( "testBigNumSuit.h", 35, "testStdListSuit", suite_testStdListSuit, Tests_testStdListSuit );

static class TestDescription_suite_testStdListSuit_testAddition : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_testStdListSuit_testAddition() : CxxTest::RealTestDescription( Tests_testStdListSuit, suiteDescription_testStdListSuit, 38, "testAddition" ) {}
 void runTest() { suite_testStdListSuit.testAddition(); }
} testDescription_suite_testStdListSuit_testAddition;

static class TestDescription_suite_testStdListSuit_testSub : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_testStdListSuit_testSub() : CxxTest::RealTestDescription( Tests_testStdListSuit, suiteDescription_testStdListSuit, 49, "testSub" ) {}
 void runTest() { suite_testStdListSuit.testSub(); }
} testDescription_suite_testStdListSuit_testSub;

static class TestDescription_suite_testStdListSuit_testMul : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_testStdListSuit_testMul() : CxxTest::RealTestDescription( Tests_testStdListSuit, suiteDescription_testStdListSuit, 60, "testMul" ) {}
 void runTest() { suite_testStdListSuit.testMul(); }
} testDescription_suite_testStdListSuit_testMul;

static class TestDescription_suite_testStdListSuit_testDiv : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_testStdListSuit_testDiv() : CxxTest::RealTestDescription( Tests_testStdListSuit, suiteDescription_testStdListSuit, 70, "testDiv" ) {}
 void runTest() { suite_testStdListSuit.testDiv(); }
} testDescription_suite_testStdListSuit_testDiv;

static class TestDescription_suite_testStdListSuit_testMod : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_testStdListSuit_testMod() : CxxTest::RealTestDescription( Tests_testStdListSuit, suiteDescription_testStdListSuit, 73, "testMod" ) {}
 void runTest() { suite_testStdListSuit.testMod(); }
} testDescription_suite_testStdListSuit_testMod;

static class TestDescription_suite_testStdListSuit_testMixOp : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_testStdListSuit_testMixOp() : CxxTest::RealTestDescription( Tests_testStdListSuit, suiteDescription_testStdListSuit, 76, "testMixOp" ) {}
 void runTest() { suite_testStdListSuit.testMixOp(); }
} testDescription_suite_testStdListSuit_testMixOp;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
