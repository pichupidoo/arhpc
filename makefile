export CFLAGS = -Wall -Wextra -Werror
export CPPFLAGS = -I$(PWD)/include -L$(PWD)/mySimpleComputer -L$(PWD)/myTerm -L$(PWD)/myBigChars -L$(PWD)/myReadKey -MMD
export CC = gcc
SUBDIRS = myTerm mySimpleComputer myBigChars myReadKey console
LFLAGS = -lmySimpleComputer -lmyTerm -lmyBigChars -lmyReadKey
LIBS = $(PWD)/mySimpleComputer/libmySimpleComputer.a $(PWD)/myTerm/libmyTerm.a $(PWD)/myBigChars/libmyBigChars.a $(PWD)/myReadKey/libmyReadKey.a
export LFLAGS
export LIBS

all: $(SUBDIRS)
$(SUBDIRS):
	@$(MAKE) --no-print-directory -C $@

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) --no-print-directory -C $$dir clean; \
	done

.PHONY: all clean $(SUBDIRS)

format:
	find . -type f -name *.[ch] | xargs clang-format --style GNU -i -verbose