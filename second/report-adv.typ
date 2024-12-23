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

#let title = "論理回路演習 後半部分 自由課題 報告書"
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

// Title row.
#align(center)[
  #block(text(textL, weight: 700, title))
  #block(text(textL, weight: 700, "キッチンタイマーの拡張・ストップウォッチの実装"))
  #v(1em, weak: true)
  2024 年 12 月 23 日
]

// Author information.
#pad(
  top: 0.5em,
  bottom: 0.5em,
  x: 2em,
  grid(
    columns: (1fr),
    gutter: 1em,
    align(center)[
      *#env.STUDENT_NAME* \
      学籍番号：#env.STUDENT_ID \
      #env.STUDENT_AFFILIATION
    ],
  ),
)

この報告書では、10 章の自由課題で制作したスケッチについて説明する。

`code05.zip` を提出した。
これを展開すると、`StopWatch` というスケッチが得られる。

== 概要

9 章で作成したキッチンタイマーを拡張したものを制作した。
主な変更は以下の通り：

- 時間を桁単位で設定できるようにした
  - 右タクトスイッチを押下することにより桁を選択することができる。
  - 選択中の桁は点滅をする
  - 上・下のタクトスイッチを押下することにより、選択された桁が増減する。
- 計れる最大時間を `99:59` に変更した
- タイマーの残り時間を砲弾型 LED に表示するようにした
  - 残り時間の割合に応じて LED が点灯する。
- ストップウォッチ機能の実装
  - 設定において `0:00` の状態でスタートボタンを押下すると、ストップウォッチとして機能するようした。
  - ストップウォッチの小数秒以下は砲弾型 LED に表示させるようにした。
  - 右タクトスイッチを押下すると、ストップウォッチは一時停止し、再度押すと再開される。
  - 左タクトスイッチを押下すると、設定に戻る。

== 実装における工夫


実装にあたってはいくつか機能を分割して関数を分けた。
以下にその概要を示す。

/ 7SegmentLED:
  / `void 7SegmentLED::setup()`:
    - 7 セグメント LED のためのピン設定などを行う。
  / `void 7SegmentLED::write_a_digit(byte digit, byte data)`:
    - 7 セグメント LED に数字 `data` を右から `digit` 桁目に 1 桁だけ表示させる。
  / `void 7SegmentLED::write_timecount(TimeCount timecount)`:
    - 7 セグメント LED に `timecount` で渡された数字を `mm:ss` 形式で表示させる。
  / `void 7SegmentLED::write_timecount_with_blink(TimeCount timecount, byte target, bool blink)`:
    - 7 セグメント LED に `timecount` で渡された数字を `mm:ss` 形式で表示させる。
    - また、`blink` が `true` であるとき、`target` で指定した桁を点滅させる。
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
/ TM1637:
  / `void TM1637::set(byte data, byte intensity)`:
    - 砲弾型 LED に光り方を指定する。
/ TimeCount:
  - 時間を管理するためのクラスである。
  - ミリ秒・秒・分を管理し、それぞれを変更できるようにしている。
  - また、対応する演算子も実装した。

== 実装できなかった部分

タイマーが減るにつれ、中央部の `:` の部分を点滅させたかったが、うまくいかなかった。
というのも、今回しようしたボード (RKE-100) では中央部分にあたる LED に配線がされていなかった。

使用されている 7 セグメント LED を特定し、その仕様書 (https://akizukidenshi.com/goodsaffix/OSL40391-XX.PDF) を読んでみたが、どうやら指定すること自体はできるようである。
