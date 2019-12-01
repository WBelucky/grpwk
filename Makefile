# 出力する実行ファイル名
PROG = grpwk

# ソースファイルがあるディレクトリ
SRCDIR = ./src

# *.oファイルが生成される場所
DIST = ./obj

# ここにsrc以下にあるファイル名を列挙する
SRC =  main.c bm.c
CC = gcc # 使うコンパイラ

CFLAGS = -O2 -W -Wall -Wextra -Wconversion -Wshadow
LDFLAGS =

.SUFFIXES: .c

$(PROG): $(SRC:%.c=$(DIST)/%.o)
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
