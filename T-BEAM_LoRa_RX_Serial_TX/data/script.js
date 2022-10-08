//Get current sensor readings when the page loads  
window.addEventListener('load', getReadings);

var gaugeSoil = new RadialGauge
(
	{
		renderTo: 'gauge-moisture',
		width: 200,
		height: 200,
		units: "%",
		minValue: 1,
		maxValue: 100,
		colorValueBoxRect: "#049faa",
		colorValueBoxRectEnd: "#049faa",
		colorValueBoxBackground: "#f1fbfc",
		valueInt: 1,
		majorTicks: 
		[
			"1",
			"10",
			"15",
			"20",
			"25",
			"30",
			"35",
			"40",
			"45",
			"50",
			"55",
			"60",
			"65",
			"70",
			"75",
			"80",
			"85",
			"90",
			"95",
			"100"
		],
		minorTicks: 5,
		strokeTicks: true,
		highlights: 
		[
			{
				"from": 1,
				"to": 35,
				"color": "#ff1100"
			},
			
			{
				"from": 35,
				"to": 65,
				"color": "#03C0C1"
			},
			
			{
				"from": 65,
				"to": 100,
				"color": "#28d900"
			}
		],
		colorPlate: "#fff",
		borderShadowWidth: 0,
		borders: false,
		needleType: "line",
		colorNeedle: "#007F80",
		colorNeedleEnd: "#007F80",
		needleWidth: 2,
		needleCircleSize: 3,
		colorNeedleCircleOuter: "#007F80",
		needleCircleOuter: true,
		needleCircleInner: false,
		animationDuration: 1500,
		animationRule: "linear"
	}
).draw();

// Function to get current readings on the webpage when it loads for the first time
function getReadings()
{
	var xhr = new XMLHttpRequest();
	xhr.onreadystatechange = function() 
	{
		if (this.readyState == 4 && this.status == 200) 
		{
			var myObj = JSON.parse(this.responseText);
			console.log(myObj);
			var temp = myObj.temperature;
			var press = myObj.pressure;
			var pH = myObj.ph;
			var lv = myObj.level;
			var press2 = myObj.pressure2;
			var fw = myObj.flow;
			var mois = myObj.moisture;
			gaugeTemp.value = temp;
			gaugePress.value = press;
			gaugePH.value = pH;
			gaugeLevel.value = lv;
			gaugePress2.value = press2;
			gaugeFlow.value = fw;
			gaugeSoil.value = mois;
		}
	}; 
	
	xhr.open("GET", "/readings", true);
	xhr.send();
}

if (!!window.EventSource) 
{
	var source = new EventSource('/events');
  
	source.addEventListener('open', function(e) 
	{
		console.log("Events Connected");
	}, false);

	source.addEventListener('error', function(e) 
	{
		if (e.target.readyState != EventSource.OPEN) 
		{
			console.log("Events Disconnected");
		}
	}, false);
  
	source.addEventListener('message', function(e) 
	{
		console.log("message", e.data);
	}, false);
  
	source.addEventListener('new_readings', function(e) 
	{
		console.log("new_readings", e.data);
		var myObj = JSON.parse(e.data);
		console.log(myObj);
		gaugeTemp.value = myObj.temperature;
		gaugePress.value = myObj.pressure;
		gaugePH.value = myObj.ph;
		gaugeLevel.value = myObj.level;
		gaugePress2.value = myObj.pressure2;
		gaugeFlow.value = myObj.flow;
		gaugeSoil.value = myObj.moisture;
	}, false);
}