//ボタン関連のテストコード

#define LED 13 //13番のピンにLEDを接続
#define BUTTON 7 //7番のピンにボタンを接続
#define FADE_LED 9 //9番のピンにLEDを接続

#define SENSOR 0 //センサがつながっているピン

int val = 0; //入力ピンの状態
int val_old = 0; //valの前の状態
int state = 0; //LEDの状態
int i;

int brightness = 128; //明るさの値を保存
unsigned long startTime = 0; //押し始める時間保存

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//毎秒9600bitでシリアルポート開放
  //pinMode(LED, OUTPUT); //LEDを接続したピンを出力に設定
  //pinMode(BUTTON, INPUT); //BUTTONを接続したピンを入力に設定
  pinMode(FADE_LED, OUTPUT); //LEDを接続したピンを出力に設定
}

void loop() {
  // put your main code here, to run repeatedly:
  //Pushing_LED(LED,BUTTON); //ボタンが押されている間，LEDを点灯する
  //Switching_LED(LED,BUTTON); //ボタンが押されると，LEDを点灯する
  //Fade_LED(FADE_LED); //フェイドイン&アウト
  //SwitchAndFade_LED(FADE_LED,BUTTON); //ボタンを押すと点灯，押してる長さで明るさ調整
  LightSensor_LED(FADE_LED); //光センサを用いてLEDの明るさを調節
  /*analogWrite(FADE_LED, 255);
  delay(500);
  analogWrite(FADE_LED, 128);
  delay(500);
  analogWrite(FADE_LED, 0);
  delay(500);
  */
}


void Pushing_LED(int Led,int Button){
  val = digitalRead(Button); //BUTTONのピンからの入力をvalに保存

/*入力がHIGHなら点灯*/
  if(val == HIGH){
  digitalWrite(Led, HIGH); //LEDを点ける  
  }else{
  digitalWrite(Led, LOW); //LEDを消す  
  }
}


void Switching_LED(int Led,int Button){
  val = digitalRead(Button); //BUTTONのピンからの入力をvalに保存

/*val前の状態と比較して異なっていたら，状態を変更*/
  if(val != val_old){
    state = 1 - state;
    delay(10);
  }

/*前の状態を保存*/
  val_old = val;

/*入力がHIGHならstateを変更*/
/*  if(val == HIGH){
  state = 1 - state;
  }
*/
  if(state == 1){
    digitalWrite(Led, HIGH); //LEDを点ける 
  }else{
    digitalWrite(Led, LOW); //LEDを消す  
  }
}

void Fade_LED(int Led){
  /*フェードイン*/
  for(i = 0; i < 255; i++ ){
    analogWrite(Led, i);
    delay(10);
  }

 /*フェードアウト*/
  for(i = 255; i > 0; i-- ){
    analogWrite(Led, i);
    delay(10);
  }
}

void SwitchAndFade_LED(int Led,int Button){
   val = digitalRead(Button); //BUTTONのピンからの入力をvalに保存

 /*val前の状態と比較して異なっていたら，状態を変更*/
  if(val != val_old){
    state = 1 - state;
    startTime = millis(); //ボードがリセットされてからの時間をmsで保存
                         //最後にボタンが押された時間を記録
    delay(10);
  }

 /*ボタンが押し続けられているかをチェック*/
 if((val == HIGH)&&(val_old == HIGH)){
  //500ms押されているかどうか
  if(state == 1 &&(millis() - startTime) > 500){
    brightness++; //明るさを1づつ上昇
    delay(10);
    if(brightness > 255){ //255を超えたらリセット
      brightness = 0;
    }
  }
 }

 /*前の状態を保存*/
  val_old = val;

  if(state == 1){
    analogWrite(Led, brightness); //LEDを設定した明るさで点ける 
  }else{
    digitalWrite(Led, 0); //LEDを消す  
  }
   
}

void LightSensor_LED(int Led){
  val = analogRead(0); //センサから値を読み込む(0~1023)

 /*点滅の周期をセンサの値で決める*/
  /*digitalWrite(Led, HIGH); //LEDを点ける 
  delay(val);

  digitalWrite(Led, LOW); //LEDを消す 
  delay(val);*/

  /*明るさをセンサの値で決める*/
  analogWrite(Led, val/4);

  /*センサの値を送信*/
  Serial.println(val);
  
  delay(10);

  //delay(100);
  
}

