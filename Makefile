all: no-leg-borerchan no-leg-parser 

no-leg-parser: parse.o jsmn.o
	g++ parse.o jsmn.o -lcurl -o no-leg-parser

parse.o: parse.cpp
	g++ -c -Ijsmn parse.cpp

jsmn.o: jsmn/jsmn.c
	g++ -c jsmn/jsmn.c

no-leg-borerchan: main.cpp
	g++ main.cpp -lcurl -o no-leg-borerchan

clean:
	rm -rf no-leg-borerchan no-leg-parser *.o
