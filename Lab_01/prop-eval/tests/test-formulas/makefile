LEX         = flex
YACC        = bison
CC = cc
FPARSER=fparser
VPATH=../../src/fparser

test1: test-fparser
	./run-test.sh data/test1 frm

test2: test-fparser
	./run-test.sh data/test2 frm

test-fparser: ${FPARSER}.c ${FPARSER}.tab.c ../../src/utils/misc.c
	${CC} -o $@ test-fparser.c $^ -I${VPATH} -I../../src/utils -I../../src/data -std=gnu99 

${FPARSER}.c: ${FPARSER}.l ${FPARSER}.tab.h
	${LEX} -o${FPARSER}.c $<

${FPARSER}.tab.h: ${FPARSER}.y
	${YACC} -d $^

clean: clean-fparser

clean-fparser:
	rm -f *~ *.o 
	rm -f ${FPARSER}.tab.h
	rm -f ${FPARSER}.tab.c
	rm -f ${FPARSER}.c
	rm -f test-fparser

