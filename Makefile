##########################
# Title: Hashing
# Author: Daib Malik
# Description : Makefile
###########################

SRCS = HashTable.cpp
HEADERS = HashTable.h
.PHONY: all clean
all: documents
documents: documents.cpp $(SRCS) $(HEADERS)
	g++ -o documents documents.cpp $(SRCS)
clean:
	rm -f documents *.o

