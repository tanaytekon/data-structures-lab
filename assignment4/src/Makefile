all:webstore

webstore: main.o BST.o AVL.o Webstore.o
	g++ -std=c++11 main.o BST.o AVL.o Webstore.o -o webstore

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Webstore.o: Webstore.cpp Webstore.h
	g++ -std=c++11 -c Webstore.cpp Webstore.h

BST.o: BST.cpp BST.h
	g++ -std=c++11 -c BST.cpp BST.h

AVL.o: AVL.cpp AVL.h
	g++ -std=c++11 -c AVL.cpp AVL.h