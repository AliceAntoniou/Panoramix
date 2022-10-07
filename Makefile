##
## EPITECH PROJECT, 2022
## wolfram
## File description:
## Makefile
##

CC	=	gcc

MAIN	=	src/main.c

SRC	=	src/villager.c	\
		src/parser.c	\
		src/global.c	\
		src/druid.c

OBJ	=	$(addsuffix .o, $(basename $(SRC)))

RM	=	rm -f

NAME	=	panoramix

OK      =       \e[32m
RED     =       \e[91m
END     =       \e[0m

LDFLAGS	=       -lpthread -lrt

CFLAGS  =	-W -Wall -Wextra -g

CPPFLAGS        =       -I./include

PHONY	=	all

define center_text
echo -e "$(OK)>>>>\t$1$(END)"
endef

all: $(NAME)

$(NAME):	$(SRC) $(MAIN)
	@$(call center_text,$(NAME))
	$(eval OBJ += $(MAIN:.cpp=.o))
	@$(MAKE) -s $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(CPPFLAGS) && \
	echo -e "$(OK)[DONE]\t$(NAME)$(END)" || \
	echo -e "$(RED)[FAILURE]\t$(NAME)$(END)"

%.o: %.c
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $< && \
	echo -e "$(OK)[OK]\t$<$(END)" || \
	echo -e "$(RED)[FAILURE]\t$<$(END)"

PHONY += clean
clean:
	@find . -name *.o -delete -o -name *.hi -type f -delete

PHONY += fclean
fclean: clean
	@$(RM) $(NAME)

PHONY += fclean
re: fclean all

.PHONY: $(PHONY)
