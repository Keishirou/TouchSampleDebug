
#define LED 13 //13番のピンにLEDを接続

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT); //デジタルピンを出力に設定
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH); //LEDを点ける
  delay(1000); //1秒待機
  digitalWrite(LED, LOW); //LEDを消す
  delay(1000); //1秒待機

}
