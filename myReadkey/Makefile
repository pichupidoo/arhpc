# Define the source files
CFILES = $(wildcard *.c)
# Define the object files
OFILES = $(CFILES:.c=.o)

# Set compiler flags
CFLAGS = -Wall -Wextra -Werror -g3

# Define the library name
NAME = myReadkey.a

# Default target
all: $(NAME)

# Compile the source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -I../include -c $< -o $@ 
# Create the static library
$(NAME): $(OFILES)
	ar rcs $(NAME) $(OFILES)

# Clean up
clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

.PHONY: all clean fclean