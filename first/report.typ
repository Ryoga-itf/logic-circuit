#import "@preview/tenv:0.1.1": parse_dotenv

#let env = parse_dotenv(read(".env"))

#let textL = 1.8em
#let textM = 1.6em
#let fontSerif = ("Noto Serif", "Noto Serif CJK JP")
#let fontSan = ("Noto Sans", "Noto Sans CJK JP")

#let title = "論理回路演習 前半部分 報告書"
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

== この演習の目的

この授業のシラバス、及び私が前半部分の演習を行った経験をもとに演習の目的について記述する。

この論理回路演習 前半部分の演習の目的は、
「実際にロジックトレーナー、や IC を用いて回路を構成することにより、論理回路の基本的な動作・仕組みについて理解する。
また、簡単な演算回路を用いて既存の回路を拡張していく方法を学ぶ。
加えて、データのまとめ方，レポートの書き方を学ぶ。」であると考えた。

== 器具および装置

本演習で使用した器具および装置の概要について述べる。

/ ブレッドボード:

  電子回路をはんだ付けなしで試作するための基板である。
  複数の電子部品やIC（集積回路）を簡単に配置し、配線することができる。
  主に電子回路の設計やテストに使用される。
  今回の演習では基本的にこのブレッドボード上で回路を構成する。

/ IC トレーナ:

  ロジック回路やデジタル回路の基礎を学ぶための教育用装置である。
  電源やクロック回路、スイッチ、LEDインジケータなどが一体化されており、
  実験や検証が容易に行えるようになっている。
  前半部分の演習の全ての演習において必要である。

/ 標準ロジックIC:

  基本的なデジタル回路を構成するための集積回路である。
  演習では CMOS 構成の 74HC シリーズを用いた。

  / 74HC00:
    NANDゲート（否定論理積）を4つ持つICである。
  / 74HC04:
    NOTゲート（否定）を6つ持つICである。
  / 74HC08:
    ANDゲートを4つ持つICである。
  / 74HC74:
    D型フリップフロップを2つ持つICである。
  / 74HC86:
    XORゲート（排他的論理和）を4つ持つICである。
  / 74HC14:
    シュミットトリガインバータを6つ持つICである。

/ ジャンパ線:

  ブレッドボードや各電子部品のピンを接続するための導線である。

/ デジタルテスタ（デジタルマルチメータ）:
  
  電圧、電流、抵抗などの電気的な値を測定するための計測器である。
  演習においては、回路の動作確認やトラブルシューティングに使用した。

/ ラジオペンチ:

  電子工作や配線作業に使用する工具で、細かい部品のつかみや曲げ、切断が可能である。
  特に、演習においてはブレッドボードからの IC の抜き差しや、IC の足の曲げの調節、ジャンパ線の取り外しなどに使用した。

== 6 章までの演習

提出物の要件に
「報告書では 6 章までの内容については殆ど書くところが無いため、触れなくて良い」
とあるためここでは省略する。

== 7 章 4bit 右方向シフトレジスタの作成と動作確認

=== 作成したネットリスト

以下の @table1 に作成したネットリストを示す。

#show table.cell.where(y: 0): strong
#set table(
  stroke: (x, y) => if y == 0 {
    (bottom: 0.7pt + black)
  },
  align: (x, y) => (
    if x == 0 { center }
    else { left }
  )
)

#figure(
  table(
    columns: 7,
    table.header(
      [NET名;],
      [ユニット名.],
      [Pin番号],
      [ユニット名.],
      [Pin番号],
      [...],
      [...],
    ),
    [N00001;], [U1.2], [ICT_D.0], [ICT_I.4], [], [], [],
    [N00002;], [U1.5], [U1.12], [ICT_I.3], [], [], [],
    [N00003;], [U1.9], [U2.2], [ICT_I.2], [], [], [],
    [N00004;], [U2.5], [U2.12], [ICT_I.1], [], [], [],
    [N00005;], [U2.9], [ICT_I.0], [], [], [], [],
    [N00006;], [ICT_D.A], [U1.3], [U1.11], [U2.3], [U2.11], [],
    [N00007;], [VDD], [U1.1], [U1.4], [U1.10], [U1.13], [U1.14],
    [N00008;], [VDD], [U2.1], [U2.4], [U2.10], [U2.13], [U2.14],
    [N00009;], [GND], [U1.7], [U2.7], [], [], [],
  ),
  caption: "作成したネットリスト"
) <table1>

=== 作成した回路図

作成した回路図を以下の @fig1 に示す。

#figure(
  image("./diagram1.png"),
  caption: "作成した回路図"
) <fig1>

== 7 章 [3]Clock にデータスイッチを使った場合の観測

=== 発生した現象

=== 発生した現象に対する考察

== 8 章 [3]同期リセット回路の付加と動作確認

=== 作成した回路図

=== 動作確認
