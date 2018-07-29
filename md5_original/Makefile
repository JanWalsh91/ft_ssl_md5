NAME := md5

all: $(NAME)

$(NAME):
	gcc -I./ md5.c mddriver.c -DMD=5 -o $(NAME)
	@echo "$(NAME) compiled"

clean:
	@rm -f $(NAME)