LEX         = flex
YACC        = bison
CC = cc
APARSER=aparser
VPATH=../../src/aparser

test1: test-aparser
	./run-test.sh data/test1 asg


test-aparser: ${APARSER}.c ${APARSER}.tab.c ../../src/utils/misc.c
	${CC} -o $@ test-aparser.c $^ -I${VPATH} -I../../src/utils -I../../src/data -std=gnu99 

${APARSER}.c: ${APARSER}.l ${APARSER}.tab.h
	${LEX} -o${APARSER}.c $<

${APARSER}.tab.h: ${APARSER}.y
	${YACC} -d $^

clean: clean-aparser

clean-aparser:
	rm -f *~ *.o 
	rm -f ${APARSER}.tab.h
	rm -f ${APARSER}.tab.c
	rm -f ${APARSER}.c
	rm -f test-aparser

