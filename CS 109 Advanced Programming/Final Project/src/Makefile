main: fact/fact.o rule/rule.o sri_engine/table.o sri_engine/sri_engine.o main.o sri_engine/predicateThread.o sri_engine/Thread.o sri_engine/ThreadManager.o sri_engine/andThread.o
	g++ -std=c++14 -g -pthread -o main fact/fact.o rule/rule.o sri_engine/table.o sri_engine/sri_engine.o main.o sri_engine/predicateThread.o sri_engine/Thread.o sri_engine/ThreadManager.o sri_engine/andThread.o

main.o: main.cpp
	g++ -std=c++14 -g -o main.o -c main.cpp

fact/fact.o: fact/fact.cpp
	g++ -std=c++14 -g -o fact/fact.o -c fact/fact.cpp

rule/rule.o: rule/rule.cpp
	g++ -std=c++14 -g -o rule/rule.o -c rule/rule.cpp

sri_engine/table.o: sri_engine/table.cpp
	g++ -std=c++14 -g -o sri_engine/table.o -c sri_engine/table.cpp

sri_engine/sri_engine.o: sri_engine/sri_engine.cpp
	g++ -std=c++14 -g -o sri_engine/sri_engine.o -c sri_engine/sri_engine.cpp

sri_engine/predicateThread.o: sri_engine/predicateThread.cpp
	g++ -std=c++14 -g -o sri_engine/predicateThread.o -c sri_engine/predicateThread.cpp

sri_engine/ThreadManager.o: sri_engine/ThreadManager.cpp
	g++ -std=c++14 -g -o sri_engine/ThreadManager.o -c sri_engine/ThreadManager.cpp

sri_engine/Thread.o: sri_engine/Thread.cpp
	g++ -std=c++14 -g -o sri_engine/Thread.o -c sri_engine/Thread.cpp

sri_engine/andThread.o: sri_engine/andThread.cpp
	g++ -std=c++14 -g -o sri_engine/andThread.o -c sri_engine/andThread.cpp

clean:
	rm *.o */*.o main
