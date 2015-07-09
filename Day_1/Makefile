TARGET=prog1
TARGET1=prog1_2
all: prog1 prog1_2
$(TARGET): prog1.o
	gcc prog1.o -o $(TARGET)
prog1.o: prog1.c
	gcc prog1.c -c
$(TARGET1): prog1_2.o
	gcc prog1_2.o -o $(TARGET1)
prog1_2.o: prog1_2.c
	gcc prog1_2.c -c
clean:
	rm -f *.o $(TARGET)
	rm -f $(TARGET1)
