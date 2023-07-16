all:networkmap

networkmap: main.o ApartmentList.o FlatList.o IO.o
	g++ -std=c++11 main.o ApartmentList.o FlatList.o IO.o -o networkmap

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

ApartmentList.o: ApartmentList.cpp ApartmentList.h
	g++ -std=c++11 -c ApartmentList.cpp

FlatList.o: FlatList.cpp FlatList.h
	g++ -std=c++11 -c FlatList.cpp

IO.o: IO.cpp IO.h
	g++ -std=c++11 -c IO.cpp

clean:
	rm *.o networkmap