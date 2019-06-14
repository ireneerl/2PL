T2 = s2pl

CC = g++
CFLAGS = -c -Wall -g -O0 -std=c++0x -Wunused-variable
#LDFLAGS = -lpthread
LDFLAGS = -pthread

O2 = s2pl.o lib.o

#
# Rules for make
#
all: $(T2) 

$(T2): $(O2) 
	$(CC) -o $@ $^ $(LDFLAGS)

.cc.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f *~ *.o *.exe *.stackdump $(T2)
