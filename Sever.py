from flask import Flask, request

app = Flask(__name__)

@app.route('/data')
def receive_data():
    # Lấy giá trị từ tham số 'value' trong URL
    value = request.args.get('value')
    
    # Hiển thị giá trị nhận được
    print(f"Received value: {value}")
    
    # Trả lại thông báo cho ESP8266
    return f"Received value: {value}"

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0')
