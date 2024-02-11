CC=gcc
CFLAGS=-Iinclude -Itests/unity -g -w
DEPS = $(wildcard include/*.h)
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=obj/%.o)
TEST_SRC = $(wildcard tests/*.c)
TEST_OBJ = $(TEST_SRC:tests/%.c=obj/%.o)  obj/util.o 
UNITY_SRC = tests/unity/unity.c
UNITY_OBJ = $(UNITY_SRC:tests/unity/%.c=obj/%.o)

OBJDIR=obj
BINDIR=bin

all: clean directories find test

run: clean directories find

directories:
	@mkdir -p $(OBJDIR)
	@mkdir -p $(BINDIR)

find: $(OBJDIR)/find.o $(OBJDIR)/util.o
	$(CC) -o $(BINDIR)/find $^ $(CFLAGS)
	
test: $(TEST_OBJ) $(UNITY_OBJ)
	$(CC) -o $(BINDIR)/test_util $^ $(CFLAGS)

$(OBJDIR)/%.o: src/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: tests/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/%.o: tests/unity/%.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BINDIR)/
	rm -rf $(OBJDIR)/