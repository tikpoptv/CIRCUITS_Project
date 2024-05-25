<?php
// กำหนดข้อมูลการเชื่อมต่อฐานข้อมูล
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "sensor_data";

// สร้างการเชื่อมต่อฐานข้อมูล
$conn = new mysqli($servername, $username, $password, $dbname);

// ตรวจสอบการเชื่อมต่อ
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

// รับค่าชื่อ LED จาก ESP32
$name = $_GET['name'];

// เตรียมคำสั่ง SQL สำหรับเลือกสถานะของ LED จากฐานข้อมูล
$sql = "SELECT status FROM led_status WHERE name = '$name'";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
    // ถ้าพบสถานะของ LED
    $row = $result->fetch_assoc();
    $status = $row["status"];
    echo $status; // คืนค่าสถานะ LED กลับไปยัง ESP32
} else {
    // ถ้าไม่พบสถานะของ LED
    echo "LED not found";
}

// ปิดการเชื่อมต่อฐานข้อมูล
$conn->close();
?>
