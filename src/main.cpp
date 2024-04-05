#include <Arduino.h>
#include "movement.hpp"
#include <TaskScheduler.h>

#define _TASK_SLEEP_ON_IDLE_RUN // Enable 1 ms SLEEP_IDLE powerdowns between runs if no callback methods were invoked during the pass
#define _TASK_STATUS_REQUEST    // Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only

#ifdef TARGET_UNO
Motor leftMotor{6, A0, A1};
Motor rightMotor{5, A2, A3};
WheelSystem wheels(leftMotor, rightMotor);
const int IR_PIN = 23;
#elif TARGET_ESP
Motor leftMotor{1, 2, 3};
Motor rightMotor{1, 2, 3};
WheelSystem wheels{leftMotor, rightMotor};
const int IR_PIN = 23;
#else // bidon
Motor leftMotor{1, 2, 3};
Motor rightMotor{1, 2, 3};
WheelSystem wheels{leftMotor, rightMotor};
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

// TODO: to make sure the teacher doesnt get confused and 
// removes points, dont forget to label the members of tasks
Task altertateRotationDirection(
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
      Vector movement{
        0, speed * 0.5
      };
      wheels.setMovement(movement);
    },
    &ts,
    true};

void setup()
{
  Serial.begin(115200);
  wheels.begin();
}

void loop()
{
  ts.execute();
  // auto current_millis = millis();

  // if (current_millis % 1000 == 0)
  // {
  //   current_direction = reverse(current_direction);
  // }
  // auto speed = (current_millis % 1000 / 1000.0) * variation(current_direction);
  // motor.setSpeed(speed);
  // Serial.println("s:" + String(speed) + " d:" + current_direction);
}
