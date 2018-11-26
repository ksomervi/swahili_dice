
CXXFLAGS =-std=c++11 -Wall -g
CXX = c++
COMPILE = $(CXX) ${CXXFLAGS}

TARGET = swahili
SRC = main.cpp dice.cpp turn.cpp
OBJ = $(subst .cpp,.o,${SRC})

default: all

all: ${TARGET}

${TARGET}: ${OBJ}
	$(COMPILE) $^ -o $@

neat:
	-rm -f *~ *.o

clean: neat
	-rm -f ${TARGET}
