.SUFFIXES: .c .o
CFLAGS = -pthread
CC = gcc
OBJDIR = objects_and_exec
vpath %.c Util main Global_structs Pthread_functions
objects = $(addprefix $(OBJDIR)/, main.o initialization_functions.o Pthread_functions.o)

make_dir:
	mkdir $(OBJDIR)

test: make_dir $(objects)
	$(CC) $(CFLAGS) $(objects) -o test

$(OBJDIR)/%.o : %.c
	$(CC) -c $< -o $@

clean:
	rm $(OBJDIR)/*.o test
	rmdir $(OBJDIR)