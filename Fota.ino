#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

#include <ESP8266HTTPClient.h>
#include "config.h"
#include <SoftwareSerial.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Provide the SD card interfaces setting and mounting
#include <addons/SDHelper.h>

// Insert your network credentials
#define WIFI_SSID "Mohamed@Saad"
#define WIFI_PASSWORD "@saad_67"

// Insert Firebase project API Key
#define API_KEY "AIzaSyDv3MYo-5ALeFpsMw7ckfPIEt9FHuh1YGI" 

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "fir-led-sing-default-rtdb.asia-southeast1.firebasedatabase.app"                           

 //Define Firebase Data object
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

FirebaseData stream;
// Variables to save database paths

String listenerPath_code_lines= "code/lines";
String listenerPath_code_new = "code/new";
String listenerPath_line = "line";


unsigned long sendDataPrevMillis = 0;
int count = 0;
int flag=0;
bool signupOK = false;                     //since we are doing an anonymous sign in 

String fireStatus = "";                                                     // led status received from firebase
//int led = D5;  //output1
int check ;
//bool wifiConnected = false;
bool newCodeAdded = false;
SoftwareSerial __uart(D5, D6);

/* To change these values you muct change it too in STM code*/
#define OTA_DATA_START_CHAR     'X'
#define OTA_LINE_BREAK_CHAR     'Y'
#define OTA_DATA_END_CHAR       'Z'
#define OTA_READ_CONFIRM_CHAR   'R'

/*******************************/
String getLine(int i)
{
    String line;
    while (Firebase.RTDB.getString(&fbdo, "line/" + String(i), &line) == false)
    {
        delay(1);
        Serial.println("GETTING LINE: INTERNET SLOW");
    }
    return line;
}
/*******************************/

String getLine1(int i)
{
    String line1;
    while (Firebase.RTDB.getString(&fbdo, "line/" + String(i), &line1) == false)
    {
        delay(1);
        Serial.println("GETTING LINE: INTERNET SLOW");
    }
    return line1;
}

/******************************/
void sendCode(void)
{
    int lines_count;
    char receivedChar;
    String line;

    Serial.println("NEW CODE ADDED");

    /* Getting number of lines */
    Serial.println("GETTING NUMBER OF LINES");
    
    while (Firebase.RTDB.getInt(&fbdo, "/code/lines", &lines_count) == false)
    {
        Serial.println("GETTING NUMBER OF LINES: INTERNET SLOW");
        delay(1);
    }
    Serial.print("NUMBER OF LINES: ");
    Serial.println(lines_count);

     /* Sending start char and wait for confirm */
    Serial.println("SENDEING START CHAR");
    while (__uart.read() != OTA_READ_CONFIRM_CHAR)
    {
        __uart.write(OTA_DATA_START_CHAR);
        delay(1000);
    }

    Serial.println("SENDEING CODE");
    /* Sending each line */
    for (int i = 0; i < lines_count; i++)
    {
        /* Getting the line text */
        line = getLine(i);
        /* Convert string into array */
        int length = line.length() + 1;
        char line_array[length];
        line.toCharArray(line_array, length);

          /* Sending line */
        __uart.write(line_array);

        /* Sending line break char after line has ended */
        __uart.flush();
        __uart.write(OTA_LINE_BREAK_CHAR);
        while (__uart.read() != OTA_READ_CONFIRM_CHAR)
        {
            delay(1);
        }
        /* Line is now sent */
        Serial.println("LINE " + String(i + 1) + " SENT: " + line);
    }

    /* Lines has ended */
    __uart.write(OTA_DATA_END_CHAR);
    while (__uart.read() != OTA_READ_CONFIRM_CHAR)
    {
        delay(1);
    }

    Serial.println("LINES ENDED");

    /* Setting the code not new */
    while (Firebase.RTDB.setBool(&fbdo, "/code/new", false) == false)
    {
        delay(1);
        Serial.println("INTERNET SLOW");
    }
    Serial.println("ALL CODE IS FLASHED");
}
/******************************************/
void sendCode1(void)
{
    int lines_count;
    char receivedChar;
    String line1;

    Serial.println("NEW CODE FOR APP2 ADDED");

    /* Getting number of lines */
    Serial.println("GETTING NUMBER OF LINES FOR APP2");
    
    while (Firebase.RTDB.getInt(&fbdo, "/code1/lines", &lines_count) == false)
    {
        Serial.println("GETTING NUMBER OF LINES FOR APP2: INTERNET SLOW");
        delay(1);
    }
    Serial.print("NUMBER OF LINES FOR APP2: ");
    Serial.println(lines_count);

    /* Sending start char and wait for confirm */
    Serial.println("SENDING START CHAR FOR APP2");
    while (__uart.read() != OTA_READ_CONFIRM_CHAR)
    {
        __uart.write(OTA_DATA_START_CHAR);
        delay(1000);
    }

    Serial.println("SENDING CODE FOR APP2");
    /* Sending each line */
    for (int i = 0; i < lines_count; i++)
    {
        /* Getting the line text */
        line1 = getLine1(i);
        /* Convert string into array */
        int length = line1.length() + 1;
        char line_array[length];
        line1.toCharArray(line_array, length);

        /* Sending line */
        __uart.write(line_array);

        /* Sending line break char after line has ended */
        __uart.flush();
        __uart.write(OTA_LINE_BREAK_CHAR);
        while (__uart.read() != OTA_READ_CONFIRM_CHAR)
        {
            delay(1);
        }
        /* Line is now sent */
        Serial.println("LINE " + String(i + 1) + " SENT FOR APP2: " + line1);
    }

    /* Lines has ended */
    __uart.write(OTA_DATA_END_CHAR);
    while (__uart.read() != OTA_READ_CONFIRM_CHAR)
    {
        delay(1);
    }

    Serial.println("LINES ENDED FOR APP2");

    /* Setting the code not new */
    while (Firebase.RTDB.setBool(&fbdo, "/code1/new", false) == false)
    {
        delay(1);
        Serial.println("INTERNET SLOW");
    }
    Serial.println("ALL CODE FOR APP2 IS FLASHED");
}


void setup() 
{
  Serial.begin(9600);
  __uart.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h

  // Assign the maximum retry of token generation
  config.max_token_generation_retry = 5;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() 
{
  if (Firebase.isTokenExpired())
  {
    Firebase.refreshToken(&config);
    Serial.println("Refresh token");
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    // Check if new code is added for app1
       Firebase.RTDB.getInt(&fbdo, "/flags/update_flag", &flag); 
       if(flag==1)
       {
              sendCode(); // Send code for app1
              newCodeAdded = false;
       }
  }
  delay(500);
}
