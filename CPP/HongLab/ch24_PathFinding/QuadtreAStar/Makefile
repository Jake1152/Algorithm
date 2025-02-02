NAME = QuadtreAStar
CXX = g++

OPENCV_CFLAGS = $(shell pkg-config --cflags opencv4)
OPENCV_LDFLAGS = $(shell pkg-config --libs opencv4)

CXXFLAGS = -g -I.. $(OPENCV_CFLAGS)
LDFLAGS = $(OPENCV_LDFLAGS) -L/usr/lib

RM = rm -f

SRCS = QuadtreAStar.cpp
OBJS = $(SRCS:.cpp=.o)

$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -o $@

all : $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re :
	make fclean
	make all

.PHONY: all clean fclean re
