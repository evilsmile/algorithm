CXXFLAGS=-g -Wall
LDFLAGS=

DEPENDS_H=$(shell ls *.h)
SRC_CPPS=$(shell ls *.cpp)
OBJS=$(patsubst %.cpp,%.o,${SRC_CPPS})

BIN=skip_list_test

all:${BIN}


${BIN}:${OBJS} ${DEPENDS_H}
	g++  ${CXXFLAGS} -o $@ $^ ${LDFLAGS}


clean:
	rm -f ${OBJS} ${BIN}
