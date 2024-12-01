NAME = LeftOrRight
CXX = g++
# CXXFLAGS = -g -std=c++17 -I/usr/include/opencv4

OPENCV_CFLAGS = $(shell pkg-config --cflags opencv4)
OPENCV_LDFLAGS = $(shell pkg-config --libs opencv4)

CXXFLAGS = -g -std=c++17 -I.. $(OPENCV_CFLAGS)
LDFLAGS = $(OPENCV_LDFLAGS) -L/usr/lib

RM = rm -f

SRCS = LeftOrRight.cpp
OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $@

# OPENCV_FLAGS = $(shell pkg-config --cflags --libs opencv4)
# OPENCV_FLAGS = $(shell pkg-config --cflags opencv4) $(shell pkg-config --libs opencv4) -L/usr/lib


# $(NAME) : $(OBJS)
#	$(CXX) $(CXXFLAGS) $(OBJS) $(OPENCV_FLAGS) -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re
