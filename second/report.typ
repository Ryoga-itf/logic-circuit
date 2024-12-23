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
  圧電サウンダ、可変抵抗器、タクトスイッチは、それぞれ一対一の接続である。

  タクトスイッチの回路には、シュミットトリガインバータ、コンデンサ、抵抗が用いられ、チャタリング除去を行っている。
  これにより、スイッチ操作時の安定した入力が保証される。

/ USB ケーブル (A to mini-B):

  Arduino nano と PC を接続するためのケーブルである。
  マイコンへの給電及び、書き込みに使用する。

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

== 8 章までの演習

提出物の要件に
「7 章までの内容はこの報告書に含めなくても良い」
とあるためここでは省略する。

なお、指導書にはこのようにあるが、特に、8 章の内容について提出物の要件は無かった上、おおよそ「8 章まで」の誤字であると考えられるため、この報告書には含めない。

== 9 章 総合課題

本章では簡易的なキッチンタイマーを作成した。
この演習の立ち会い検査において合格をもらったため、作成したキッチンタイマーは正しく動作しており、適切に演習に取り組めたと考えている。

=== 作成したキッチンタイマーについて

指導書に示された仕様をもとに制作した。以下にそれを引用する。

#set enum(numbering: "(a)")

#blockquote[
  + 秒を単位として時間を保持する”timecount”変数を持つ。
  + “timecount”の初期値は 0 である。
  + “timecount”の値は分・秒の形に変換し、常時 4 桁の 7 segment LED に表示する。最大 59 分 59 秒まで表示できるものとする。
  + 時間設定モードとカウントダウンモードとビープ(音出し)モードを持ち、モード切替用として定義した特定のタクトスイッチと”timecount”の値によってモードが切り替わる。初期値は時間設定モードである。
  + 時間設定モードかつ “timecount” の値が 0 でない時にモード切替用スイッチを押すとカウントダウンモードになる。
  + カウントダウンモード中にモード切替用スイッチを押すと時間設定モードになる。
  + 時間設定モードとビープ(音だし)モードでは”timercount”は自動的には変化しない。
  + 時間設定モードでは、加算に対応したタクトスイッチを押したときに ”timecount” の値を 1 秒に相当する分だけ加算し、減算に対応したタクトスイッチを押したときに ”timecount” の値を 1 秒に相当する分だけ減算する。
  + 上記(h)の操作の時タクトスイッチを 1 秒ほど押し続けるとキーリピートを開始し、高速に”timecount”の値を変化させることができる。
  + カウントダウンモードでは時間の加減算に対応したスイッチを押しても“timecount”の値は変化しない。
  + カウントダウンモードでは“timecount"は、割り込みによって起動される関数中で、実時間に対応する分だけ減算され、0 になったら止まる。
  + カウントダウンモードで”timecount”が 0 になったらビープ(音出し)モードになる。
  + 音を出し終わったら、自動的に時間設定モードになる。図 17. に上記の仕様のキッチンタイマーの状態遷移の概要を示す。明示的に定義された状態は三つであるが、”timecount”をインクリメント・デクリメントする二つの状態を加え、時間設定モードから遷移すると考えると製作しやすい。

  (指導書 9 章総合課題の仕様より引用)
]

また、タクトスイッチへの機能割当については以下のようにした。
なお、この割当の図についてはソースコード中にコメントで示したものを引用している。

#sourcecode[```
/*
 *             keyUp (A6)
 *                 |
 *                 o
 * keyMode (A2)--o   o-- *none* (A3)
 *         (16)    o            (17)
 *                 |
 *            KeyDown (A7)
 */
```]

より具体的に書くと以下の通り：

/ タクトスイッチ上: 設定において加算に対応するスイッチ
/ タクトスイッチ下: 設定において減算に対応するスイッチ
/ タクトスイッチ右: 割当はない
/ タクトスイッチ左: モード切替用スイッチ

操作方法については、前述した仕様の通りである。

=== 実装における工夫

実装にあたってはいくつか機能を分割して関数を分けた。
以下にその概要を示す。

/ 7SegmentLED:
  / `void 7SegmentLED::setup()`:
    - 7 セグメント LED のためのピン設定などを行う。
  / `void 7SegmentLED::write_a_digit(byte digit, byte data)`:
    - 7 セグメント LED に数字 `data` を右から `digit` 桁目に 1 桁だけ表示させる。
  / `void 7SegmentLED::write_timecount(unsigned int timecount)`:
    - 7 セグメント LED に `timecount` で渡された数字を `mm:ss` 形式で表示させる。
  / `void 7SegmentLED::clear()`:
    - 7 セグメント LED の表示を消す。
/ KeyRepeat:
  / `KeyRepeat::KeyRepeat(uint8_t pin, time_type delay_ms, time_type interval_ms, bool isAnalogPin = false)`:
    - `KeyRepeat` クラスのコンストラクタである。スイッチの入力に対してキーリピート（一定間隔で連続的に動作させる機能）を実装するためのものである。
    - 引数 `pin` で指定されたピン番号を制御対象とする。
    - 引数 `delay_ms` 初回のキーリピートが発生するまでの遅延時間（ミリ秒単位）を指定する。
    - 引数 `interval_ms` キーリピートが発生する間隔時間（ミリ秒単位）を指定する。
    - 引数 `isAnalogPin` は制御対象のピンがアナログピンかどうかを指定する。デフォルト値は `false` であり、`true` を指定するとアナログピンとして扱われる。
  / `void KeyRepeat::setup()`:
    - キーリピートのためのピン設定などを行う。
  / `int KeyRepeat::read()`:
    - 状態を返す関数である。
    - 押されていない場合、`0` を返す。
    - 初回に押された場合、`1` を返す。
    - キーリピートにより押されたと判定された場合は `2` を返す。

詳細な実装についてはソースコードを参照。
なお、`7SegmentLED` に該当するコードは `7SegmentLED.hpp` 及び `7SegmentLED.cpp`、
`KeyRepeat` に該当するコードは、`KeyRepeat.hpp` 及び `KeyRepeat.cpp` である。

`7SegmentLED` の実装は `TimerOne.h` の `Timer1` を参考にした。

また、実装において以下のような点を工夫した。

- `#define` ではなく `constexpr` 修飾を使用し、型が付くようにした。
- クラスとして分けることにより、まとまりを良くした。特にキーリピートについては再利用できるようになった。
- `enum` ではなく `enum class` を使用することにより、モダンな形式で書けるようにした。また間違えにくくなった。
- `Timer1` の `attachInterrupt` の引数をラムダ関数を用いて記述することにより、冗長さを無くした。
