const char MAIN_page[] PROGMEM = R"=====(
<!doctype html>
<html lang="en">

<head>
    <meta charset="utf-8">
    <meta name="description" content="">
    <meta name="author" content="">
    <link rel="stylesheet" href="https://unpkg.com/purecss@2.0.3/build/pure-min.css" crossorigin="anonymous">
    <link rel="stylesheet" href="https://unpkg.com/purecss@2.0.3/build/grids-responsive-min.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.1/css/all.min.css"
        crossorigin="anonymous">
    <meta name="viewport" content="width=device-width, initial-scale=1">
</head>

<body>
    <div id="layout" class="pure-g">
        <div class="sidebar pure-u-1 pure-u-md-1-4">
            <div class="header">
                <h1 class="brand-title" style="color: gray;">Mysakova udirna</h1>
                <h2 class="brand-tagline" style="color: silver;">Uzeni s laskou v0.1</h2>
            </div>
        </div>

        <div class="content pure-u-1 pure-u-md-3-4">
            <div>
                <h2>Ovladani</h2>
                <button type="button" id="LEDOn" onclick="sendData(1)"> Relay On <i
                        class="fas fa-toggle-on"></i></button>
                <button type="button" id="LEDOff" onclick="sendData(0)"> Relay Off <i
                        class="fas fa-toggle-off"></i></button>
                <button type="button" id="LEDState">--</button>

                <h2>Stav</h2>
                <ul>
                    <li>Alive <span id="alive"><i class="fa fa-thumbs-up" aria-hidden="true"></i></span></li>
                </ul>
                <ul>
                    <li>Teplota <span id="DHTValue">--.-</span> C</li>
                </ul>
                <ul>
                    <li>Vlhkost <span id="DHTValueHum">--.-</span> %</li>
                </ul>

                <h2>Grafy</h2>
                <p>Grafy teploty, tlaku, rosneho bodu, stavu masa, ....</p>
                <div class="chart-container" style="position: relative; width:90%">
                    <canvas id="myChart"></canvas>
                </div>
            </div>

            <div class="footer">
                <div class="pure-menu pure-menu-horizontal">
                    <ul>
                        <li class="pure-menu-item"><a href="https://github.com/krakorj/wemos-sandbox/blob/main/README.md"
                                class="pure-menu-link">GitHub</a></li>
                    </ul>
                </div>
            </div>
        </div>
    </div>

    <!-- Graphs -->
    <script src="https://cdnjs.cloudflare.com/ajax/libs/Chart.js/2.7.1/Chart.min.js"></script>
    <script>
        var dataTempBuffer = [0, 5, 10, 18, 24, 23, 24, 26];
        var dataHumBuffer = [20, 20, 30, 30, 35, 35, 35, 35];
        var labelBuffer = ["0", "1", "2", "3", "4", "5", "6", "7"];
        var ctx = document.getElementById("myChart");
        var myChart = new Chart(ctx, {
            type: 'line',
            data: {
                labels: labelBuffer,
                datasets: [{
                    data: dataTempBuffer,
                    lineTension: 0,
                    backgroundColor: 'transparent',
                    borderColor: '#007bff',
                    borderWidth: 4,
                    pointBackgroundColor: '#007bff',
                    label: "Temp"
                }, {
                    data: dataHumBuffer,
                    lineTension: 0,
                    backgroundColor: 'transparent',
                    borderColor: '#7bff00',
                    borderWidth: 4,
                    pointBackgroundColor: '#7bff00',
                    label: "Hum"
                }
                ]
            },
            options: {
                scales: {
                    yAxes: [{
                        ticks: {
                            beginAtZero: false
                        }
                    }]
                },
                legend: {
                    display: true,
                }
            }
        });
    </script>
    <script>
        function sendData(led) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("LEDState").innerHTML = this.responseText;
                }
            };
            xhttp.open("GET", "/setLED?LEDstate=" + led, true);
            xhttp.send();
        }

        // Call a function repetatively with 2 Second interval
        setInterval(function () {
            getDhtData();
        }, 2000); //2000msec update rate

        function getDhtData() {
            var data = 0;
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    var data=this.responseText;
                    var json = JSON.parse(data);
                    document.getElementById("DHTValue").innerHTML = json["temp"];
                    document.getElementById("DHTValueHum").innerHTML = json["hum"];
                    dataTempBuffer.push(json["temp"]);
                    dataHumBuffer.push(json["hum"]);
                    labelBuffer.push(labelBuffer.length);
                    myChart.update();
                }
            };
            xhttp.open("GET", "readDHT", true);
            xhttp.send();
        }
    </script>
</body>
</html>
)====="; 
