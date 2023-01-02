##**********##
### COLORS ###
##**********##

BLACK		= \033[1;30m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
VIOLET		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
IGREY		= \x1b[40m
IRED		= \x1b[41m
IGREEN		= \x1b[42m
IYELLOW		= \x1b[43m
IBLUE		= \x1b[44m
IPURPLE		= \x1b[45m
ICYAN		= \x1b[46m
IWHITE		= \x1b[47m
END			= \x1b[0m
UNDERLINE	= \x1b[4m
REV			= \x1b[7m
ERASE		= \033[2K\r

##********##
### NAME ###
##********##
NAME	= miniRT

##***************##
### COMPILATION ###
##**************###
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address -g3
CMLX	= -framework OpenGL -framework AppKit -g -lmlx -Lmlx

##*******************##
### DIRECTORY PATHS ###
##*******************##
HEADER		= ./incl/miniRT.h
MLX			= ./mlx
OBJ_PATH	= ./objs
SRC_PATH	= ./srcs

##***********##
### OBJECTS ###
##***********##
SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

##****************##
### SOURCE FILES ###
##****************##
SOURCES	=	check.c					\
			color.c					\
			cylinder.c				\
			free.c					\
			ft_ato.c				\
			ft_create.c				\
			ft_is2.c				\
			ft_is.c					\
			ft_join.c				\
			ft_malloc.c				\
			ft_split.c				\
			ft_testsplit.c			\
			ft_verif.c				\
			generator.c				\
			get_next_line_utils.c	\
			get_next_line.c			\
			get.c					\
			intersection.c			\
			main.c					\
			plan.c					\
			print.c					\
			shadow.c				\
			sphere.c				\
			strmod.c				\
			vectors.c				\
			vectorscalcul.c			\
			vectorsnotused.c		\
			windows.c				\


##*********##
### RULES ###
##*********##

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER) Makefile
			@mkdir -p objs
			@printf "$(ERASE)$(BLUE)$(UNDERLINE)Compiling:$(END)$(CYAN)$<"
			@${CC} ${CFLAGS} -c $< -o $@

all:	mlx ${NAME}

${NAME}:	${OBJS}
				@${CC} ${CFLAGS} ${CMLX} ${OBJS} -o ${NAME}
				@printf "\n$(GREEN)Successful compilation$(END)\n"

mlx:
		@make -C ${MLX}

mini:	all
		@echo "$(VIOLET)you enter an area of testing, be carefull$(END)"
		@./${NAME} scenes/test.rt

clean:
		@rm -f ${OBJS}
		@printf "\n$(BLUE)Object files cleaned\n$(DEF_COLOR)"

fclean:	clean
		@rm -f ${NAME}
		@make -C ${MLX} clean
		@printf "\n$(CYAN)Executable files cleaned\n$(END)"

re:	fclean
	@${MAKE} all
	@printf "\n$(VIOLET)Cleaned and rebuilt everything\n$(END)"

t:	all
	./miniRT scenes/test.rt

t3:	all
	./miniRT scenes/test3.rt

sus:	all
	@echo "$(IRED)           ⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀        $(END)"
	@echo "$(IRED)        ⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀     $(END)"
	@echo "$(IRED)        ⣼⣿⠋       ⢀⣀⣀⠈⢻⣿⣿⡄    $(END)"
	@echo "$(IRED)       ⣸⣿⡏   ⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄   $(END)"
	@echo "$(IRED)       ⣿⣿⠁  ⢰⣿⣿⣯⠁       ⠈⠙⢿⣷⡄ $(END)"
	@echo "$(IRED)  ⣀⣤⣴⣶⣶⣿⡟   ⢸⣿⣿⣿⣆          ⣿⣷ $(END)"
	@echo "$(IRED) ⢰⣿⡟⠋⠉⣹⣿⡇   ⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿ $(END)"
	@echo "$(IRED) ⢸⣿⡇  ⣿⣿⡇    ⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃ $(END)"
	@echo "$(IRED) ⣸⣿⡇  ⣿⣿⡇     ⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛⢻⣿⡇  $(END)"
	@echo "$(IRED) ⠸⣿⣧⡀ ⣿⣿⡇                ⣿⣿⠃  $(END)"
	@echo "$(IRED)  ⠛⢿⣿⣿⣿⣿⣇     ⣰⣿⣿⣷⣶⣶⣶⣶⠶ ⢠⣿⣿   $(END)"
	@echo "$(IRED)       ⣿⣿     ⣿⣿⡇ ⣽⣿⡏⠁  ⢸⣿⡇   $(END)"
	@echo "$(IRED)       ⣿⣿     ⣿⣿⡇ ⢹⣿⡆   ⣸⣿⠇   $(END)"
	@echo "$(IRED)       ⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁ ⠈⠻⣿⣿⣿⣿⡿⠏    $(END)"
	@echo "$(IRED)       ⠈⠛⠻⠿⠿⠿⠿⠋⠁              $(END)"
	@echo "$(WHITE)         ░█▀▀░█░█░█▀▀$(END)"
	@echo "$(WHITE)         ░▀▀█░█░█░▀▀█$(END)"
	@echo "$(WHITE)         ░▀▀▀░▀▀▀░▀▀▀$(END)"
	./${NAME} scenes/sus.rt

susleft:	all
			./${NAME} scenes/susleft.rt

susright:	all
			./${NAME} scenes/susright.rt

susup:	all
		./${NAME} scenes/susup.rt

susdown:	all
			./${NAME} scenes/susdown.rt

color:	all
		./${NAME} scenes/happycolor.rt

42:	all
		./${NAME} scenes/intheshadow.rt

front:	all
		./${NAME} scenes/front.rt
back:	all
		./${NAME} scenes/back.rt
left:	all
		./${NAME} scenes/left.rt
right:	all
		./${NAME} scenes/right.rt

.PHONY:	all clean fclean re sus mlx mini susleft susright susup susdown color 42
