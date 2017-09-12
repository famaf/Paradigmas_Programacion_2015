LEX         = flex
YACC        = bison

CC = cc
FPARSER=fparser
APARSER=aparser

prop-eval: ${FPARSER}.c ${APARSER}.c
	${CC} -o$@ prop-eval.c ${FPARSER}.c ${FPARSER}.tab.c ${APARSER}.c ${APARSER}.tab.c eval/evaluator.c utils/misc.c -Iutils -Idata -Ifparser -Iaparser -Ieval -std=gnu99 

${FPARSER}.c: fparser/${FPARSER}.l ${FPARSER}.tab.h
	${LEX} -o${FPARSER}.c fparser/${FPARSER}.l

${FPARSER}.tab.h: fparser/${FPARSER}.y
	${YACC} -d fparser/${FPARSER}.y


${APARSER}.c: aparser/${APARSER}.l ${APARSER}.tab.h
	${LEX} -o${APARSER}.c aparser/${APARSER}.l

${APARSER}.tab.h: aparser/${APARSER}.y
	${YACC} -d aparser/${APARSER}.y

clean: clean-fparser clean-aparser

clean-fparser:
	rm -f *~ *.o 
	rm -f ${FPARSER}.tab.h
	rm -f ${FPARSER}.tab.c
	rm -f ${FPARSER}.c
	rm -f fparser/${FPARSER}.c

clean-aparser:
	rm -f *~ *.o 
	rm -f ${APARSER}.tab.h
	rm -f ${APARSER}.tab.c
	rm -f ${APARSER}.c
	rm -f aparser/${APARSER}.c
