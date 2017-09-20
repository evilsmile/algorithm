CXXFLAGS=-g -Wall
SRC=$(shell ls *cpp)
OBJS=$(patsubst %.cpp,%.o,${SRC})
CC=g++

all: test

test:${OBJS}
