NAME := a.out

CC := c++
STDFLAGS := -std=c++98
CFLAGS := -Wall -Werror -Wextra 
INCLUDE := -I include/
TESTFLAGS := -lgtest -lgtest_main -lgmock
F17:= -std=c++98

SRCDIR := src/
OBJSDIR := objs/
TESTDIR := test/

SRC := 

ifeq ($(INT_ONLY), 1)
	CFLAGS		+= -DINT_ONLY
endif

ifeq ($(NICE), 1)
	CFLAGS  += -DNICE
endif

TEST := stack_test.cpp 

OBJS := $(SRC:%.cpp=$(OBJSDIR)%.o)
OBJSTEST := $(TEST:%.cpp=$(OBJSDIR)%.o)

all:
	make $(NAME)

$(NAME): $(OBJSDIR)main.o $(OBJS)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) $^ -o $@

tests: $(OBJS) $(OBJSTEST)
	$(CC) $(CFLAGS) $(STDFLAGS) $(F17) $(INCLUDE) $^ $(TESTFLAGS) -o $@

$(OBJSDIR)%.o: $(TESTDIR)%.cpp 
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(F17) $(INCLUDE) -c $< -o $@

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
