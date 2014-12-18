#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <string>
#include <vector>
#include <iterator>
#include "U8glib.h"
#include <AeonUI.h>
#include <AeonServer.h>

using namespace AeonUI;
using namespace AeonServer;

U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE);
Page page;
Server server;

const uint8_t tool_icon_image[] U8G_PROGMEM = {
  0x00, 0x00, 0x0E, 0x00, 0x00, 0x80, 0x0F, 0x00, 0x04, 0xC0, 0x0F, 0x00, 
  0x0E, 0xE0, 0x07, 0x00, 0x1F, 0xE0, 0x03, 0x00, 0x3F, 0xF0, 0x03, 0x00, 
  0x3E, 0xF0, 0x03, 0x00, 0x7C, 0xF0, 0x03, 0x00, 0xF0, 0xF0, 0x03, 0x0E, 
  0xE0, 0xF1, 0x07, 0x0F, 0xC0, 0xF3, 0xFF, 0x0F, 0x80, 0xFF, 0xFF, 0x07, 
  0x00, 0xFF, 0xFF, 0x07, 0x00, 0xFE, 0xFF, 0x03, 0x00, 0xFF, 0xFF, 0x01, 
  0x80, 0xFF, 0x7F, 0x00, 0xC0, 0xFF, 0x01, 0x00, 0xE0, 0xFF, 0x01, 0x00, 
  0xF0, 0xFF, 0x03, 0x00, 0xF8, 0xBF, 0x0F, 0x00, 0xFC, 0x1F, 0x3F, 0x00, 
  0xFE, 0x0F, 0x7F, 0x00, 0xCF, 0x07, 0xFF, 0x00, 0xC7, 0x03, 0xFE, 0x01, 
  0xE7, 0x01, 0xFE, 0x01, 0xFF, 0x00, 0xFC, 0x01, 0x7E, 0x00, 0xF8, 0x01, 
  0x3C, 0x00, 0xE0, 0x00
};

void setup(void)
{
	// flip screen, if required
	// u8g.setRot90();
	u8g.setRot180();

	u8g.setFont(u8g_font_6x10);
	u8g.setFontPosTop();
	Serial.begin(9600);
	pinMode(6, INPUT);
	pinMode(7, INPUT);

	// set REST HIGH
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);

	page.context = &u8g;
	server.registerPage(&page);
}

void loop(void)
{
	if (Serial.available() > 0) {
		std::string title, body;
		do{
		    char c = Serial.read();
		    title += c;
		} while (c != '\0');
		do{
		    char c = Serial.read();
		    body += c;
		} while (c != '\0');
		Notification *n = new Notification("Title", "Body\nBody2\nBody3");
		page.postNotification(n);
	}
	if (page.needToRefresh()) {
		u8g.firstPage();
		do {
			page.draw();
		} while(u8g.nextPage());
	}
}
