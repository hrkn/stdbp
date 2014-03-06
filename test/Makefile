GTEST_DIR = ./gtest
PWD = $(shell pwd)

UNIT_TESTERS = threadTest utilityTest algorithmTest
UNIT_TESTER_OBJECTS = $(addsuffix .o, $(UNIT_TESTERS))
UNIT_TEST_COVERAGE_DATA = $(addsuffix .gcda, $(UNIT_TESTERS)) $(addsuffix .gcno, $(UNIT_TESTERS)) 
COVERAGE_INFO = coverage.info
COVERAGE_REPORT_DIR = lcov_report

GTEST_INCLUDES = -I$(GTEST_DIR)/include
GTEST_BUILD_INCLUDES = $(GTEST_INCLUDES) -I$(GTEST_DIR)

CXXFLAGS = -g3 -O0 -Wall -std=c++98 $(GTEST_INCLUDES) -I$(PWD)/../include -pthread -coverage
LIBS = 
LDFLAGS = $(addprefix -l,$(LIBS)) -pthread -coverage

all: gtest-all.o runner.o $(UNIT_TESTERS)

clean:
	rm -f *.gcda *.gcno *.o $(COVERAGE_INFO)
	rm -rf $(COVERAGE_REPORT_DIR)
	rm -f $(UNIT_TESTERS)
	rm -f sources.mk

analyse-coverage: $(UNIT_TEST_COVERAGE_DATA)
	lcov -c -d . -o $(COVERAGE_INFO)
	lcov -r $(COVERAGE_INFO) '/usr/include/*' -o $(COVERAGE_INFO)
	lcov -r $(COVERAGE_INFO) 'third_party/gtest/*' -o $(COVERAGE_INFO)
	genhtml --frames --num-spaces 4 --legend -o $(COVERAGE_REPORT_DIR) $(COVERAGE_INFO)

runner.o: runner.cpp
	g++ -g $(GTEST_INCLUDES) -c $<

gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc
	g++ $(GTEST_BUILD_INCLUDES) -c $<

$(UNIT_TESTERS): runner.o gtest-all.o
	make $@.o
	g++ -o $@ $@.o $^ $(LDFLAGS)

%.o: %.cpp
	g++ $(CXXFLAGS) -c $<


	