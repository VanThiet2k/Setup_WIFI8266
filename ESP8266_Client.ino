#include <ESP8266WiFi.h>  // Dùng cho ESP8266

const char* ssid = "Phòng IT";      // Tên Wi-Fi của bạn
const char* password = "Year2000.com.vn";  // Mật khẩu Wi-Fi của bạn

WiFiClient client;

const char* serverIP = "192.168.0.198"; // Địa chỉ IP của server trong mạng nội bộ
int serverPort = 5000;  // Cổng server (Flask mặc định 5000)

void setup() {
  Serial.begin(9600);  // Khởi tạo Serial
  WiFi.begin(ssid, password);  // Kết nối vào Wi-Fi

  // Chờ kết nối Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi!");
}

void loop() {
  if (client.connect(serverIP, serverPort)) {  // Kết nối tới server Flask
    Serial.println("Connected to server!");

    String url = "/data?value=HelloServer";  // Tạo URL yêu cầu HTTP
    client.print("GET " + url + " HTTP/1.1\r\n");
    client.print("Host: " + String(serverIP) + "\r\n");
    client.print("Connection: close\r\n\r\n");

    // Đọc phản hồi từ server Flask
    while (client.available()) {
      String response = client.readString();
      Serial.println("Server Response: ");
      Serial.println(response);  // Hiển thị phản hồi từ Flask
    }

    client.stop();  // Đóng kết nối HTTP
  } else {
    Serial.println("Connection failed!");  // In lỗi nếu không kết nối được
  }

  delay(2000);  // Đợi 2 giây trước khi thử lại
}
