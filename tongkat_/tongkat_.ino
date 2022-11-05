/* Utk parameter program
 * tone(pin, frekuensi, durasi);
 * sensor_atas(frekuensi, durasi);
 * sensor_bawah(frekuensi, durasi);
 * 
 * program multitasking millis();
 * waktu sebelum 1 => sensor_atas()
 * waktu sebelum 2 => sensor_bawah()
 */

/* waktu interval
 * durasi program 1 detik = 1000 ms
 * 
 */
 
unsigned long interval_1 = 500;
unsigned long interval_2 = 200;

// waktu awal 
unsigned long waktuSebelum_1 = 0;
unsigned long waktuSebelum_2 = 0;

// sensor atas
#define trig_atas 9
#define echo_atas 8
#define freq_atas 3000 // 3kHz frequency for tone buzzer

// sensor bawah
#define trig_bawah 7
#define echo_bawah 6
#define freq_bawah 5000 // 5kHz frequency for tone buzzer

// Pin buzer
const int buzzPin = 10;

long durasi, jarak;     // membuat variabel durasi dan jarak
long durasi1, jarak1;     // membuat variabel durasi dan jarak

void setup() {
  Serial.begin(9600);
  pinMode(buzzPin, OUTPUT);
  pinMode(trig_atas, OUTPUT);    // set pin trig menjadi OUTPUT
  pinMode(echo_atas, INPUT);     // set pin echo menjadi INPUT
  pinMode(trig_bawah, OUTPUT);
  pinMode(echo_bawah, INPUT);

}

void loop() {

  // program dibawah ini agar trigger memancarakan suara ultrasonic
  unsigned long waktuSesudah_1 = millis();
  unsigned long waktuSesudah_2 = millis();
  if((unsigned long)(waktuSesudah_1 - waktuSebelum_1) >= interval_1){
    sensor_atas(freq_atas, 90);
    waktuSebelum_1 = millis();
  }

  if((unsigned long)(waktuSesudah_2 - waktuSebelum_2) >= interval_2){
    sensor_bawah(freq_bawah, 100);
    waktuSebelum_2 = millis();
  }

//  sensor_atas(3000, 90);
//  delay(1000);
//  sensor_bawah(5000, 60);
//  delay(1000);
  
}

void sensor_atas(int frek, int durasi_buzzer) {
  digitalWrite(trig_atas, LOW);
  delayMicroseconds(80);
  digitalWrite(trig_atas, LOW);
  digitalWrite(trig_atas, HIGH);
  delayMicroseconds(80);
  delayMicroseconds(80);
  durasi = pulseIn(echo_atas, HIGH); // menerima suara ultrasonic
  jarak = (durasi / 2) / 29.1;  // mengubah durasi menjadi jarak (cm)
  Serial.print(F("Jarak Sensor 1 : "));
  Serial.print(jarak);
  Serial.println(F(" cm"));
  
  if(jarak <= 50 && jarak >=0){
//    digitalWrite(buzzPin,HIGH);
    tone(buzzPin, frek, durasi_buzzer);
//delay(60);
  } else {
    noTone(buzzPin);
//    digitalWrite(buzzPin,LOW);
//delay(60);
  }
}

void sensor_bawah(int frek, int durasi_buzzer) {
  digitalWrite(trig_bawah, LOW);
  delayMicroseconds(80);
  digitalWrite(trig_bawah, LOW);
  digitalWrite(trig_bawah, HIGH);
  delayMicroseconds(80);
  delayMicroseconds(80);
  durasi1 = pulseIn(echo_bawah, HIGH); // menerima suara ultrasonic
  jarak1 = (durasi1 / 2) / 29.1;  // mengubah durasi menjadi jarak (cm)
  Serial.print(F("Jarak 2 : "));
  Serial.println(jarak1);
  if(jarak1 <= 60 && jarak1 >= 0){
//    digitalWrite(buzzPin,HIGH);
    tone(buzzPin, frek, durasi_buzzer); 
//delay(90);
  } else {
//    digitalWrite(buzzPin,LOW);
    noTone(buzzPin);
//delay(90);
  }
}
