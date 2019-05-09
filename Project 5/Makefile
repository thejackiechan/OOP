all: proj5.exe

proj5.exe: random.o StatsClass.o EventClass.o RiderClass.o AttractionClass.o ParkSimulationClass.o Project5.o
	g++ random.o StatsClass.o EventClass.o RiderClass.o AttractionClass.o ParkSimulationClass.o Project5.o -o proj5.exe

Project5.o: Project5.cpp ParkSimulationClass.h AttractionClass.h StatsClass.h RiderClass.h FIFOQueueClass.h SortedListClass.h LinkedNodeClass.h EventClass.h random.h constants.h
	g++ -c Project5.cpp -o Project5.o

ParkSimulationClass.o: ParkSimulationClass.cpp AttractionClass.h SortedListClass.h StatsClass.h EventClass.h random.h constants.h
	g++ -c ParkSimulationClass.cpp -o ParkSimulationClass.o

AttractionClass.o: AttractionClass.cpp AttractionClass.h FIFOQueueClass.h RiderClass.h StatsClass.h constants.h
	g++ -c AttractionClass.cpp -o AttractionClass.o

RiderClass.o: RiderClass.cpp RiderClass.h
	g++ -c RiderClass.cpp -o RiderClass.o

EventClass.o: EventClass.cpp EventClass.h constants.h
	g++ -c EventClass.cpp -o EventClass.o

StatsClass.o: StatsClass.cpp StatsClass.h
	g++ -c StatsClass.cpp -o StatsClass.o

random.o: random.cpp random.h
	g++ -c random.cpp -o random.o

clean:
	rm -f *.o *.exe