
C_FILES=state_parser.c matcher.c
MAIN=main.c
PROG=sgrep

all: $(PROG)

include rules.mk

clean:
	if [ -d tests ] ; then cd tests && make clean ; fi
	@rm -f *.o $(PROG)

bb: $(PROG)
	echo "Carl-Einar" | ./$(PROG) carl ; if [ $$? -ne 1 ] ; then exit 1 ; fi
	echo "Carl-Einar" | ./$(PROG) Carl ; if [ $$? -ne 0 ] ; then exit 1 ; fi
	export CNT=$$(printf "Apa\nbepa\nApa\nbepa\n" | ./$(PROG) Apa | wc -l) ; if [ $$CNT -ne 2 ] ; then exit 1 ; fi
	export CNT=$$(printf "Apa\nbepa\nApa\nbepaApa\nbepa\nApa\nBepa\n" | ./$(PROG) Bepa | wc -l) ; if [ $$CNT -ne 1 ] ; then exit 1 ; fi
	cat Makefile | ./$(PROG) OBJS  >/dev/null;  if [ $$? -ne 0 ] ; then exit 1 ; fi
	cat sgrep.h | ./$(PROG) OBJSSLS >/dev/null; if [ $$? -ne 1 ] ; then exit 1 ; fi
	echo "" | ./$(PROG) "" >/dev/null; if [ $$? -ne 0 ] ; then exit 1 ; fi
	echo -n "" | ./$(PROG) "" >/dev/null; if [ $$? -ne 1 ] ; then exit 1 ; fi
	seq 1 100002 | awk ' { printf "%s " , $$0 }' | ./$(PROG) 777 >/dev/null;  if [ $$? -ne 0 ] ; then exit 1 ; fi
	seq 1 100002 | awk ' { printf "%s " , $$0 }' | ./$(PROG) 777ss; if [ $$? -ne 1 ] ; then exit 1 ; fi
	seq 1 1000000 | awk ' { printf "%s " , $$0 }' | ./$(PROG) 777s; if [ $$? -ne 1 ] ; then exit 1 ; fi
#	seq 1 12345678 | awk ' { printf "%s " , $$0 }' | ./$(PROG) 777s; if [ $$? -ne 1 ] ; then exit 1 ; fi
	cat /bin/ls | ./$(PROG) 777s; if [ $$? -ne 1 ] ; then exit 1 ; fi
	@echo ""
	@echo "All tests passed."

bible-extra: $(PROG)
	@echo "sgrep bible run:"
	@echo -n "\tNumber of jesus: "
	@./$(PROG) -i -c "jesus" bible.txt
	@echo -n "\tNumber of god: "
	@./$(PROG) -i -c "god" bible.txt
	@echo "Pulp fiction:"
	@./$(PROG) -i "ezekiel 25:17" bible.txt
	@echo "Finally:"
	./$(PROG) -i -c "logic" bible.txt; if [ $$? -ne 1 ] ; then exit 1 ; fi
	@echo "I rest my case"

check:
	cd tests && make check

valgrind: all
	cat Makefile | valgrind --leak-check=full ./$(PROG) OBJS
