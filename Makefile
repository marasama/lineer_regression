CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11

NAME_TRAIN = train
NAME_PREDICT = predict

SRCS_TRAIN = train.cpp
SRCS_PREDICT = predict.cpp

OBJS_TRAIN = $(SRCS_TRAIN:.cpp=.o)
OBJS_PREDICT = $(SRCS_PREDICT:.cpp=.o)

all: $(NAME_TRAIN) $(NAME_PREDICT)

$(NAME_TRAIN): $(OBJS_TRAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(NAME_PREDICT): $(OBJS_PREDICT)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS_TRAIN) $(OBJS_PREDICT)

fclean: clean
	rm -f $(NAME_TRAIN) $(NAME_PREDICT)

re: fclean all

.PHONY: all clean fclean re
