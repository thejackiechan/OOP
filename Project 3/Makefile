all: proj3.exe

proj3.exe: trimLine.o openFile.o ColorClass.o MessageClass.o RowColumnClass.o ColorImageClass.o  MenuClass.o Project3.o 
	g++  trimLine.o openFile.o ColorClass.o MessageClass.o RowColumnClass.o ColorImageClass.o  MenuClass.o Project3.o -o proj3.exe

Project3.o: Project3.cpp MenuClass.h ColorImageClass.h RowColumnClass.h MessageClass.h ColorClass.h openFile.h trimLine.h constants.h
	g++ -c Project3.cpp -o Project3.o

MenuClass.o: MenuClass.cpp MenuClass.h ColorImageClass.h trimLine.h constants.h
	g++ -c MenuClass.cpp -o MenuClass.o

ColorImageClass.o: ColorImageClass.cpp ColorImageClass.h ColorClass.h MessageClass.h RowColumnClass.h trimLine.h constants.h
	g++ -c ColorImageClass.cpp -o ColorImageClass.o

RowColumnClass.o: RowColumnClass.cpp RowColumnClass.h constants.h
	g++ -c RowColumnClass.cpp -o RowColumnClass.o

MessageClass.o: MessageClass.cpp MessageClass.h constants.h
	g++ -c MessageClass.cpp -o MessageClass.o

ColorClass.o: ColorClass.cpp ColorClass.h constants.h
	g++ -c ColorClass.cpp -o ColorClass.o

openFile.o: openFile.cpp openFile.h constants.h
	g++ -c openFile.cpp -o openFile.o

trimLine.o: trimLine.cpp trimLine.h constants.h
	g++ -c trimLine.cpp -o trimLine.o

clean: 
	rm -f *.o *.exe