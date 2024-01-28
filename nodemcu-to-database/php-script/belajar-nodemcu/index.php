<?php

$servername = "localhost";
$dbname = "belajar_nodemcu";
$username = "root";
$password = "";


if (isset($_GET['temperature'])) {
  $temperature = $_GET['temperature'];

  // Create connection
  $conn = new mysqli($servername, $username, $password, $dbname);

  // Check connection
  if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
  }

  $sql = "INSERT INTO `suhu` (`timestamp`, `temperature`) VALUES (current_timestamp(), ?)";

  $stmt = $conn->prepare($sql);
  $stmt->bind_param("d", $temperature);
  $stmt->execute();

  $stmt->close();

  $conn->close();
}


echo "success";
die;
