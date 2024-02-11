CC=gcc
CFLAGS=-Iinclude -Itests/unity -g -w
DEPS = $(wildcard include/*.h)
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=obj/%*.o)
TEST_SRC = $(wildcard tests/*.c)
TEST_OBJ = $(TEST_SRC:tests/%.c=obj/%*.o) obj/util.o
OBJ = $(SRC:src/%.c=obj/%*.o)
UNITY_SRC = $(wildcard tests/*.c)
UNITY_OBJ = $(UNITY_SRC:tests/unity/%.c=obj/%*.o)

OBJDIR=obj
BINDIR=bin

all: directories find test

directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

find: $(OBJ)
	$(CC) -o $(BINDIR)/find $^ $(CFLAGS)
	
test: $(TEST_OBJ) $(UNITY_OBJ)
	$(CC) -o $(BINDIR)/test_util $^ $(CFLAGS)
	./$(BINDIR)/test_util

$(OBJDIR)/%.o: src/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: tests/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: tests/unity/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BINDIR)/*
	rm -rf $(OBJDIR)/*