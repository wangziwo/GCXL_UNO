#include "header.h"


void setup() {
Serial.begin(9600,SERIAL_8N1);  //启动串行通信

Serial.print(read_rgb());
}
void loop(){



}
