CXX=g++
CXXFLAGS=-g -std=c++20

LIBSRCDIR=libsrc
LIBOBJDIR=libobj
LIBDIR=lib
SRC=src
OBJ=obj
BUILD=build

LIB=$(LIBDIR)/libBigNumLibrary.a

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

LIBSRCS = $(wildcard $(LIBSRCDIR)/*.cpp)
LIBOBJS = $(patsubst $(LIBSRCDIR)/%.cpp, $(LIBOBJDIR)/%.o, $(LIBSRCS))

TEST=tests
TESTS=$(wildcard $(TEST)/*.cpp)
TESTBINS=$(patsubst $(TEST)/%.cpp, $(TEST)/bin/%, $(TESTS))

all: $(LIB) $(BUILD)/main

$(BUILD)/main: $(OBJ) $(OBJS) $(BUILD)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BUILD)/main -L./$(LIBDIR)/ -lBigNumLibrary

$(LIB): $(LIBDIR) $(LIBOBJDIR) $(LIBOBJS)
	ar -cvrs $(LIB) $(LIBOBJS)

$(LIBOBJDIR)/%.o: $(LIBSRCDIR)/%.cpp $(LIBSRCDIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.cpp $(SRC)/%.h
	$(CXX) $(CXXFLAGS) -llibrary $(LIB) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -I./$(LIBSRCDIR)/

$(TEST)/bin/%: $(TEST)/%.cpp
	$(CXX) $(CXXFLAGS) $< -I./$(LIBSRCDIR)/ -o $@ -L./$(LIBDIR)/ -lBigNumLibrary

$(OBJ):
	mkdir $@

$(LIBDIR):
	mkdir $@

$(LIBOBJDIR):
	mkdir $@

$(BUILD):
	mkdir $@

$(TEST)/bin:
	mkdir $@

test: $(LIB) $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

run: $(BUILD)/main
	@./$(BUILD)/main

clean:
	@rm -r $(OBJ) $(LIBOBJDIR) $(LIBDIR) $(BUILD) $(TEST)/bin

.PHONY: run clean
