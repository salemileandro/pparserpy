CC = g++ -std=c++17


default: main.o
	$(CC)  -o main main.o

clean:
	rm -f main.o main


./%.o: ./%.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

