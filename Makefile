# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/src
.PATH: ${.CURDIR}/src/utils
.PATH: ${.CURDIR}/src/drivers
.PATH: ${.CURDIR}/src/text 

# source code files to be compiled
SRCS = main.c \
		timer.c \
		kbc.c \
		keyboard.c \
		mouse.c \
		graphics.c \
		utils.c \
		font8x16.c \
		text_renderer.c \
		backbuffer.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -O3

# list of library dependencies
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
