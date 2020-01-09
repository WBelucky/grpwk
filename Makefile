ARG = 
# 出力する実行ファイル名
PROG = grpwk

# ソースファイルがあるディレクトリ
SRCDIR = ./src

# *.oファイルが生成される場所
DIST = ./obj

# ここにsrc以下にあるファイル名を列挙する
SRC =  main.c solve.c KMP.c bm.c markov.c bitap.c

# 使うコンパイラ
CC = gcc

# コンパイルオプション
CFLAGS = -O2 -W -Wall -Wextra -Wconversion -Wshadow
LDFLAGS = -O2

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
	    ./$(PROG) "data/dat$${i}_in" out.txt $(ARG);\
	    ./bin/perform_test "data/dat$${i}_in" out.txt "data/dat$${i}_ref";\
	done

unit_test:
	mkdir -p ./bin
	gcc -o ./bin/bm_test src/bm_test.c src/bm.c
	./bin/bm_test
13.tar: grpwk
	mkdir -p ./13
	cp -r src ./13
	cp Makefile ./13
	cp README_FOR_SUBMIT.md ./13
	tar -cvf 13.tar ./13
markov_test:
	g++ -o ./bin/markov_data ./tools/markov.cpp
	cat data/dat0_ref | ./bin/markov_data 7 1 > ./src/markov.txt
	gcc -o ./bin/markov_test src/markov.c src/markov_test.c
	./bin/markov_test
