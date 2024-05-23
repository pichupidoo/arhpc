EXE    := ../sc
CC     := gcc -I../include -Wall -g3
CPPFLAGS := 

MAIN_OBS := $(patsubst %.c,%.o,$(wildcard *.c))
LIB_OBS  := ../mySimpleComputer/mySimpleComputer.a ../myTerm/myTerm.a ../myBigChars/myBigChars.a ../myReadkey/myReadkey.a

all: $(EXE)

$(EXE) : $(MAIN_OBS) $(LIB_OBS)
	$(CC) -o $@ $(LDFLAGS) $^ $(LDLIBS)

clean:
	rm -f $(MAIN_OBS) $(LIB_OBS) $(EXE)
	rm -f genfont font.bin


.PHONY: all clean  