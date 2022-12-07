NAME := a.out

CC := c++
STDFLAGS := -std=c++98
CFLAGS := -Wall -Werror -Wextra -std=c++17
INCLUDE := -I include/
TESTFLAGS := -lgtest -lgtest_main

SRCDIR := src/
OBJSDIR := objs/
TESTDIR := test/

SRC := sample1.cpp

TEST := sample1_unittest.cpp

OBJS := $(SRC:%.cpp=$(OBJSDIR)%.o)
OBJSTEST := $(TEST:%.cpp=$(OBJSDIR)%.o)

all:
	make $(NAME)

$(NAME): $(OBJSDIR)main.o $(OBJS)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) $^ -o $@

tests: $(OBJS) $(OBJSTEST)
	$(CC) $(CFLAGS) $(INCLUDE) $^ $(TESTFLAGS) -o $@

$(OBJSDIR)%.o: $(TESTDIR)%.cpp 
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJSDIR)%.o: $(SRCDIR)%.cpp 
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJSDIR) 

fclean: clean
	rm -rf $(NAME)
	rm -rf tests

re: fclean
	make $(NAME)

.PHONY: all clean re fclean tests
