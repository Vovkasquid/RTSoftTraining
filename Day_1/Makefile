TARGET=prog1
TARGET1=prog1_2
TARGET2=HWFIFO
TARGET3=HWFIFO1
all: $(TARGET) $(TARGET1) $(TARGET2) $(TARGET3)
$(TARGET): prog1.o
	gcc prog1.o -o $(TARGET)
prog1.o: prog1.c
	gcc prog1.c -c
$(TARGET1): prog1_2.o
	gcc prog1_2.o -o $(TARGET1)
prog1_2.o: prog1_2.c
	gcc prog1_2.c -c
$(TARGET2): HWFIFO.o
	gcc HWFIFO.o -o $(TARGET2)
HWFIFO.o: HWFIFO.c
	gcc HWFIFO.c -c
$(TARGET3): HWFIFO1.o
	gcc HWFIFO1.o -o $(TARGET3)
HWFIFO1.o: HWFIFO1.c
	gcc HWFIFO1.c -c
clean:
	rm -f *.o $(TARGET)
	rm -f $(TARGET1)
	rm -f $(TARGET2)
	rm -f $(TARGET3)
