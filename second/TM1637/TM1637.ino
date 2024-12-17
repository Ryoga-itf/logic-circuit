// TM1637 用定数
const byte LCLK = 14, DIO = 12; // LED Driver 用 Clock, Data I/O pin
const byte Mode =  0b01000100;  // 固定アドレスモード
const byte ADR =   0b11000000;  // 1桁目アドレス

// Pulse width の設定(下位3bit) 、仕様書(5 Page) Display controlを参照
const byte Dcont[] = {0b10001111, // 14/16
                      0b10001110, // 13/16
                      0b10001101, // 12/16
                      0b10001100, // 11/16
                      0b10001011, // 10/16
                      0b10001010, //  4/16
                      0b10001001, //  2/16
                      0b10001000  //  1/16
                     };

const byte halfCLK = 10;        // TM1637 への送信用クロックの半周期の長さをμsで指定

void setup() {
  // 初期設定は何も無し
  // pinMode は送信時に指定
}

void loop() {
  static byte data8 = 0b11000001; // 点灯パターン
  byte LSB;                       // シフトアウトされる最下位ビットをとっておくため

  static unsigned long lastShift; // 最後にシフトした時間
  unsigned long now;              // 現在時刻
  static byte i;                  // 明るさを指定するためのインデックス

  // 0.2 秒毎に data8 を左ローテイトして 8 個の砲弾型LEDに表示
  now = millis();                 // 現在時刻を得る
  if (now - lastShift > 200 ) {    // 最後にシフトしてから 0.2 秒経っていれば
    LSB = data8 & 0b00000001;     // LSB を保存しておいて

    // byte は符号無しなので、>> は論理シフトになる。一応注意は必要
    data8 = (data8 >> 1) |        // シフトして
            (LSB << 7);           // LSB を MSB にして戻す

    lastShift = now;              // シフトした時刻を記録

    // TM1637 に点灯パターンを送って表示
    // この IC は送信した瞬間だけではなく常時表示し続ける
    LED8_SET(data8, Dcont[i]);
    i = (i + 1) % 8;              // i は 0 ～ 8
  }

  delay(1);
}

void LED8_SET(byte data, byte intensity) {
  S();
  writeS_Byte(Mode);
  E();

  // 5mm LED 点灯パターンの送信
  S();
  writeS_Byte(ADR);
  writeS_Byte(data);
  E();

  S();
  writeS_Byte(intensity);
  E();
}

// 以下
// pinMode(ピン番号 , INPUT) で HIGH
// pinMode(ピン番号 , INPUT) で LOW
// TM1637 と通信する線には pull up 抵抗があるため

//スタート コンディション
// TM1637に command 送信 開始 を示す
void S()
{
  pinMode(LCLK, INPUT);
  delayMicroseconds(halfCLK);
  pinMode(DIO, INPUT);
  delayMicroseconds(halfCLK);
  pinMode(DIO, OUTPUT);
  delayMicroseconds(halfCLK);
}

//エンド コンディション
// TM1637に command 送信 終了 を示す
void E()
{
  pinMode(DIO, OUTPUT);
  delayMicroseconds(halfCLK);
  pinMode(LCLK, INPUT);
  delayMicroseconds(halfCLK);
  pinMode(DIO, INPUT);
  delayMicroseconds(halfCLK);
}

// write Serial Byte
// 1 バイト シリアル送信する
bool writeS_Byte(byte b)
{
  byte data = b;

  // 1バイトデータ
  for (byte i = 0; i < 8; i++) {
    // データの送信はクロックがLOWの時に行う
    // pinMode で OUTPUT にすると、Arduino の仕様では、
    // その pin は LOW になる
    pinMode(LCLK, OUTPUT);
    delayMicroseconds(halfCLK);

    // ビットセット
    if (data & 0b00000001) // AND を取って LSB の値を検出する。
      pinMode(DIO, INPUT);
    else
      pinMode(DIO, OUTPUT);

    delayMicroseconds(halfCLK);

    // CLK high　1ビットのデータの区切り
    // pinMode で INPUT にすると、Arduino の仕様では、
    // その pin はハイインピーダンスになる。
    // 途中 pull-up 抵抗が入っているので、この線は HIGH になる。
    pinMode(LCLK, INPUT);
    delayMicroseconds(halfCLK);

    // 1 bit 右シフトして LSB を更新する。
    data = data >> 1;
  }

  // ACK信号待ち
  pinMode(LCLK, OUTPUT);
  pinMode(DIO, INPUT);
  delayMicroseconds(halfCLK);

  // CLKをHIGHにすることでACK解除
  pinMode(LCLK, INPUT);
  delayMicroseconds(halfCLK);
  byte ack = digitalRead(DIO);

  if (ack == 0)
    pinMode(DIO, OUTPUT);

  delayMicroseconds(halfCLK);
  pinMode(LCLK, OUTPUT);
  delayMicroseconds(halfCLK);

  return ack;
}
