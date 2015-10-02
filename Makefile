COMPILER = gcc
CCFLAGS  = -Wall -ansi
all: tokenizer

tokenizer: tokenizer.o
	$(COMPILER) $(CCFLAGS) -o tokenizer tokenizer.o
tokenizer.o: tokenizer.c
	$(COMPILER) $(CCFLAGS) -c tokenizer.c 
clean:
	rm -f tokenizer tokenizer.o