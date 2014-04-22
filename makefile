Test.exe : Test.o MemIniParser.o
	g++ -o Test.exe Test.o MemIniParser.o

MemIniParser.o : core/MemIniParser.cpp
	g++ -g -c core/MemIniParser.cpp

Test.o : Test.cpp
	g++ -g -c Test.cpp

clean : 
	rm Test.exe Test.o MemIniParser.o
