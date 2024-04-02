#include <Arduino.h>
#include "movement.hpp"
#include <TScheduler.hpp>

#define _TASK_SLEEP_ON_IDLE_RUN  // Enable 1 ms SLEEP_IDLE powerdowns between runs if no callback methods were invoked during the pass
#define _TASK_STATUS_REQUEST     // Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only


Motor motor{5, A0, A1};
TsScheduler ts;

enum Direction
{
  CLOCKWISE,
  COUNTER_CLOCKWISE
} current_direction;

Direction reverse(Direction direction)
{
  return direction == CLOCKWISE ? COUNTER_CLOCKWISE : CLOCKWISE;
}

int variation(Direction direction)
{
  return direction == CLOCKWISE ? 1 : -1;
}

void clbk() {

}

TsTask altertateRotateDirection (
  1 * TASK_SECOND, 1* TASK_SECOND, clbk, &ts, true
);

void setup()
{
  // put your setup code here, to run once:
  motor.begin();
}

void loop()
{
  ts.execute();
  auto current_millis = millis();

  // put your main code here, to run repeatedly:
  if (current_millis % 1000 == 0)
  {
    current_direction = reverse(current_direction);
  }
  auto speed = (current_millis % 1000 / 1000.0) * variation(current_direction);
  motor.setSpeed(speed);
  Serial.print("s:" + String(speed) + " d:" + current_direction);
}
