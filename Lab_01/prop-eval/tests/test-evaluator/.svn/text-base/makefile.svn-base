LEX         = flex
YACC        = bison
CC = cc
APARSER=aparser
FPARSER=fparser

VPATH=../../src/fparser:../../src/aparser:../../src/eval:../../src/utils

test: test-eval	
	./run-test.sh ../test-evaluator/data/test1


test-eval: ${FPARSER}.c ${FPARSER}.tab.c ${APARSER}.c ${APARSER}.tab.c evaluator.c misc.c 
	${CC} -o$@ ../../src/prop-eval.c $^ -I../../src/utils -I../../src/data -I../../src/eval -I../../src/fparser -I../../src/aparser  -std=gnu99

${APARSER}.c: ${APARSER}.l ${APARSER}.tab.h
	${LEX} -o${APARSER}.c $<

${APARSER}.tab.h: ${APARSER}.y
	${YACC} -d $^

${FPARSER}.c: ${FPARSER}.l ${FPARSER}.tab.h
	${LEX} -o${FPARSER}.c $<

${FPARSER}.tab.h: ${FPARSER}.y
	${YACC} -d $^

clean: clean-aparser clean-fparser
	rm -f test-eval

clean-aparser:
	rm -f *~ *.o 
	rm -f ${APARSER}.tab.h
	rm -f ${APARSER}.tab.c
	rm -f ${APARSER}.c
	rm -f test-aparser

clean-fparser:
	rm -f *~ *.o 
	rm -f ${FPARSER}.tab.h
	rm -f ${FPARSER}.tab.c
	rm -f ${FPARSER}.c
	rm -f test-fparser
