const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<body>

<h1>Web page with Ajax refresh</h1>

<div id="demo">
	<button type="button" onclick="sendData(1)">LED ON</button>
	<button type="button" onclick="sendData(0)">LED OFF</button><BR>
</div>

<div>
	DTH Value: <span id="DHTValue">0</span><br>
  LED State: <span id="LEDState">--</span>
</div>

<script>
function sendData(led) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("LEDState").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "setLED?LEDstate="+led, true);
  xhttp.send();
}

setInterval(function() {
  // Call a function repetatively with 2 Second interval
  getDhtData();
}, 2000); //2000msec update rate

function getDhtData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("DHTValue").innerHTML =
      this.responseText;
    }
  };
  xhttp.open("GET", "readDHT", true);
  xhttp.send();
}
</script>
</body>
</html>
)====="; 
