gcc -fsanitize=address -I /usr/local/include *.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework Appkit -g ; ./a.out