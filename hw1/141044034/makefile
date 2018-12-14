all: Myprogram

Myprogram: main.o
	g++ HW1.o  -o Myprogram

main.o: HW1.cpp
	g++ -c HW1.cpp

clean:
	rm *.o Myprogram

execute0:
	./Myprogram file.txt 0 

execute1:
	./Myprogram file.txt 1 

