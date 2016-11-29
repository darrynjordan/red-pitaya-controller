CC=arm-linux-gnueabi-gcc
#HAD TO CHANGE AWAY FROM GNUEABIHF

#Default location for h files is ./source
CFLAGS= -std=gnu99 -Wall -Werror -I./source -I./source/rpad/src -pthread -L lib -lm -lpthread -lrp

#h files used go here
DEPS= includes.h rp.h controller.h mon.h scope.h options.h transfer.h

#c files used go here (with .o extension)
OBJ = main.o source/ini.o source/controller.o source/mon.o source/options.o source/transfer.o source/scope.o 

#name of generated binaries
BIN = RPCC

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFlags)

RPCC: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(BIN) *.o source/*.o
