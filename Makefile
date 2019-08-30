Project2.out: main.o ImageProcessor.o
	g++ main.o ImageProcessor.o -o Project2.out

main.o: src/main.cpp
	g++ -c src/main.cpp

ImageProcessor.o: src/ImageProcessor.cpp src/ImageProcessor.h src/Image.h
	g++ -c src/ImageProcessor.cpp

clean:
	rm *.o Project2.out
