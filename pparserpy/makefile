CC = g++ -std=c++17


default: main.o
	> log
	$(CC)  -o main main.o >> log 2>&1

clean:
	rm -f main.o main


./%.o: ./%.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $< >> log 2>&1

