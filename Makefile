binaries = main.o Bibliotheques.o traitement.o program.exe

all: clean $(binaries)

program.exe : main.o Bibliotheques.o traitement.o
	g++ -o program.exe main.o Bibliotheques.o traitement.o -W -Wall -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio

main.o : ./Source/main.cpp 
	g++ -c ./Source/main.cpp -W -Wall  -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio 

Bibliotheques.o : ./Source/Bibliotheques.cpp ./header/Bibliotheques.hpp
	g++ -c ./Source/Bibliotheques.cpp -W -Wall -lstdc++fs  -ljsoncpp -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio

traitement.o : ./Source/traitement.cpp ./header/traitement.hpp
	g++ -c ./Source/traitement.cpp -W -Wall -lstdc++fs  -ljsoncpp -lstdc++fs -I/opencv2/include/ -lopencv_core -lopencv_highgui -lopencv_imgcodecs -lopencv_imgproc -lopencv_videoio

.PHONY: clean

clean:
	rm -f $(binaries) *.o

