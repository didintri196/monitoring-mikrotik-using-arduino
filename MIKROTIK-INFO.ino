
#include <SPFD5408_Adafruit_GFX.h>    // Core graphics library
#include <SPFD5408_Adafruit_TFTLCD.h> // Hardware-specific library
#include <SPI.h>
#include <Ethernet.h>
#include <aWOT.h>

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0

#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin

// Assign human-readable names to some common 16-bit color values:
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// Ethernet
IPAddress ip(192, 168, 60, 1);
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetServer server(80);

Application app;

String myStrings[10] = {};
int totArray = 0;

void setup(void) {

//  Serial.begin(9600);
  
  tft.reset();
  tft.begin(0x9341); // SDFP5408
  tft.setRotation(1); // Need for the Mega, please changed for your choice or rotation initial
  tft.fillScreen(BLACK);
  drawGrid();
  tft.setCursor (3, 4);
      
  tft.setTextSize(1.5);
  tft.setTextColor(WHITE);
  Ethernet.begin(mac, ip);
  tft.println(Ethernet.localIP());

  // mount the handler to the default router
  app.get("/", &index);
  app.get("/log/bandwidth", &logBandwith);
  app.get("/log/any", &logAny);
  app.get("/log/internet", &logInternet);
}

void index(Request &req, Response &res) {
  //res.set("Content-Type", "application/json");
  res.print("Server Arduino Running.");
}

void DefaultResponse(Response &res) {
  res.set("Content-Type", "application/json");
  res.print("{\"messsage\":\"OK\"}");
}

void logBandwith(Request &req, Response &res) {
  char upload[64];
  char download[64];
  
  req.query("upload", upload, 64);
  req.query("download", download, 64);
  tft.setTextSize(1.5);
  tft.setTextColor(WHITE);
  tft.fillRect(1,1,159,23,BLACK);
  tft.setCursor(3, 4);
  tft.print("Upload:");
  tft.print(upload);
  tft.print(" Mbps");
  tft.setCursor(3, 13);
  tft.print("Download:");
  tft.print(download);
  tft.print(" Mbps");
  DefaultResponse(res);
}

void logAny(Request &req, Response &res) {
  char data[64];
  
  req.query("data", data, 64);
  tft.setTextSize(1.5);
  tft.setTextColor(WHITE);
  tft.fillRect(1,30,319,200,BLACK);
  if(totArray==9){
    pop();
  }
      
myStrings[totArray] = {data};
//Serial.print(totArray); Serial.print("-"); Serial.println(data);
  if(totArray<9){
    totArray++;
  }
  
  // print log
  int scroll = 30;
  for (int i = 0; i<=totArray; i++) {
    tft.setCursor(3, scroll);
    tft.print(myStrings[i]);
    scroll=scroll+9;
  }
  //set response
  DefaultResponse(res);
}

void pop(){
  String tmpStrings[10]=myStrings;
  for (int i = 0; i<=totArray; i++) {
    tmpStrings[i]={myStrings[i+1]};
  }

  for (int i = 0; i<=totArray; i++) {
    myStrings[i]={tmpStrings[i]};
//    Serial.print(i); Serial.print("x"); Serial.println(myStrings[i]);
  }
  
}

void logInternet(Request &req, Response &res) {
  char data[64];
  req.query("data", data, 64);
  tft.fillRect(160,1,319,23,BLACK);
  tft.setCursor(170, 5);
  tft.setTextSize(2);
  if(strcmp(data, "OFFLINE") == 0){
    tft.fillRect(160,1,319,23,RED);
    tft.setTextColor(WHITE);
    tft.print("OFFLINE"); 
  }else{
    tft.fillRect(160,1,319,23,GREEN);
    tft.setTextColor(WHITE);
    tft.print("ONLINE"); 
  }
  DefaultResponse(res);
}

void loop(void) {
  EthernetClient client = server.available();
  if(client.connected()) {
     app.process(&client);
     client.stop();
  }
}

// Draw a grid

void drawGrid () {
  //max W = 319
  tft.drawRect(0,0,160,25,WHITE); // BOX UPLOAD
  tft.drawRect(160,0,319,25,WHITE);  // BOX DOWNLOAD

  //DEBUG MAP
//  tft.setTextColor(WHITE);
//  tft.setTextSize(1);
//  
//  for(uint16_t y = 0; y <= 340; y+=25) { 
//    tft.setCursor (200, y);
//    tft.print(y);
//  }
}
