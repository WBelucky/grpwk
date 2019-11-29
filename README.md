# grpwk

# これは何
情理B2 アルゴリズムとデータ構造Bのグループワーク用レポジトリです

# ファイル構成
とりあえずsrc以下にソースコードをおいていく

# 実行方法
```bash
cd ...../grpwk # grpwkディレクトリに移動する

make # Makefileをもとにコンパイル

./grpwk <入力ファイル> <出力ファイル>
```


# git の使い方

まずレポジトリを作ってないなら
```bash
git clone https://github.com/WBelucky/grpwk.git
```

ファイルを変更したら変更したファイルをgit に認識させる
```bash
git add 変更したファイル名かディレクトリ名
```

ファイルの更新を確定する
```bash
git commit -m "ここにコミットメッセージを書く"
```

ファイルをリモート(github.com)に上げる
ブランチ名はいま作業しているブランチ(master pushは良くない)
```bash
git push origin (ブランチ名)
```

他の人が更新したものを持ってくる
```bash
git pull origin (ブランチ名)
```

