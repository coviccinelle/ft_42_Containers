NAME := a.out

CC := c++
STDFLAGS := -std=c++98
CFLAGS := -Wall -Werror -Wextra -MMD #-fsanitize=address
INCLUDE := -I . -I ./lib/googletest_build/googletest/include
TESTFLAGS := -L ./lib/googletest_build/googletest/lib -lgtest -lgtest_main -lgmock

SRCDIR := src/
OBJSDIR := objs/
TESTDIR := test/

SRC := 

TEST := vector_test.cpp \
	map_test.cpp

OBJS := $(SRC:%.cpp=$(OBJSDIR)%.o)
OBJSTEST := $(TEST:%.cpp=$(OBJSDIR)%.o)

all:
	make $(NAME)

$(NAME): $(OBJSDIR)main.o $(OBJS)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) $^ -o $@

tests: $(OBJSTEST)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) $^ $(TESTFLAGS) -o $@

$(OBJSDIR)%.o:  $(TESTDIR)%.cpp
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) -c $< -o $@

$(OBJSDIR)%.o: $(SRCDIR)%.cpp 
	mkdir -p $(OBJSDIR)
	$(CC) $(CFLAGS) $(STDFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -rf $(OBJSDIR) 

fclean: clean
	rm -rf $(NAME)
	rm -rf tests

re: fclean
	make $(NAME)

-include $(OBJSTEST:.o=.d)

.PHONY: all clean re fclean tests
