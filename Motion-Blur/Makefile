all: motionblur

motionblur: pbmLib.o fft.o test.o
	g++ -I /usr/include/netpbm -o motionblur pbmLib.o fft.o test.o -lnetpbm

pbmLib.o: pbmLib.cc pbmLib.h
	g++ -I /usr/include/netpbm -c pbmLib.cc -Wall -lnetpbm

fft.o: fft.cc fft.h
	g++ -c fft.cc -Wall -lnetpbm

test.o: test.cc fft.h pbmLib.h
	g++ -I /usr/include/netpbm -c test.cc -Wall -lnetpbm

clean:
	rm -f *~ *.o

clean-all: clean
	rm -f motionblur
