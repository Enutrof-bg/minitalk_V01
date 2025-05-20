# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 10:20:51 by kevwang           #+#    #+#              #
#    Updated: 2025/05/19 10:20:54 by kevwang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra

CLIENT = client.o
SERVER = server.o
UTILS = utils.o

FILE1 = server.c utils.c
FILE2 = client.c utils.c

OBJ1 = ${FILE1:.c=.o}
OBJ2 = ${FILE2:.c=.o}

EXEC = exec

all:${EXEC}

${EXEC}: ${OBJ1} ${OBJ2}
	${CC} ${CFLAGS} ${OBJ1} -o server
	${CC} ${CFLAGS} ${OBJ2} -o client
		

%.o:%.c
	${CC} ${CFLAGS} -c $<

clean :
	rm -f client.o server.o utils.o

fclean: clean
	rm -f client server
	
re: fclean
	make