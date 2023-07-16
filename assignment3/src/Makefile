all:Assignment3

Assignment3: main.o
	g++ -std=c++11 main.o Operations.o Workers.o Queue.o Order.o -o Assignment3

main.o: main.cpp Operations.o
	g++ -std=c++11 -c main.cpp

Operations.o: Operations.cpp Operations.h Workers.o
	g++ -std=c++11 -c Operations.cpp Operations.h

Workers.o: Workers.cpp Workers.h Queue.o
	g++ -std=c++11 -c Workers.cpp Workers.h

Queue.o: Queue.cpp Queue.h Order.o
	g++ -std=c++11 -c Queue.cpp Queue.h

Order.o: Order.cpp Order.h
	g++ -std=c++11 -c Order.cpp Order.h