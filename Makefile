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