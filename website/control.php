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

// ตรวจสอบว่ามีการส่งข้อมูล POST มาหรือไม่
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    // รับข้อมูลจากฟอร์ม
    $name = $_POST['name'];
    $status = $_POST['status'];

    // เตรียมคำสั่ง SQL สำหรับอัปเดตข้อมูล
    $sql = "UPDATE led_status SET status='$status' WHERE name='$name'";

    // ทำการอัปเดตข้อมูล
    if ($conn->query($sql) === TRUE) {
        echo "Record updated successfully";
    } else {
        echo "Error updating record: " . $conn->error;
    }
}

// ปิดการเชื่อมต่อฐานข้อมูล
$conn->close();
?>
