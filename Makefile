all: 8chan-boardfind 

8chan-boardfind: main.cpp
	g++ main.cpp -lcurl -o 8chan-boardfind

clean:
	rm -rf 8chan-boardfind 
