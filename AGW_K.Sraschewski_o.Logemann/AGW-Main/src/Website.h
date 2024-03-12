
// HTML-Seiteninhalt im PROGMEM-Bereich für einen verbesserten Speicherzugriff
const char PAGE_MAIN[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en" class="js-focus-visible">
<title>AGW-Interface</title>

<!-- Stildefinitionen für die HTML-Seite -->
<style>
    /* Tabellenformatierung */
    table {
        position: relative;
        width: 100%;
        border-spacing: 0px;
    }
    tr {
        border: 1px solid white;
        font-family: "Verdana", "Arial", sans-serif;
        font-size: 20px;
    }
    th {
        height: 20px;
        padding: 3px 15px;
        background-color: #343a40;
        color: #FFFFFF !important;
    }
    td {
        height: 20px;
        padding: 3px 15px;
    }
    /* Formatierung für Tabellendaten */
    .tabledata {
        font-size: 24px;
        position: relative;
        padding-left: 5px;
        padding-top: 5px;
        height: 25px;
        border-radius: 5px;
        color: #FFFFFF;
        line-height: 20px;
        transition: all 200ms ease-in-out;
    }
    /* Formatierung für Schieberegler */
    .fanrpmslider {
        width: 30%;
        height: 55px;
        outline: none;
        height: 25px;
    }
    /* Formatierung für Text im Body */
    .bodytext {
        font-family: "Verdana", "Arial", sans-serif;
        font-size: 24px;
        text-align: left;
        font-weight: light;
        border-radius: 5px;
        display: inline;
    }
    /* Formatierung für die Navigationsleiste */
    .navbar {
        width: 100%;
        height: 50px;
        margin: 0;
        padding: 10px 0px;
        background-color: #FFF;
        color: #000000;
        border-bottom: 5px solid #293578;
    }
    /* Festpositionierung für die Navigationsleiste */
    .fixed-top {
        position: fixed;
        top: 0;
        right: 0;
        left: 0;
        z-index: 1030;
    }
    /* Formatierung für den Titel in der Navigationsleiste */
    .navtitle {
        float: left;
        height: 50px;
        font-family: "Verdana", "Arial", sans-serif;
        font-size: 50px;
        font-weight: bold;
        line-height: 50px;
        padding-left: 20px;
    }
    /* Formatierung für den Untertitel in der Navigationsleiste */
    .navheading {
        position: fixed;
        left: 60%;
        height: 50px;
        font-family: "Verdana", "Arial", sans-serif;
        font-size: 20px;
        font-weight: bold;
        line-height: 20px;
        padding-right: 20px;
    }
    /* Formatierung für die Daten in der Navigationsleiste */
    .navdata {
        justify-content: flex-end;
        position: fixed;
        left: 70%;
        height: 50px;
        font-family: "Verdana", "Arial", sans-serif;
        font-size: 20px;
        font-weight: bold;
        line-height: 20px;
        padding-right: 20px;
    }
    /* Formatierung für Kategorien */
    .category {
        font-family: "Verdana", "Arial", sans-serif;
        font-weight: bold;
        font-size: 32px;
        line-height: 50px;
        padding: 20px 10px 0px 10px;
        color: #000000;
    }
    /* Formatierung für Überschriften */
    .heading {
        font-family: "Verdana", "Arial", sans-serif;
        font-weight: normal;
        font-size: 28px;
        text-align: left;
    }
    /* Formatierung für Buttons */
    .btn {
        background-color: #444444;
        border: none;
        color: white;
        padding: 10px 20px;
        text-align: center;
        text-decoration: none;
        display: inline-block;
        font-size: 16px;
        margin: 4px 2px;
        cursor: pointer;
    }
    /* Formatierung für den Fußbereich */
    .foot {
        font-family: "Verdana", "Arial", sans-serif;
        font-size: 20px;
        position: relative;
        height: 30px;
        text-align: center;
        color: #AAAAAA;
        line-height: 20px;
    }
    /* Containerformatierung */
    .container {
        max-width: 1800px;
        margin: 0 auto;
    }
    /* Runde Ecken für die Tabellenzellen */
    table tr:first-child th:first-child {
        border-top-left-radius: 5px;
    }
    table tr:first-child th:last-child {
        border-top-right-radius: 5px;
    }
    table tr:last-child td:first-child {
        border-bottom-left-radius: 5px;
    }
    table tr:last-child td:last-child {
        border-bottom-right-radius: 5px;
    }
</style>
)=====";


<!-- HTML-Struktur für den Body der Webanwendung -->
<body style="background-color: #efefef" onload="process()">

  <!-- Header mit Navigationsleiste -->
  <header>
    <div class="navbar fixed-top">
      <div class="container">
        <!-- Titel des Dashboards -->
        <div class="navtitle">Gewaechshaus Dashboard</div>
        <!-- Datum anzeigen -->
        <div class="navdata" id="date">mm/dd/yyyy</div>
        <div class="navheading">Datum:</div><br>
        <!-- Uhrzeit anzeigen -->
        <div class="navdata" id="time">00:00:00</div>
        <div class="navheading">Zeit:</div>
      </div>
    </div>
  </header>

  <!-- Hauptbereich der Webanwendung -->
  <main class="container" style="margin-top:70px">
    <!-- Kategorie "Informationen" -->
    <div class="category">Informationen</div>
    <!-- Tabelle für Sensordaten -->
    <div style="border-radius: 10px !important;">
      <table style="width:50%">
        <!-- Spaltengruppierung für das Styling -->
        <colgroup>
          <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
          <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
          <col span="1" style="background-color:rgb(180,180,180); width: 15%; color:#000000 ;">
        </colgroup>
        <!-- Überschriftenzeile -->
        <tr>
          <th colspan="1"><div class="heading">Sensor</div></th>
          <th colspan="1"><div class="heading">Wert</div></th>
          <th colspan="1"><div class="heading">Sollwert</div></th>
        </tr>
        <!-- Zeilen für Sensordaten -->
        <tr>
          <td><div class="bodytext">Temperatur</div></td>
          <td><div class="tabledata" id="b0"></div></td>
          <td><div class="tabledata" id="v0"></div></td>
        </tr>
        <tr>
          <td><div class="bodytext">Bodenfeuchte</div></td>
          <td><div class="tabledata" id="b2"></div></td>
          <td><div class="tabledata" id="v2"></div></td>
        </tr>
        <tr>
          <td><div class="bodytext">Wasserstand</div></td>
          <td><div class="tabledata" id="b1"></div></td>
          <td><div class="tabledata" id="v1"></div></td>
        </tr>
        <tr>
          <td><div class="bodytext">Luftfeuchtigkeit</div></td>
          <td><div class="tabledata" id="b3"></div></td>
          <td><div class="tabledata" id=""></div></td>
        </tr>
        <tr>
          <td><div class="bodytext">Luefter</div></td>
          <td><div class="tabledata" id="luefter"></div></td>
          <td><div class="tabledata" id=""></div></td>
        </tr>
        <tr>
          <td><div class="bodytext">Pumpe</div></td>
          <td><div class="tabledata" id="pumpe"></div></td>
          <td><div class="tabledata" id=""></div></td>
        </tr>
        <tr>
          <td><div class="bodytext">LED</div></td>
          <td><div class="tabledata" id="switch"></div></td>
          <td><div class="tabledata" id=""></div></td>
        </tr>
      </table>
    </div>
    <br>
    <br>
  </main>
</body>


<!-- Bereich für die Schaltflächen -->
<div class="category">Kontrollmenü</div>
<!-- Tabelle für die Schaltflächen -->
<table style="width:50%">
  <colgroup>
    <!-- Spaltenbreiten -->
    <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
    <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
    <col span="1" style="background-color:rgb(180,180,180); width: 15%; color:#000000 ;">
  </colgroup>
  <!-- Überschriften für die Spalten -->
  <tr>
    <th colspan="1"><div class="heading">Sensor</div></th>
    <th colspan="1"><div class="heading">Manuell</div></th>
    <th colspan="1"><div class="heading">Automatisch</div></th>
  </tr>
  <!-- Schaltflächen für LED -->
  <tr>
    <td><div class="bodytext">LED</div></td>
    <!-- Schaltfläche für manuelle Steuerung der LED -->
    <td><div class="tabledata"><button type="button" class="btn" id="btn0" onclick="ButtonPress0()">Toggle</button></div></td>
    <!-- Schaltfläche für automatische Steuerung der LED -->
    <td><div class="tabledata"><button type="button" class="btn" id="btn4" onclick="ButtonPress4()">Toggle</button></div></td>
  </tr>
  <!-- Schaltflächen für Lüfter -->
  <tr>
    <td><div class="bodytext">Lüfter</div></td>
    <!-- Schaltfläche für manuelle Steuerung des Lüfters -->
    <td><div class="tabledata"><button type="button" class="btn" id="btn2" onclick="ButtonPress2()">Toggle</button></div></td>
    <!-- Schaltfläche für automatische Steuerung des Lüfters -->
    <td><div class="tabledata"><button type="button" class="btn" id="btn5" onclick="ButtonPress5()">Toggle</button></div></td>
  </tr>
  <!-- Schaltflächen für Pumpe -->
  <tr>
    <td><div class="bodytext">Pumpe</div></td>
    <!-- Schaltfläche für manuelle Steuerung der Pumpe -->
    <td><div class="tabledata"><button type="button" class="btn" id="btn3" onclick="ButtonPress3()">Toggle</button></div></td>
    <!-- Schaltfläche für automatische Steuerung der Pumpe -->
    <td><div class="tabledata"><button type="button" class="btn" id="btn6" onclick="ButtonPress6()">Toggle</button></div></td>
  </tr>
</table>


<br>
<br>

<!-- Bereich für Einstellungen -->
<div class="category">Einstellungen</div>
<!-- Tabelle für Einstellungen -->
<table style="width:50%">
  <colgroup>
    <!-- Spaltenbreiten -->
    <col span="1" style="background-color:rgb(230,230,230); width: 20%; color:#000000 ;">
    <col span="1" style="background-color:rgb(200,200,200); width: 15%; color:#000000 ;">
    <col span="1" style="background-color:rgb(180,180,180); width: 15%; color:#000000 ;">
  </colgroup>
  <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
  <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
  <col span="2"style="background-color:rgb(0,0,0); color:#FFFFFF">
  <!-- Überschriften für die Spalten -->
  <tr>
    <th colspan="1"><div class="heading">Sensor</div></th>
    <th colspan="1"><div class="heading">Eingabe</div></th>
    <th colspan="1"><div class="heading">Bestätigung</div></th>
  </tr>
  <!-- Einstellungen für Temperatur -->
  <tr>
    <td><div class="bodytext">Temperatur</div></td>
    <!-- Eingabefeld für den Temperaturschwellwert -->
    <td><div class="tabledata"><input type="text" id="temp_schwellwert" name="temp_schwellwert"></div></td>
    <!-- Schaltfläche zur Änderung des Temperaturschwellwerts -->
    <td><div class="tabledata"><button type="button" class="btn" id="btn7" onclick="ButtonPress7()">ändern</button></div></td>
  </tr>
  <!-- Einstellungen für Bodenfeuchte -->
  <tr>
    <td><div class="bodytext">Bodenfeuchte</div></td>
    <!-- Eingabefeld für den Bodenfeuchtigkeitsschwellwert -->
    <td><div class="tabledata"><input type="text" id="boden_schwellwert" name="boden_schwellwert"></div></td>
    <!-- Schaltfläche zur Änderung des Bodenfeuchtigkeitsschwellwerts -->
    <td><div class="tabledata"><button type="button" class="btn" id="btn8" onclick="ButtonPress8()">ändern</button></div></td>
  </tr>
</table>
<br>
<br>
<br>

    
  </main>

  <footer div class="foot" id = "temp" >ESP32 Web Page Creation and Data Update Demo</div></footer>
  
  </body>


// Die Funktion erstellt ein XMLHttpRequest-Objekt, das je nach Browser entweder ein XMLHttpRequest-Objekt oder ein ActiveXObject erstellt.
function createXmlHttpObject(){
  if(window.XMLHttpRequest){
    xmlHttp=new XMLHttpRequest();
  }
  else{
    xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
  }
  return xmlHttp;
}

// Globale Variable, die das XMLHttpRequest-Objekt speichert
var xmlHttp=createXmlHttpObject();

// Funktion, die aufgerufen wird, wenn Button 0 gedrückt wird
function ButtonPress0() {
  var xhttp = new XMLHttpRequest(); 
  xhttp.open("PUT", "BUTTON_0", false); // Die Anfrage wird vorbereitet, um BUTTON_0 auf dem Server zu aktualisieren
  xhttp.send(); // Die Anfrage wird gesendet
}

// Funktion, die aufgerufen wird, wenn Button 1 gedrückt wird
function ButtonPress1() {
  var xhttp = new XMLHttpRequest(); 
  xhttp.open("PUT", "BUTTON_1", false); // Die Anfrage wird vorbereitet, um BUTTON_1 auf dem Server zu aktualisieren
  xhttp.send(); // Die Anfrage wird gesendet
}

// Funktion, die aufgerufen wird, wenn Button 2 gedrückt wird (analog zu Button 1)
function ButtonPress2() {
  var xhttp = new XMLHttpRequest(); 
  xhttp.open("PUT", "BUTTON_2", false); 
  xhttp.send(); 
}

// Funktion, die aufgerufen wird, wenn Button 3 gedrückt wird (analog zu Button 1)
function ButtonPress3() {
  var xhttp = new XMLHttpRequest(); 
  xhttp.open("PUT", "BUTTON_3", false); 
  xhttp.send(); 
}

// Funktion, die aufgerufen wird, wenn Button 4 gedrückt wird (analog zu Button 1)
function ButtonPress4() {
  var xhttp = new XMLHttpRequest(); 
  xhttp.open("PUT", "BUTTON_4", false); 
  xhttp.send(); 
}

// Funktion, die aufgerufen wird, wenn Button 5 gedrückt wird (analog zu Button 1)
function ButtonPress5() {
  var xhttp = new XMLHttpRequest(); 
  xhttp.open("PUT", "BUTTON_5", false); 
  xhttp.send(); 
}

// Funktion, die aufgerufen wird, wenn Button 6 gedrückt wird (analog zu Button 1)
function ButtonPress6() {
  var xhttp = new XMLHttpRequest(); 
  xhttp.open("PUT", "BUTTON_6", false); 
  xhttp.send(); 
}

// Funktion, die aufgerufen wird, wenn Button 7 gedrückt wird
function ButtonPress7() {
  var xhttp = new XMLHttpRequest(); 
  var inputElement = document.getElementById("temp_schwellwert");
  var value = inputElement.value; // Der Wert des Eingabefelds "temp_schwellwert" wird abgerufen
  xhttp.open("GET", "BUTTON_7?temp_schwellwert="+value, false); // Die Anfrage wird vorbereitet, um BUTTON_7 auf dem Server zu aktualisieren und den Wert von temp_schwellwert zu senden
  xhttp.send(); // Die Anfrage wird gesendet
}

// Funktion, die aufgerufen wird, wenn Button 8 gedrückt wird (analog zu Button 7)
function ButtonPress8() {
  var xhttp = new XMLHttpRequest(); 
  var inputElement = document.getElementById("boden_schwellwert");
  var value = inputElement.value; 
  xhttp.open("GET", "BUTTON_8?boden_schwellwert="+value, false); 
  xhttp.send(); 
}

 
// Die Funktion wird aufgerufen, um die empfangene Antwort vom Server zu verarbeiten und die entsprechenden HTML-Elemente zu aktualisieren.
function response(){
  // Deklaration der Variablen
  var message; // Speichert den Wert aus der XML-Antwort
  var barwidth; // Berechnet die Balkenbreite basierend auf dem Wert
  var currentsensor; // Unbenutzt (kann entfernt werden)
  var xmlResponse; // Speichert die XML-Antwort
  var xmldoc; // Speichert die XML-Knoten für die Verarbeitung
  var dt = new Date(); // Aktuelles Datum und Uhrzeit
  var color = "#e8e8e8"; // Standardfarbe für Balken und Hintergrund

  // Die XML-Antwort vom Server wird abgerufen
  xmlResponse = xmlHttp.responseXML;

  // Die aktuelle Uhrzeit und das aktuelle Datum werden in die entsprechenden HTML-Elemente eingefügt
  document.getElementById("time").innerHTML = dt.toLocaleTimeString();
  document.getElementById("date").innerHTML = dt.toLocaleDateString();

  // Verarbeitung der XML-Daten für B0
  xmldoc = xmlResponse.getElementsByTagName("B0"); 
  message = xmldoc[0].firstChild.nodeValue; // Der Wert für B0 wird aus der XML-Antwort extrahiert

  // Die Balkenbreite wird basierend auf dem Wert von B0 berechnet und die entsprechenden HTML-Elemente aktualisiert
  barwidth = message / 40.95;
  document.getElementById("b0").innerHTML = message;
  document.getElementById("b0").style.width = (barwidth + "%");

  // Verarbeitung der XML-Daten für V0
  xmldoc = xmlResponse.getElementsByTagName("V0"); 
  message = xmldoc[0].firstChild.nodeValue;
  document.getElementById("v0").innerHTML = message;
  document.getElementById("temp_schwellwert").innerHTML = message;
  document.getElementById("v0").style.width = (barwidth + "%");
  document.getElementById("v0").style.backgroundColor = color;

  // Verarbeitung der XML-Daten für B1 und B2
  // Die Farbe der Balken wird basierend auf dem Wert von B1 und B2 geändert
  xmldoc = xmlResponse.getElementsByTagName("B1");
  message = xmldoc[0].firstChild.nodeValue;
  if (message > 2048) {
    color = "#aa0000"; 
  } else {
    color = "#0000aa"; 
  }
  // Die entsprechenden HTML-Elemente für B1 werden aktualisiert
  document.getElementById("b1").innerHTML = message;
  width = message / 40.95;
  document.getElementById("b1").style.width = (width + "%");
  document.getElementById("b1").style.backgroundColor = color;

  // Ähnliche Verarbeitung wird für B2 durchgeführt
  // ...

  // Verarbeitung der XML-Daten für V2
  // Ähnliche Verarbeitung wie für V0, jedoch basierend auf den Daten von B2
  xmldoc = xmlResponse.getElementsByTagName("V2");
  message = xmldoc[0].firstChild.nodeValue;
  document.getElementById("v2").innerHTML = message;
  document.getElementById("v2").style.width = (width + "%");
  document.getElementById("v2").style.backgroundColor = color;



// Verarbeitung der XML-Daten für den Sensor B3
xmldoc = xmlResponse.getElementsByTagName("B3");
message = xmldoc[0].firstChild.nodeValue;
if (message > 2048) {
  color = "#aa0000"; // Rote Farbe, wenn der Wert größer als 2048 ist
} else {
  color = "#0000aa"; // Blaue Farbe, wenn der Wert kleiner oder gleich 2048 ist
}
// Aktualisierung des HTML-Elements für B3 mit dem erhaltenen Wert und der entsprechenden Breite und Farbe des Balkens
document.getElementById("b3").innerHTML = message;
width = message / 40.95;
document.getElementById("b3").style.width = (width + "%");
document.getElementById("b3").style.backgroundColor = color;

// Verarbeitung der Daten für die LED
xmldoc = xmlResponse.getElementsByTagName("LED");
message = xmldoc[0].firstChild.nodeValue;
// Aktualisierung des HTML-Elements für die LED mit entsprechendem Text
if (message == 0) {
  document.getElementById("btn0").innerHTML = "Anschalten";
} else {
  document.getElementById("btn0").innerHTML = "Ausschalten";
}

// Verarbeitung der Daten für den Schalter (SWITCH)
xmldoc = xmlResponse.getElementsByTagName("SWITCH");
message = xmldoc[0].firstChild.nodeValue;
document.getElementById("switch").style.backgroundColor = "rgb(200,200,200)";
// Aktualisierung des HTML-Elements für den Schalter (SWITCH) mit entsprechendem Text und Farbe
if (message == 0) {
  document.getElementById("switch").innerHTML = "Aus";
  document.getElementById("switch").style.color = "#0000AA"; 
} else {
  document.getElementById("switch").innerHTML = "An";
  document.getElementById("switch").style.color = "#00AA00";
}

// Verarbeitung der Daten für den Lüfter (LUEFTER)
xmldoc = xmlResponse.getElementsByTagName("LUEFTER");
message = xmldoc[0].firstChild.nodeValue;
document.getElementById("luefter").style.backgroundColor = "rgb(200,200,200)";
// Aktualisierung des HTML-Elements für den Lüfter (LUEFTER) mit entsprechendem Text und Farbe
if (message == 0) {
  document.getElementById("luefter").innerHTML = "Aus";
  document.getElementById("btn2").innerHTML = "Anschalten";
  document.getElementById("luefter").style.color = "#0000AA"; 
} else {
  document.getElementById("luefter").innerHTML = "An";
  document.getElementById("btn2").innerHTML = "Ausschalten";
  document.getElementById("luefter").style.color = "#00AA00";
}

// Verarbeitung der Daten für den Auto-Licht-Button (AUTOLIGHT)
xmldoc = xmlResponse.getElementsByTagName("AUTOLIGHT");
message = xmldoc[0].firstChild.nodeValue;
// Aktualisierung des HTML-Elements für den Auto-Licht-Button (AUTOLIGHT) mit entsprechendem Text
if (message == 0) {
  document.getElementById("btn4").innerHTML = "Anschalten";
} else {
  document.getElementById("btn4").innerHTML = "Ausschalten";
}

// Verarbeitung der Daten für den Auto-Lüfter-Button (AUTOLUEFTER)
xmldoc = xmlResponse.getElementsByTagName("AUTOLUEFTER");
message = xmldoc[0].firstChild.nodeValue;
// Aktualisierung des HTML-Elements für den Auto-Lüfter-Button (AUTOLUEFTER) mit entsprechendem Text
if (message == 0) {
  document.getElementById("btn5").innerHTML = "Anschalten";
} else {
  document.getElementById("btn5").innerHTML = "Ausschalten";
}

// Verarbeitung der Daten für den Auto-Pumpe-Button (AUTOPUMPE)
xmldoc = xmlResponse.getElementsByTagName("AUTOPUMPE");
message = xmldoc[0].firstChild.nodeValue;
// Aktualisierung des HTML-Elements für den Auto-Pumpe-Button (AUTOPUMPE) mit entsprechendem Text
if (message == 0) {
  document.getElementById("btn6").innerHTML = "Anschalten";
} else {
  document.getElementById("btn6").innerHTML = "Ausschalten";
}

// Verarbeitung der Daten für die Pumpe
xmldoc = xmlResponse.getElementsByTagName("PUMPE");
message = xmldoc[0].firstChild.nodeValue;
document.getElementById("pumpe").style.backgroundColor = "rgb(200,200,200)";
// Aktualisierung des HTML-Elements für die Pumpe mit entsprechendem Text und Farbe
if (message == 0) {
  document.getElementById("pumpe").innerHTML = "Aus";
  document.getElementById("btn3").innerHTML = "Anschalten";
  document.getElementById("pumpe").style.color = "#0000AA"; 
} else {
  document.getElementById("pumpe").innerHTML = "An";
  document.getElementById("btn3").innerHTML = "Ausschalten";
  document.getElementById("pumpe").style.color = "#00AA00";
}


  
   
// Die Funktion process() wird verwendet, um regelmäßig Anfragen an den Server zu senden und die Seite zu aktualisieren.
function process() {
  // Überprüfen des ReadyStates des xmlHttp-Objekts, um sicherzustellen, dass es entweder nicht verwendet wird oder bereits eine Antwort erhalten hat
  if (xmlHttp.readyState == 0 || xmlHttp.readyState == 4) {
    // Öffnen einer PUT-Anfrage an die URL "xml" auf dem Server
    xmlHttp.open("PUT", "xml", true);
    // Festlegen der onreadystatechange-Eigenschaft des xmlHttp-Objekts auf die response()-Funktion, die aufgerufen wird, wenn die Antwort empfangen wird
    xmlHttp.onreadystatechange = response;
    // Senden der PUT-Anfrage mit null als Datenparameter
    xmlHttp.send(null);
  }
  // Starten des Timeout-Timers, um die process() -Funktion alle 100 Millisekunden erneut aufzurufen
  setTimeout("process()", 100);
}

