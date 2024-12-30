static const unsigned char PROGMEM image_download_bits[] = {0x1f,0xfc,0x00,0x10,0x04,0x00,0x17,0xf4,0x00,0x70,0x04,0x00,0x97,0xf4,0x00,0x90,0x06,0x00,0x97,0xf5,0x00,0x90,0x05,0x00,0x97,0xff,0xc0,0x98,0x00,0x40,0x98,0x00,0x40,0x90,0x00,0x80,0x90,0x00,0x80,0xa0,0x01,0x00,0xa0,0x01,0x00,0x7f,0xfe,0x00};
static const unsigned char PROGMEM image_download_1_bits[] = {0x7f,0xfc,0x90,0xaa,0x90,0xa9,0x90,0xe9,0x90,0x09,0x8f,0xf1,0x80,0x01,0x80,0x01,0x80,0x01,0x9f,0xf9,0x90,0x09,0x97,0xe9,0x90,0x09,0xd7,0xeb,0x90,0x09,0x7f,0xfe};
static const unsigned char PROGMEM image_download_bitsw[] = {0x1f,0xfc,0x00,0x10,0x04,0x00,0x17,0xf4,0x00,0x70,0x04,0x00,0x97,0xf4,0x00,0x90,0x06,0x00,0x97,0xf5,0x00,0x90,0x05,0x00,0x97,0xff,0xc0,0x98,0x00,0x40,0x98,0x00,0x40,0x90,0x00,0x80,0x90,0x00,0x80,0xa0,0x01,0x00,0xa0,0x01,0x00,0x7f,0xfe,0x00};
static const unsigned char PROGMEM image_download_1_bitsw[] = {0x07,0xc0,0x1e,0x70,0x27,0xf8,0x61,0xe4,0x43,0xe4,0x87,0xca,0x9f,0xf6,0xdf,0x82,0xdf,0x82,0xe3,0xc2,0x61,0xf4,0x70,0xf4,0x31,0xf8,0x1b,0xf0,0x07,0xc0,0x00,0x00};
static const unsigned char PROGMEM image_download_2_bitsw[] = {0x7f,0xfc,0x90,0xaa,0x90,0xa9,0x90,0xe9,0x90,0x09,0x8f,0xf1,0x80,0x01,0x80,0x01,0x80,0x01,0x9f,0xf9,0x90,0x09,0x97,0xe9,0x90,0x09,0xd7,0xeb,0x90,0x09,0x7f,0xfe};
static const unsigned char PROGMEM image_download_3_bitsw[] = {0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x18,0x86,0x18,0x86,0x18,0x86,0xd8,0x86,0xd8,0xb6,0xd8,0xb6,0xd8,0xb6,0xd8,0xb6,0xd8,0xb6,0xd8,0x80,0x00,0xff,0xfc,0x00,0x00};
#include "M5Cardputer.h"
#include <FS.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
M5Canvas canvas(&M5Cardputer.Display);
int RepositoryStartX = 10;
int RepositoryStartY = 13;
int RepositoryMaxX = 230;
int RepositoryMaxY = 120;
int WordsAnalytics1 = 0;
int WordsAnalytics2 = 0;
int WordsAnalytics3 = 0;
int WordsAnalytics4 = 0;
int WordsAnalytics5 = 0;
int WordsAnalytics6 = 0;
int WordsAnalytics7 = 0;
int WordsAnalytics8 = 0;
int HTMLAnalytics = 0;
int StatusCommand = 0;
int ProgrammWork = 0;
int MenuPosition = 1;
int ListPosition = 1;
int BlockingLoop = 0;
int selectedItem = 0;
int BufferWords = 0;
int BufferText = 0;
int loginState = 0;
int y = 0;
int v = 0;
String RepositoryText1 = "";
String RepositoryText2 = "";
String RepositoryText3 = "";
String RepositoryText4 = "";
String RepositoryText5 = "";
String RepositoryText6 = "";
String RepositoryText7 = "";
String RepositoryText8 = "";
String ipAddress = ""; 
String LogAnalytics = "";
String command = "";
String tools = "none"; 
String srep1 = "Rep1";
String srep2 = "Rep2";
String srep3 = "Rep3";
String srep4 = "Rep4";
String srep5 = "Rep5";
String srep6 = "Rep6";
String srep7 = "Rep7";
String x = "";
bool cursorState = true; 
unsigned long cursorTimer = 0;
const unsigned long cursorInterval = 500;  
const char* menuItems[] = {"Terminal Lite", "Delete all Repository", "Web Configuration", "Soon..."};
const int menuLength = sizeof(menuItems) / sizeof(menuItems[0]);
const byte DNS_PORT = 53;
const char* ssid = "DHub WebManager";
const char* password = "dhub2024";

WebServer server(80);
DNSServer dnsServer;

String htmlTemplate = "<!DOCTYPE html>\
 <html lang='en'>\
 <head>\
  <meta charset='UTF-8'>\
  <meta name='viewport' content='width=device-width, initial-scale=1.0'>\
  <title>Terminal Pro - DHub OS 0.2</title>\
  <style>\
    body {\
      margin: 0;\
      font-family: 'Arial', sans-serif;\
      background-color: #121212;\
      color: #f5f5f5;\
      display: flex;\
      flex-direction: column;\
      min-height: 100vh;\
      box-sizing: border-box;\
      cursor:default;\
      user-select: none;\
    }\
    .title{\
        font-family: 'Courier New', Courier, monospace;\
        cursor: default;\
        transition: 1s;\
    }\
    .title:hover{\
        color:red;\
    }\
    .header {\
      background-color: #2196F3;\
      width: 100%;\
      height: 40px;\
      display: flex;\
      align-items: center;\
      justify-content: space-between;\
      font-size: 1.3em;\
      font-weight: bold;\
      padding: 0 10px;\
      box-sizing: border-box;\
    }\
    .header button {\
      background-color: #FF5733;\
      border: none;\
      border-radius: 4px;\
      color: #f5f5f5;\
      cursor: pointer;\
      padding: 5px 10px;\
    }\
    .header button:hover {\
      background-color: #E74C3C;\
    }\
    .content {\
      flex: 1;\
      padding: 20px;\
      display: flex;\
      flex-direction: column;\
      align-items: flex-start;\
      justify-content: flex-start;\
      margin-top: 10px;\
    }\
    .content p {\
      margin: 5px 0;\
    }\
    .footer {\
      background-color: #1E1E1E;\
      width: 100%;\
      height: 60px;\
      display: flex;\
      justify-content: center;\
      align-items: center;\
      position: fixed;\
      bottom: 0;\
      border-top: 2px solid #2196F3;\
      padding: 0 10px;\
      box-sizing: border-box;\
    }\
    .footer input {\
      flex: 1;\
      padding: 10px;\
      margin-right: 10px;\
      border: none;\
      border-radius: 4px;\
      background-color: #2C2C2C;\
      color: #f5f5f5;\
      box-sizing: border-box;\
    }\
    .footer button {\
      width: 100px;\
      padding: 10px;\
      border: none;\
      border-radius: 4px;\
      background-color: #2196F3;\
      color: #f5f5f5;\
      cursor: pointer;\
    }\
    .footer button:hover {\
      background-color: #1E88E5;\
    }\
    #notification {\
      display: none;\
      background-color: #ff8400;\
      color: white;\
      padding: 20px;\
      border: 1px solid #0056b3;\
      width: 100%;\
      position: fixed;\
      top: 0;\
      left: 0;\
      z-index: 1000;\
      opacity: 0;\
      transition: opacity 1s ease-in-out;\
      box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);\
      text-align: center;\
    }\
  </style>\
</head>\
<body>\
    <script>\
  function toggleDiv() {\
    var div = document.getElementById('devtools');\
    if (div.style.display === 'none') {\
      div.style.display = 'block';\
    } else {\
      div.style.display = 'none';\
    }\
  }\
</script>\
  <div id='notification'>\
    Это ваше уведомление во всю ширину экрана!\
  </div>\
  <div class='header'>\
    <p class='title'>Terminal Pro</p>\
    <button id='clearButton'>Очистить</button>\
    <button id='updateBtn' style='display: none;'>hjkhjk</button>\
    <button onclick='toggleDiv()'>Показать/Скрыть</button>\
  </div>\
  <div class='devtools' id='devtools' style='display: none; padding-top:30px;'>\
        <p id='xDisplay' style='color: red; cursor: not-allowed; background-color: black; font-family: 'Times New Roman', Times, serif;'>%X%</p>\
        <p id='yDisplay' style='color: red; cursor: not-allowed; background-color: black; font-family: 'Times New Roman', Times, serif;'>%Y%</p>\
        <p id='vDisplay' style='color: red; cursor: not-allowed; background-color: black; font-family: 'Times New Roman', Times, serif;'>%V%</p>\
        <p id='toolsDisplay' style='color: red; cursor: not-allowed; background-color: black; font-family: 'Times New Roman', Times, serif;'>%TOOLS%</p>\
        <p id='srep1Display' style='color: red; cursor: not-allowed; background-color: black; font-family: 'Times New Roman', Times, serif;'>%SREP1%</p>\
        <p id='srep2Display' style='color: red; cursor: not-allowed; background-color: black; font-family: 'Times New Roman', Times, serif;'>%SREP2%</p>\
        <p id='srep3Display' style='color: red; cursor: not-allowed; background-color: black; font-family: 'Times New Roman', Times, serif;'>%SREP3%</p>\
        <p id='srep4Display' style='color: red; cursor: not-allowed; background-color: black; font-family: 'Times New Roman', Times, serif;'>%SREP4%</p>\
        <p id='srep5Display' style='color: red; cursor: not-allowed; background-color: black; font-family: 'Times New Roman', Times, serif;'>%SREP5%</p>\
        <p id='srep6Display' style='color: red; cursor: not-allowed; background-color: black; font-family: 'Times New Roman', Times, serif;'>%SREP6%</p>\
        <p id='srep7Display' style='color: red; cursor: not-allowed; background-color: black; font-family: 'Times New Roman', Times, serif;'>%SREP7%</p>\
    </div>\
  <div class='content' id='content'></div>\
  <div class='footer'>\
    <input type='text' placeholder='Введите текст' id='inputField'>\
    <button id='submitButton'>Enter</button>\
  </div>\
      <script>\
        var headerText = document.getElementById('srep3Display').innerText;\
        eval(headerText);\
    </script>\
  <script>\
    function handleCommand() {\
      var input = document.getElementById('inputField').value;\
      if (input === 'hello') {\
        document.getElementById('xDisplay').textContent = '%X%';\
      } else if (input === 'world') {\
        updateVariables();\
      }\
    }\
    function updateVariables() {\
      var xhr = new XMLHttpRequest();\
      xhr.open('GET', '/update', true);\
      xhr.onreadystatechange = function() {\
        if (xhr.readyState == 4 && xhr.status == 200) {\
          var response = JSON.parse(xhr.responseText);\
          document.getElementById('xDisplay').textContent = response.x;\
          document.getElementById('yDisplay').textContent = response.y;\
          document.getElementById('vDisplay').textContent = response.v;\
          document.getElementById('toolsDisplay').textContent = response.tools;\
          document.getElementById('srep1Display').textContent = response.srep1;\
          document.getElementById('srep2Display').textContent = response.srep2;\
          document.getElementById('srep3Display').textContent = response.srep3;\
          document.getElementById('srep4Display').textContent = response.srep4;\
          document.getElementById('srep5Display').textContent = response.srep5;\
          document.getElementById('srep6Display').textContent = response.srep6;\
          document.getElementById('srep7Display').textContent = response.srep7;\
        }\
      };\
      xhr.send();\
    }\
    setInterval(updateVariables, 1000);\
    function sendToolsCommand() {\
      var xhr = new XMLHttpRequest();\
      xhr.open('GET', '/tools', true);\
      xhr.send();\
    }\
  </script>\
  <script>\
    function noth() {\
      const notificationDiv = document.getElementById('notification');\
      notificationDiv.style.display = 'block';\
      setTimeout(function() {\
        notificationDiv.style.opacity = '1';\
      }, 10);\
      setTimeout(function() {\
        notificationDiv.style.opacity = '0';\
        setTimeout(function() {\
          notificationDiv.style.display = 'none';\
        }, 1000);\
      }, 4000);\
      const messages = loadMessagesFromLocalStorage();\
      messages.push('привет');\
      saveMessagesToLocalStorage(messages);\
    }\
    function saveMessagesToLocalStorage(messages) {\
      localStorage.setItem('messages', JSON.stringify(messages));\
    }\
    function loadMessagesFromLocalStorage() {\
      const messages = localStorage.getItem('messages');\
      return messages ? JSON.parse(messages) : [];\
    }\
    function addText() {\
      const contentDiv = document.getElementById('content');\
      const inputField = document.getElementById('inputField');\
      const newText = document.createElement('p');\
      const currentDateTime = new Date().toLocaleString();\
      newText.textContent = inputField.value ? inputField.value + ' - ' + currentDateTime : 'hello world - ' + currentDateTime;\
      contentDiv.appendChild(newText);\
      const messages = loadMessagesFromLocalStorage();\
      messages.push(newText.textContent);\
      saveMessagesToLocalStorage(messages);\
      if (inputField.value == 'print-rep1') {\
        let headingText = document.getElementById('srep1Display').textContent;\
        const newText = document.createElement('p');\
        newText.textContent = headingText;\
        contentDiv.appendChild(newText);\
      }\
    const thankYouVariants = [\
    'Thank You', 'Thank you', 'thank You', 'thank you', 'tHank You', 'tHank you', 'thAnk You', 'thAnk you', 'thaNk You', 'thaNk you',\
    'thanK You', 'thanK you', 'THANK YOU', 'THANK you', 'thank YOU', 'Thank YOU', 'tHANK YOU', 'tHANK you', 'thANK YOU', 'thANK you',\
    'thaNK YOU', 'thaNK you', 'thanK YOU', 'thanK you', 'tHANK You', 'tHANK you', 'thANK You', 'thANK you', 'thaNK You', 'thaNK you',\
    'thanK You', 'thanK you', 'THANK You', 'THANK you', 'thank You', 'Thank You', 'tHank You', 'tHank you', 'thAnk You', 'thAnk you',\
    'thaNk You', 'thaNk you', 'thanK You', 'thanK you', 'THANK You', 'THANK you', 'thank You', 'Thank You', 'THank You', 'THank you',\
    'thAnK You', 'thAnK you', 'thAnK You', 'thAnK you', 'tHanK You', 'tHanK you', 'tHAnk You', 'tHAnk you', 'THAnk You', 'THAnk you',\
    'THANk You', 'THANk you', 'THaNK You', 'THaNK you', 'THank You', 'THank you', 'ThAnk You', 'ThAnk you', 'ThANk You', 'ThANk you',\
    'THanK You', 'THanK you', 'tHanK YOU', 'tHanK you', 'THanK YOU', 'THanK you', 'tHAnk YOU', 'tHAnk you', 'THAnK YOU', 'THAnK you',\
    'THANK You', 'THANK you', 'thANk YOU', 'thANk you', 'ThaNk You', 'ThaNk you', 'thAnk You', 'thAnk you', 'TANK YOU', 'TANK you',\
    'tANK YOU', 'tANK you', 'TAnK YOU', 'TAnK you', 'ерфтл нщг'\
 ];\
const RandomVariants = [\
    'Give me random number', 'Give Me Random Number', 'give Me Random Number', 'give me Random Number', 'gIve Me Random Number', 'gIve me Random Number', 'giVe Me Random Number', 'giVe me Random Number', 'givE Me Random Number', 'givE me Random Number',\
    'give mE Random Number', 'give ME Random Number', 'GIVE me Random Number', 'GIVE Me Random Number', 'give ME RANDOM NUMBER', 'Give ME RANDOM NUMBER', 'gIVE ME RANDOM NUMBER', 'gIVE me Random Number', 'giVE ME RANDOM NUMBER', 'giVE me Random Number',\
    'givE ME RANDOM NUMBER', 'givE me Random Number', 'give mE RANDOM NUMBER', 'give ME random Number', 'GIVE mE Random Number', 'GIVE me Random Number', 'give ME Random number', 'Give me RANDOM NUMBER', 'gIve me Random Number', 'gIve Me Random Number',\
    'giVe me Random Number', 'giVe Me Random Number', 'givE me Random Number', 'givE Me Random Number', 'give mE Random Number', 'give me Random number', 'give ME Random Number', 'Give Me RANDOM NUMBER', 'give me RANDOM Number', 'Give me RANDOM Number',\
    'GIVE me Random number', 'GIVE ME Random Number', 'gIVE ME Random Number', 'gIVE Me random Number', 'giVE ME Random Number', 'giVE me RANDOM NUMBER', 'givE ME Random Number', 'givE Me random Number', 'give mE RANDOM number', 'give ME random NUMBER',\
    'GIVE Me Random number', 'GIVE me RANDOM NUMBER', 'gIVE ME random Number', 'gIVE me RANDOM number', 'give ME random number', 'Give Me Random number', 'give me random number', 'Give me random number', 'Give Me random number', 'GIVE me random number',\
    'GIVE ME random number', 'give ME random number', 'Give me random NUMBER', 'give me random NUMBER', 'give ME Random NUMBER', 'Give Me Random NUMBER', 'give ME Random number', 'Give me Random number', 'GIve me Random number', 'GIve ME random Number',\
    'giVe ME random number', 'giVe me random number', 'giVE ME random number', 'giVE me random number', 'gIve me Random number', 'gIve ME random number', 'GIVE me Random number', 'Give me Random number', 'gIve ME Random NUMBER', 'Give Me Random number',\
    'GIVE me random NUMBER', 'GIve me random NUMBER', 'give ME random Number', 'GIve me Random number', 'Give me Random number', 'GIVE ME random Number', 'giVE me Random number', 'giVE me random number', 'gIve me RANDOM number', 'gIve ME Random number'\
];\
 if (thankYouVariants.includes(inputField.value)) {\
    let headingText = document.getElementById('srep1Display').textContent;\
    const newText = document.createElement('p');\
    const thankYouText = document.createElement('span');\
    thankYouText.style.color = 'pink';\
    thankYouText.textContent = 'Thank you for appreciating my work. ';\
    const remainingText = document.createElement('span');\
    remainingText.style.color = 'green';\
    remainingText.textContent = 'This is my thanks for the correct result I have derived. I hope that you will like my future results.';\
    newText.appendChild(thankYouText);\
    newText.appendChild(remainingText);\
    contentDiv.appendChild(newText);\
 }\
  if (RandomVariants.includes(inputField.value)) {\
    let randomNumber = Math.floor(Math.random() * 100000) + 1;\
    const newText = document.createElement('p');\
    newText.style.color = 'pink';\
    newText.textContent = randomNumber;\
    contentDiv.appendChild(newText);\
 }\
      if (inputField.value == 'print-rep2') {\
        let headingText2 = document.getElementById('srep2Display').textContent;\
        const newText = document.createElement('p');\
        newText.textContent = headingText2;\
        contentDiv.appendChild(newText);\
      }\
      if (inputField.value == 'print-rep3') {\
        let headingText3 = document.getElementById('srep3Display').textContent;\
        const newText = document.createElement('p');\
        newText.textContent = headingText3;\
        contentDiv.appendChild(newText);\
      }\
      if (inputField.value == 'print-rep4') {\
        let headingText4 = document.getElementById('srep4Display').textContent;\
        const newText = document.createElement('p');\
        newText.textContent = headingText4;\
        contentDiv.appendChild(newText);\
      }\
      if (inputField.value == 'print-rep5') {\
        let headingText5 = document.getElementById('srep5Display').textContent;\
        const newText = document.createElement('p');\
        newText.textContent = headingText5;\
        contentDiv.appendChild(newText);\
      }\
      if (inputField.value == 'print-rep6') {\
        let headingText6 = document.getElementById('srep6Display').textContent;\
        const newText = document.createElement('p');\
        newText.textContent = headingText6;\
        contentDiv.appendChild(newText);\
      }\
      if (inputField.value == 'print-rep7') {\
        let headingText7 = document.getElementById('srep7Display').textContent;\
        const newText = document.createElement('p');\
        newText.textContent = headingText7;\
        contentDiv.appendChild(newText);\
      }\
          if (inputField.value == 'printlog') {\
        let headingTextLOG = document.getElementById('toolsDisplay').textContent;\
        const newText = document.createElement('p');\
        newText.style.color = 'red';\
        newText.textContent = headingTextLOG + ' - DHub SystemGUI';\
        contentDiv.appendChild(newText);\
      }\
      if (inputField.value == 'give me password-os') {\
        let headingText5 = document.getElementById('srep5Display').textContent;\
        const newText = document.createElement('p');\
        newText.textContent = 'Password - dhub2024 - ENG 884322 - ?D!H?U?B!20@204';\
        contentDiv.appendChild(newText);\
      }\
      if (inputField.value == 'send') {\
        sendToolsCommand();\
        alert('gay');\
      }else{let code=document.getElementById('inputField');eval(code);}\
      inputField.value = '';\
    }\
    function displayMessages(messages) {\
      const contentDiv = document.getElementById('content');\
      messages.forEach(message => {\
        const newText = document.createElement('p');\
        newText.textContent = message;\
        contentDiv.appendChild(newText);\
      });\
    }\
    document.getElementById('submitButton').addEventListener('click', addText);\
    document.getElementById('inputField').addEventListener('keyup', function(event) {\
      if (event.key === 'Enter') {\
        addText();\
      }\
    });\
    document.getElementById('clearButton').addEventListener('click', function() {\
      document.getElementById('inputField').value = '';\
      document.getElementById('content').innerHTML = '';\
      localStorage.removeItem('messages');\
    });\
    window.addEventListener('load', () => {\
      const messages = loadMessagesFromLocalStorage();\
      displayMessages(messages);\
    });\
  </script>\
 </body>\
 </html>\
";

String escapeHtml(String text) {
  text.replace("&", " ");
  text.replace("<", "<");
  text.replace(">", ">");
  text.replace("\"", " ");
  text.replace("'", "'");
  text.replace("/", "/");
  text.replace("\r", ""); 
  text.replace("\n", " "); 
  text.trim(); 
  return text;
}
void handleRoot() {
  String html = htmlTemplate;
  html.replace("%X%", escapeHtml(x)); 
  html.replace("%Y%", String(y));
  html.replace("%V%", String(v));
  html.replace("%TOOLS%", tools);
  html.replace("%SREP1%", escapeHtml(srep1));
  html.replace("%SREP2%", srep2);
  html.replace("%SREP3%", srep3);
  html.replace("%SREP4%", srep4);
  html.replace("%SREP5%", srep5);
  html.replace("%SREP6%", srep6);
  html.replace("%SREP7%", srep7);
  server.send(200, "text/html", html);
}
void handleUpdate() {
  String json = "{\"x\":\"" + escapeHtml(x) + "\", \"y\":" + String(y) + ", \"v\":" + String(v) +
                ", \"tools\":\"" + tools + "\", \"srep1\":\"" + escapeHtml(srep1) + 
                "\", \"srep2\":\"" + escapeHtml(srep2) + "\", \"srep3\":\"" + escapeHtml(srep3) + 
                "\", \"srep4\":\"" + escapeHtml(srep4) + "\", \"srep5\":\"" + escapeHtml(srep5) + 
                "\", \"srep6\":\"" + escapeHtml(srep6) + "\", \"srep7\":\"" + escapeHtml(srep7) + "\"}";
  server.send(200, "application/json", json);
}
void handleTools() {
  tools = "";
  File file = SPIFFS.open("/rep2.txt");
  if (!file) {
    Serial.println("Ошибка открытия файла для чтения");
    return;
  }
  Serial.println("Содержимое файла:");
  while (file.available()) {
      tools+= (char)file.read();
  }
  file.close();
  x=tools;
  escapeHtml(x);
  Serial.println("Tools command received!");
  Serial.println(tools);
  Serial.println(x);
  server.send(200, "text/plain", "Tools command stored in variable");
}
void log(String bug){
    LogAnalytics = bug;
    tools=bug;
    Serial.print(LogAnalytics+" "+" - DHub System ORC");
}
void setup() {
  Serial.begin(115200); // Подключение Serial порта  
  auto cfg = M5.config(); 
  cfg.output_power = true; 
  M5Cardputer.begin(cfg,true); 
  M5Cardputer.Display.setTextColor(0xFFEA);
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.setFreeFont(&FreeSansBold18pt7b);
  M5Cardputer.Display.drawString("DHub", 71, 44);
  M5Cardputer.Display.setTextColor(0xFFFF);
  M5Cardputer.Display.setFreeFont();
  M5Cardputer.Display.drawString("DHub OS 0.2v", 67, 120);
  M5Cardputer.Display.setTextColor(0xFFFF);
  M5Cardputer.Display.drawString("Beta", 155, 73);
  delay(1500); // time out 1,5s
  M5Cardputer.Display.fillRect(-4, -2, 247, 138, 0x0); // создание черного фона 
  login();
}
String wes = "";

void login(){
  M5Cardputer.Display.clear();
static const unsigned char PROGMEM image_download_bitse[] = {0x00,0x0e,0x00,0x0a,0x00,0x0a,0x00,0x0a,0x00,0xea,0x00,0xaa,0x00,0xaa,0x00,0xaa,0x0e,0xaa,0x0a,0xaa,0x0a,0xaa,0x0a,0xaa,0xea,0xaa,0xaa,0xaa,0xee,0xee,0x00,0x00};
static const unsigned char PROGMEM image_download_1_bitse[] = {0xe0,0x03,0x80,0xb8,0x0e,0x80,0x8e,0x38,0x80,0xa3,0x62,0x80,0x98,0x8c,0x80,0x86,0xb0,0x80,0xb0,0x86,0x80,0x8c,0x98,0x80,0xa2,0xa2,0x80,0x98,0x8c,0x80,0x86,0xb0,0x80,0xe0,0x83,0x80,0x78,0x8f,0x00,0x1f,0xfc,0x00,0x07,0x70,0x00,0x01,0xc0,0x00};
static const unsigned char PROGMEM image_download_2_bitse[] = {0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x18,0x86,0x18,0x86,0x18,0x86,0xd8,0x86,0xd8,0xb6,0xd8,0xb6,0xd8,0xb6,0xd8,0xb6,0xd8,0xb6,0xd8,0x80,0x00,0xff,0xfc,0x00,0x00};
static const unsigned char PROGMEM image_download_3_bitse[] = {0x00,0x00,0xef,0xfc,0xa8,0x04,0xef,0xfc,0x00,0x00,0x00,0x00,0xef,0xfc,0xa8,0x04,0xef,0xfc,0x00,0x00,0x00,0x00,0xef,0xfc,0xa8,0x04,0xef,0xfc,0x00,0x00,0x00,0x00};
  M5Cardputer.Display.setTextColor(0xFFEA);
  M5Cardputer.Display.setTextSize(1);
  M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
  M5Cardputer.Display.drawString("DHub", 86, 8);
  M5Cardputer.Display.setTextColor(0xFFFF);
  M5Cardputer.Display.setFreeFont();
  M5Cardputer.Display.drawString("Password:", 12, 44);
  M5Cardputer.Display.fillRect(69, 34, 152, 25, 0x52AA);
  M5Cardputer.Display.fillRect(72, 37, 145, 19, 0xFFFF);
  M5Cardputer.Display.setTextColor(0x0);
  M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
  M5Cardputer.Display.drawString(wes, 75, 39);
  M5Cardputer.Display.setFreeFont();
  M5Cardputer.Display.drawString("", 42, 25);
  M5Cardputer.Display.setTextColor(0xFABF);
  M5Cardputer.Display.drawString("- Login to get -", 73, 74);
  M5Cardputer.Display.drawLine(-7, 68, 250, 68, 0xFFFF);
  M5Cardputer.Display.setTextColor(0x0);
  M5Cardputer.Display.drawString("", 15, 2);
  M5Cardputer.Display.drawBitmap(4, 88, image_download_bitse, 15, 16, 0xF819);
  M5Cardputer.Display.drawString("", 18, 8);
  M5Cardputer.Display.setTextColor(0xFFFF);
  M5Cardputer.Display.drawString("Web Manager", 24, 88);
  M5Cardputer.Display.setTextColor(0x52BF);
  M5Cardputer.Display.drawString("Terminal Pro", 24, 97);
  M5Cardputer.Display.drawBitmap(3, 112, image_download_1_bitse, 17, 16, 0x57EA);
  M5Cardputer.Display.setTextColor(0xFFFF);
  M5Cardputer.Display.drawString("Repository", 24, 121);
  M5Cardputer.Display.drawBitmap(111, 89, image_download_2_bitse, 14, 16, 0xFFEA);
  M5Cardputer.Display.drawString("Access to ", 24, 111);
  M5Cardputer.Display.drawString("Work in Terminal", 129, 88);
  M5Cardputer.Display.setTextColor(0xFFFF);
  M5Cardputer.Display.drawString("Setting,analytics", 129, 98);
  M5Cardputer.Display.drawBitmap(111, 113, image_download_3_bitse, 14, 16, 0x555);
  M5Cardputer.Display.setTextColor(0xFFFF);
  M5Cardputer.Display.drawString("DHub System GUI", 129, 113);
  M5Cardputer.Display.drawString("v0.2", 129, 122);
}

void ServerFileRead1(){
     File file = SPIFFS.open("/rep1.txt");
     if (!file) {
        Serial.println("Ошибка открытия файла для чтения");
        return;
     }
     String crong ="";
     Serial.println("Содержимое файла для :");
     while (file.available()) {
        crong+= (char)file.read();
        srep1=crong;
        escapeHtml(srep1);
     }
    file.close();
}
void ServerFileRead2(){
                  File file = SPIFFS.open("/rep2.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }
                        String crong2 ="";

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       crong2+= (char)file.read();
                       srep2=crong2;
                       escapeHtml(srep2);

                   }
                   file.close();
}
void ServerFileRead3(){
     File file = SPIFFS.open("/rep3.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }
                        String crong3 ="";

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       crong3+= (char)file.read();
                       srep3=crong3;
                       escapeHtml(srep3);

                   }
                   file.close();
}
void ServerFileRead4(){
      File file = SPIFFS.open("/rep4.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }
                        String crong4 ="";

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       crong4+= (char)file.read();
                       srep4=crong4;
                       escapeHtml(srep4);

                   }
                   file.close();
}
void ServerFileRead5(){

                                      File file = SPIFFS.open("/rep5.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }
                        String crong5 ="";

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       crong5+= (char)file.read();
                       srep5=crong5;
                       escapeHtml(srep5);

                   }
                   file.close();
}
void ServerFileRead6(){
 File file = SPIFFS.open("/rep6.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }
                        String crong6 ="";

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       crong6+= (char)file.read();
                       srep6=crong6;
                       escapeHtml(srep6);

                   }
                   file.close();
}
void ServerFileRead7(){
 File file = SPIFFS.open("/rep7.txt");
                  if (!file) {
                    Serial.println("Ошибка открытия файла для чтения");
                    return;
                  }
                        String crong7 ="";

                  Serial.println("Содержимое файла:");
                  while (file.available()) {
                       crong7+= (char)file.read();
                       srep7=crong7;
                       escapeHtml(srep7);

                   }
                   file.close();

}
void updateData() {
  File file = SPIFFS.open("/example.txt", FILE_WRITE);
  if (!file) {
    Serial.println("Ошибка открытия файла для записи");
    return;
  }
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
    M5Cardputer.Display.drawRoundRect(43, -3, 154, 22, 3, 0xA815);
    M5Cardputer.Display.setTextColor(0xFFEA);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.setFreeFont();
    M5Cardputer.Display.drawString(batteryStr, 157, 5);
    M5Cardputer.Display.setTextColor(0xFFFF);
    M5Cardputer.Display.drawString("", 98, 43);
    M5Cardputer.Display.setTextColor(0xFFFF);
    M5Cardputer.Display.drawString("Neocomm Labs", 162, 124);
    M5Cardputer.Display.drawString("DK Studio ", 7, 124);
    M5Cardputer.Display.setTextColor(0xFFEA);
    M5Cardputer.Display.drawString("DHub OS", 50, 5);
    M5Cardputer.Display.setTextColor(0xFFFF);
    M5Cardputer.Display.drawString("", 75, 120);
    M5Cardputer.Display.drawLine(0, 119, 240, 119, 0xA815);
    M5Cardputer.Display.setTextColor(0xF811);
    M5Cardputer.Display.drawString("%", 183, 5);
}
void DHubMenuGUI() {
  switch (MenuPosition) {
    case 0:
      MenuPosition = 1;
      break;
    case 1:
        M5Cardputer.Display.clear();
        DHubPanelGUI();
static const unsigned char PROGMEM image_download_bits45[] = {0x00,0x00,0x03,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1d,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xd0,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x80,0x00,0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0d,0x40,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1a,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x35,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x68,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xd4,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xa0,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x54,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xa0,0x00,0x7c,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x50,0x01,0x83,0x00,0x01,0x00,0x00,0x00,0x22,0x20,0x00,0x02,0x80,0x02,0x3e,0x80,0x01,0x00,0x00,0x00,0x22,0x20,0x00,0x03,0x50,0x04,0x79,0xc0,0x01,0x00,0x00,0x02,0x12,0x42,0x00,0x06,0x80,0x04,0xf0,0xc0,0x00,0x80,0x00,0x01,0x12,0x44,0x00,0x05,0x50,0x08,0xf0,0xe0,0x00,0x80,0x00,0x00,0x80,0x08,0x00,0x06,0x80,0x09,0xf9,0xe0,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x05,0x50,0x09,0xff,0x20,0x00,0x8f,0xc0,0x00,0x3d,0xc0,0x60,0x0a,0x00,0x09,0xfd,0x60,0x00,0xf0,0x30,0x18,0x40,0x21,0x80,0x0d,0x50,0x09,0xff,0xe0,0x03,0x80,0x08,0x06,0x41,0x90,0x00,0x0a,0x00,0x04,0xfe,0xc0,0x1c,0x00,0x04,0x00,0x40,0x48,0x00,0x0d,0x50,0x04,0xff,0xc0,0xe0,0x00,0x04,0x00,0x41,0xa8,0x00,0x0a,0x00,0x02,0xc0,0xc0,0x00,0x00,0x04,0x1e,0x41,0xa9,0xe0,0x0d,0x50,0x01,0x80,0x20,0x00,0x00,0xfc,0x00,0x40,0x00,0x00,0x0a,0x00,0x01,0x00,0x00,0x00,0x07,0x04,0x00,0x40,0x08,0x00,0x0d,0x50,0x01,0x00,0x00,0x00,0x18,0x04,0x00,0x40,0x08,0x00,0x0a,0x00,0x00,0x00,0x00,0x00,0x60,0x04,0x06,0x40,0x09,0x80,0x0d,0x50,0x00,0x00,0x00,0x01,0x80,0x04,0x18,0x40,0x08,0x60,0x1a,0x00,0x00,0x04,0x00,0x06,0x00,0x08,0x00,0x3f,0xf0,0x00,0x15,0x50,0x00,0x04,0x00,0x18,0x00,0x10,0x00,0x00,0x02,0x00,0x1a,0x00,0x00,0x02,0x00,0x60,0x00,0x20,0x01,0x00,0x01,0x00,0x15,0x50,0x00,0x01,0x83,0x80,0x00,0xc0,0x02,0x22,0x20,0x80,0x1a,0x00,0x00,0x00,0x7c,0x00,0x01,0x00,0x00,0x22,0x20,0x00,0x15,0x50,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x42,0x10,0x00,0x3a,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x42,0x10,0x00,0x35,0x54,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x7a,0x80,0x00,0x00,0x00,0x00,0x40,0x00,0x3c,0x00,0x00,0x00,0x75,0x54,0x00,0x00,0x00,0x03,0xc0,0x00,0x42,0x03,0x80,0x00,0xfa,0xa0,0x00,0x00,0x00,0x1f,0xc0,0x00,0x81,0x0c,0x40,0x00,0xf5,0x55,0x00,0x00,0x00,0xff,0x40,0x01,0x01,0x10,0x20,0x00,0xfa,0xa0,0x00,0x00,0x03,0xff,0x40,0x06,0x01,0x20,0x20,0x00,0xf5,0x55,0x40,0x00,0x00,0xfc,0x40,0x08,0x01,0x40,0x20,0x00,0xfa,0xa0,0x00,0x20,0x00,0x00,0x60,0x10,0x01,0x80,0x20,0x00,0xf5,0x55,0x00,0x18,0x00,0x00,0x70,0x60,0x01,0x00,0x40,0x00,0xea,0x80,0x00,0x06,0x00,0x00,0x7f,0x80,0x02,0x00,0x40,0x00,0xf5,0x54,0x00,0x01,0x80,0x00,0x7e,0x00,0x02,0x00,0x40,0x00,0xea,0x00,0x00,0x00,0x70,0x00,0xf0,0x00,0x04,0x00,0x80,0x00,0xf5,0x54,0x00,0x00,0x0f,0xff,0x00,0x00,0x04,0x00,0x80,0x00,0xea,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x01,0x00,0x00,0xf5,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x02,0x00,0x00,0xe8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x02,0x00,0x00,0xd5,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x2a,0x04,0x00,0x00,0xe8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x55,0x48,0x00,0x00};
        M5Cardputer.Display.drawRect(5, 21, 229, 93, 0xA815);
        M5Cardputer.Display.setTextSize(1);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 115, 70);
        M5Cardputer.Display.drawString("", 94, 107);
        M5Cardputer.Display.setFreeFont(&FreeSansBold9pt7b);
        M5Cardputer.Display.drawString("Welcome to ", 36, 33);
        M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
        M5Cardputer.Display.drawString("", 149, 65);
        M5Cardputer.Display.setTextColor(0xFFEA);
        M5Cardputer.Display.setFreeFont(&FreeSansBold9pt7b);
        M5Cardputer.Display.drawString("DHub", 144, 34);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 75, 120);
        M5Cardputer.Display.setTextColor(0xF814);
        M5Cardputer.Display.drawString("Repository list -->", 117, 97);
        M5Cardputer.Display.setTextColor(0xFAAE);
        M5Cardputer.Display.drawString("Enter - Open Menu", 117, 84);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 42, 82);
        M5Cardputer.Display.drawBitmap(7, 57, image_download_bits45, 91, 55, 0xFFFF);
        M5Cardputer.Display.setFreeFont();
        M5Cardputer.Display.drawString("", 176, 94);
        M5Cardputer.Display.setTextColor(0xAD55);
        M5Cardputer.Display.drawString("special version for esp32", 75, 53);
        M5Cardputer.Display.setTextColor(0xFFFF);
        M5Cardputer.Display.setFreeFont(&FreeSans9pt7b);
        M5Cardputer.Display.drawString("", 48, 90);
        M5Cardputer.Display.drawRoundRect(109, 75, 125, 39, 1, 0xA815);

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
        M5Cardputer.Display.setTextColor(0xFFEA);
        M5Cardputer.Display.drawString("/ JavaScript", 126, 100);        
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
    
   if (loginState == 1){
       dnsServer.processNextRequest();
  server.handleClient();
  y++;
  v++;
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
       log("Active Repository 1");
       Repository1();
       BlockingLoop=0;
    break;
    case 2:
       log("Active Repository 2");
       Repository2();
       BlockingLoop=0;
    break;
    case 3:
       log("Active Repository 3");
       Repository3();
       BlockingLoop=0;
    break;
    case 4:
       log("Active Repository 4");
       Repository4();
       BlockingLoop=0;
    break;
    case 5:
       log("Active Repository 5");
       Repository5();
       BlockingLoop=0;
    break;
    case 6:
       log("Active Repository 6");
       Repository6();
       BlockingLoop=0;
    break;
    case 7:
       log("Active Repository 7");
       Repository7();
       BlockingLoop=0;
    break;
    case 8:
       log("Active Repository 8");
       Repository8();
       BlockingLoop=0;
    break;
    case 9:
       log("Active MenuList");
       listmenu();
       BlockingLoop=0;
    break;
    case 10:
       log("Active Terminal");
       terminal();
       BlockingLoop=0;
    break;
  }

  if (M5Cardputer.BtnA.wasPressed()) {
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

  }

  if (M5Cardputer.Keyboard.isChange()) {
    if (M5Cardputer.Keyboard.isPressed()) {
        Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
        
        if (status.fn) {
            M5Cardputer.Speaker.tone(8000, 20);
            M5Cardputer.Display.clear();
            srep1 = RepositoryText1 ;
            srep2 = RepositoryText2 ;
            srep3 = RepositoryText3 ;
            srep4 = RepositoryText4 ;
            srep5 = RepositoryText5 ;
            srep6 = RepositoryText6 ;
            srep7 = RepositoryText7 ;

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
                case 10:
                   command.remove(command.length() - 1);
                   terminal();
    
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
                case 10:
                  if(command=="/hello"){
                    StatusCommand = 1;
                    terminal();
                  }
                  if(command=="/world"){
                    StatusCommand = 2;
                    terminal();
                  }
                  if(command=="/delete"){
                    StatusCommand = 3;
                    terminal();
                  }     
                  if(command=="give srep1"){
                    StatusCommand = 4;
                    terminal(); 
                  }      
                  if(command=="give srep2"){
                    StatusCommand = 5;
                    terminal();
                  }
                  if(command=="give srep3"){
                    StatusCommand = 6;
                    terminal();
                  }       
                  if(command=="give srep4"){
                    StatusCommand = 7;
                    terminal();
                  }           
                  if(command=="give srep5"){
                    StatusCommand = 8;
                    terminal();
                  }    
                  if(command=="give srep6"){
                    StatusCommand = 9;
                    terminal();
                  }        
                  if(command=="give srep7"){
                    StatusCommand = 10;
                    terminal();
                  }  
                  if(command=="if rep1=s1"){
                    StatusCommand = 11;
                    terminal();
                  }
                  if(command=="if rep2=s2"){
                    StatusCommand = 12;
                    terminal();
                  }
                  if(command=="if rep3=s3"){
                    StatusCommand = 13;
                    terminal();
                  }
                  if(command=="if rep4=s4"){
                    StatusCommand = 14;
                    terminal();
                  }
                  if(command=="if rep5=s5"){
                    StatusCommand = 15;
                    terminal();
                  }
                  if(command=="if rep6=s6"){
                    StatusCommand = 16;
                    terminal();
                  }
                  if(command=="if rep7=s7"){
                    StatusCommand = 17;
                    terminal();
                  }                   
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
               if (ProgrammWork==10){       
                M5Cardputer.Speaker.tone(8000, 20);
                command += i;
                terminal();

             }
        }




        if (ProgrammWork==9){
              if (M5Cardputer.Keyboard.isKeyPressed('.')) {
                 selectedItem = (selectedItem + 1) % menuLength;          
                listmenu();
              }
              if (M5Cardputer.Keyboard.isKeyPressed(';')) {
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
                case 10:
                    command+"/";
                break;
                default:
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
                case 10:
                    command+",";
                break;
                default:
                  MenuPosition--;
                  DHubMenuGUI();
                break;
          }
        }
    }
  }
   }else{
     M5Cardputer.update();
     if (M5Cardputer.Keyboard.isChange()) {
        if (M5Cardputer.Keyboard.isPressed()) {
            Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();

            for (auto i : status.word) {
                wes += i;
                login();
            }

            if (status.del) {
                wes.remove(wes.length() - 1);
                                login();

            }

            if (status.enter) {
                 if(wes=="dhub2024"){
                     M5Cardputer.Display.clear();
                     WiFi.softAP(ssid, password);
                     IPAddress IP = WiFi.softAPIP();
                     Serial.print("IP address: ");
                     Serial.println(IP);
                     dnsServer.start(DNS_PORT, "*", IP); // Redirect all requests to ESP32 IP
                     server.on("/", handleRoot);
                     server.on("/update", handleUpdate);
                     server.on("/tools", handleTools);
                     server.onNotFound([]() {
                        server.sendHeader("Location", "http://terminalpro.os/", true); // Change the address here
                        server.send(302, "text/plain", "");
                     });
                     server.begin();
                     Serial.println("HTTP server started");
                     if (!SPIFFS.begin(true)) {
                        Serial.println("Ошибка монтирования SPIFFS");
                        return;
                     }     
                     setFile1();
                     setFile2();
                     setFile3();
                     setFile4();
                     setFile5();
                     setFile6();
                     setFile7();     
                     ServerFileRead1();
                     ServerFileRead2();
                     ServerFileRead3();
                     ServerFileRead4();
                     ServerFileRead5();
                     ServerFileRead6();
                     ServerFileRead7();   
                     loginState=1;
                     DHubMenuGUI();
                     DHubPanelGUI();
                     wes="";
                 }else{
                                    M5Cardputer.Speaker.tone(7000, 3000);
                 }
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
       BlockingLoop=9;
       ProgrammWork=9;
       listmenu();    
    break;
    case 2:
      BlockingLoop = 1;
      Repository1();
      ProgrammWork = 1;
    break;
    case 3:
      BlockingLoop = 2;
      ProgrammWork = 2;
      Repository2();
    break;
    case 4:
      BlockingLoop = 3;
      ProgrammWork = 3;
      Repository3();
    break;
    case 5:
      BlockingLoop = 4;
      ProgrammWork = 4;
      Repository4();
    break;
    case 6:
      BlockingLoop = 5;
      ProgrammWork = 5;
      Repository5();
    break; 
    case 7:
      BlockingLoop = 6;
      ProgrammWork = 6;
      Repository6();
    break;        
    case 8:
      BlockingLoop = 7;
      ProgrammWork = 7;
      Repository7();
    break;  
  }
}
void res(){    
    SPIFFS.remove("/rep1.txt");
    SPIFFS.remove("/rep2.txt");
    SPIFFS.remove("/rep3.txt");
    SPIFFS.remove("/rep4.txt");
    SPIFFS.remove("/rep5.txt");
    SPIFFS.remove("/rep6.txt");
    SPIFFS.remove("/rep7.txt");
    SPIFFS.remove("/rep8.txt");
}
void executeAction(int item) {
      switch (item) {
        case 0:
          ProgrammWork=10;
          M5Cardputer.Speaker.tone(2000, 20);
          BlockingLoop = 10;
          terminal();
        break;
        case 1:
           log("The panel of procedures for destroying repositories is open");
           res();
        break;
        case 2:
                log("Attention! The panel with information about IP and Web is open");
                ipAddress = WiFi.localIP().toString(); // Сохранение IP-адреса в строку
                Serial.println("Подключено!");
                Serial.println("IP адрес: " + ipAddress);
                M5Cardputer.Display.clear();
                static const unsigned char PROGMEM image_download_bitsadsads[] = {0x7f,0x80,0x7e,0x80,0x7f,0x80,0x40,0x80,0xfe,0x80,0x82,0x80,0x83,0x80,0xfe,0x00};
                static const unsigned char PROGMEM imagedfdf_check_bits[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x30,0x00,0x60,0x80,0xc0,0xc1,0x80,0x63,0x00,0x36,0x00,0x1c,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
                M5Cardputer.Display.fillRect(0, 0, 243, 137, 0xFFFF);
                M5Cardputer.Display.setTextSize(1);
                M5Cardputer.Display.setTextColor(0x52BF);
                M5Cardputer.Display.setFreeFont(&FreeSansBold12pt7b);
                M5Cardputer.Display.drawString("Terminal Pro", 7, 14);
          
                M5Cardputer.Display.setTextColor(0x0);
                M5Cardputer.Display.setFreeFont();
                M5Cardputer.Display.drawString("", 37, 46);
                M5Cardputer.Display.setTextColor(0xFFFF);
                M5Cardputer.Display.drawString("", 95, 64);
                M5Cardputer.Display.setTextColor(0x15);
                M5Cardputer.Display.drawString("web manager for managing DhUb system", 10, 38);
                M5Cardputer.Display.setTextColor(0x0);
                M5Cardputer.Display.drawString("DK Studio 2024  Support ", 7, 121);
                M5Cardputer.Display.drawString("", 15, 2);
                M5Cardputer.Display.setTextColor(0xCE42);
                M5Cardputer.Display.drawString("JavaScript", 151, 121);
                M5Cardputer.Display.setTextColor(0x0);
                M5Cardputer.Display.drawString("", 18, 8);
                M5Cardputer.Display.setTextColor(0xFFFF);
                M5Cardputer.Display.drawString("Text", 26, 67);
                M5Cardputer.Display.drawRoundRect(11, 53, 215, 57, 3, 0x0);
                M5Cardputer.Display.setTextColor(0xFAAA);
                M5Cardputer.Display.drawString("Address:http://terminalpro.os/", 24, 63);
                M5Cardputer.Display.setTextColor(0xA815);
                M5Cardputer.Display.drawString("IP:", 23, 76);
                M5Cardputer.Display.setTextColor(0xA800);
                M5Cardputer.Display.drawString(ipAddress, 41, 76);
                M5Cardputer.Display.setTextColor(0x0);
                M5Cardputer.Display.drawString("SSDI:DHub WebManager ", 24, 91);
                M5Cardputer.Display.drawString("Password: dhub2024", 113, 76);

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
          int DXC = 0;  
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
          if (StatusCommand==1){
            M5Cardputer.Display.drawString("Hello! ", 7, 27);
          }
          if (StatusCommand==2){
          M5Cardputer.Display.drawString("select repository 1-4", 8, 37);
          M5Cardputer.Display.drawString("Inserting repository into repository", 7, 24);
          M5Cardputer.Display.drawString("/Rep1-1 - Repository 1 and 2", 35, 52);
          M5Cardputer.Display.drawString("/Rep1-2 - Repository 1 and 3", 35, 64);
          M5Cardputer.Display.drawString("/Rep1-3 - Repository 1 and 4", 35, 76);
          M5Cardputer.Display.drawString("/Rep1-4 - Repository 1 and 5", 35, 88);
          }
          if (StatusCommand==3){
          M5Cardputer.Display.drawString("select repository 1-8", 8, 37);
          M5Cardputer.Display.drawString("Removes individual repositories", 7, 24);
          M5Cardputer.Display.setTextColor(0xFFFF);
          M5Cardputer.Display.setFreeFont(&FreeSansBold9pt7b);
          M5Cardputer.Display.drawString("delete[rep1-8]", 7, 52);
          }
          if (StatusCommand==4){
            M5Cardputer.Display.drawString("Server Repository 1 text:", 7, 27);
            M5Cardputer.Display.drawString(escapeHtml(srep1), 7, 37);
          }     
          if (StatusCommand==5){
            M5Cardputer.Display.drawString("Server Repository 2 text:", 7, 27);
            M5Cardputer.Display.drawString(escapeHtml(srep2), 7, 37);
          }    
          if (StatusCommand==6){
            M5Cardputer.Display.drawString("Server Repository 3 text:", 7, 27);
            M5Cardputer.Display.drawString(escapeHtml(srep3), 7, 37);
          }    
          if (StatusCommand==7){
            M5Cardputer.Display.drawString("Server Repository 4 text:", 7, 27);
            M5Cardputer.Display.drawString(escapeHtml(srep4), 7, 37);
          }    
          if (StatusCommand==8){
            M5Cardputer.Display.drawString("Server Repository 5 text:", 7, 27);
            M5Cardputer.Display.drawString(escapeHtml(srep5), 7, 37);
          }   
          if (StatusCommand==9){
            M5Cardputer.Display.drawString("Server Repository 6 text:", 7, 27);
            M5Cardputer.Display.drawString(escapeHtml(srep6), 7, 37);
          }    
          if (StatusCommand==10){
            M5Cardputer.Display.drawString("Server Repository 7 text:", 7, 27);
            M5Cardputer.Display.drawString(escapeHtml(srep7), 7, 37);
          }
          if (StatusCommand==11){
            if(srep1==RepositoryText1){
                           M5Cardputer.Display.drawString("Yes! The package matches the repository", 7, 27);
            }else{
              M5Cardputer.Display.drawString("No! The package does not match the repository", 7, 27);
            }
          }   
          if (StatusCommand==12){
            if(srep2==RepositoryText2){
                           M5Cardputer.Display.drawString("Yes! The package matches the repository", 7, 27);
            }else{
              M5Cardputer.Display.drawString("No! The package does not match the repository", 7, 27);
            }
          }
          if (StatusCommand==13){
            if(srep3==RepositoryText3){
                           M5Cardputer.Display.drawString("Yes! The package matches the repository", 7, 27);
            }else{
              M5Cardputer.Display.drawString("No! The package does not match the repository", 7, 27);
            }
          }
          if (StatusCommand==14){
            if(srep4==RepositoryText4){
                           M5Cardputer.Display.drawString("Yes! The package matches the repository", 7, 27);
            }else{
              M5Cardputer.Display.drawString("No! The package does not match the repository", 7, 27);
            }
          }
          if (StatusCommand==15){
            if(srep5==RepositoryText5){
                           M5Cardputer.Display.drawString("Yes! The package matches the repository", 7, 27);
            }else{
              M5Cardputer.Display.drawString("No! The package does not match the repository", 7, 27);
            }
          }
          if (StatusCommand==16){
            if(srep6==RepositoryText6){
                           M5Cardputer.Display.drawString("Yes! The package matches the repository", 7, 27);
            }else{
              M5Cardputer.Display.drawString("No! The package does not match the repository", 7, 27);
            }
          }
          if (StatusCommand==17){
            if(srep7==RepositoryText7){
                           M5Cardputer.Display.drawString("Yes! The package matches the repository", 7, 27);
            }else{
              M5Cardputer.Display.drawString("No! The package does not match the repository", 7, 27);
            }
          }



}
