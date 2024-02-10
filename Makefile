CXX=g++
CXXFLAGS=-O2 -g0 -std=c++20

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

PIOBJ=piobj
PISRC=pisrc
PISRCS=$(wildcard $(PISRC)/*.cpp)
PIOBJS=$(patsubst $(PISRC)/%.cpp, $(PIOBJ)/%.o, $(PISRCS))

all: $(LIB) $(BUILD)/main

$(BUILD)/main: $(OBJ) $(OBJS) $(BUILD)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(BUILD)/main -L./$(LIBDIR)/ -lBigNumLibrary

$(LIB): $(LIBDIR) $(LIBOBJDIR) $(LIBOBJS) $(LIBSRCS)
	@ar -cvrs $(LIB) $(LIBOBJS)

$(LIBOBJDIR)/%.o: $(LIBSRCDIR)/%.cpp $(LIBSRCDIR)/%.h
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# $(OBJ)/%.o: $(SRC)/%.cpp $(SRC)/%.h
# 	$(CXX) $(CXXFLAGS) -c $< -o $@ -I./$(LIBSRCDIR)/

$(OBJ)/%.o: $(SRC)/%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -I./$(LIBSRCDIR)/

$(TEST)/bin/%: $(TEST)/%.cpp $(PIOBJ) $(PIOBJS)
	$(CXX) $(CXXFLAGS) $< -I./$(LIBSRCDIR)/ -I./$(PISRC)/ -o $@ $(PIOBJS) -L./$(LIBDIR)/ -lBigNumLibrary

$(PIOBJ)/%.o: $(PISRC)/%.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@ -I./$(LIBSRCDIR)/

$(OBJ):
	@mkdir $@

$(LIBDIR):
	@mkdir $@

$(LIBOBJDIR):
	@mkdir $@

$(BUILD):
	@mkdir $@

$(TEST)/bin:
	@mkdir $@

$(PI):
	@mkdir $@

$(PIOBJ):
	@mkdir $@

test: $(LIB) $(TEST)/bin $(TESTBINS)
	for test in $(TESTBINS) ; do ./$$test ; done

run: $(BUILD)/main
	@./$(BUILD)/main

clean:
	@rm -rf $(OBJ) $(LIBOBJDIR) $(LIBDIR) $(BUILD) $(TEST)/bin $(PIOBJ)

.PHONY: run clean
