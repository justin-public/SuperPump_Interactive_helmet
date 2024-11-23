/*
 * company : nines.co.ltd
 * writer : justin
 * Date : 2021 . 12 .15
 *        sound effect addtion 
 * Config frame : Config;battery rfid;event rfid;on/off
 * Device name : interactive helmat #2 
 */
#include "Sound.h"
#include "Socket.h"
#include "thread.h"
#include "Animation.h"
#include "Sound.h"
#include "ticker.h"
#include <EEPROM.h>

int data_load, init_load;
String idle_animation_csv;
String idle_animation_csv_cmp;
String idle_animation_csv_save[1];
String idle_animation;
int play_time_3min;
int play_time_1min;
int interaction_led;

int music_play_time;
int music_video;
int spectrum_led;
int spectrum_audio;

int music_play_end;
int server_connect_check;

char f[] = "";

boolean rxStart = false;
String data_line = "";

int memory_clear;

void setup() 
{
  /*********************LED*****************************/
  pixels.begin();
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(BRIGHTNESS);
  matrix.setTextColor( matrix.Color(255, 255, 255));
  // Test full bright of all LEDs. If brightness is too high
  // for your current limit (i.e. USB), decrease it.
  //matrix->fillScreen(LED_WHITE_HIGH);
  //matrix->show();
  //delay(1000);
  matrix.clear();
  //bilderanzahl=(sizeof(RGB_bmp) / sizeof(RGB_bmp[0]));
  /********************SOCKET***************************/
  WiFi.mode(WIFI_STA);
  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.println(".");
  }
  
  data_load = 1;       // 초기 설정값을 로드 하기 위한 변수
  /********************************************************/
  /************************AUDIO***************************/
  mySerial.begin(9600);
  Serial.begin(115200);
  myDFPlayer.begin(mySerial);
  if(!myDFPlayer.begin(mySerial))
  {
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(15);
  myDFPlayer.play(1);
  /**********************************************************/
  /********************THREAD********************************/
  Thread1->onRun(socketThread);
  Thread1->setInterval(1);
  controll.add(Thread1);
  flipper.attach(1,flip_timer);
  
  state_ip_check = 1;    // standby no event
  idle_animation_csv = "led_00";
  pre_timer1 = 0;
}

void socketThread()
{
  WiFiClient client;
  if(!client.connect(host,port))
  {
    int connecttry = client.connected();
    if(connecttry != 1){
      client.connect(host,port);
      data_load = 2;
    }
    return;
  }
  while (client.available() == 0){
      state_ip = client.connected();
      if(state_ip != 1){
        client.connect(host,port);
        data_load = 2;
        init_load = 1;
      }
      /*
      if(state_ip_check == 1)
      {
        client.stop();
        Serial.println("led off!!");  
        state_ip_check = 0;
      }
      */
      if(data_load == 1)
      {
        client.print("Config;3DD3CD5E;10a164;off\n");           // 10a164             
        data_load = 0;
        init_load = 1;
      }
      if(data_load == 2)
      {
        client.print("Config;3DD3CD5E;10a164;on\n"); 
        data_load = 0;
        init_load = 1;
      }
      if(music_play_end == 1){
        idle_animation_csv = "led_02";
        music_play_end = 0;
      }
      /*
      if(server_connect_check == 1)
      {
        client.print("connect;192.168.2.121\n");
        delay(10);
        server_connect_check = 0;
      }
      */
      if(idle_animation_csv == "led_00")black_off();
      if(idle_animation_csv == "led_02")rain(1,80);      // 5  --> 8   100   60   30
      if(spectrum_led == 51){
        idle_animation_csv = "   "; 
        sineWave(1, 15);
      }
      if(spectrum_led == 52){
        idle_animation_csv = "   "; 
        audioLevels(1, 15);
      }
      if(spectrum_led == 53){
        idle_animation_csv = "   "; 
        rainbow(5);
      }
      if(interaction_led == 1 && state_ip_check != 1){
         idle_animation = "   ";
         myDFPlayer.play(7);
         min_animation_three();
         interaction_led = 0;
         data_load = 1;
      }
      if(interaction_led == 2 && state_ip_check != 1){
         idle_animation = "   ";
         myDFPlayer.play(8);
         min_animation_one();
         interaction_led = 0;
         pre_timer1 = 0;
         data_load = 1; 
      }
  }
  while(client.available() > 0)
  {
    char c = client.read();
    if(rxStart == true)
    {
      if(c == '\n')
      {
          data_line_interactive(data_line);
          rxStart = false;
          data_line = "";
          
          int data_line_len = data_line.length() + 1;   
          char Temp[data_line_len];
          data_line.toCharArray(Temp,data_line_len);
          
          memset(Temp,0,sizeof(data_line_len));
      }
      else
      {
        data_line += c;
      }
    }
    else{
      if(c == 'C')rxStart = true;        // Config
      if(c == 'r')rxStart = true;        // rx01  
      if(c == 'B')rxStart = true;        // B_01
      if(c == 'o')rxStart = true;
    }
  }
}

void data_line_interactive(String data)
{
  int delimiter, delimiter_1, delimiter_2, delimiter_3 , delimiter_4, delimiter_5;
  int led_num , sound_num = 0;
  char play_time[4];
  int cmd_02_delimiter;
  
  if(init_load == 1)
  {
      delimiter = data.indexOf(";");
      delimiter_1 = data.indexOf(";", delimiter + 1);
      delimiter_2 = data.indexOf(";", delimiter_1 +1);
      delimiter_3 = data.indexOf(";", delimiter_2 +1);
      delimiter_4 = data.indexOf(";", delimiter_3 +1);

      String play_time_csv = data.substring(delimiter + 1, delimiter_1);
      idle_animation_csv = data.substring(delimiter_1 + 1, delimiter_2);
      String auto_manual_csv = data.substring(delimiter_2 + 1, delimiter_3);
      String auto_play_term_csv = data.substring(delimiter_3 + 1, delimiter_4);

      int min_len = play_time_csv.length()+1;
      char min_array[min_len];
      play_time_csv.toCharArray(min_array,min_len);
      
      play_time_3min = (atoi(min_array) * 60) - 180;
      play_time_1min = (atoi(min_array) * 60) - 60;
      
      int idle_len = idle_animation_csv.length() + 1;      // 초기 에니메이션 연출관련 명령어
      char idle_array[idle_len];  
      idle_animation_csv.toCharArray(idle_array,idle_len);

      for(int i = 0; i<idle_animation_csv.length(); i++){
        EEPROM.write(i,idle_animation_csv[i]);  
      }
      delay(500);
      init_load = 0;
  }
  delimiter = data.indexOf(";");
  delimiter_1 = data.indexOf(";", delimiter + 1);
  delimiter_2 = data.indexOf(";", delimiter_1 +1);
  delimiter_3 = data.indexOf(";", delimiter_2 +1);
  delimiter_4 = data.indexOf(";", delimiter_3 +1);

  String cmd_01 = data.substring(0, delimiter);                     
  String cmd_02 = data.substring(delimiter + 1, delimiter_1);
  String cmd_03 = data.substring(delimiter_1 + 1, delimiter_2);
  String cmd_04 = data.substring(delimiter_2 + 1, delimiter_3);
  String cmd_05 = data.substring(delimiter_3 + 1, delimiter_4);
  String cmd_06 = data.substring(delimiter_4 + 1, delimiter_5);

  Serial.print(cmd_01);
  Serial.print(" : ");
  Serial.print(cmd_02);
  Serial.print(" : ");
  Serial.print(cmd_03);
  Serial.print(" : ");
  Serial.print(cmd_04);
  Serial.print(" : ");
  Serial.print(cmd_05);
  Serial.print(" : ");
  Serial.print(cmd_06);
  Serial.println();

  if(cmd_03 == "off"){
    black_off();
  }
  if(cmd_02 == "10a164")        // Device #2 event rfid..
  {
     if(cmd_01 == "x01")
     {
       char cmd_third_num[2]; 
       char cmd_four_num[2];
        
       cmd_03.substring(5,6).toCharArray(cmd_third_num,2);
       led_num = atoi(cmd_third_num);
       
       cmd_04.substring(7,8).toCharArray(cmd_four_num,2);
       sound_num = atoi(cmd_four_num);
       
       myDFPlayer.play(sound_num);

       if(led_num == 1){
         font_animation();
         led_num = 0;
       }
       led_animation(led_num);
     }
     if(cmd_01 == "x02")
     {
       char cmd_third_num[2]; 
       char cmd_four_num[2];
        
       cmd_03.substring(5,6).toCharArray(cmd_third_num,2);
       led_num = atoi(cmd_third_num);
       
       cmd_04.substring(7,8).toCharArray(cmd_four_num,2);
       sound_num = atoi(cmd_four_num);
       
       myDFPlayer.play(sound_num);

       if(led_num == 1){
         font_animation();
         led_num = 0;
       }
       led_animation(led_num);
     }
     if(cmd_01 == "x03")
     {
       char cmd_third_num[2]; 
       char cmd_four_num[2];
        
       cmd_03.substring(5,6).toCharArray(cmd_third_num,2);
       led_num = atoi(cmd_third_num);
       
       cmd_04.substring(7,8).toCharArray(cmd_four_num,2);
       sound_num = atoi(cmd_four_num);
       
       myDFPlayer.play(sound_num);

       if(led_num == 1){
         font_animation();
         led_num = 0;
       }
       led_animation(led_num);
     }
     if(cmd_01 == "x04")
     {
       char cmd_third_num[2]; 
       char cmd_four_num[2];
        
       cmd_03.substring(5,6).toCharArray(cmd_third_num,2);
       led_num = atoi(cmd_third_num);
       
       cmd_04.substring(7,8).toCharArray(cmd_four_num,2);
       sound_num = atoi(cmd_four_num);
       
       myDFPlayer.play(sound_num);

       if(led_num == 1){
         font_animation();
         led_num = 0;
       }
       led_animation(led_num);
     }
     if(cmd_01 == "x05")
     {
       char cmd_third_num[2]; 
       char cmd_four_num[2];
        
       cmd_03.substring(5,6).toCharArray(cmd_third_num,2);
       led_num = atoi(cmd_third_num);
       
       cmd_04.substring(7,8).toCharArray(cmd_four_num,2);
       sound_num = atoi(cmd_four_num);
       
       myDFPlayer.play(sound_num);

       if(led_num == 1){
         font_animation();
         led_num = 0;
       }
       led_animation(led_num);
     }
     if(cmd_01 == "ff"){
        state_ip_check = 1;
        black_off();
        idle_animation_csv = "";
        spectrum_led = 0;
        delay(5000);
     }
     if(cmd_01 == "n"){
        //client.close();
        //client.connect(host,port);
        state_ip_check = 0;
        idle_animation_csv = "led_02";
        //data_load = 1;
     }
   }
   if(cmd_01 == "_1" && state_ip_check != 1)
   {
      char led_pattern_num[3];
      char sound_pattern_num[3];
      char play_time[4];
      
      pre_timer = 0;
      
      data.substring(7,10).toCharArray(led_pattern_num,3);
      data.substring(10,14).toCharArray(play_time,4);
      data.substring(20,23).toCharArray(sound_pattern_num,3);
      
      music_play_time = atoi(play_time);
      spectrum_led = atoi(led_pattern_num);
      spectrum_audio = atoi(sound_pattern_num);
      if(spectrum_audio == 51)myDFPlayer.play(6);
   }
   if(cmd_01 == "_2" && state_ip_check != 1)
   {
      char led_pattern_num[3];
      char sound_pattern_num[3];
      char play_time[4];
      
      pre_timer = 0;
      
      data.substring(7,10).toCharArray(led_pattern_num,3);
      data.substring(10,14).toCharArray(play_time,4);
      data.substring(20,23).toCharArray(sound_pattern_num,3);
      
      music_play_time = atoi(play_time);
      spectrum_led = atoi(led_pattern_num);
      spectrum_audio = atoi(sound_pattern_num);
      if(spectrum_audio == 51)myDFPlayer.play(6);        
   }
   if(cmd_01 == "_3" && state_ip_check != 1)
   {
      char led_pattern_num[3];
      char sound_pattern_num[3];
      char play_time[4];
      
      pre_timer = 0;
      data.substring(7,10).toCharArray(led_pattern_num,3);
      data.substring(10,14).toCharArray(play_time,4);
      data.substring(20,23).toCharArray(sound_pattern_num,3);
      
      music_play_time = atoi(play_time);
      spectrum_led = atoi(led_pattern_num);
      spectrum_audio = atoi(sound_pattern_num);
      if(spectrum_audio == 51)myDFPlayer.play(6);
   }
   if(cmd_01 == "_4" && state_ip_check != 1)
   {
      char led_pattern_num[3];
      char sound_pattern_num[3];
      char play_time[4];
      
      pre_timer = 0;
      data.substring(7,10).toCharArray(led_pattern_num,3);
      data.substring(10,14).toCharArray(play_time,4);
      data.substring(20,23).toCharArray(sound_pattern_num,3);
      
      music_play_time = atoi(play_time);
      spectrum_led = atoi(led_pattern_num);
      spectrum_audio = atoi(sound_pattern_num);
      if(spectrum_audio == 51)myDFPlayer.play(6);
   }
   if(cmd_01 == "_5" && state_ip_check != 1)
   {
      char led_pattern_num[3];
      char sound_pattern_num[3];
      char play_time[4];
      
      pre_timer = 0;
      data.substring(7,10).toCharArray(led_pattern_num,3);
      data.substring(10,14).toCharArray(play_time,4);
      data.substring(20,23).toCharArray(sound_pattern_num,3);
      
      music_play_time = atoi(play_time);
      spectrum_led = atoi(led_pattern_num);
      spectrum_audio = atoi(sound_pattern_num);
      if(spectrum_audio == 51)myDFPlayer.play(6);
   }
   if(cmd_01 == "_6" && state_ip_check != 1)
   {
      char led_pattern_num[3];
      char sound_pattern_num[3];
      char play_time[4];
      
      pre_timer = 0;
      data.substring(7,10).toCharArray(led_pattern_num,3);
      data.substring(10,14).toCharArray(play_time,4);
      data.substring(20,23).toCharArray(sound_pattern_num,3);
      
      music_play_time = atoi(play_time);
      spectrum_led = atoi(led_pattern_num);
      spectrum_audio = atoi(sound_pattern_num);
      if(spectrum_audio == 51)myDFPlayer.play(6);
   }
   if(cmd_01 == "_7" && state_ip_check != 1)
   {
      char led_pattern_num[3];
      char sound_pattern_num[3];
      char play_time[4];
      
      pre_timer = 0;
      data.substring(7,10).toCharArray(led_pattern_num,3);
      data.substring(10,14).toCharArray(play_time,4);
      data.substring(20,23).toCharArray(sound_pattern_num,3);
      
      music_play_time = atoi(play_time);
      spectrum_led = atoi(led_pattern_num);
      spectrum_audio = atoi(sound_pattern_num);
      if(spectrum_audio == 51)myDFPlayer.play(6);
   }
   if(cmd_01 == "_8" && state_ip_check != 1)
   {
      char led_pattern_num[3];
      char sound_pattern_num[3];
      char play_time[4];
      
      pre_timer = 0;
      data.substring(7,10).toCharArray(led_pattern_num,3);
      data.substring(10,14).toCharArray(play_time,4);
      data.substring(20,23).toCharArray(sound_pattern_num,3);
      
      music_play_time = atoi(play_time);
      spectrum_led = atoi(led_pattern_num);
      spectrum_audio = atoi(sound_pattern_num);
      if(spectrum_audio == 51)myDFPlayer.play(6);
   }
   if(cmd_01 == "_9" && state_ip_check != 1)
   {
      char led_pattern_num[3];
      char sound_pattern_num[3];
      char play_time[4];
      
      pre_timer = 0;
      data.substring(7,10).toCharArray(led_pattern_num,3);
      data.substring(10,14).toCharArray(play_time,4);
      data.substring(20,23).toCharArray(sound_pattern_num,3);
      
      music_play_time = atoi(play_time);
      spectrum_led = atoi(led_pattern_num);
      spectrum_audio = atoi(sound_pattern_num);
      if(spectrum_audio == 51)myDFPlayer.play(6);
   }
   if(cmd_01 == "_0" && state_ip_check != 1)
   {
      char led_pattern_num[3];
      char sound_pattern_num[3];
      char play_time[4];
      
      pre_timer = 0;
      data.substring(7,10).toCharArray(led_pattern_num,3);
      data.substring(10,14).toCharArray(play_time,4);
      data.substring(20,23).toCharArray(sound_pattern_num,3);
      
      music_play_time = atoi(play_time);
      spectrum_led = atoi(led_pattern_num);
      spectrum_audio = atoi(sound_pattern_num);
      if(spectrum_audio == 51)myDFPlayer.play(6);
   }
}

void flip_timer()
{
  pre_timer++;
  pre_timer1++;
  //pre_timer2++;
  if(pre_timer1 == play_time_3min){
    interaction_led = 1;
  }
  if(pre_timer1 == play_time_1min){
    interaction_led = 2;
  }
  if(pre_timer == music_play_time)
  {
    spectrum_led = 0;
    pre_timer = 0;
    music_play_time = 0;
    //idle_animation_csv == "led_02";
    //pre_timer = 0;
    //data_load = 1;
    music_play_end = 1;
  }
  /*
  if(pre_timer2 == 1)
  {
      server_connect_check = 1;
      pre_timer2 = 0;
  }
  */
}

void minute_animation_a(int time_d)
{
  black_off();
  delay(500);
  minute_wait_A();
  delay(time_d);
  minute_wait_B();
  delay(3000);
  black_off();
  delay(time_d);
}

void led_animation(int led_num)
{
  if(led_num == 2)
  {
    for(int i=0; i<6; i++){
      black_off();
      delay(10);
      if(i==1){
        smile_frame_2();
        delay(500);
        smile_frame_1();
        delay(500);
      }
      if(i==2){
        smile_frame_2();
        delay(500);
        smile_frame_1();
        delay(500);
      }
      if(i==3){
        smile_frame_2();
        delay(500);
        smile_frame_1();
        delay(500);
      }
      if(i==4){
        smile_frame_2();
        delay(500);
        smile_frame_1();
        delay(500);
      }
      if(i==5){
        smile_frame_2();
        delay(500);
        smile_frame_1();
        delay(500);
        led_num = 0;
      }
    }
  }
  if(led_num == 3)tunnelAnimation(pixels.Color(0,0,255), true, 5, 50);
  if(led_num == 4)drawShape(smile, pixels.Color(255,227,0), true, 5, 500);
  if(led_num == 5)
  {
    for(int i=0; i<6; i++){
      black_off();
      delay(10);
      if(i==1){
        love_frame_1();
        delay(500);
        love_frame_2();
        delay(500);
      }
      if(i==2){
        love_frame_1();
        delay(500);
        love_frame_2();
        delay(500);
      }
      if(i==3){
        love_frame_1();
        delay(500);
        love_frame_2();
        delay(500);
      }
      if(i==4){
        love_frame_1();
        delay(500);
        love_frame_2();
        delay(500);
      }
      if(i==5){
        love_frame_1();
        delay(500);
        love_frame_2();
        delay(500);
        led_num = 0;
      }
    }
  }
}

int x = matrix.width();
int pass = 0;

void font_animation()
{
  for(;;){
    matrix.fillScreen(matrix.Color(255, 255, 0));
    matrix.setCursor(x, 0);
    matrix.print(F("HI !"));
    
    if(--x < -36) {
      x = matrix.width();
      if(++pass >= 4){
        pass = 0;
        break;
      }
      matrix.setTextColor(colors[pass]);
    }
    
    matrix.show();
    delay(80);
  }
}

void min_animation_three()
{
  for(int i=0; i<6; i++)
  {
      black_off();
      delay(10);
      if(i==1){
        min_frame_three_1();
        delay(500);
        min_frame_three_2();
        delay(500);
      }
      if(i==2){
        min_frame_three_1();
        delay(500);
        min_frame_three_2();
        delay(500);
      }
      if(i==3){
        min_frame_three_1();
        delay(500);
        min_frame_three_2();
        delay(500);
      }
      if(i==4){
        min_frame_three_1();
        delay(500);
        min_frame_three_2();
        delay(500);
      }
      if(i==5){
        min_frame_three_1();
        delay(500);
        min_frame_three_2();
        //delay(500);
      }
  }
}

void min_animation_one()
{
  for(int i=0; i<6; i++)
  {
      black_off();
      delay(10);
      if(i==1){
        min_frame_one_1();
        delay(500);
        min_frame_one_2();
        delay(500);
      }
      if(i==2){
        min_frame_one_1();
        delay(500);
        min_frame_one_2();
        delay(500);
      }
      if(i==3){
        min_frame_one_1();
        delay(500);
        min_frame_one_2();
        delay(500);
      }
      if(i==4){
        min_frame_one_1();
        delay(500);
        min_frame_one_2();
        delay(500);
      }
      if(i==5){
        min_frame_one_1();
        delay(500);
        min_frame_one_2();
        //delay(500);
      }
  }
}


void loop() 
{
  //black_off();
  controll.run();
}
