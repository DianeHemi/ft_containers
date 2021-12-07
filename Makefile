F_NAME	= test_ft
S_NAME	= test_std

VPATH	= 	objs:./srcs

SRCS	= 	main.cpp \
			test_vector.cpp \
			test_stack.cpp \
			test_map.cpp \
			test_set.cpp

INCL	= 	./includes/pair.hpp \
			./includes/enable_if.hpp\
			./includes/iterator_traits.hpp \
			./includes/lexicographical_compare.hpp \
			./includes/map/iterator_map.hpp \
			./includes/map/map.hpp \
			./includes/map/RBTree_map.hpp \
			./includes/set/iterator_set.hpp \
			./includes/set/set.hpp \
			./includes/set/RBTree_set.hpp \
			./includes/stack/stack.hpp \
			./includes/vector/iterator_vector.hpp \
			./includes/vector/vector.hpp \
			./srcs/tests.hpp

OBJS_FT		= $(addprefix ${PATH_OBJS_FT},${SRCS:.cpp=.o})
OBJS_STD	= $(addprefix ${PATH_OBJS_STD},${SRCS:.cpp=.o})

CXX		= clang++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

PATH_OBJS		= ./objs
PATH_OBJS_FT	= ./objs/ft/
PATH_OBJS_STD	= ./objs/std/


$(PATH_OBJS_FT)%.o :%.cpp $(INCL)
	$(CXX) $(CXXFLAGS) -D NAMESPACE=ft -c $< -o $@ 

$(PATH_OBJS_STD)%.o :%.cpp $(INCL)
	$(CXX) $(CXXFLAGS) -D NAMESPACE=std -c $< -o $@ 


all: ${PATH_OBJS} ${PATH_OBJS_FT} $(F_NAME) ${PATH_OBJS_STD} $(S_NAME)


$(F_NAME): $(OBJS_FT)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(S_NAME): $(OBJS_STD)
	$(CXX) $(CXXFLAGS) $^ -o $@


clean:
	rm -f $(OBJS_FT)
	rm -f $(OBJS_STD)

fclean: clean
	rm -f $(F_NAME) $(S_NAME)
	if [ -d $(PATH_OBJS_FT) ]; then rm -r $(PATH_OBJS_FT); fi;
	if [ -d $(PATH_OBJS_STD) ]; then rm -r $(PATH_OBJS_STD); fi;
	if [ -d $(PATH_OBJS) ]; then rm -r $(PATH_OBJS); fi;

re: fclean
	$(MAKE)


${PATH_OBJS}:
	mkdir -p $@
${PATH_OBJS_FT}:
	mkdir -p $@
${PATH_OBJS_STD}:
	mkdir -p $@


.PHONY : all clean fclean re test_ft test_std