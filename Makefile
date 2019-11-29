# 出力する実行ファイル名
PROG = grpwk

# ソースファイルがあるディレクトリ
SRCDIR = ./src

# SRCDIRディレクトリ以下にあるファイル名を書く
SRC = main.c

# *.oファイルが生成される場所
DIST = ./obj

OBJS =  $(SRC:%.c=%.o)
CC = gcc # 使うコンパイラ

# TODO: リリース時にはO2オプションをつけたい
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
test:	$(PROG)
	mkdir -p ./bin
	gcc -o ./bin/perform_test tools/perform_test.c
	for i in 0 1 2 3 4; do\
	    ./$(PROG) "data/dat$${i}_in" out.txt;\
	    ./bin/perform_test out.txt "data/dat$${i}_ref";\
	done
