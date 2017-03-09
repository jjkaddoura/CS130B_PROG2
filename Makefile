CXX=g++ -std=c++11 -O3
#clang++

BINARIES=payoff_sched

all: ${BINARIES}

payoff_sched: payoff_sched.o main.o
	${CXX} $^ -o $@ 

clean:
	/bin/rm -f ${BINARIES} *.o *~
