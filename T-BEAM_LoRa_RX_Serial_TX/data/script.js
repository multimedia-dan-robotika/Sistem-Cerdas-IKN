//Get current sensor readings when the page loads  
window.addEventListener('load', getReadings);

var gaugeSoil = new RadialGauge({
  renderTo: 'gauge-moisture',
  width: 300,
  height: 300,
  units: "Humidity (%)",
  minValue: 0,
  maxValue: 100,
  colorValueBoxRect: "#049faa",
  colorValueBoxRectEnd: "#049faa",
  colorValueBoxBackground: "#f1fbfc",
  valueInt: 1,
  majorTicks: [
    "0",
    "10",
    "20",
    "30",
    "40",
    "50",
    "60",
    "70",
    "80",
    "90",
    "100"
  ],
  minorTicks: 10, // edited 4
  strokeTicks: true,
  highlights: [{
      "from": 80,
      "to": 100,
      "color": "#f20202"
    },
    {
      "from": 0,
      "to": 20,
      "color": "#dbd7cc"
    }, {
      "from": 60,
      "to": 80,
      "color": "#f2ee02"
    }, {
      "from": 20,
      "to": 60,
      "color": "#02f262"
    }
  ],
  colorPlate: "#fff",
  borderShadowWidth: 1, // edited 0
  borders: true,
  colorNeedle: "#007F80",
  colorNeedleEnd: "#007F80",
  needleWidth: 2,
  needleCircleSize: 3,
  colorNeedleCircleOuter: "#007F80",
  needleCircleOuter: true,
  needleCircleInner: false,
  needleType: 'arrow',
  animationDuration: 500, // edited 1500
  animationRule: "bounce"
}).draw();

// Function to get current readings on the webpage when it loads for the first time
function getReadings() {
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function () {
    if (this.readyState == 4 && this.status == 200) {
      var myObj = JSON.parse(this.responseText);
      console.log(myObj);

      let mois = myObj.moisture;

      gaugeSoil.value = mois;
      console.log(mois);
    }
  };

  xhr.open("GET", "/readings", true);
  xhr.send();
}

if (!!window.EventSource) {
  var source = new EventSource('/events');

  source.addEventListener('open', function (e) {
    console.log("Events Connected");
  }, false);

  source.addEventListener('error', function (e) {
    if (e.target.readyState != EventSource.OPEN) {
      console.log("Events Disconnected");
      alert("Device Not Connected!");

    }
  }, false);

  source.addEventListener('message', function (e) {
    console.log("message", e.data);
  }, false);

  source.addEventListener('new_readings', function (e) {
    console.log("new_readings", e.data);
    var myObj = JSON.parse(e.data);
    console.log(myObj);

    gaugeSoil.value = myObj.moisture;
  }, false);
}