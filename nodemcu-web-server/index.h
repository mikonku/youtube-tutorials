const char page[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8"/>
  <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
  <title>Nodemcu-IoT</title>
  <style>
  	body {
    	margin: 0;
        font-family: Arial, sans-serif;
    }
    
    nav {
    	background-color: #333;
    }
    
    nav ul {
    	list-style-type: none;
        margin: 0;
        padding: 0;
        overflow: hidden;
    }
    
    nav ul li {
    	float: left;
    }
    
    nav ul li a {
    	display: block;
        color: white;
        text-align: center;
        padding: 14px 16px;
        text-decoration: none;
    }
    
    nav ul li a:hover {
    	background-color: #555;
    }
    
    .card {
    	background-color: #fff;
        border-radius:5px;
        box-shadow: 0 4px 8px rgba(0,0,0,0.1);
        padding: 20px;
        margin: 20px auto;
        max-width: 300px;
    }
    
    .card h2 {
    	margin-top: 0;
    }
    
    .card p {
    	margin-bottom: 0;
    }
    
    .card span {
    	font-weight: bold;
        color: #007bff;
    }
    
  
  </style>
</head>

<body>
 <nav>
   <ul>
        <li><a href="/">Bedroom</a></li>
        <li><a href="/kitchen">Kitchen</a></li>
   </ul>
 </nav>
 
 <div class="card">
 	<h2>{{device}}</h2>
    <p>
    Suhu saat ini: <span id="temperature-{{device}}">0 C</span>
    </p>
 </div>

</body>

<script>

// membuat fungsi untuk melakukan ajax request
function getTemperature(device){
	var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function(){
    	if(this.readyState == 4){
        	if(this.status == 200){
            	var response = JSON.parse(this.responseText);
                if(response.responseCode == 200){
                	var responseData = response.responseData;
                    if(responseData.type == "temperature"){
                    	// membuat id
                        var temperatureId = responseData.type+"-"+device;
                        
                        // ubah isi pada tag yang memiliki id pada temperatureId
                        document.getElementById(temperatureId).innerText = responseData.value + " " + responseData.label;
                        
                    }
                } else {
                	console.error("response error: ", response.responseMessage);
                }
            } else{
            	console.error("request failed: ", this.status);
            }
        }
    };
    
    // menambahkan query parameter "device" ke url
    var url = "?device="+encodeURIComponent(device);
    xhr.open("GET", url, true);
    xhr.send();
}

// membuat agar request selalu berjalan setiap 3 detik sekali
setInterval(function () {
	getTemperature("{{device}}");
}, 3000);

</script>
</html>


)=====";