CXX = g++

AR = ar

CXXFLAGS = -O2 -g -Wall -fmessage-length=0 -std=c++14

SRCS = $(shell find src/ -type f -name *.cc)

OBJS = $(SRCS:.cc=.o)

LIBS = 

LDFLAGS =

LDLIBS =

TARGET = elephly

TEST_FLAGS = -O2 -g -Wall -fmessage-length=0 -std=c++14 -Isrc

TEST_SRCS = $(shell find tests/ -type f -name *.test.cc)

TEST_OBJS = $(filter-out src/$(TARGET).o, $(OBJS))

TEST_LIBS =

TESTS = $(TEST_SRCS:.test.cc=.test)

CHECKS = $(TESTS:.test=.check)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(LDFLAGS) $(LDLIBS) $(OBJS) $(LIBS)

test: $(TESTS)

%.test: %.cc $(TEST_OBJS)
	    $(CXX) -o $@ $(TEST_FLAGS) $(LDFLAGS) $(LDLIBS) $^ $(LIBS)

%.check: %.test
	    $<

check: $(CHECKS)

clean:
	rm -f $(OBJS) $(TARGET)
	rm -f $(TESTS)

.PHONY: clean all test check

