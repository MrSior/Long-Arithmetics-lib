CXX=g++
CXXFLAGS=-g -std=c++20

LIBSRCDIR=libsrc
LIBOBJDIR=libobj
LIBDIR=lib
SRC=src
OBJ=obj
BUILD=build

LIB=$(LIBDIR)/BigNumLibrary.a

SRCS = $(wildcard $(SRC)/*.cpp) 
OBJS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRCS))

LIBSRCS = $(wildcard $(LIBSRCDIR)/*.cpp) 
LIBOBJS = $(patsubst $(LIBSRCDIR)/%.cpp, $(LIBOBJDIR)/%.o, $(LIBSRCS))

all: $(LIB) main

main: $(OBJ) $(OBJS) $(BUILD)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(BUILD)/main


$(LIB): $(LIBDIR) $(LIBOBJDIR) $(LIBOBJS)
# 	rm $(LIB)
	ar -cvrs $(LIB) $(LIBOBJS)

$(LIBOBJDIR)/%.o: $(LIBSRCDIR)/%.cpp $(LIBSRCDIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.cpp $(SRC)/%.h
	$(CXX) $(CXXFLAGS) -llibrary $(LIB) -c $< -o $@

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXXFLAGS) $(LIBOBJS) -c $< -o $@



$(OBJ):
	mkdir $@

$(LIBDIR):
	mkdir $@

$(LIBOBJDIR):
	mkdir $@

$(BUILD):
	mkdir $@

clean:
	rm -r $(OBJ) $(LIBOBJDIR) $(LIBDIR) $(BUILD) 