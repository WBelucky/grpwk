# grpwk

## これは何
情理B2 アルゴリズムとデータ構造Bの13班グループワーク用レポジトリです

## ファイル構成

エントリーポイントはsrc/main.c
src/ ... コードがある
obj/ ... ここに中間生成物(*.o)が置かれるようになっている

## 実行方法
```bash

# wsl上のgrpwkディレクトリに移動する
# windows側から移動するときは, windowsのファイル(win+Eとかで出るやつ)からレポジトリのファイルまで移動してCtrl+L => wsl => Enterで行くと速い
cd ...../grpwk 

# 最新のmasterブランチを実行するならpullしてくる(失敗したらgit stashとかする)
git pull origin master

# Makefileをもとにコンパイル
make

./grpwk <入力ファイル> <出力ファイル>
```
makeがないって言われたらmakeを入れてください..

### 精度のテストをする
```
make test
```
とすると, 5つのテストデータを順にテストする.

## ユニットテストをする 
bm_searchなど, 自分が制作したライブラリが間違っていないかテストする
```
make unit_test
```
でunit_testを行うようにしたい

