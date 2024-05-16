LIB_PATH = libmyReadKey.a
SRC_EXT = c
APP_SOURCES = $(wildcard *.$(SRC_EXT))
LIB_OBJECTS := $(patsubst %.$(SRC_EXT),%.o,$(APP_SOURCES))
DEPS = $(LIB_OBJECTS:.o=.d)

.PHONY: all

all: $(LIB_PATH)
-include $(DEPS)

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

/%.o: /%.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

.PHONY: clean

clean:
	rm -rf $(LIB_OBJECTS)
	rm -rf $(DEPS)
	rm -rf $(LIB_PATH)