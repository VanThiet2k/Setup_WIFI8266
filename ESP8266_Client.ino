#include <ESP8266WiFi.h>  

const char* ssid = "??? ???";      // Tên Wi-Fi của bạn
const char* password = "?????";  // Mật khẩu Wi-Fi của bạn

WiFiClient client;

const char* serverIP = "???.???.???"; // Địa chỉ IP của server trong mạng nội bộ
int serverPort = 5000;  

void setup() {
  Serial.begin(9600);  
  WiFi.begin(ssid, password);  

  // Chờ kết nối Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi!");
}

void loop() {
  if (client.connect(serverIP, serverPort)) {  
    Serial.println("Connected to server!");

    String url = "/data?value=HelloServer";  
    client.print("GET " + url + " HTTP/1.1\r\n");
    client.print("Host: " + String(serverIP) + "\r\n");
    client.print("Connection: close\r\n\r\n");

    // Đọc phản hồi từ server Flask
    while (client.available()) {
      String response = client.readString();
      Serial.println("Server Response: ");
      Serial.println(response); 
    }

    client.stop();  
  } else {
    Serial.println("Connection failed!");  
  }

  delay(2000);  
}
