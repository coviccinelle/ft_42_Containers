NAME := a.out

CC := c++
STDFLAGS := -std=c++98
STDFLAGSTEST := -std=c++17
CFLAGS := -Wall -Werror -Wextra 
INCLUDE := -I include/
TESTFLAGS := -lgtest -lgtest_main -std=c++17

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
	$(CC) $(CFLAGS) $(STDFLAGSTEST) $(INCLUDE) -c $< -o $@

$(OBJSDIR)%.o: $(SRCDIR)%.cpp 
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) -c $< -o $@

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
