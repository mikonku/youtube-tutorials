<?php
$servername = "localhost";
$dbname = "belajar_nodemcu";
$username = "root";
$password = "";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}

$sql = "SELECT  id, timestamp, temperature FROM `suhu`  order by timestamp desc limit 1";
$result = $conn->query($sql);

if ($result->num_rows > 0) {
  // output data of each row
  $row = $result->fetch_assoc();
} else {
  // echo "0 results";
}
$conn->close();

header("Content-Type: application/json");

$respons = [

  'responseCode' => 200,
  'responseMessage' => 'success',
  'responseData' => $row
];
echo json_encode($respons);
