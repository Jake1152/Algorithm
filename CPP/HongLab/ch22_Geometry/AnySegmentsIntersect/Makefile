NAME = AnySegmentsIntersect
CXX = g++
CXXFLAGS = -g -std=c++11#-Wall -Wextra -Werror
RM = rm -f

SRCS = AnySegmentsIntersect.cpp

OBJS = $(SRCS:.cpp=.o)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re
