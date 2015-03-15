
CXX_TEST_ROOT = /work/ShareForWin/SourceCode/Research/CxxTest/cxxtest-4.3

TEST_SUITE_HEADER_FILES = \
    test_TwentyFourGame.h \

runner : runner.cpp
	#g++ -o runner -I$(CXX_TEST_ROOT) $<
runner.cpp : makefile $(TEST_SUITE_HEADER_FILES)
	cxxtestgen --error-printer -o runner.cpp $(TEST_SUITE_HEADER_FILES)
