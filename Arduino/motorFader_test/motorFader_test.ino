#define SENSOR 0 //センサがつながっているピン

#define SPEED1 240  // スライダを縮める場合
#define SPEED2 170  // スライダを高速で動かす場合（これが最高速）
#define JITTER 10    // スライダが正しい位置に移動したかを判定する閾値

int slide=0;        // 受信したデータ（スライダを移動させる位置）
int speed_level;  // 指定したモータの回転速度（現在未使用）
int diff;         // 指定されたスライダの位置と現在の位置の差
int slide_old;
int slide_temp;

void setup() {
  Serial.begin(9600);
  // モーターAの制御用ピン設定
  pinMode(12, OUTPUT); // 回転方向 (HIGH/LOW)
  pinMode(9, OUTPUT); // ブレーキ (HIGH/LOW)
  pinMode(3, OUTPUT); // PWMによるスピード制御 (0-255)
}

void loop() {

  int vr = analogRead(A2); //A2にボリューム部の2ピンを接続。1=5V,0=GND
  slide_temp = analogRead(0)*5; //センサから値を読み込む(0~1023)

if((slide - slide_old < JITTER)&&(slide - slide_old > -JITTER)){
  slide = slide_temp;
}

//  if ( Serial.available() ) {//受信の有無
//   String str = Serial.readStringUntil(';');//1bit以上の情報を通信
//    slide = str.toInt();//intに変換
//    //slide =  Serial.read();
//  }
  Serial.println(slide);
  if (slide >= 0) {
    slide_device();
  } else {
    //speed_change(slide);
  }

 int v = analogRead(A2);

 slide_old = slide;
 //Serial.println(v);
/*
  // モーターA: 正転
  digitalWrite(12, HIGH);
  digitalWrite(9, LOW);


  while (vr > 0) { //一番端っこ(抵抗値がMAX)に行くまで正転
    vr = analogRead(A2);
    analogWrite(3, 120);
    Serial.println(vr);
  }
  digitalWrite(9, HIGH); //端っこに行ったらブレーキ
  // 2秒間上記設定で回転
  delay(2000);


  // モーターA: 逆転
  digitalWrite(12, LOW);
  digitalWrite(9, LOW);
  while (vr < 1023) { //一番端っこ(抵抗値が0側。電圧が高くなるほう)に行くまで逆転
    vr = analogRead(A2);
    analogWrite(3, 120);
    Serial.println(vr);
  }
  digitalWrite(9, HIGH); //端っこに行ったらブレーキ
  // 2秒間上記設定で回転
*/

//delay(2000);
}

/*スライダの位置を決める*/
void slide_device(){
  int vr = analogRead(A2); //A2にボリューム部の2ピンを接続。1=5V,0=GND
  
  if(vr > slide){     // モーターA: 正転
    digitalWrite(12, HIGH);
    digitalWrite(9, LOW);
    analogWrite(3, SPEED1);
    
    while(vr > slide){    // 受信したデータよりスライダの位置が大きい場合
      vr = analogRead(A2);
      diff = vr - slide;
      if(-JITTER < diff && diff < JITTER){  // 一定の閾値以内であれば指定の位置まで移動したとみなす
        break;
      }
      if ( Serial.available() ) {   // 上記で制止しなかったとしても，伸縮距離が変更されているかもしれないので再度データを受信
        String str = Serial.readStringUntil(';');
        slide = str.toInt();
      }
      delay(1);
    }  
    digitalWrite(9, HIGH);
  }else if(vr < slide){     // モーターA: 逆転 
    digitalWrite(12, LOW);
    digitalWrite(9, LOW);
    analogWrite(3, SPEED2);
   
   while(vr < slide){    // 受信したデータよりスライダの位置が小さい場合
      vr = analogRead(A2);
      int diff = vr - slide;
      if(-JITTER < diff && diff < JITTER){  // 一定の閾値以内であれば指定の位置まで移動したとみなす
        break;
      }
      if ( Serial.available() ) {   // 上記で制止しなかったとしても，伸縮距離が変更されているかもしれないので再度データを受信
        String str = Serial.readStringUntil(';');
        slide = str.toInt();
      }
      delay(1);
    }
    digitalWrite(9, HIGH); 
  }
}

/*speedを変える（動的な変更はできてない）*/
void speed_change(int speedFlag){
  if(speedFlag == -1){
    speed_level = SPEED1;
  }else if(speedFlag == -2){
    speed_level = SPEED2;
  }
  analogWrite(3, speed_level);
}
