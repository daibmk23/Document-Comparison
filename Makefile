##########################
# Title: Hashing
# Author: Daib Malik
# ID: 22201013
# Section : 1
# Homework: 3
# Description : Makefile
###########################

SRCS = HashTable.cpp
HEADERS = HashTable.h
.PHONY: all clean
all: substrings documents lexicographic minimalset
substrings: substrings.cpp $(SRCS) $(HEADERS)
	g++ -o substrings substrings.cpp $(SRCS)
documents: documents.cpp $(SRCS) $(HEADERS)
	g++ -o documents documents.cpp $(SRCS)
lexicographic: lexicographic.cpp $(SRCS) $(HEADERS)
	g++ -o lexicographic lexicographic.cpp $(SRCS)
minimalset: minimalset.cpp $(SRCS) $(HEADERS)
	g++ -o minimalset minimalset.cpp $(SRCS)
clean:
	rm -f substrings documents lexicographic minimalset *.o

