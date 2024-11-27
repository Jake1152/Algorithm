NAME = LeftOrRight
CXX = g++
CXXFLAGS = -g -std=c++17 #-Wall -Wextra -Werror
RM = rm -f

SRCS = LeftOrRight.cpp

OBJS = $(SRCS:.cpp=.o)

# OpenCV 플래그 추가
OPENCV_FLAGS = $(shell pkg-config --cflags --libs opencv4)

%.o : %.cpp
	$(CXX) $(CXXFLAGS) $(OPENCV_FLAGS) -c $^ -o $@

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(OPENCV_FLAGS) -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re
