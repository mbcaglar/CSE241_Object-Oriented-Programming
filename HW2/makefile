all: hw2 clean

hw2: main.o
	g++ main.o -o hw2 -std=c++11
main.o:
	g++ -c main.cpp -std=c++11

clean:

	./hw2 hw2.txt 0
	rm *.o hw2
