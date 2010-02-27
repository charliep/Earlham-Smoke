GPPFLAGS=-ggdb -Wall -pedantic

all: smoke

smoke: code/Smoke.cpp
	g++ ${GPPFLAGS} code/Smoke.cpp -o Smoke

clean:
	find . -name *.o -delete 
	rm Smoke
