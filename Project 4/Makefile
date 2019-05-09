all: proj4.exe

proj4.exe: LinkedNodeClass.o SortedListClass.o FIFOQueueClass.o LIFOStackClass.o Project4.o
	g++ LinkedNodeClass.o SortedListClass.o FIFOQueueClass.o LIFOStackClass.o Project4.o -o proj4.exe

Project4.o: Project4.cpp LIFOStackClass.h FIFOQueueClass.h SortedListClass.h LinkedNodeClass.h
	g++ -c Project4.cpp -o Project4.o

LIFOStackClass.o: LIFOStackClass.cpp LIFOStackClass.h LinkedNodeClass.h
	g++ -c LIFOStackClass.cpp -o LIFOStackClass.o

FIFOQueueClass.o: FIFOQueueClass.cpp FIFOQueueClass.h LinkedNodeClass.h
	g++ -c FIFOQueueClass.cpp -o FIFOQueueClass.o

SortedListClass.o: SortedListClass.cpp SortedListClass.h LinkedNodeClass.h
	g++ -c SortedListClass.cpp -o SortedListClass.o

LinkedNodeClass.o: LinkedNodeClass.cpp LinkedNodeClass.h
	g++ -c LinkedNodeClass.cpp -o LinkedNodeClass.o

clean:
	rm -f *.o *.exe