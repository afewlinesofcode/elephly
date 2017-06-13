CXX = g++

AR = ar

CXXFLAGS = -O2 -g -Wall -fmessage-length=0 -std=c++14

SRCS = $(shell find src/ -type f -name *.cc)

OBJS = $(SRCS:.cc=.o)

LIBS = 

LDFLAGS =

LDLIBS = -lboost_locale

TARGET = elephly

TEST_FLAGS = -O2 -g -Wall -fmessage-length=0 -std=c++14 -Isrc

TEST_SRCS = $(shell find tests/ -type f -name *.test.cc)

TEST_OBJS = $(filter-out src/$(TARGET).o, $(OBJS))

TEST_LDFLAGS =

TEST_LDLIBS = -lboost_unit_test_framework -lboost_locale

TESTS = $(TEST_SRCS:.test.cc=.test)

CHECKS = $(TESTS:.test=.check)

all: build build_test

build: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(LDFLAGS) $(LDLIBS) $(OBJS) $(LIBS)

run:
	./$(TARGET) words.txt dict.txt

build_test: $(TESTS)

%.test: %.test.cc $(TEST_OBJS)
	    $(CXX) -o $@ $(TEST_FLAGS) $(TEST_LDFLAGS) $(TEST_LDLIBS) $^ $(LIBS)

%.check: %.test
	    $<

test: $(CHECKS)

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f $(TESTS)

.PHONY: clean all test check

