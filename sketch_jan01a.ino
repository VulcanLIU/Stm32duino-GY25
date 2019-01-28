#include "ComwithGY25.h"

void setup() {
  // put your setup code here, to run once:
  Serial2.begin(115200);
	GY25.begin();
	GY25.singleMode();
	GY25.correctYaw();
}

void loop() {
  // put your main code here, to run repeatedly:
  GY25.singleMode();
  GY25.refresh();
  Serial2.println(GY25.YPR[2]);
  delay(500);
}

