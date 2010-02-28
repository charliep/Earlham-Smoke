GPPFLAGS=-ggdb -Wall -pedantic

all: Smoke

Smoke: code/Smoke.cpp
	g++ ${GPPFLAGS} code/Smoke.cpp -o Smoke

clean:
	rm -rf Smoke 
	find . -name *.o -delete 
