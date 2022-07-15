

/* include library */
#include <ESP8266WiFi.h>
#include<string.h>

#define red_light_pin D1
#define green_light_pin D2
#define blue_light_pin D3
/* define port */
WiFiClient client;
WiFiServer server(80);

/* WIFI settings */
const char* ssid = "Wifi_SSID";
const char* password = "password";

/* data received from application */
String  data =""; 


 
void setup()
{
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  Serial.begin(9600);
  /* start server communication */
  server.begin();
}

int i=0;
float a[3]={0};
void split(String str, char del){
    // declaring temp string to store the curr "word" upto del
      String temp = "";
   
      for( i=0; i<str.length(); i++){
        // If cur char is not del, then append it to the cur "word", otherwise
          // you have completed the word, print it, and start a new word.
         if(str[i] != del){
            temp += str[i];
        }
          else{
              a[i]=temp.toFloat();
              temp = "";
        }
    }
       
      a[2]=temp.toFloat();
}
void update_rgb(){
  for(int i=0;i<3;i++){
    a[i]+=10.0f;
    a[i]*=25.0f;
  }
  RGB_color(a[0],a[1],a[2]);
}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value){
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
void loop()
{
    /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (!client) return; 
    data = checkClient ();
    split(data,'_');
    data="";
    update_rgb();
        // Keep printing tokens while one of the
    // delimiters present in str[].
    
   
    



 
} 

String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
