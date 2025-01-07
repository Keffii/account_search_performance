PROG = main.exe 
SRC = src/main.cpp src/bank.cpp src/bankaccount.cpp src/binarysearchstorage.cpp
CFLAGS = -g -std=c++17
LIBS = 
CC=g++

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC)  $(LIBS) 

clean:
	rm -f $(PROG)

.PHONY: all clean