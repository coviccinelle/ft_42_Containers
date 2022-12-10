NAME := a.out

CC := c++
STDFLAGS := -std=c++98
CFLAGS := -Wall -Werror -Wextra -std=c++17
INCLUDE := -I include/
TESTFLAGS := -lgtest -lgtest_main 

SRCDIR := src/
OBJSDIR := objs/
TESTDIR := test/

SRC := 

ifeq ($(INT_ONLY), 1)
	CFLAGS		+= -DINT_ONLY
endif


TEST := vector_test.cpp

OBJS := $(SRC:%.cpp=$(OBJSDIR)%.o)
OBJSTEST := $(TEST:%.cpp=$(OBJSDIR)%.o)

all:
	make $(NAME)

$(NAME): $(OBJSDIR)main.o $(OBJS)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) $^ -o $@

tests: $(OBJS) $(OBJSTEST)
	$(CC) $(CFLAGS) $(INCLUDE) $^ $(TESTFLAGS) -o $@

$(OBJSDIR)%.o: $(TESTDIR)%.cpp 
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS)  $(INCLUDE) -c $< -o $@

$(OBJSDIR)%.o: $(SRCDIR)%.cpp 
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJSDIR) 

retet: fclean
	make tests

retet_int: fclean
	make tests INT_ONLY=1

fclean: clean
	rm -rf $(NAME)
	rm -rf tests

re: fclean
	make $(NAME)

.PHONY: all clean re fclean tests retet retet_int
