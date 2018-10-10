#define SPEED1 255
#define SPEED2 122
#define MAX_LENGTH 1023
#define JITTER 6    // スライダが正しい位置に移動したかを判定する閾値

int slide;        // 受信したデータ（スライダを移動させる位置）
int speed_level;  // 指定したモータの回転速度（現在未使用）
int diff;         // 指定されたスライダの位置と現在の位置の差

void setup() {
  Serial.begin(9600);
  // モーターAの制御用ピン設定
  pinMode(12, OUTPUT); // 回転方向 (HIGH/LOW)
  pinMode(9, OUTPUT); // ブレーキ (HIGH/LOW)
  pinMode(3, OUTPUT); // PWMによるスピード制御 (0-255) こいつの値でフェーダーの動きにくさが変化？
  slide = MAX_LENGTH / 2;
}

void loop() {
  int temp = 0;
  int vr = analogRead(A2); //A2にボリューム部の2ピンを接続。1=5V,0=GND

  if (vr != slide) {
    set_deviceLength(slide,vr);
  }
  delay(10);
}

void set_deviceLength(int slide, int vr) {

  int diff;
  if (vr < slide) {
    // モーターA: 正転
    digitalWrite(12, HIGH);
    digitalWrite(9, LOW);
    analogWrite(3, SPEED1);
    diff = vr - slide;
    while (vr != slide) {
      if (-JITTER < diff && diff < JITTER) { // 一定の閾値以内であれば指定の位置まで移動したとみなす
        break;
      }
      if ( Serial.available() ) {   // 上記で制止しなかったとしても，伸縮距離が変更されているかもしれないので再度データを受信
        String str = Serial.readStringUntil(';');
        slide = str.toInt();
      }
    }
    delay(1);
    //analogWrite(3, 0);
    digitalWrite(12, LOW);
    digitalWrite(9, LOW);
  }
}
