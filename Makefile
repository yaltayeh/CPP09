NAME = CPP09

BUILD_DIR = build

FILES = main.cpp \

CC = c++
CFLAGS = -Wall -Wextra -Werror -MMD -std=c++98

OFILES = ${FILES:%.cpp=$(BUILD_DIR)/%.o}
DFILES = ${OFILES:%.o=$(BUILD_DIR)/%.d}

all: $(NAME)

$(NAME): $(OFILES)
	$(CC) $^ -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OFILES) $(DFILES) $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DFILES)