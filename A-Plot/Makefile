CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++11

NAME_LIB    = libaplot.a

SRCS_LIB    = A_Plot.cpp
OBJS_LIB    = $(SRCS_LIB:.cpp=.o)

all: $(NAME_LIB)

$(NAME_LIB): $(OBJS_LIB)
	ar rcs $@ $^

clean:
	rm -f $(OBJS_LIB)

fclean: clean
	rm -f $(NAME_LIB)

re: fclean all

.PHONY: all clean fclean re
