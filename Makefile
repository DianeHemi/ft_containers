F_NAME	= test_ft
S_NAME	= test_std

VPATH	= objs:./srcs

SRCS	= main.cpp \
			test_vector.cpp \
			test_stack.cpp \
			test_map.cpp \
			test_set.cpp

INCL	= -I /includes -I /srcs

OBJS_FT	= $(addprefix ${PATH_OBJS_FT},${SRCS:.cpp=.o})
OBJS_STD	= $(addprefix ${PATH_OBJS_STD},${SRCS:.cpp=.o})

CC		= clang++
CFLAGS	= -Wall -Wextra -Werror -std=c++98

PATH_OBJS_FT = ./objs/ft/
PATH_OBJS_STD = ./objs/std/

$(PATH_OBJS_FT)%.o :%.cpp
	$(CC) $(CFLAGS) -D SPACE=ft -c $< -o $@ 

$(PATH_OBJS_STD)%.o :%.cpp
	$(CC) $(CFLAGS) -D SPACE=std -c $< -o $@ 

all: ${PATH_OBJS_FT} $(F_NAME) ${PATH_OBJS_STD} $(S_NAME)

$(F_NAME): $(OBJS_FT)
	$(CC) $(CFLAGS) $(OBJS_FT) $(INCL) -o $@

$(S_NAME): $(OBJS_STD)
	$(CC) $(CFLAGS) $(OBJS_STD) $(INCL) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(F_NAME) $(S_NAME)
	rm -r ${PATH_OBJS_FT} ${PATH_OBJS_STD}

re: fclean
	$(MAKE)

${PATH_OBJS_FT}:
	mkdir -p $@
${PATH_OBJS_STD}:
	mkdir -p $@

.PHONY : all clean fclean re test_ft test_std