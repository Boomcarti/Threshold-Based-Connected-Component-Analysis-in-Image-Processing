
findcomp:  ConnectedComponent.o PGMimageProcessor.o  findcomp.o
	g++  ConnectedComponent.o PGMimageProcessor.o findcomp.o -o findcomp -std=c++2a

findcomp.o: findcomp.cpp 
	g++ -c findcomp.cpp -o findcomp.o -std=c++2a

PGMimageProcessor.o:  PGMimageProcessor.cpp PGMimageProcessor.h 
	g++ -c  PGMimageProcessor.cpp -o PGMimageProcessor.o -std=c++2a

ConnectedComponent.o: ConnectedComponent.cpp ConnectedComponent.h
	g++ -c ConnectedComponent.cpp -o ConnectedComponent.o -std=c++2a


run1: findcomp
	./findcomp -s 100 10000 -t 180 -p -w output chess.pgm


run2: findcomp
	./findcomp -s 200 7000 -t 175 -p -w output chess.pgm

run3: findcomp
	./findcomp -s 15 1000000 -t 180 -p -w output dog.pgm

run4: findcomp
	./findcomp -s 2 6000 -t 178 -p -w output simple.pgm


Test: a.out
	./a.out 

a.out: Test.o 
	g++ -c Test.o -o a.out -std=c++2a

Test.o: Test.cpp
	g++ -c Test.cpp -o Test.o -std=c++2a
	

clean:
	rm *.o findcomp a.out





