#import "@preview/tenv:0.1.1": parse_dotenv
#import "@preview/codelst:2.0.2": sourcecode, sourcefile

#import "@preview/showybox:2.0.1":*
#let blockquote(body) = showybox(
  frame: (
    thickness: (left: 1pt),
    radius: 0pt
    ),
  par(text(size: 0pt, ""))
  + v(-1em-2.926pt)
  + body
  )

#let env = parse_dotenv(read(".env"))

#let textL = 1.8em
#let textM = 1.6em
#let fontSerif = ("Noto Serif", "Noto Serif CJK JP")
#let fontSan = ("Noto Sans", "Noto Sans CJK JP")

#let title = "論理回路演習 後半部分 報告書"
#set document(author: env.STUDENT_NAME, title: title)
#set page(numbering: "1", number-align: center)
#set text(font: fontSerif, lang: "ja")

#show heading: set text(font: fontSan, weight: "medium", lang: "ja")

#show heading.where(level: 2): it => pad(top: 1em, bottom: 0.4em, it)
#show heading.where(level: 3): it => pad(top: 1em, bottom: 0.4em, it)

// Figure
#show figure: it => pad(y: 1em, it)
#show figure.caption: it => pad(top: 0.6em, it)
#show figure.caption: it => text(size: 0.8em, it)

== 後半の演習の目的

この授業のシラバス、及び私が後半部分の演習を行った経験をもとに演習の目的について記述する。

この論理回路演習 後半部分の演習の目的は、
「実際にマイコンボードを用いてその上で動作するプログラムを作成することにより、出力信号と表示、値の取り込み、時間の計測と割り込みなどといった動作について理解する。
また、それらを組み合わせることにより複雑な動作をするものを完成させる。
加えて、データのまとめ方、レポートの書き方を学ぶ。」であると考えた。

== 器具および装置

本演習で使用した器具および装置の概要について述べる。

/ マイコンボード (RKE-100):

  本演習に用いるマイコンボードは型番 RKE-100 で、Arduino nano モジュールを中心に構成されている。
  このモジュールは、mini USB コネクタを持ち、外部のピンにほとんどの I/O が接続されている。
  本ボードには、4 桁の 7 セグメント LED、8 個の砲弾型 LED、一つの圧電サウンダ、4 つのタクトスイッチ、可変抵抗器、そして加速度センサが備わっており、多様な演習に対応できるよう設計されている。

  Arduino nano は、AVR マイコンに USB インターフェース、最低限の LED、リセットボタンを追加したモジュールであり、ほとんどのピンが外部に出ているため、様々な接続が可能である。
  このボードでは、ピン不足を補うために 2 to 4-line デコーダ (74139) を用いて 7 セグメント LED の桁選択を行い、8 個の砲弾型 LED はシリアル通信対応のドライバ IC (TM1637) を使用して接続している。
  加速度センサは I#super[2]C 接続により接続されており、シリアルバスを介した通信をサポートしている。
  圧電サウンダ、可変抵抗器、タクトスイッチは、それぞれ一対一の接続であり、直感的に理解しやすい。

  タクトスイッチの回路には、シュミットトリガインバータ、コンデンサ、抵抗が用いられ、チャタリング除去を行っている。
  これにより、スイッチ操作時の安定した入力が保証される。

/ USB ケーブル (TypeA to mini-B):

  Arduino nano と PC を接続するためのケーブルである。
  給電及び、マイコンへの書き込みに使用する。

== 本演習を行った環境

本演習を行った環境を以下に示す。

#sourcecode[```
$ cat /proc/version
Linux version 6.6.56_2 (voidlinux@voidlinux) (gcc (GCC) 13.2.0, GNU ld (GNU Binutils) 2.41) #1 SMP PREEMPT_DYNAMIC Tue Oct 15 02:54:10 UTC 2024

$ arduino-cli version
arduino-cli  Version: 1.1.0 Commit:  Date: 

$ make --version
GNU Make 4.4.1
Built for x86_64-unknown-linux-gnu
Copyright (C) 1988-2023 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
```]

指導書には Arduino IDE を用いて開発を行う方法が示されているが、
手元のパソコンではうまく動作しなかった上、慣れているエディタとの相性が悪かったため、Arduino CLI を用いてコンパイル・書き込みを行った。

また、以下に示す Makefile を用いて演習を行った。

#sourcefile(read("./Makefile"), lang: "makefile", file:"./Makefile")

なお、`make setup` で生成される `compile_flags.txt` は clangd LSP で使用されるものである。（なので本質的な部分は `compile` と `upload` である。）

また、今回の演習で提出したコードやこの報告書で示すコードは C++14 が使用できることを仮定している。
