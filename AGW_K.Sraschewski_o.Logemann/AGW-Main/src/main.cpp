/* Libarys */
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <WiFi.h>
#include <WebServer.h>
#include "Website.h"


/* DEFINES / Pin Output */
#define DHTPIN 32 //Temperatur & Bodenfeuchte Sensor
#define DHTTYPE DHT11 //DHT Typ
#define WLPIN 35 // Wasserlevel Sesnor
#define MPIN 33 // Bodenfeuchte Sensor
#define LPIN 34 //Lichtsensor

#define RELAIPINLED 0 //Ralai LED
#define RELAIPINPUMPE 4 // Relai Pumpe
#define RELAIPINCOOLER 16 // Relai Lüfter

#define WATER_MAX 4095 //Max. Wasserstand

#define AP_SSID "AGW-Webinterface" //SSID 
#define AP_PASS "0123456789" //Password

/* Allgemeine Variablen */

/* Alle Funktionen & Variablen DHT11  */'
DHT_Unified dht(DHTPIN, DHTTYPE);
sensors_event_t event;
double temp = 18.00;
double humi = 20.00;


/* Funktionen & Variablen Lichtsteuerung */
bool auto_light = true;
bool enable_light = false;
bool on_light = false;

/* Funktionen & Variablen Temperatursteuerung */
bool auto_luefter = true;
bool on_luefter = false;
bool enable_luefter = false;
double kuehl_temp = 18.00;

/* Funktionen & Variablen Bodenfeuchtesteuerung */ 
bool auto_pumpe = true;
bool on_pumpe = false;
bool enable_pumpe = false;
double soll_bodenfeuchte = 40.00;
 
/* Setzen der Standart-Werte */
double wasserLvlProzent = 20.00;
double bodenfeuchteProzent = 20.00;

/* Webserver Variablen */
IPAddress Actual_IP;
char XML[2048];
IPAddress PageIP(192, 168, 113, 200);
IPAddress gateway(192, 168, 113, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress ip;
WebServer server(80);
char buf[32];

// Funktionen zur Erfassung von Sensorwerten
void read_Tempi(); // Funktion zum Lesen der Temperatur
void read_Humi(); // Funktion zum Lesen der Luftfeuchtigkeit
void read_Waterlevel(); // Funktion zum Lesen des Wasserstands
void read_Moisture(); // Funktion zum Lesen der Bodenfeuchte
void read_light(); // Funktion zum Lesen der Lichtintensität

// Funktionen zur Verarbeitung von Benutzerinteraktionen
void ProcessButton_0(); // Funktion zur Verarbeitung von Button 0-Interaktionen
void ProcessButton_2(); // Funktion zur Verarbeitung von Button 2-Interaktionen
void ProcessButton_3(); // Funktion zur Verarbeitung von Button 3-Interaktionen
void ProcessButton_4(); // Funktion zur Verarbeitung von Button 4-Interaktionen
void ProcessButton_5(); // Funktion zur Verarbeitung von Button 5-Interaktionen
void ProcessButton_6(); // Funktion zur Verarbeitung von Button 6-Interaktionen

// Funktionen zur Behandlung von Formular-Submits
void handleSubmitTest(); // Funktion zur Behandlung von Formular-Submits für Testzwecke
void handleSubmitBoden(); // Funktion zur Behandlung von Formular-Submits für Bodenfeuchte

// Funktionen zum Senden von Webinhalten
void SendWebsite(); // Funktion zum Senden der Webseite an den Client
void SendXML(); // Funktion zum Senden von XML-Daten an den Client


//Setup 
void setup()
{
// Setup-Funktion: Initialisierung und Konfiguration beim Start des Programms

// Pin-Modi festlegen
pinMode(WLPIN, INPUT); // Konfiguriert den Pin für den Wasserstandssensor als Eingang
pinMode(MPIN, INPUT); // Konfiguriert den Pin für den Bodenfeuchtesensor als Eingang
pinMode(LPIN, INPUT); // Konfiguriert den Pin für den Lichtsensor als Eingang
pinMode(RELAIPINLED, OUTPUT); // Konfiguriert den Pin für die LED-Relaisausgabe
pinMode(RELAIPINPUMPE, OUTPUT); // Konfiguriert den Pin für die Pumpen-Relaisausgabe
pinMode(RELAIPINCOOLER, OUTPUT); // Konfiguriert den Pin für die Lüfter-Relaisausgabe

/* Setup Serialport für Debugging */
Serial.begin(9600); // Startet die serielle Kommunikation mit einer Baudrate von 9600

/* DHT11 Setup */
dht.begin(); // Initialisiert den DHT11-Temperatur- und Luftfeuchtigkeitssensor

/* Webserver start */
// Starten des Webserver: Einrichtung eines WLAN-Zugangspunkts
WiFi.softAP(AP_SSID, AP_PASS); // Konfiguriert einen WLAN-Zugangspunkt mit den angegebenen SSID und Passwort
delay(100); // Kurze Verzögerung zur Stabilisierung des WLAN-Moduls
WiFi.softAPConfig(PageIP, gateway, subnet); // Konfiguriert die IP-Adresse für den WLAN-Zugangspunkt
delay(100); // Weitere kurze Verzögerung
Actual_IP = WiFi.softAPIP(); // Ruft die tatsächliche IP-Adresse des Access Points ab
Serial.print("IP address: "); // Ausgabe der IP-Adresse auf der seriellen Schnittstelle zur Überwachung
Serial.println(Actual_IP);

// Festlegen von Handlern für verschiedene HTTP-Anfragen
server.on("/", SendWebsite); // Handler für die Hauptseite der Website
server.on("/xml", SendXML); // Handler für XML-Datenanfragen
server.on("/BUTTON_0", ProcessButton_0); // Handler für Button 0
server.on("/BUTTON_2", ProcessButton_2); // Handler für Button 2
server.on("/BUTTON_3", ProcessButton_3); // Handler für Button 3
server.on("/BUTTON_4", ProcessButton_4); // Handler für Button 4
server.on("/BUTTON_5", ProcessButton_5); // Handler für Button 5
server.on("/BUTTON_6", ProcessButton_6); // Handler für Button 6
server.on("/BUTTON_7", handleSubmitTest); // Handler für Formularsubmit Test
server.on("/BUTTON_8", handleSubmitBoden); // Handler für Formularsubmit Bodenfeuchte

// Starten des Webserver, um Anfragen zu verarbeiten
server.begin();
}

// Hauptprogrammschleife
void loop()
{
    // Ausführen der Funktionen zur Erfassung von Sensorwerten
    read_Tempi(); // Temperatur lesen
    read_Humi(); // Luftfeuchtigkeit lesen
    read_Waterlevel(); // Wasserstand lesen
    read_Moisture(); // Bodenfeuchte lesen
    read_light(); // Lichtintensität lesen

    // Verarbeiten von Client-Anfragen an den Webserver
    server.handleClient(); // Behandeln von Webserver-Anfragen
}


// Funktion: Auslesen der Temperatur und Steuerung des Lüfters basierend auf den Temperaturbedingungen
void read_Tempi()
{
    // Temperaturwert vom DHT-Sensor abrufen
    dht.temperature().getEvent(&event);
    
    // Überprüfen, ob ein Fehler beim Lesen der Temperatur aufgetreten ist
    if (isnan(event.temperature))
    {
        /* Fehlerbehandlung: Sensor nicht gefunden */
        Serial.println(F("Error reading temperature!")); // Fehlermeldung ausgeben
    }
    else
    {
        /* Sensor gefunden: Temperatur ausgelesen */
        Serial.print(F("Temperature: "));
        Serial.print(event.temperature - 2); // Korrektur des Temperaturwertes (Abweichung des Sensors)
        Serial.println(F("°C"));
        temp = event.temperature - 2; // Aktualisieren des globalen Temperaturwerts

        // Überprüfen, ob der Lüfter gestartet werden soll
        if (enable_luefter || (temp >= kuehl_temp && auto_luefter)) // Lüfter starten, wenn die Bedingungen erfüllt sind
        {
            digitalWrite(RELAIPINCOOLER, HIGH); // Lüfter einschalten
            on_luefter = true; // Den Status des Lüfters aktualisieren
        }
        else
        {
            digitalWrite(RELAIPINCOOLER, LOW); // Lüfter ausschalten
            on_luefter = false; // Den Status des Lüfters aktualisieren
        }
    }
}



// Funktion: Auslesen der Luftfeuchtigkeit
void read_Humi()
{
    // Luftfeuchtigkeitswert vom DHT-Sensor abrufen
    dht.humidity().getEvent(&event);
    
    // Überprüfen, ob ein Fehler beim Lesen der Luftfeuchtigkeit aufgetreten ist
    if (isnan(event.relative_humidity))
    {
        /* Fehlerbehandlung: Sensor nicht gefunden */
        Serial.println(F("Error reading humidity!")); // Fehlermeldung ausgeben
    }
    else
    {
        /* Sensor gefunden: Luftfeuchtigkeit ausgelesen */
        Serial.print(F("Humidity: "));
        Serial.print(event.relative_humidity); // Luftfeuchtigkeitswert ausgeben
        Serial.println(F("%")); // Einheit anzeigen
        humi = event.relative_humidity; // Aktualisieren des globalen Luftfeuchtigkeitswerts
    }
}



// Funktion: Auslesen des Wasserstands
void read_Waterlevel()
{
    int wlv = analogRead(WLPIN); // Den analogen Wert des Wasserstandssensors lesen
    Serial.print("Wasserlevel bei:"); // Ausgabe der Wasserstandsinformation auf der seriellen Schnittstelle
    Serial.println(wlv); // Wasserstandswert ausgeben

    /* Unnötig komplexes Mapping */
    // Berechnung des Wasserstands in Prozent basierend auf dem gemessenen analogen Wert
    wasserLvlProzent = ((-1.00) * ((wlv / (double)WATER_MAX) * 100)) + 100;
    Serial.println(wasserLvlProzent); // Wasserstand in Prozent ausgeben
}


// Funktion: Auslesen der Bodenfeuchte
void read_Moisture()
{
    int mlv = analogRead(MPIN); // Den analogen Wert des Bodenfeuchtigkeitssensors lesen
    Serial.print("Bodenfeuchte bei:"); // Ausgabe der Bodenfeuchtigkeitsinformation auf der seriellen Schnittstelle
    Serial.println(mlv); // Bodenfeuchtigkeitswert ausgeben

    
    // Berechnung der Bodenfeuchtigkeit in Prozent basierend auf dem gemessenen analogen Wert
    bodenfeuchteProzent = ((-1.00) * ((mlv / 4096.00) * 100)) + 100;
    Serial.println(bodenfeuchteProzent); // Bodenfeuchtigkeit in Prozent ausgeben

    // Überprüfen, ob die Pumpe aktiviert werden soll
    if ((enable_pumpe || (bodenfeuchteProzent >= soll_bodenfeuchte && auto_pumpe)) && wasserLvlProzent >= 5)
    {
        digitalWrite(RELAIPINPUMPE, HIGH); // Pumpe einschalten
        on_pumpe = true; // Den Status der Pumpe aktualisieren
    }
    else
    {
        digitalWrite(RELAIPINPUMPE, LOW); // Pumpe ausschalten
        on_pumpe = false; // Den Status der Pumpe aktualisieren
    }
}

// Funktion: Auslesen der Lichtintensität
void read_light()
{
    int light = analogRead(LPIN); // Den analogen Wert der Lichtintensität lesen
    Serial.println(light); // Lichtintensitätswert ausgeben

    // Überprüfen, ob das Licht eingeschaltet werden soll
    if (enable_light || (light >= 2000 && auto_light))
    {
        digitalWrite(RELAIPINLED, HIGH); // LED einschalten
        on_light = true; // Den Status des Lichts aktualisieren
    }
    else
    {
        digitalWrite(RELAIPINLED, LOW); // LED ausschalten
        on_light = false; // Den Status des Lichts aktualisieren
    }
}


/* Alles fürs Webinterface  */

// Funktion: Verarbeitung des Buttons 0 (Licht Manuell)
void ProcessButton_0()
{
    // Überprüfen, ob das Licht nicht aktiviert ist
    if (!enable_light)
    {
        enable_light = true; // Licht aktivieren
        on_light = true; // Den Status des Lichts aktualisieren
    }
    else
    {
        enable_light = false; // Licht deaktivieren
        on_light = false; // Den Status des Lichts aktualisieren
    }
    server.send(200, "text/plain", ""); // Webseitenantwort senden
}

// Lüfter Manuell
void ProcessButton_2()
{
  if (!enable_luefter)
  {
    enable_luefter = true;
    on_luefter = true;
  }
  else
  {
    enable_luefter = false;
    on_luefter = false;
  }
  server.send(200, "text/plain", ""); // 
}

// Pumpe Manuell
void ProcessButton_3()
{
  if (!enable_pumpe)
  {
    enable_pumpe = true;
    on_pumpe = true;
  }
  else
  {
    enable_pumpe = false;
    on_pumpe = false;
  }
  server.send(200, "text/plain", ""); 
}
// Automode Buttons:

// Auto Licht:
void ProcessButton_4()
{
    // Überprüfen, ob die automatische Lichtsteuerung aktiviert ist
    if (auto_light)
    {
        auto_light = false; // Automatische Lichtsteuerung deaktivieren
    }
    else
    {
        auto_light = true; // Automatische Lichtsteuerung aktivieren
    }
    server.send(200, "text/plain", ""); // Webseitenantwort senden
}


// Auto Lüfter:
void ProcessButton_5()
{
  if (auto_luefter)
  {
    auto_luefter = false;
  }
  else
  {
    auto_luefter = true;
  }
  server.send(200, "text/plain", "");
}

//Auto Pumpe
void ProcessButton_6()
{
  if (auto_pumpe)
  {
    auto_pumpe = false;
  }
  else
  {
    auto_pumpe = true;
  }
  server.send(200, "text/plain", ""); // Senden an Web Oberfläche
}

// Funktion: Verarbeitung des Formulars für den Temperaturschwellwert
void handleSubmitTest()
{
    // Überprüfen, ob ein Temperaturschwellwert im Formular vorhanden ist
    if (server.hasArg("temp_schwellwert"))
    {
        Serial.println(server.arg("temp_schwellwert")); // Temperaturschwellwert auf der seriellen Schnittstelle ausgeben
        String inputValue = server.arg("temp_schwellwert"); // Den eingegebenen Wert des Temperaturschwellwerts abrufen
        kuehl_temp = inputValue.toDouble(); // Den eingegebenen Wert in eine Gleitkommazahl konvertieren und dem Kühltemperaturwert zuweisen
        Serial.print("Eingabewert empfangen: "); // Ausgabe des empfangenen Werts auf der seriellen Schnittstelle
        Serial.println(inputValue);
        server.send(200, "text/plain", "Daten empfangen"); // Erfolgreiche Antwort an die Webseitenanfrage senden
    }
    else
    {
        server.send(400, "text/plain", "Fehler: Kein Wert empfangen"); // Fehlermeldung senden, wenn kein Temperaturschwellwert vorhanden ist / nicht empfangen wurde
    }
}


void handleSubmitBoden()
{
  if (server.hasArg("boden_schwellwert"))
  {
    Serial.println(server.arg("boden_schwellwert"));
    String inputValue = server.arg("boden_schwellwert");
    soll_bodenfeuchte = inputValue.toDouble();
    Serial.print("Eingabewert empfangen: ");
    Serial.println(inputValue);
    server.send(200, "text/plain", "Daten empfangen");
  }
  else
  {
    server.send(400, "text/plain", "Fehler: Kein Wert empfangen");
  }
}


// Funktion: Senden der Hauptwebsite
void SendWebsite()
{
    server.send(200, "text/html", PAGE_MAIN); // Senden der Hauptwebsite mit dem HTTP-Statuscode 200 (OK) und dem Inhaltstyp "text/html"
}


// Funktion: Sendet XML-Daten an den Client
void SendXML()
{
    // Kopiert den XML-Header und öffnet das <Data>-Element
    strcpy(XML, "<?xml version = '1.0'?>\n<Data>\n");

    // Sendet Temperatur
    // Aktuelle Temperatur
    sprintf(buf, "<B0>%.2f°C</B0>\n", temp);
    strcat(XML, buf);
    // Soll-Temperatur
    sprintf(buf, "<V0>%.2f°C</V0>\n", kuehl_temp);
    strcat(XML, buf);

    // Sendet Wasserstand
    // Aktueller Wasserstand
    sprintf(buf, "<B1>%0.2f</B1>\n", wasserLvlProzent);
    strcat(XML, buf);

    // Sendet Bodenfeuchte
    // Aktuelle Bodenfeuchte
    sprintf(buf, "<B2>%0.2f</B2>\n", bodenfeuchteProzent);
    strcat(XML, buf);
    // Soll-Bodenfeuchte
    sprintf(buf, "<V2>%0.2f</V2>\n", soll_bodenfeuchte);
    strcat(XML, buf);

    // Sendet Luftfeuchtigkeit
    // Aktuelle Luftfeuchtigkeit
    sprintf(buf, "<B3>%0.2f</B3>\n", humi);
    strcat(XML, buf);
    // Soll-Bodenfeuchte
    sprintf(buf, "<V3>%0.2f</V3>\n", soll_bodenfeuchte);
    strcat(XML, buf);



// Fügt Zustände und Einstellungen zu den XML-Daten hinzu und sendet sie an den Client
if (on_light)
{
    strcat(XML, "<LED>1</LED>\n");          // Status der LED (eingeschaltet)
    strcat(XML, "<SWITCH>1</SWITCH>\n");    // Schalterzustand (eingeschaltet)
}
else
{
    strcat(XML, "<LED>0</LED>\n");          // Status der LED (ausgeschaltet)
    strcat(XML, "<SWITCH>0</SWITCH>\n");    // Schalterzustand (ausgeschaltet)
}

// Lüfterstatus
if (on_luefter)
{
    strcat(XML, "<LUEFTER>1</LUEFTER>\n");  // Lüfterstatus (eingeschaltet)
}
else
{
    strcat(XML, "<LUEFTER>0</LUEFTER>\n");  // Lüfterstatus (ausgeschaltet)
}

// Pumpenstatus
if (on_pumpe)
{
    strcat(XML, "<PUMPE>1</PUMPE>\n");      // Pumpenstatus (eingeschaltet)
}
else
{
    strcat(XML, "<PUMPE>0</PUMPE>\n");      // Pumpenstatus (ausgeschaltet)
}

// Automatikmodus für Licht
if (auto_light)
{
    strcat(XML, "<AUTOLIGHT>1</AUTOLIGHT>\n");    // Automatikmodus für Licht (aktiviert)
}
else
{
    strcat(XML, "<AUTOLIGHT>0</AUTOLIGHT>\n");    // Automatikmodus für Licht (deaktiviert)
}

// Automatikmodus für Lüfter
if (auto_luefter)
{
    strcat(XML, "<AUTOLUEFTER>1</AUTOLUEFTER>\n");    // Automatikmodus für Lüfter (aktiviert)
}
else
{
    strcat(XML, "<AUTOLUEFTER>0</AUTOLUEFTER>\n");    // Automatikmodus für Lüfter (deaktiviert)
}

// Automatikmodus für Pumpe
if (auto_pumpe)
{
    strcat(XML, "<AUTOPUMPE>1</AUTOPUMPE>\n");    // Automatikmodus für Pumpe (aktiviert)
}
else
{
    strcat(XML, "<AUTOPUMPE>0</AUTOPUMPE>\n");    // Automatikmodus für Pumpe (deaktiviert)
}
}
// Schließt das <Data>-Element im XML und sendet es an den Client
strcat(XML, "</Data>\n");
server.send(200, "text/xml", XML);   // Sendet die XML-Daten an den Client mit dem HTTP-Statuscode 200 (OK)

