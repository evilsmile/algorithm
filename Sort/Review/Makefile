SRCS=$(shell ls *cpp)
HEADERS=$(shell ls *h)
OBJS=$(patsubst cpp,o,${SRCS})
BIN=algorithm_review

all:${BIN}


${BIN}:${OBJS} ${HEADERS}
	g++ -g -o algorithm_review ${OBJS}

sort:
	./algorithm_review

clean:
	rm -f *.o ${BIN}
