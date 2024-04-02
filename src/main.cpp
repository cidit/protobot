#include <Arduino.h>
#include "movement.hpp"
#include <TaskScheduler.h>

#define _TASK_SLEEP_ON_IDLE_RUN // Enable 1 ms SLEEP_IDLE powerdowns between runs if no callback methods were invoked during the pass
#define _TASK_STATUS_REQUEST    // Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only

#ifdef TARGET_UNO
Motor motor{6, A0, A1};
const int IR_PIN = 23;
#elif TARGET_ESP
Motor motor{1, 2, 3};
const int IR_PIN = 23;
#else
Motor motor{1, 2, 3}; // bidon
const int IR_PIN = 23;
#endif

Scheduler ts;

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

Task altertateRotateDirection(
    1 * TASK_SECOND,
    TASK_FOREVER,
    []()
    {
      current_direction = reverse(current_direction);
    },
    &ts,
    true);

Task changeSpeed{
    10 * TASK_MILLISECOND,
    TASK_FOREVER,
    []()
    {
      auto speed = (millis() % 1000 / 1000.0) * variation(current_direction);
      motor.setSpeed(speed);
    },
    &ts,
    true};

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  motor.begin();
}

void loop()
{
  ts.execute();
  // auto current_millis = millis();

  // put your main code here, to run repeatedly:
  // if (current_millis % 1000 == 0)
  // {
  //   current_direction = reverse(current_direction);
  // }
  // auto speed = (current_millis % 1000 / 1000.0) * variation(current_direction);
  // motor.setSpeed(speed);
  // Serial.println("s:" + String(speed) + " d:" + current_direction);
}
