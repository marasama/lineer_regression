CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -I./A_Plot

NAME_TRAIN = train
NAME_PREDICT = predict
NAME_GRAPH = graph

SRCS_TRAIN = train.cpp
SRCS_PREDICT = predict.cpp
SRCS_GRAPH = graph.cpp
OBJS_TRAIN = $(SRCS_TRAIN:.cpp=.o)
OBJS_PREDICT = $(SRCS_PREDICT:.cpp=.o)
OBJS_GRAPH = $(SRCS_GRAPH:.cpp=.o)

LIBFOLDER = A-Plot
LIBAPLOT = $(LIBFOLDER)/libaplot.a

all: $(LIBAPLOT) $(NAME_TRAIN) $(NAME_PREDICT) $(NAME_GRAPH)

$(LIBAPLOT):
	$(MAKE) -C $(LIBFOLDER)

$(NAME_TRAIN): $(OBJS_TRAIN)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

$(NAME_PREDICT): $(OBJS_PREDICT)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

$(NAME_GRAPH): $(OBJS_GRAPH) $(LIBAPLOT)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS_TRAIN) $(OBJS_PREDICT) graph.o
	$(MAKE) -C $(LIBFOLDER) clean

fclean: clean
	rm -f $(NAME_TRAIN) $(NAME_PREDICT)
	$(MAKE) -C $(LIBFOLDER) fclean

re: fclean all

.PHONY: all clean fclean re
