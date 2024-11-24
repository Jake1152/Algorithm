NAME = LeftOrRight
CXX = g++
CXXFLAGS = -g -std=c++11 $(FLAGS) #-Wall -Wextra -Werror
RM = rm -f

SRCS = LeftOrRight.cpp

# g++ LeftOrRight.cpp -o a.out $(pkg-config --cflags --libs opencv4)

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
