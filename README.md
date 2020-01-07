# grpwk

## これは何
情理B2 アルゴリズムとデータ構造Bの13班グループワーク用レポジトリです

## ファイル構成

エントリーポイントはsrc/main.c
src/ ... コードがある
obj/ ... ここに中間生成物(\*.o)が置かれるようになっている

## 実行方法
```bash

# wsl上のgrpwkディレクトリに移動する
# windows側から移動するときは, windowsのファイル(win+Eとかで出るやつ)からレポジトリのファイルまで移動してCtrl+L => wsl => Enterで行くと速い
cd ...../grpwk 

# 最新のmasterブランチを実行するならpullしてくる(失敗したらgit stashとかする)
git pull origin master

# 精度のテストをする
make test

```
makeがないって言われたらmakeを入れてください..

### 単体で実行(本番はこれ)
```
# Makefileをもとにコンパイル
make

# 実行
./grpwk <入力ファイル> <出力ファイル>
```
とすると, 5つのテストデータを順にテストする.

### 方法を変えて検証する(ポスターを書く時とかに活かしてほしい)
```
make test ARG="--search-limit 9000 --search-method SIMPLE_BM --remaining FILL_WITH_A"
```
などとして引数をあたえることで, 探索方法などを変えて実行できる. 現在は
--search-limit, --search-method, --markov の3つのオプションがある.

* --search-limit
    バラバラ文字列郡sを虫食い文字列tに当てはめてxを埋めていくが, 40000個あるすべての文字を当てはめていっても時間がかかるだけ(sが1文字の時などはどこにでもマッチしてしまって, 正しくならない.)
    よって, 文字列郡sを降順ソートしてある個数になるまでtに当てはめていくが, "--search-limit value" で指定された値valueになるとパターンマッチをやめて, 残りのxを適当に埋めるパートに入る.
    デフォルト値は12500
* --search-method
    上記の方法でバラバラ文字列郡sを使って虫食い文字列tを埋めていく時に使用する探索方法. "--search-method method-name"としたときのmethod-nameによって処理を分岐する.
    method-nameに入りうるは次の3つ. SIMPLE_BM, KMP, MULTIMATCH_BMである.
    * SIMPLE_BM
    単純なbm(boyer-moore search)法を実行する, sそれぞれに対して前から探索していって, tのはじめにマッチした部分に挿入する.
    * KMP
    単純なKMP法を実行する, Shinさんが作ってくれた.
    * MULTIMATCH_BM
    デフォルト. bm法を実行するが, あるsをtのはじめにマッチした部分に挿入するのではなく, sがマッチしうるtのすべての箇所を比較し, その中で不確定文字xが一番少ないところにマッチする.
* --remaining
    今まで述べた方法でsをtに当てはめていくが, どうしても確定できない部分が存在する. その部分を適当な方法で埋める.
    現在3つの方法 FILL_WITH_A, MARKOV1, MARKOV3がある.
    * FILL_WITH_A
    xを全部aで埋める
    * MARKOV1
    前後1文字を考慮したマルコフ則を考慮. これがデフォルト
    * MARKOV3
    前後3文字(tools/markov.cppをいじればソレ以上も可)を考慮したマルコフ則で埋める. あんま精度上がらない
### ユニットテストをする 
bm_searchなど, 自分が制作したライブラリが間違っていないかテストする
```
make unit_test
```
でunit_testを行うようにしたい

### 提出ファイル作成方法
```bash
make 13.tar
```
で提出ファイルである13.tarを生成します
### 機能追加の方法

#### このレポジトリの開発方針
まず, masterブランチは常に動くようにしたいので, masterブランチへの直接pushは控える.
機能追加する際は, `git checkout -b ブランチ名`などでmasterブランチから自分のブランチを切り出して, そこで作業する.

作業が終了したら, github.comのこのレポジトリのページから作業ブランチからmasterブランチへのpull requestを送る.
それを誰かにレビューしてもらってマージする.

#### C言語ファイル追加の方法
c言語ファイルを追加するときは, .cファイルとそれに対応した.hファイルを用意する.
例えばhoge.cを作るときはhoge.hも作る. .hファイルのほうに関数定義や構造体定義をして, その実装を.cファイルでやる.

また, ファイルを追加したときは, MakefileのSRCに空白区切りで追加したファイルを列挙する.

## git の使い方

まずレポジトリを作ってないなら
```bash
git clone https://github.com/WBelucky/grpwk.git
```

他の人が更新したものを持ってくる
```bash
git pull origin ブランチ名
```

自分のブランチを作ってそこに移動する
```
git checkout -b 作るブランチ名
```

ブランチを移動する
```
git checkout ブランチ名
```

ファイルを変更したら変更したファイルをgit に認識させる
```bash
git add 変更したファイル名かディレクトリ名
```

ファイルの更新を確定する
```bash
git commit -m "ここにコミットメッセージを書く(~~を修正, 追加とか)"
```

ファイルをリモート(github.com)に上げる
ブランチ名はリモートに上げるブランチ(masterブランチに直接pushは良くない)
```bash
git push origin ブランチ名
```
