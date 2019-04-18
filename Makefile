.SUFFIXES: .c .o

CC = gcc
OBJDIR = objects_and_exec
vpath %.c Initialization main
objects = $(addprefix $(OBJDIR)/, main.o initialization_functions.o)

make_dir:
	mkdir $(OBJDIR)

test: make_dir $(objects)
	$(CC) $(objects) -o test

$(OBJDIR)/%.o : %.c
	$(CC) -c $< -o $@

clean:
	rm $(OBJDIR)/*.o test
	rmdir $(OBJDIR)