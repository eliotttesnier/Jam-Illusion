##
## EPITECH PROJECT, 2024
## Rush 3
## File description:
## Makefile
##

.PHONY: all clean fclean re coverage test_run tests_run

# Couleurs ANSI
GREEN=\033[1;32m
BLUE=\033[1;34m
RED=\033[1;31m
YELLOW=\033[1;33m
NC=\033[0m

SRC =   src/main.cpp					\
		src/Game.cpp					\
		src/Player.cpp					\
		src/MainMenu.cpp				\
		src/PauseMenu.cpp				\
		src/Object.cpp					\
		src/dialogueLoader.cpp			\
		src/pnj.cpp						\
		src/rooms/Room.cpp				\
		src/rooms/Exterior.cpp			\
		src/rooms/FirstRoom.cpp			\
		src/rooms/SecondRoom.cpp		\
		src/rooms/ThirdRoom.cpp			\
		src/rooms/FourthRoom.cpp		\
		src/rooms/Final.cpp			\

OBJ = $(SRC:.cpp=.o)

TEST_SRC =  tests/tests.cpp

INCLUDES = -I./src/ -I./src/rooms/

CFLAGS =	-std=c++20 -Wall -Wextra -Werror -Wno-unused-parameter \
			-Wno-unused-variable

LIBS =  -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio \
		-lsfml-network

NAME =  Game

CC = g++

all: $(NAME)

$(NAME): $(OBJ)
	@echo -e "$(BLUE)ᒥ🔧ᒧ Compilation de $(NAME)...$(NC)"
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(INCLUDES) $(LIBS)
	@echo -e "$(GREEN)ᒥ✅ᒧ Compilation terminée avec succès !$(NC)"

%.o: %.cpp
	@echo -e "$(YELLOW)ᒥ🚀ᒧ Compilation de $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@echo -e "$(RED)ᒥ🔥ᒧ Suppression des fichiers objets...$(NC)"
	@rm -rf $(OBJ)
	@rm -rf $(OBJ_MAIN)
	@echo -e "$(GREEN)ᒥ✅ᒧ Clean terminé !$(NC)"

fclean: clean
	@echo -e "$(RED)ᒥ🔥ᒧ Suppression de $(NAME)...$(NC)"
	@rm -rf $(NAME)
	@rm -rf unit_tests
	@rm -rf *.gcno
	@rm -rf *.gcda
	@rm -rf vgcore.*
	@echo -e "$(GREEN)ᒥ✅ᒧ Full clean terminé !$(NC)"

re: fclean all

coverage: test_run
	@echo -e "$(BLUE)ᒥ📊ᒧ Génération du rapport de couverture...$(NC)"
	@gcovr
	@echo -e "$(GREEN)ᒥ✅ᒧ Rapport généré !$(NC)"

test_run: $(OBJ)
	@echo -e "$(BLUE)ᒥ🧪ᒧ Compilation des tests...$(NC)"
	@gcc -o unit_tests $(SRC) $(TEST_SRC) $(CFLAGS) $(INCLUDES) \
		--coverage -lcriterion
	@echo -e "$(GREEN)ᒥ✅ᒧ Tests compilés ! Lancement...$(NC)"
	@./unit_tests

tests_run: test_run
