#include <SoftwareSerial.h>

SoftwareSerial SIM900A(3, 4); // RX, TX
String smsContent = ""; // Biến lưu nội dung SMS

void setup() {
  SIM900A.begin(9600);
  Serial.begin(9600);

  Serial.println("SIM900A Ready");
  delay(1000);

  // Cấu hình SIM900A
  SIM900A.println("AT");
  delay(500);
  SIM900A.println("AT+CMGF=1"); // Text Mode
  delay(500);
  SIM900A.println("AT+CNMI=2,2,0,0,0"); // Nhận SMS ngay
  delay(1000);

  pinMode(13, OUTPUT); // <-- Khai báo chân LED
  digitalWrite(9, LOW); // LED ban đầu tắt
}

void loop() {
  if (SIM900A.available()) {
    char c = SIM900A.read();
    smsContent += c;
    Serial.print(c);
    
    // Khi đọc hết tin nhắn (dấu xuống dòng '\n')
    if (c == '\n') {
      // Kiểm tra nếu smsContent chứa "LEDON"
      if (smsContent.indexOf("LEDON") >= 0) {
        digitalWrite(9, HIGH);
        Serial.println("=> Da bat den LED!");
      } 
      else if (smsContent.indexOf("LEDOFF") >= 0) {
        digitalWrite(9, LOW);
        Serial.println("=> Da tat den LED!");
      } 
      
      smsContent = ""; // Xóa biến để chuẩn bị đọc tin mới
    }
  }
}