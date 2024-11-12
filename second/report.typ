#import "@preview/tenv:0.1.1": parse_dotenv

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
