CC = cc
CFLAGS = -Wall -Wextra -ggdb -fPIC -shared -o
OBJECT = libxtreme.so
SRC = $(shell find src/ -type f -name *.c)
INCLUDE = include/*
INSTALLATION_TARGET = /usr/lib/$(OBJECT)
INCLUDE_TARGET = /usr/include/
DEPS = /usr/lib/libraylib.so*
LIBS = -lraylib

default: $(SRC) $(DEPS)
	@$(CC) $(CFLAGS) $(OBJECT) $(SRC) $(LIBS)

clean: $(OBJECT)
	@rm $(OBJECT)

install: $(DEPS)
	@make default
	@sudo mv $(OBJECT) $(INSTALLATION_TARGET)
	@sudo cp -r $(INCLUDE) $(INCLUDE_TARGET)

uninstall: $(INSTALLATION_TARGET)
	@sudo rm -r $(INSTALLATION_TARGET)
	@sudo rm -r $(INCLUDE_TARGET)
