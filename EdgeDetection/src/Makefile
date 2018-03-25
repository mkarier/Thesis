ImageFilter:ArrayBuffer.o Canny.o ColorReduce.o HighContrast.o Otsu.o Sobel.o Wavelet.o SharedMethods.o 
	g++ -Wall -std=c++11 -o image EdgeDetection.cpp ArrayBuffer.o Canny.o ColorReduce.o HighContrast.o Otsu.o Sobel.o Wavelet.o SharedMethods.o -pthread `pkg-config opencv --cflags --libs`
ArrayBuffer.o:
	g++ -std=c++11 -o ArrayBuffer.o ArrayBuffer.cpp -c

Canny.o:
	g++ -std=c++11 -o Canny.o Canny.cpp -c

ColorReduce.o:
	g++ -std=c++11 -o ColorReduce.o ColorReduce.cpp -c

HighContrast.o:
	g++ -std=c++11 -o HighContrast.o HighContrast.cpp -c

Otsu.o:
	g++ -std=c++11 -o Otsu.o Otsu.cpp -c

Sobel.o:
	g++ -std=c++11 -o Sobel.o Sobel.cpp -c

Wavelet.o:
	g++ -std=c++11 -o Wavelet.o Wavelet.cpp -c

SharedMethods.o:
	g++ -std=c++11 -o SharedMethods.o SharedMethods.cpp -c

clean:
	rm *.o
	rm image
