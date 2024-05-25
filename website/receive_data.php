<?php
// รับข้อมูล POST จาก ESP32
$data = json_decode(file_get_contents("php://input"), true);

// ถ้ามีข้อมูล
if ($data) {
    // เชื่อมต่อกับฐานข้อมูล MySQL
    $conn = new mysqli("localhost", "root", "", "sensor_data");

    // ตรวจสอบการเชื่อมต่อ
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }

    // สร้างคำสั่ง SQL เพื่อเพิ่มข้อมูลลงในตาราง
    $sql = "INSERT INTO sensor_data (sensor, value) VALUES ('" . $data['sensor'] . "', '" . $data['value'] . "')";

    // รันคำสั่ง SQL
    if ($conn->query($sql) === TRUE) {
        echo "Record inserted successfully";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }

    // ปิดการเชื่อมต่อกับ MySQL
    $conn->close();
} else {
    echo "No data received";
}
?>
