GPPFLAGS=-ggdb -Wall -pedantic -msse2 -Wno-long-long

all: Smoke

Smoke: code/Smoke.cpp
	g++ ${GPPFLAGS} code/Smoke.cpp -o Smoke

clean:
	rm -rf Smoke 
	find . -name *.o -delete 
