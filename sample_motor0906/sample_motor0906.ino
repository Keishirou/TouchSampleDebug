#define SPEED 255
#define SPEED2 122
#define MAX_LENGTH 1023
void setup() {
Serial.begin(9600);
// モーターAの制御用ピン設定
pinMode(12, OUTPUT); // 回転方向 (HIGH/LOW)
pinMode(9, OUTPUT); // ブレーキ (HIGH/LOW)
pinMode(3, OUTPUT); // PWMによるスピード制御 (0-255) こいつの値でフェーダーの動きにくさが変化
}

void loop() {
  int temp=0;
  int vr = analogRead(A2); //A2にボリューム部の2ピンを接続。1=5V,0=GND
  
  // モーターA: 正転
  digitalWrite(12, HIGH);
  digitalWrite(9, LOW);
  while(vr > (MAX_LENGTH/2.0)){ //一番端っこ(抵抗値がMAX)に行くまで正転
    vr = analogRead(A2);
   // analogWrite(3, SPEED-temp);
    analogWrite(3, SPEED2);
    temp+=10;
    Serial.println(vr);
  }

// モーターA: 正転
  digitalWrite(12, HIGH);
  digitalWrite(9, LOW);
  while(vr > 0){ //一番端っこ(抵抗値がMAX)に行くまで正転
    vr = analogRead(A2);
    analogWrite(3, SPEED);
    temp+=10;
    Serial.println(vr);
  }
  
  digitalWrite(9, HIGH); //端っこに行ったらブレーキ
  // 2秒間上記設定で回転
  delay(2000);
  temp=0;
  
  // モーターA: 逆転
  digitalWrite(12, LOW);
  digitalWrite(9, LOW);
  while(vr <1023){ //一番端っこ(抵抗値が0側。電圧が高くなるほう)に行くまで逆転
    vr = analogRead(A2);
    analogWrite(3, SPEED);
    temp+=10;
    Serial.println(vr);
  }
  digitalWrite(9, HIGH); //端っこに行ったらブレーキ
  // 2秒間上記設定で回転
  temp=0;
  delay(2000);
}
