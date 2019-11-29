# grpwk

## これは何
情理B2 アルゴリズムとデータ構造Bのグループワーク用レポジトリです

## ファイル構成
src/ ... コードがある
obj/ ... ここに中間生成物(*.o)が置かれるようになっている

## 実行方法
```bash

# grpwkディレクトリに移動する
cd ...../grpwk 

# 最新のmasterブランチを実行するならpullしてくる(失敗したらgit stashとかする)
git pull origin master

# Makefileをもとにコンパイル
make

./grpwk <入力ファイル> <出力ファイル>
```


## git の使い方

まずレポジトリを作ってないなら
```bash
git clone https://github.com/WBelucky/grpwk.git
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

他の人が更新したものを持ってくる
```bash
git pull origin ブランチ名
```





