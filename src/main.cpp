#include <M5Dial.h>
#include <M5GFX.h>
#include <Encoder.h>
#include <USB.h>
#include <USBHIDGamepad.h>

USBHIDGamepad gamepad;
M5GFX display;

void setup()
{
  M5Dial.begin(true);
  USB.begin();
  display.begin();
  gamepad.begin();
  init_encoder();

  Serial.begin(115200);
  Serial.println("Start");
}

int16_t lastPosition = 0;

void loop()
{
  M5Dial.update();
  int16_t position = (get_encoder() + 48) % 96;

  int8_t joystickValue = map(position, 0, 96, -128, 127);

  // Send to gamepad
  gamepad.leftStick(joystickValue, 0);

  // Debug output
  Serial.print("Position: ");
  Serial.print(position);
  Serial.print(" -> Axis: ");
  Serial.println(joystickValue);

  if (lastPosition != position)
  {
    lastPosition = position;
    display.fillScreen(TFT_BLACK);
    display.setCursor(50, 100);
    display.printf("Position: %d\n", position);

    display.setCursor(50, 120);
    display.printf("Axis: %d\n", joystickValue);
  }

  delay(10);
}
