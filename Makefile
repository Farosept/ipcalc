all: makedir ipclc
main.o:
	gcc -c $(CURDIR)/src/main.c
	mv main.o $(CURDIR)/build/main.o
ipclc.o:
	gcc -c $(CURDIR)/src/ipclc.c
	mv ipclc.o $(CURDIR)/build/ipclc.o
ipclc: main.o ipclc.o
	gcc -o ipclc $(CURDIR)/build/main.o $(CURDIR)/build/ipclc.o
	mv ipclc $(CURDIR)/bin/ipclc
makedir:
	mkdir -p $(CURDIR)/build
	mkdir -p $(CURDIR)/bin
	mkdir -p $(CURDIR)/build/test

tests.o:
	gcc -I src -c $(CURDIR)/test/tests.c -o $(CURDIR)/build/test/tests.o
maintest.o:
	gcc -I src -c $(CURDIR)/test/maintest.c -o $(CURDIR)/build/test/maintest.o
test: makedir tests.o maintest.o ipclc.o
	gcc $(CURDIR)/build/test/main.o $(CURDIR)/build/test/tests.o $(CURDIR)/build/ipclc.o -o $(CURDIR)/build/test/test