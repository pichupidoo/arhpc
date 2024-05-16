APP_NAME = app
SRC_EXT = c
APP_SOURCES = $(filter-out font.c, $(wildcard *.$(SRC_EXT)))
APP_OBJECTS := $(patsubst %.$(SRC_EXT),%.o,$(APP_SOURCES))
DEPS = $(APP_OBJECTS:.o=.d)

.PHONY: all
all: $(APP_NAME) font.bin
-include $(DEPS)
$(APP_NAME): $(APP_OBJECTS) $(LIBS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LFLAGS)
/%.o: /%.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ $(LFLAGS)

font.bin: font
	./font
	rm font

font: font.c $(LIBS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@ $(LFLAGS)

.PHONY: clean

clean:
	rm -rf $(APP_OBJECTS) $(DEPS) $(APP_NAME) font.d font.bin