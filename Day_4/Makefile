TARGET=RS
TARGET1=RC
all: $(TARGET) $(TARGET1)
$(TARGET): RawServ.o
	gcc RawServ.o -o $(TARGET)
RawServ.o: RawServ.c
	gcc RawServ.c -c
$(TARGET1): RawClient.o
	gcc RawClient.o -o $(TARGET1)
RawClient.o: RawClient.c
	gcc RawClient.c -c
clean:
	rm -f *.o $(TARGET)
	rm -f $(TARGET1)
