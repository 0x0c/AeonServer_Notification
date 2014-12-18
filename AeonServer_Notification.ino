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
		char c;
		do{
		    c = Serial.read();
		    title += c;
		} while (c != '\0');
		do{
		    c = Serial.read();
		    body += c;
		} while (c != '\0');
		Notification *n = new Notification(title.c_str(), body.c_str());
		page.postNotification(n);
	}
	if (page.needToRefresh()) {
		u8g.firstPage();
		do {
			page.draw();
		} while(u8g.nextPage());
	}
}
