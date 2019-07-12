all: calistir

calistir: _mainTester.o
	g++ _mainTester.o  -o exe -std=c++11
_mainTester.o:_mainTester.cpp

	g++ -c _mainTester.cpp -std=c++11

clean:

	rm *.o exe
