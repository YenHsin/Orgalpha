CC = g++
CFLAGS = -Wall -Ofast -std=c++17 -g
OBJS = myvec.o 

all: smile2adj smile

smile: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o smiles main.cpp 

smile2adj: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o s2adj smile2adj.cpp  

myvec.o: myvec.cpp myvec.h
	$(CC) $(CFLAGS) -c myvec.cpp
	
clean:
	rm -f *~ *.o smiles

