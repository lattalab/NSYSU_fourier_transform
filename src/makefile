CC=g++
LDFLAGS+= -lboost_system -lboost_filesystem -lboost_iostreams -lsndfile
OBJ = FFT.o

all: FFT

FFT: $(OBJ)
	$(CC) -o FFT $(OBJ) $(LDFLAGS)

	
%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	rm -f *.o FFT
