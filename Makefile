NAME			=	RV32I_to_MC

SRCS			=	main.cpp \
					RV32I_C.cpp

OBJS			=	$(SRCS:.cpp=.o)

CXX				=	c++
RM				=	rm -f
CXXFLAGS		=	-Wall -Wextra -Werror -g -std=c++98 -pedantic

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CXX) $(CXXFLAGS) -g -o $(NAME) $(OBJS)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

test:			$(NAME)

.PHONY:			all clean fclean re test
