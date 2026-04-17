CXX = g++
CXXFLAGS = -O3 -Wall -march=native -funroll-loops -ffast-math 
OMPFLAG = -fopenmp

all: par seq


par: main_par.o tensor.o conv_par.o
	$(CXX) $(CXXFLAGS) $(OMPFLAG) -o dwconv_par.exe main_par.o tensor.o conv_par.o

seq: main.o tensor.o conv.o
	$(CXX) $(CXXFLAGS) -o dwconv_seq.exe main.o tensor.o conv.o


main.o: main.cpp Tensor.h Conv.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

tensor.o: tensor.cpp Tensor.h
	$(CXX) $(CXXFLAGS) -c tensor.cpp -o tensor.o

conv.o: conv.cpp Conv.h Tensor.h
	$(CXX) $(CXXFLAGS) -c conv.cpp -o conv.o

main_par.o: main.cpp Tensor.h Conv.h
	$(CXX) $(CXXFLAGS) $(OMPFLAG) -c main.cpp -o main_par.o

conv_par.o: conv.cpp Conv.h Tensor.h
	$(CXX) $(CXXFLAGS) $(OMPFLAG) -c conv.cpp -o conv_par.o

benchmark_par: dwconv_par.exe
	@echo Avvio Benchmark Parallelo...
	powershell -ExecutionPolicy Bypass -File .\benchmark_par.ps1

benchmark_seq: dwconv_seq.exe
	@echo Avvio Benchmark Sequenziale...
	powershell -ExecutionPolicy Bypass -File .\benchmark_seq.ps1

clean:
	rm -f *.o *.exe