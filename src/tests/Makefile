C_FILES=../state_parser.c ../matcher.c
MAIN=test.c
PROG=all-tests

all: $(PROG) $(OBJS)

view:
	echo "PROG: $(PROG)"
	echo "OBJS: $(OBJS)"

check: $(PROG) $(OBJS)
	./$(PROG)

clean:
	@-rm -f *.o *~ $(PROG) test/*~ test/*.o

include ../rules.mk
