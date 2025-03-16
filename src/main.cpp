#include <M5Dial.h>
#include <Encoder.h>
#include <USB.h>
#include <USBHIDGamepad.h>

USBHIDGamepad gamepad;

void setup()
{
  M5Dial.begin(true);
  USB.begin();
  gamepad.begin();
  init_encoder();

  Serial.begin(115200);
  Serial.println("Start");
}

void loop()
{
  M5Dial.update();
  int16_t position = get_encoder();

  if (position < -48)
  {
    position = -48;
  }
  if (position > 48)
  {
    position = 48;
  }

  int8_t joystickValue = map(position, -48, 48, -128, 127);

  // Send to gamepad
  gamepad.leftStick(joystickValue, 0);

  // Debug output
  Serial.print("Position: ");
  Serial.print(position);
  Serial.print(" -> Axis: ");
  Serial.println(joystickValue);

  delay(10);
}
