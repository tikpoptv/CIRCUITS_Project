<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Update LED Status</title>
</head>
<body>
    <h2>Update LED Status</h2>
    <form action="control.php" method="post">
        <label for="name">LED Name:</label>
        <select name="name" id="name">
            <option value="Led1">Led1</option>
            <option value="Led2">Led2</option>
            <option value="Led3">Led3</option>
            <option value="Led4">Led4</option>
        </select>
        <br><br>
        <label for="status">Status:</label>
        <select name="status" id="status">
            <option value="ON">ON</option>
            <option value="OFF">OFF</option>
        </select>
        <br><br>
        <button type="submit">Update Status</button>
    </form>
</body>
</html>
