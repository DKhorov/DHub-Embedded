/* 

   DHub Embedded 
   Versin: 0.1 ( Beta )

*/   


static const unsigned char PROGMEM image_download_bits[] = {0x1f,0xfc,0x00,0x10,0x04,0x00,0x17,0xf4,0x00,0x70,0x04,0x00,0x97,0xf4,0x00,0x90,0x06,0x00,0x97,0xf5,0x00,0x90,0x05,0x00,0x97,0xff,0xc0,0x98,0x00,0x40,0x98,0x00,0x40,0x90,0x00,0x80,0x90,0x00,0x80,0xa0,0x01,0x00,0xa0,0x01,0x00,0x7f,0xfe,0x00};
static const unsigned char PROGMEM image_download_1_bits[] = {0x7f,0xfc,0x90,0xaa,0x90,0xa9,0x90,0xe9,0x90,0x09,0x8f,0xf1,0x80,0x01,0x80,0x01,0x80,0x01,0x9f,0xf9,0x90,0x09,0x97,0xe9,0x90,0x09,0xd7,0xeb,0x90,0x09,0x7f,0xfe};
static const unsigned char PROGMEM image_download_bitsw[] = {0x1f,0xfc,0x00,0x10,0x04,0x00,0x17,0xf4,0x00,0x70,0x04,0x00,0x97,0xf4,0x00,0x90,0x06,0x00,0x97,0xf5,0x00,0x90,0x05,0x00,0x97,0xff,0xc0,0x98,0x00,0x40,0x98,0x00,0x40,0x90,0x00,0x80,0x90,0x00,0x80,0xa0,0x01,0x00,0xa0,0x01,0x00,0x7f,0xfe,0x00};
static const unsigned char PROGMEM image_download_1_bitsw[] = {0x07,0xc0,0x1e,0x70,0x27,0xf8,0x61,0xe4,0x43,0xe4,0x87,0xca,0x9f,0xf6,0xdf,0x82,0xdf,0x82,0xe3,0xc2,0x61,0xf4,0x70,0xf4,0x31,0xf8,0x1b,0xf0,0x07,0xc0,0x00,0x00};
static const unsigned char PROGMEM image_download_2_bitsw[] = {0x7f,0xfc,0x90,0xaa,0x90,0xa9,0x90,0xe9,0x90,0x09,0x8f,0xf1,0x80,0x01,0x80,0x01,0x80,0x01,0x9f,0xf9,0x90,0x09,0x97,0xe9,0x90,0x09,0xd7,0xeb,0x90,0x09,0x7f,0xfe};
static const unsigned char PROGMEM image_download_3_bitsw[] = {0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x18,0x86,0x18,0x86,0x18,0x86,0xd8,0x86,0xd8,0xb6,0xd8,0xb6,0xd8,0xb6,0xd8,0xb6,0xd8,0xb6,0xd8,0x80,0x00,0xff,0xfc,0x00,0x00};

#include "M5Cardputer.h"
#include <FS.h>
#include <SPIFFS.h>
M5Canvas canvas(&M5Cardputer.Display);

int ProgrammWork = 0;
int MenuPosition = 1;
int ListPosition = 1;
int BufferWords = 0;
int HTMLAnalytics =0;
int RepositoryMaxX = 230;
int RepositoryMaxY = 120;
int RepositoryStartX = 10;
int RepositoryStartY = 13;
int BlockingLoop = 0;
int WordsAnalytics1 = 0;
int WordsAnalytics2 = 0;
int WordsAnalytics3 = 0;
int WordsAnalytics4 = 0;
int WordsAnalytics5 = 0;
int WordsAnalytics6 = 0;
int WordsAnalytics7 = 0;
int WordsAnalytics8 = 0;
int BufferText = 0;
int selectedItem = 0;
String RepositoryText1 = "";
String RepositoryText2 = "";
String RepositoryText3 = "";
String RepositoryText4 = "";
String RepositoryText5 = "";
String RepositoryText6 = "";
String RepositoryText7 = "";
String RepositoryText8 = "";
String command = "";
String LogAnalytics = "";
bool cursorState = true; 
unsigned long cursorTimer = 0;
const unsigned long cursorInterval = 500;  
const char* menuItems[] = {"Termianl", "Delete all Repository", "Soon...", "Soon..."};
const int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);


void log(String bug){
    LogAnalytics = bug;
    Serial.print(LogAnalytics+" "+" - DHub System ORC");
}

void setup() {
  Serial.begin(115200); // Подключение Serial порта
  if (!SPIFFS.begin(true)) {
    Serial.println("Ошибка монтирования SPIFFS");
    return;
  }
  auto cfg = M5.config(); // инт. m5.config
  cfg.output_power = true; // задаем cfg.output_power в true
  M5Cardputer.begin(cfg,true); // инт. M5Cardputer
  M5Cardputer.Display.setTextColor(0xFFEA);
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.setFreeFont(&FreeSansBold18pt7b);
  M5Cardputer.Display.drawString("DHub", 71, 44);
  M5Cardputer.Display.setTextColor(0xFFFF);
  M5Cardputer.Display.setFreeFont();
  M5Cardputer.Display.drawString("DHub Embedded 0.1v", 67, 120);
  M5Cardputer.Display.setTextColor(0xFFFF);
  M5Cardputer.Display.drawString("Beta", 155, 73);
  delay(1500); // time out 1,5s
  M5Cardputer.Display.fillRect(-4, -2, 247, 138, 0x0); // создание черного фона 
  DHubMenuGUI();
  DHubPanelGUI();
}

void updateData() {
  File file = SPIFFS.open("/example.txt", FILE_WRITE);
  if (!file) {
    Serial.println("Ошибка открытия файла для записи");
    return;
  }

  // Данные для записи
  String data = "Обновленные данные: " + String(millis());
  file.println(data);
  file.close();
  Serial.println("Данные успешно записаны в файл");
}


void dev(){
  static const unsigned char PROGMEM logo[] = {0x80,0xe0,0xc1,0x60,0x42,0x80,0x22,0x8c,0x13,0x0c,0x0a,0xb4,0x06,0x48,0x05,0xf0,0x0b,0x00,0x14,0xe0,0x29,0xb0,0x50,0xd8,0xa0,0x6c,0xc0,0x34,0x00,0x1c,0x00,0x00};
  M5Cardputer.Display.fillRect(2, 84, 237, 51, 0x0);
  M5Cardputer.Display.drawRect(2, 1, 237, 134, 0xA800);
  M5Cardputer.Display.setTextColor(0xF800);
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.setFreeFont();
  M5Cardputer.Display.drawString("DHub Embedded - Version ---", 10, 91);
  M5Cardputer.Display.setTextColor(0xA800);
  M5Cardputer.Display.drawString("CPU: ESP32-S3 40MHz", 10, 102);
  M5Cardputer.Display.drawString("Core: DHub ORC 3.5", 10, 111);
  M5Cardputer.Display.drawString("LCD 240x135 ", 10, 121);
  M5Cardputer.Display.setTextColor(0xE0A2);
  M5Cardputer.Display.drawString("Repository:", 82, 121);
  M5Cardputer.Display.setTextColor(0xA800);
  M5Cardputer.Display.drawString("1", 148, 122);
  M5Cardputer.Display.setTextColor(0xD082);
  M5Cardputer.Display.drawString("ProgrammWork:", 122, 111);
  M5Cardputer.Display.setTextColor(0xA800);
  M5Cardputer.Display.drawString("1", 199, 111);
  M5Cardputer.Display.setTextColor(0xD020);
  M5Cardputer.Display.drawString("WordsAnalytics:", 129, 102);
  M5Cardputer.Display.setTextColor(0xA800);
  M5Cardputer.Display.drawString("300", 219, 102);
  M5Cardputer.Display.setTextColor(0xF800);
  M5Cardputer.Display.drawString("DevTools", 185, 123);
  M5Cardputer.Display.drawBitmap(217, 6, logo, 14, 16, 0xF800);
  M5Cardputer.Display.setTextColor(0xA800);
  M5Cardputer.Display.drawString("Log and Bug:", 6, 4);
  M5Cardputer.Display.setTextColor(0xFFEA);
  M5Cardputer.Display.drawString("Text", 16, 16);


  



}


void DHubPanelGUI(){
    float battery_voltage = M5Cardputer.Power.getBatteryVoltage();
    int battery_percentage = M5Cardputer.Power.getBatteryLevel();
    String batteryStr = String(battery_percentage);
    M5Cardputer.Display.drawRoundRect(5, -3, 229, 22, 3, 0xA815);
    M5Cardputer.Display.setTextColor(0xFFEA);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setFreeFont();
    M5Cardputer.Display.drawString(batteryStr, 196, 6);
    M5Cardputer.Display.setTextColor(0xFFFF);
    M5Cardputer.Display.drawString("", 98, 43);
    M5Cardputer.Display.setTextColor(0xFFEA);
    M5Cardputer.Display.drawString("DHub Embedded", 12, 6);
    M5Cardputer.Display.setTextColor(0xFFFF);
    M5Cardputer.Display.drawString("", 75, 120);
    M5Cardputer.Display.drawLine(180, 120, 180, 139, 0xA815);
    M5Cardputer.Display.drawLine(0, 119, 240, 119, 0xA815);
    M5Cardputer.Display.setTextColor(0xF81E);
    M5Cardputer.Display.drawString("(c) DK Studio 2024", 6, 124);
    M5Cardputer.Display.setTextColor(0x57EA);
    if (ProgrammWork==9){
          M5Cardputer.Display.drawString("Menu Apps", 104, 6);
    }else{
        M5Cardputer.Display.drawString("DHub Main", 104, 6);
    }
    M5Cardputer.Display.setTextColor(0xFABF);
    M5Cardputer.Display.drawString("ESP32", 195, 124);
    M5Cardputer.Display.drawLine(98, -2, 98, 17, 0xA815);
    M5Cardputer.Display.drawLine(190, -2, 190, 17, 0xA815);
    M5Cardputer.Display.setTextColor(0xF811);
    M5Cardputer.Display.drawString("%", 222, 6);
}

void DHubMenuGUI() {
  switch (MenuPosition) {
    case 0:
      MenuPosition = 1;
      break;
    case 1:
        M5Cardputer.Display.clear();
        DHubPanelGUI();
        M5Cardputer.Display.drawRoundRect(5, 21, 229, 93, 3, 0xA815);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("Welcome to ", 16, 32);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 114, 70);
        M5Cardputer.Display.drawString("", 94, 107);
        M5Cardputer.Display.setTextColor(0xAD55);
        M5Cardputer.Display.drawString("Special verison DHub for ESP32", 33, 57);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("", 149, 65);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 75, 120);
        M5Cardputer.Display.setTextColor(0xFFEA);
        M5Cardputer.Display.drawString("Repository list", 121, 79);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("DHub", 157, 32);
        M5Cardputer.Display.setTextColor(0xAD55);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("press / for next", 120, 89);
        M5Cardputer.Display.setTextColor(0xFABF);
        M5Cardputer.Display.drawString("opt - Open menu", 15, 81);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.drawString("", 176, 94);
        M5Cardputer.Display.drawLine(29, 93, 17, 105, 0xFFFF);
        M5Cardputer.Display.drawLine(17, 105, 17, 97, 0xFFFF);
        M5Cardputer.Display.drawLine(217, 85, 226, 85, 0xFFFF);
        M5Cardputer.Display.drawLine(17, 105, 24, 105, 0xFFFF);
        M5Cardputer.Display.drawLine(228, 85, 224, 81, 0xFFFF);
        M5Cardputer.Display.drawLine(225, 85, 228, 85, 0xFFFF);
        M5Cardputer.Display.drawLine(228, 85, 224, 89, 0xFFFF);
    break;
    case 2:
        M5Cardputer.Display.clear();
        DHubPanelGUI();
        M5Cardputer.Display.drawRoundRect(5, 21, 229, 93, 3, 0xA815);
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 114, 70);
        M5Cardputer.Display.drawString("", 94, 107);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("Repository 1", 13, 33);
        M5Cardputer.Display.setTextColor(0xAD55);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("DHub RepositoryCenter", 15, 59);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("", 149, 65);
        M5Cardputer.Display.drawBitmap(179, 33, image_download_bitsw, 18, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 75, 120);
        M5Cardputer.Display.drawBitmap(206, 46, image_download_1_bitsw, 15, 16, 0xFFFF);
        M5Cardputer.Display.drawBitmap(183, 59, image_download_2_bitsw, 16, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 42, 82);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 176, 94);
        M5Cardputer.Display.drawBitmap(209, 72, image_download_3_bitsw, 14, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 48, 90);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("204 Words /", 15, 100);
        M5Cardputer.Display.setTextColor(0x57EA);
        M5Cardputer.Display.drawString("active", 85, 100);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.drawString("/ ORC 3.5", 126, 100);
      break;
      case 3:
        M5Cardputer.Display.clear();
        DHubPanelGUI();
        M5Cardputer.Display.drawRoundRect(5, 21, 229, 93, 3, 0xA815);
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 114, 70);
        M5Cardputer.Display.drawString("", 94, 107);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("Repository 2", 13, 33);
        M5Cardputer.Display.setTextColor(0xAD55);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("DHub RepositoryCenter", 15, 59);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("", 149, 65);
        M5Cardputer.Display.drawBitmap(179, 33, image_download_bitsw, 18, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 75, 120);
        M5Cardputer.Display.drawBitmap(206, 46, image_download_1_bitsw, 15, 16, 0xFFFF);
        M5Cardputer.Display.drawBitmap(183, 59, image_download_2_bitsw, 16, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 42, 82);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 176, 94);
        M5Cardputer.Display.drawBitmap(209, 72, image_download_3_bitsw, 14, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 48, 90);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("204 Words /", 15, 100);
        M5Cardputer.Display.setTextColor(0x57EA);
        M5Cardputer.Display.drawString("active", 85, 100);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.drawString("/ ORC 3.5", 126, 100);
      break;
      case 4:
       M5Cardputer.Display.clear();
        DHubPanelGUI();
        M5Cardputer.Display.drawRoundRect(5, 21, 229, 93, 3, 0xA815);
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 114, 70);
        M5Cardputer.Display.drawString("", 94, 107);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("Repository 3", 13, 33);
        M5Cardputer.Display.setTextColor(0xAD55);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("DHub RepositoryCenter", 15, 59);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("", 149, 65);
        M5Cardputer.Display.drawBitmap(179, 33, image_download_bitsw, 18, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 75, 120);
        M5Cardputer.Display.drawBitmap(206, 46, image_download_1_bitsw, 15, 16, 0xFFFF);
        M5Cardputer.Display.drawBitmap(183, 59, image_download_2_bitsw, 16, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 42, 82);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 176, 94);
        M5Cardputer.Display.drawBitmap(209, 72, image_download_3_bitsw, 14, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 48, 90);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("204 Words /", 15, 100);
        M5Cardputer.Display.setTextColor(0x57EA);
        M5Cardputer.Display.drawString("active", 85, 100);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.drawString("/ ORC 3.5", 126, 100);
      break;      
      case 5:
        M5Cardputer.Display.clear();
        DHubPanelGUI();
        M5Cardputer.Display.drawRoundRect(5, 21, 229, 93, 3, 0xA815);
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 114, 70);
        M5Cardputer.Display.drawString("", 94, 107);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("Repository 4", 13, 33);
        M5Cardputer.Display.setTextColor(0xAD55);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("DHub RepositoryCenter", 15, 59);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("", 149, 65);
        M5Cardputer.Display.drawBitmap(179, 33, image_download_bitsw, 18, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 75, 120);
        M5Cardputer.Display.drawBitmap(206, 46, image_download_1_bitsw, 15, 16, 0xFFFF);
        M5Cardputer.Display.drawBitmap(183, 59, image_download_2_bitsw, 16, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 42, 82);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 176, 94);
        M5Cardputer.Display.drawBitmap(209, 72, image_download_3_bitsw, 14, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 48, 90);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("204 Words /", 15, 100);
        M5Cardputer.Display.setTextColor(0x57EA);
        M5Cardputer.Display.drawString("active", 85, 100);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.drawString("/ ORC 3.5", 126, 100);
      break;      
      case 6:  
 M5Cardputer.Display.clear();
        DHubPanelGUI();
        M5Cardputer.Display.drawRoundRect(5, 21, 229, 93, 3, 0xA815);
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 114, 70);
        M5Cardputer.Display.drawString("", 94, 107);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("Repository 5", 13, 33);
        M5Cardputer.Display.setTextColor(0xAD55);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("DHub RepositoryCenter", 15, 59);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("", 149, 65);
        M5Cardputer.Display.drawBitmap(179, 33, image_download_bitsw, 18, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 75, 120);
        M5Cardputer.Display.drawBitmap(206, 46, image_download_1_bitsw, 15, 16, 0xFFFF);
        M5Cardputer.Display.drawBitmap(183, 59, image_download_2_bitsw, 16, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 42, 82);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 176, 94);
        M5Cardputer.Display.drawBitmap(209, 72, image_download_3_bitsw, 14, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 48, 90);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("204 Words /", 15, 100);
        M5Cardputer.Display.setTextColor(0x57EA);
        M5Cardputer.Display.drawString("active", 85, 100);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.drawString("/ ORC 3.5", 126, 100);
      break;   
      case 7:     
       M5Cardputer.Display.clear();
        DHubPanelGUI();
        M5Cardputer.Display.drawRoundRect(5, 21, 229, 93, 3, 0xA815);
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 114, 70);
        M5Cardputer.Display.drawString("", 94, 107);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("Repository 6", 13, 33);
        M5Cardputer.Display.setTextColor(0xAD55);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("DHub RepositoryCenter", 15, 59);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("", 149, 65);
        M5Cardputer.Display.drawBitmap(179, 33, image_download_bitsw, 18, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 75, 120);
        M5Cardputer.Display.drawBitmap(206, 46, image_download_1_bitsw, 15, 16, 0xFFFF);
        M5Cardputer.Display.drawBitmap(183, 59, image_download_2_bitsw, 16, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 42, 82);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 176, 94);
        M5Cardputer.Display.drawBitmap(209, 72, image_download_3_bitsw, 14, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 48, 90);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("204 Words /", 15, 100);
        M5Cardputer.Display.setTextColor(0x57EA);
        M5Cardputer.Display.drawString("active", 85, 100);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.drawString("/ ORC 3.5", 126, 100);
      break;  
      case 8:
       M5Cardputer.Display.clear();
        DHubPanelGUI();
        M5Cardputer.Display.drawRoundRect(5, 21, 229, 93, 3, 0xA815);
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 114, 70);
        M5Cardputer.Display.drawString("", 94, 107);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("Repository 7", 13, 33);
        M5Cardputer.Display.setTextColor(0xAD55);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("DHub RepositoryCenter", 15, 59);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("", 149, 65);
        M5Cardputer.Display.drawBitmap(179, 33, image_download_bitsw, 18, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 75, 120);
        M5Cardputer.Display.drawBitmap(206, 46, image_download_1_bitsw, 15, 16, 0xFFFF);
        M5Cardputer.Display.drawBitmap(183, 59, image_download_2_bitsw, 16, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 42, 82);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 176, 94);
        M5Cardputer.Display.drawBitmap(209, 72, image_download_3_bitsw, 14, 16, 0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 48, 90);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("204 Words /", 15, 100);
        M5Cardputer.Display.setTextColor(0x57EA);
        M5Cardputer.Display.drawString("active", 85, 100);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.drawString("/ ORC 3.5", 126, 100);
      break;  
      case 9:
         MenuPosition= 0;
      break;  
  }
}

void loop() {
  M5Cardputer.update();
  if (WordsAnalytics1>=204){
      M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
      log("Repository 1 exceeds character limit. Maximum characters can only be 240");
  }
  if (WordsAnalytics2>=204){
      M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
      log("Repository 2 exceeds character limit. Maximum characters can only be 240");
  }
  if (WordsAnalytics3>=204){
      M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
      log("Repository 3 exceeds character limit. Maximum characters can only be 240");
  }
  if (WordsAnalytics4>=204){
      M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
      log("Repository 4 exceeds character limit. Maximum characters can only be 240");
  }
  if (WordsAnalytics5>=204){
      M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
      log("Repository 5 exceeds character limit. Maximum characters can only be 240");
  }
  if (WordsAnalytics6>=204){
      M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
      log("Repository 6 exceeds character limit. Maximum characters can only be 240");
  }
  if (WordsAnalytics7>=204){
      M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
      log("Repository 7 exceeds character limit. Maximum characters can only be 240");
  }
  if (WordsAnalytics8>=204){
      M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
      log("Repository 8 exceeds character limit. Maximum characters can only be 240");
  }

  switch (BlockingLoop) {
    case 1:
       log("loop Block 1");
       Repository1();
       BlockingLoop=0;
    break;
    case 2:
       log("loop Block 2");
       Repository2();
       BlockingLoop=0;
    break;
    case 3:
       log("loop Block 3");
       Repository3();
       BlockingLoop=0;
    break;
    case 4:
       log("loop Block 4");
       Repository4();
       BlockingLoop=0;
    break;
    case 5:
       log("loop Block 5");
       Repository5();
       BlockingLoop=0;
    break;
    case 6:
       log("loop Block 6");
       Repository6();
       BlockingLoop=0;
    break;
    case 7:
       log("loop Block 7");
       Repository7();
       BlockingLoop=0;
    break;
    case 8:
       log("loop Block 8");
       Repository8();
       BlockingLoop=0;
    break;
    case 9:
       log("loop Block 9");
       listmenu();
       BlockingLoop=0;
    break;
    case 10:
       log("loop Block 10");
       terminal();
       BlockingLoop=0;
    break;
  }

  if (M5Cardputer.BtnA.wasPressed()) {
    M5Cardputer.Speaker.tone(8000, 20);
    BlockingLoop=9;
    ProgrammWork=9;
    listmenu(); 
  }

  if (M5Cardputer.Keyboard.isChange()) {
    if (M5Cardputer.Keyboard.isPressed()) {
        Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
        
        if (status.fn) {
            M5Cardputer.Speaker.tone(8000, 20);
            if (ProgrammWork == 1){
                      File file = SPIFFS.open("/rep1.txt", FILE_WRITE);
                  if (!file) {
                     Serial.println("Ошибка открытия файла для записи");
                     return;
                  }
                  String data = RepositoryText1 ;
                  file.println(data);
                  file.close();
                  Serial.println("Данные успешно записаны в файл");
         
            }
            if (ProgrammWork == 2){
                  File file = SPIFFS.open("/rep2.txt", FILE_WRITE);
                  if (!file) {
                     Serial.println("Ошибка открытия файла для записи");
                     return;
                  }
                  String data = RepositoryText2 ;
                  file.println(data);
                  file.close();
                  Serial.println("Данные успешно записаны в файл");
         
            }
            if (ProgrammWork == 3){
                  File file = SPIFFS.open("/rep3.txt", FILE_WRITE);
                  if (!file) {
                     Serial.println("Ошибка открытия файла для записи");
                     return;
                  }
                  String data = RepositoryText3 ;
                  file.println(data);
                  file.close();
                  Serial.println("Данные успешно записаны в файл");
         
            }
            if (ProgrammWork == 4){
                  File file = SPIFFS.open("/rep4.txt", FILE_WRITE);
                  if (!file) {
                     Serial.println("Ошибка открытия файла для записи");
                     return;
                  }
                  String data = RepositoryText4 ;
                  file.println(data);
                  file.close();
                  Serial.println("Данные успешно записаны в файл");
         
            }
            if (ProgrammWork == 5){
                  File file = SPIFFS.open("/rep5.txt", FILE_WRITE);
                  if (!file) {
                     Serial.println("Ошибка открытия файла для записи");
                     return;
                  }
                  String data = RepositoryText5 ;
                  file.println(data);
                  file.close();
                  Serial.println("Данные успешно записаны в файл");
         
            }
            if (ProgrammWork == 6){
                  File file = SPIFFS.open("/rep6.txt", FILE_WRITE);
                  if (!file) {
                     Serial.println("Ошибка открытия файла для записи");
                     return;
                  }
                  String data = RepositoryText6 ;
                  file.println(data);
                  file.close();
                  Serial.println("Данные успешно записаны в файл");
         
            }
            if (ProgrammWork == 7){
                  File file = SPIFFS.open("/rep7.txt", FILE_WRITE);
                  if (!file) {
                     Serial.println("Ошибка открытия файла для записи");
                     return;
                  }
                  String data = RepositoryText7 ;
                  file.println(data);
                  file.close();
                  Serial.println("Данные успешно записаны в файл");
         
            }
            if (ProgrammWork == 8){
                  File file = SPIFFS.open("/rep8.txt", FILE_WRITE);
                  if (!file) {
                     Serial.println("Ошибка открытия файла для записи");
                     return;
                  }
                  String data = RepositoryText8 ;
                  file.println(data);
                  file.close();
                  Serial.println("Данные успешно записаны в файл");
         
            }
           
            M5Cardputer.Display.clear();
            RepositoryText1 = "";
            RepositoryText2 = "";
            RepositoryText3 = "";
            RepositoryText4 = "";
            RepositoryText5 = "";
            RepositoryText6 = "";
            RepositoryText7 = "";
            RepositoryText8 = "";
            ProgrammWork=0;
            DHubMenuGUI();
        }
        if (status.opt) {
                   File file = SPIFFS.open("/rep1.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       Serial.write(file.read());
                   }
                   file.close();

        }           
        if (status.tab) {
          log("hull");
        }
        if (status.alt) {
          log("hull");
        }
        if (status.del) {
          switch (ProgrammWork) {
                case 1:
                   RepositoryText1.remove(RepositoryText1.length() - 1);
                   Repository1();
                   WordsAnalytics1--;
                break;
                case 2:
                   RepositoryText2.remove(RepositoryText2.length() - 1);
                   Repository2();
                   WordsAnalytics1--;
                break;
                case 3:
                   RepositoryText3.remove(RepositoryText3.length() - 1);
                   Repository3();
                   WordsAnalytics3--;
                break;
                case 4:
                   RepositoryText4.remove(RepositoryText4.length() - 1);
                   Repository4();
                   WordsAnalytics4--;
                break;
                case 5:
                   RepositoryText5.remove(RepositoryText5.length() - 1);
                   Repository4();
                   WordsAnalytics5--;
                break;
                case 6:
                   RepositoryText6.remove(RepositoryText6.length() - 1);
                   Repository6();
                   WordsAnalytics6--;
                break;
                case 7:
                   RepositoryText7.remove(RepositoryText7.length() - 1);
                   Repository7();
                   WordsAnalytics7--;
                break;
                case 8:
                   RepositoryText8.remove(RepositoryText8.length() - 1);
                   Repository8();
                   WordsAnalytics8--;
                break;
             }
        }
        if (status.enter) {
             switch (ProgrammWork) {
                case 1:
                  RepositoryText1 += '\n';
                  WordsAnalytics1++;
                break;
                case 2:
                  RepositoryText2 += '\n';
                  WordsAnalytics2++;
                break;
                case 3:
                  RepositoryText3 += '\n';
                  WordsAnalytics3++;
                break;
                case 4:
                  RepositoryText4 += '\n';
                  WordsAnalytics4++;
                break;
                case 5:
                  RepositoryText5 += '\n';
                  WordsAnalytics5++;
                break;
                case 6:
                  RepositoryText6 += '\n';
                  WordsAnalytics6++;
                break;
                case 7:
                  RepositoryText7 += '\n';
                  WordsAnalytics7++;
                break;
                case 8:
                  RepositoryText8 += '\n';
                  WordsAnalytics8++;
                break;
                case 9:
                    executeAction(selectedItem);
                break;
                default:
                  M5Cardputer.Speaker.tone(8000, 20);
                  executeAction();
                  DHubMenuGUI();
                break;
             }
        }
        for (auto i : status.word) {
          if (ProgrammWork==1){
              WordsAnalytics1++;
              if (i == '\r' || i == '\n') {  
                 RepositoryText1 += '\n';
              } else if (i == 27) {  
                 RepositoryText1 = "";  
              } else {
                 RepositoryText1 += i;
              }
              Repository1();
          }
          if (ProgrammWork==2){
              WordsAnalytics2++;
              if (i == '\r' || i == '\n') {  
                 RepositoryText2 += '\n';
              } else if (i == 27) {  
                 RepositoryText2 = "";  
              } else {
                 RepositoryText2 += i;
              }
              Repository2();
          }
          if (ProgrammWork==3){
              WordsAnalytics3++;
              if (i == '\r' || i == '\n') {  
                 RepositoryText3 += '\n';
              } else if (i == 27) {  
                 RepositoryText3 = "";  
              } else {
                 RepositoryText3 += i;
              }
              Repository3();
          }
          if (ProgrammWork==4){
              WordsAnalytics4++;
              if (i == '\r' || i == '\n') {  
                 RepositoryText4 += '\n';
              } else if (i == 27) {  
                 RepositoryText4 = "";  
              } else {
                 RepositoryText4 += i;
              }
              Repository4();
          }
          if (ProgrammWork==5){
              WordsAnalytics5++;
              if (i == '\r' || i == '\n') {  
                 RepositoryText5 += '\n';
              } else if (i == 27) {  
                 RepositoryText5 = "";  
              } else {
                 RepositoryText5 += i;
              }
              Repository5();
          }
          if (ProgrammWork==6){
              WordsAnalytics6++;
              if (i == '\r' || i == '\n') {  
                 RepositoryText6 += '\n';
              } else if (i == 27) {  
                 RepositoryText6 = "";  
              } else {
                 RepositoryText6 += i;
              }
              Repository6();
          }
          if (ProgrammWork==7){
              WordsAnalytics7++;
              if (i == '\r' || i == '\n') {  
                 RepositoryText7 += '\n';
              } else if (i == 27) {  
                 RepositoryText7 = "";  
              } else {
                 RepositoryText7 += i;
              }
              Repository7();
          }
          if (ProgrammWork==8){
              WordsAnalytics8++;
              if (i == '\r' || i == '\n') {  
                 RepositoryText8 += '\n';
              } else if (i == 27) {  
                 RepositoryText8 = "";  
              } else {
                 RepositoryText8 += i;
              }
              Repository8();
          }
             if (ProgrammWork==9){       
                M5Cardputer.Speaker.tone(8000, 20);
                command += i;
                terminal();

             }
        }




        if (ProgrammWork==9){
              if (M5Cardputer.Keyboard.isKeyPressed(';')) {
                 selectedItem = (selectedItem + 1) % menuLength;          
                listmenu();
              }
              if (M5Cardputer.Keyboard.isKeyPressed('.')) {
                        selectedItem = (selectedItem - 1 + menuLength) % menuLength;
                        listmenu();
              } 
        }
        if (M5Cardputer.Keyboard.isKeyPressed('/')) {
          switch (ProgrammWork) {
                case 1:
                    RepositoryText1+"/";
                break;
                case 2:
                    RepositoryText2+"/";
                break;
                case 3:
                    RepositoryText3+"/";
                break;
                case 4:
                    RepositoryText4+"/";
                break;
                case 5:
                     RepositoryText5+"/";
                break;
                case 6:
                     RepositoryText6+"/";
                break;
                case 7:
                    RepositoryText7+"/";
                break;
                case 8:
                    RepositoryText8+"/";
                break;
                default:
                  M5Cardputer.Speaker.tone(5000, 20);
                  MenuPosition++;
                  DHubMenuGUI();
                break;
          }

        }
        if (M5Cardputer.Keyboard.isKeyPressed(',')) {
          switch (ProgrammWork) {
                case 1:
                    RepositoryText1+",";
                break;
                case 2:
                    RepositoryText2+",";
                break;
                case 3:
                    RepositoryText3+",";
                break;
                case 4:
                    RepositoryText4+",";
                break;
                case 5:
                     RepositoryText5+",";
                break;
                case 6:
                     RepositoryText6+",";
                break;
                case 7:
                    RepositoryText7+",";
                break;
                case 8:
                    RepositoryText8+",";
                break;
                default:
                  MenuPosition--;
                  DHubMenuGUI();
                break;
          }
        }
    }
  }
}

void Repository1(){
      if (ProgrammWork == 1){
         M5Cardputer.Display.clear();
      }
      int x = RepositoryStartX;
      int y = RepositoryStartY;
      bool overflow = false;
      M5Cardputer.Display.drawRect(128, 113, 67, 15, 0xFFFF);
      M5Cardputer.Display.setTextColor(0xAD55);
      M5Cardputer.Display.drawString("Words", 135, 117);
      M5Cardputer.Display.setTextColor(0xFFFF);
      String stringNumber = String(WordsAnalytics1); // Преобразование int в String
      M5Cardputer.Display.drawString(stringNumber, 169, 117);

      for (int i = 0; i < RepositoryText1.length(); i++) {
       if (RepositoryText1[i] == '\n' || x + 10 > RepositoryMaxX) {
         y += 12; // Уменьшенная высота строки
         x = RepositoryStartX; // Начало новой строки
    
         if (y >= RepositoryMaxY) {
           overflow = true;
           M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
        break;
         }
       }
  
       if (RepositoryText1[i] != '\n') {
         M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
         M5Cardputer.Display.drawChar(RepositoryText1[i], x, y);
         x += 10; // Ширина символа
       }
  }


  // Рисование мигающего курсора
  if (cursorState) {
    M5Cardputer.Display.drawChar('_', x, y);  // Курсор
  }

  // Звуковое предупреждение, если текст выходит за границы
  if (overflow) {
    tone(9, 1000);  // Включить зуммер на 1000 Гц
    delay(100);
    noTone(9);  // Выключить зуммер
  }
  }



void Repository2(){
      if (ProgrammWork == 2){
         M5Cardputer.Display.clear();
      }
      int x = RepositoryStartX;
      int y = RepositoryStartY;
      bool overflow = false;
      M5Cardputer.Display.drawRect(128, 113, 67, 15, 0xFFFF);
      M5Cardputer.Display.setTextColor(0xAD55);
      M5Cardputer.Display.drawString("Words", 135, 117);
      M5Cardputer.Display.setTextColor(0xFFFF);
      String stringNumber = String(WordsAnalytics2); // Преобразование int в String
      M5Cardputer.Display.drawString(stringNumber, 169, 117);

      for (int i = 0; i < RepositoryText2.length(); i++) {
       if (RepositoryText2[i] == '\n' || x + 10 > RepositoryMaxX) {
         y += 12; // Уменьшенная высота строки
         x = RepositoryStartX; // Начало новой строки
    
         if (y >= RepositoryMaxY) {
           overflow = true;
           M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
        break;
         }
       }
  
       if (RepositoryText2[i] != '\n') {
         M5Cardputer.Display.drawChar(RepositoryText2[i], x, y);
         x += 10; // Ширина символа
       }
 }


  // Рисование мигающего курсора
  if (cursorState) {
    M5Cardputer.Display.drawChar('_', x, y);  // Курсор
  }

  // Звуковое предупреждение, если текст выходит за границы
  if (overflow) {
    tone(9, 1000);  // Включить зуммер на 1000 Гц
    delay(100);
    noTone(9);  // Выключить зуммер
  }
  }



void Repository3(){
      if (ProgrammWork == 3){
         M5Cardputer.Display.clear();
      }      
      int x = RepositoryStartX;
      int y = RepositoryStartY;
      bool overflow = false;
      M5Cardputer.Display.drawRect(128, 113, 67, 15, 0xFFFF);
      M5Cardputer.Display.setTextColor(0xAD55);
      M5Cardputer.Display.drawString("Words", 135, 117);
      M5Cardputer.Display.setTextColor(0xFFFF);
      String stringNumber = String(WordsAnalytics3); // Преобразование int в String
      M5Cardputer.Display.drawString(stringNumber, 169, 117);

      for (int i = 0; i < RepositoryText3.length(); i++) {
       if (RepositoryText3[i] == '\n' || x + 10 > RepositoryMaxX) {
         y += 12; // Уменьшенная высота строки
         x = RepositoryStartX; // Начало новой строки
    
         if (y >= RepositoryMaxY) {
           overflow = true;
           M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
        break;
         }
       }
  
       if (RepositoryText3[i] != '\n') {
         M5Cardputer.Display.drawChar(RepositoryText3[i], x, y);
         x += 10; // Ширина символа
       }
 }


  // Рисование мигающего курсора
  if (cursorState) {
    M5Cardputer.Display.drawChar('_', x, y);  // Курсор
  }

  // Звуковое предупреждение, если текст выходит за границы
  if (overflow) {
    tone(9, 1000);  // Включить зуммер на 1000 Гц
    delay(100);
    noTone(9);  // Выключить зуммер
  }
  }



void Repository4(){
      if (ProgrammWork == 4){
         M5Cardputer.Display.clear();
      }  
      int x = RepositoryStartX;
      int y = RepositoryStartY;
      bool overflow = false;
      M5Cardputer.Display.drawRect(128, 113, 67, 15, 0xFFFF);
      M5Cardputer.Display.setTextColor(0xAD55);
      M5Cardputer.Display.drawString("Words", 135, 117);
      M5Cardputer.Display.setTextColor(0xFFFF);
      String stringNumber = String(WordsAnalytics4); // Преобразование int в String
      M5Cardputer.Display.drawString(stringNumber, 169, 117);

      for (int i = 0; i < RepositoryText4.length(); i++) {
       if (RepositoryText4[i] == '\n' || x + 10 > RepositoryMaxX) {
         y += 12; // Уменьшенная высота строки
         x = RepositoryStartX; // Начало новой строки
    
         if (y >= RepositoryMaxY) {
           overflow = true;
           M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
        break;
         }
       }
  
       if (RepositoryText4[i] != '\n') {
         M5Cardputer.Display.drawChar(RepositoryText4[i], x, y);
         x += 10; // Ширина символа
       }
 }


  // Рисование мигающего курсора
  if (cursorState) {
    M5Cardputer.Display.drawChar('_', x, y);  // Курсор
  }

  // Звуковое предупреждение, если текст выходит за границы
  if (overflow) {
    tone(9, 1000);  // Включить зуммер на 1000 Гц
    delay(100);
    noTone(9);  // Выключить зуммер
  }
  }



void Repository5(){
      if (ProgrammWork == 5){
        M5Cardputer.Display.clear();
      }
      int x = RepositoryStartX;
      int y = RepositoryStartY;
      bool overflow = false;
      M5Cardputer.Display.drawRect(128, 113, 67, 15, 0xFFFF);
      M5Cardputer.Display.setTextColor(0xAD55);
      M5Cardputer.Display.drawString("Words", 135, 117);
      M5Cardputer.Display.setTextColor(0xFFFF);
      String stringNumber = String(WordsAnalytics5); // Преобразование int в String
      M5Cardputer.Display.drawString(stringNumber, 169, 117);

      for (int i = 0; i < RepositoryText5.length(); i++) {
       if (RepositoryText5[i] == '\n' || x + 10 > RepositoryMaxX) {
         y += 12; // Уменьшенная высота строки
         x = RepositoryStartX; // Начало новой строки
    
         if (y >= RepositoryMaxY) {
           overflow = true;
           M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
        break;
         }
       }
  
       if (RepositoryText5[i] != '\n') {
         M5Cardputer.Display.drawChar(RepositoryText5[i], x, y);
         x += 10; // Ширина символа
       }
 }


  // Рисование мигающего курсора
  if (cursorState) {
    M5Cardputer.Display.drawChar('_', x, y);  // Курсор
  }

  // Звуковое предупреждение, если текст выходит за границы
  if (overflow) {
    tone(9, 1000);  // Включить зуммер на 1000 Гц
    delay(100);
    noTone(9);  // Выключить зуммер
  }
  }


void Repository6(){
      if (ProgrammWork == 6){
        M5Cardputer.Display.clear();
      }
      int x = RepositoryStartX;
      int y = RepositoryStartY;
      bool overflow = false;
      M5Cardputer.Display.drawRect(128, 113, 67, 15, 0xFFFF);
      M5Cardputer.Display.setTextColor(0xAD55);
      M5Cardputer.Display.drawString("Words", 135, 117);
      M5Cardputer.Display.setTextColor(0xFFFF);
      String stringNumber = String(WordsAnalytics6); // Преобразование int в String
      M5Cardputer.Display.drawString(stringNumber, 169, 117);

      for (int i = 0; i < RepositoryText6.length(); i++) {
       if (RepositoryText6[i] == '\n' || x + 10 > RepositoryMaxX) {
         y += 12; // Уменьшенная высота строки
         x = RepositoryStartX; // Начало новой строки
    
         if (y >= RepositoryMaxY) {
           overflow = true;
           M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
        break;
         }
       }
  
       if (RepositoryText6[i] != '\n') {
         M5Cardputer.Display.drawChar(RepositoryText6[i], x, y);
         x += 10; // Ширина символа
       }}


  // Рисование мигающего курсора
  if (cursorState) {
    M5Cardputer.Display.drawChar('_', x, y);  // Курсор
  }

  // Звуковое предупреждение, если текст выходит за границы
  if (overflow) {
    tone(9, 1000);  // Включить зуммер на 1000 Гц
    delay(100);
    noTone(9);  // Выключить зуммер
  }
  }


void Repository7(){
      if (ProgrammWork == 7){
        M5Cardputer.Display.clear();
      }
      int x = RepositoryStartX;
      int y = RepositoryStartY;
      bool overflow = false;
      M5Cardputer.Display.drawRect(128, 113, 67, 15, 0xFFFF);
      M5Cardputer.Display.setTextColor(0xAD55);
      M5Cardputer.Display.drawString("Words", 135, 117);
      M5Cardputer.Display.setTextColor(0xFFFF);
      String stringNumber = String(WordsAnalytics8); // Преобразование int в String
      M5Cardputer.Display.drawString(stringNumber, 169, 117);

      for (int i = 0; i < RepositoryText7.length(); i++) {
       if (RepositoryText7[i] == '\n' || x + 10 > RepositoryMaxX) {
         y += 12; // Уменьшенная высота строки
         x = RepositoryStartX; // Начало новой строки
    
         if (y >= RepositoryMaxY) {
           overflow = true;
           M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
        break;
         }
       }
  
       if (RepositoryText8[i] != '\n') {
         M5Cardputer.Display.drawChar(RepositoryText7[i], x, y);
         x += 10; // Ширина символа
       }}


  // Рисование мигающего курсора
  if (cursorState) {
    M5Cardputer.Display.drawChar('_', x, y);  // Курсор
  }

  // Звуковое предупреждение, если текст выходит за границы
  if (overflow) {
    tone(9, 1000);  // Включить зуммер на 1000 Гц
    delay(100);
    noTone(9);  // Выключить зуммер
  }
  }


void Repository8(){

      if (ProgrammWork == 8){
         M5Cardputer.Display.clear();
      }
      int x = RepositoryStartX;
      int y = RepositoryStartY;
      bool overflow = false;
      M5Cardputer.Display.drawRect(128, 113, 67, 15, 0xFFFF);
      M5Cardputer.Display.setTextColor(0xAD55);
      M5Cardputer.Display.drawString("Words", 135, 117);
      M5Cardputer.Display.setTextColor(0xFFFF);
      String stringNumber = String(WordsAnalytics8); // Преобразование int в String
      M5Cardputer.Display.drawString(stringNumber, 169, 117);

      for (int i = 0; i < RepositoryText8.length(); i++) {
       if (RepositoryText8[i] == '\n' || x + 10 > RepositoryMaxX) {
         y += 12; // Уменьшенная высота строки
         x = RepositoryStartX; // Начало новой строки
    
         if (y >= RepositoryMaxY) {
           overflow = true;
           M5Cardputer.Display.fillEllipse(15, 121, 9, 9, 0xFAAA);
        break;
         }
       }
  
       if (RepositoryText8[i] != '\n') {
         M5Cardputer.Display.drawChar(RepositoryText8[i], x, y);
         x += 10; // Ширина символа
       }}


  // Рисование мигающего курсора
  if (cursorState) {
    M5Cardputer.Display.drawChar('_', x, y);  // Курсор
  }

  }




void setFile1(){
                  File file = SPIFFS.open("/rep1.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       RepositoryText1+= (char)file.read();
                   }
                   file.close();
}
void setFile2(){
                  File file = SPIFFS.open("/rep2.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       RepositoryText2+= (char)file.read();
                   }
                   file.close();
}

void setFile3(){
                  File file = SPIFFS.open("/rep3.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       RepositoryText3+= (char)file.read();
                   }
                   file.close();
}

void setFile4(){
                  File file = SPIFFS.open("/rep4.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       RepositoryText4+= (char)file.read();
                   }
                   file.close();
}

void setFile5(){
                  File file = SPIFFS.open("/rep5.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       RepositoryText5+= (char)file.read();
                   }
                   file.close();
}

void setFile6(){
                  File file = SPIFFS.open("/rep6.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       RepositoryText6+= (char)file.read();
                   }
                   file.close();
}

void setFile7(){
                 File file = SPIFFS.open("/rep7.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       RepositoryText7+= (char)file.read();
                   }
                   file.close();
}

void setFile8(){
                  File file = SPIFFS.open("/rep8.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       RepositoryText8+= (char)file.read();
                   }
                   file.close();
}

void executeAction() {
  switch (MenuPosition) {
    case 1:
      log("Error status menu");
    break;
    case 2:
      BlockingLoop = 1;
     
      
      Repository1();
      setFile1();
       ProgrammWork = 1;
    break;
    case 3:
      BlockingLoop = 2;
      ProgrammWork = 2;
      setFile2();
      Repository2();
    break;
    case 4:
      BlockingLoop = 3;
      ProgrammWork = 3;
      setFile3();
      Repository3();
    break;
    case 5:
      BlockingLoop = 4;
      ProgrammWork = 4;
      setFile4();
      Repository4();
    break;
    case 6:
      BlockingLoop = 5;
      ProgrammWork = 5;
      setFile5();
      Repository5();
    break; 
    case 7:
      BlockingLoop = 6;
      ProgrammWork = 6;
      setFile6();
      Repository6();
    break;        
    case 8:
      BlockingLoop = 7;
      ProgrammWork = 7;
      setFile7();
      Repository7();
    break;  
  }
}

void res(){    SPIFFS.remove("/rep1.txt");
    SPIFFS.remove("/rep2.txt");
    SPIFFS.remove("/rep3.txt");
    SPIFFS.remove("/rep4.txt");
    SPIFFS.remove("/rep5.txt");
    SPIFFS.remove("/rep6.txt");
    SPIFFS.remove("/rep7.txt");
    SPIFFS.remove("/rep8.txt");}
void executeAction(int item) {
      switch (item) {
        case 0:
          M5Cardputer.Speaker.tone(2000, 20);
          BlockingLoop = 10;
          terminal();
        break;
        case 1:
           res();
        break;
        case 2:
          M5Cardputer.Speaker.tone(5000, 20);
        break;
        case 3:
          M5Cardputer.Speaker.tone(5000, 20);
        break;
        default:
        break;
      }
    }

void listmenu() {
  M5Cardputer.Display.fillScreen(BLACK);
  M5Cardputer.Display.clear();
  DHubPanelGUI();
  for (int i = 0; i < menuLength; i++) {
        if (i == selectedItem) {
            M5Cardputer.Display.setTextColor(TFT_YELLOW, TFT_BLACK);
        } else {
            M5Cardputer.Display.setTextColor(TFT_WHITE, TFT_BLACK);
        }
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString(menuItems[i], 10, 25 + (i * 18));
  }
}


void terminal(){
          M5Cardputer.Display.clear();
          M5Cardputer.Display.fillRect(-4, -3, 267, 20, 0x15);
          M5Cardputer.Display.setTextSize(1);
          M5Cardputer.Display.setFreeFont();
          M5Cardputer.Display.setTextColor(0xFFFF);
          M5Cardputer.Display.drawString("Terminal - DHub ORC 3.5", 5, 5);
          M5Cardputer.Display.fillRoundRect(8, 107, 224, 25, 2, 0xAD55);
          M5Cardputer.Display.fillRoundRect(12, 110, 217, 19, 1, 0xFFFF);
          M5Cardputer.Display.setTextColor(0x0);
          M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
          M5Cardputer.Display.drawString(command, 18, 111);
          M5Cardputer.Display.setTextColor(0xFFFF);
          M5Cardputer.Display.setFreeFont();
          M5Cardputer.Display.drawString("enter - start ", 156, 5);
          M5Cardputer.Display.drawLine(149, 13, 149, 4, 0xFFFF);
          M5Cardputer.Display.setTextColor(0xFFFF);
          M5Cardputer.Display.drawString("This is command is corect", 7, 24);
}
