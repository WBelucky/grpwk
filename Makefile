PROG = grpwk # 出力する実行ファイル名

SRCDIR = ./src

# SRCDIRディレクトリ以下にあるファイル名を書く
SRC = main.c

DIST = ./obj

OBJS =  $(SRC:%.c=%.o)
CC = gcc # 使うコンパイラ
CFLAGS = -W -Wall -Wextra -Wconversion -Wshadow
LDFLAGS = 

.SUFFIXES: .c

$(PROG): $(DIST)/$(OBJS)
	$(CC) $(LDFLAGS) -o $(PROG) $^
# $< は
$(DIST)/%.o: $(SRCDIR)/%.c
	mkdir -p $(DIST)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm  $(OBJS) $(PROG)
