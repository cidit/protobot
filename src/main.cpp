#ifdef USING_PIO

#include <Arduino.h>
#include "movement.hpp"
#include <TaskScheduler.h>
#include "ultrasound.hpp"
#include "communication.hpp"

#define _TASK_SLEEP_ON_IDLE_RUN // Enable 1 ms SLEEP_IDLE powerdowns between runs if no callback methods were invoked during the pass
#define _TASK_STATUS_REQUEST    // Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only

#ifdef TARGET_UNO

Motor leftMotor{6, A0, A1};
Motor rightMotor{5, A2, A3};
WheelSystem wheels(leftMotor, rightMotor);

Ultrasound ultrasound(2, 3);

// #define IR_PIN 4

#elif TARGET_ESP // bidon, je ne le supporte pas encore

Motor leftMotor{1, 2, 3};
Motor rightMotor{1, 2, 3};
WheelSystem wheels{leftMotor, rightMotor};

Ultrasound ultrasound(1, 2);

// #define IR_PIN 23

#else // bidon, tant que ca compile

Motor leftMotor{1, 2, 3};
Motor rightMotor{1, 2, 3};
WheelSystem wheels{leftMotor, rightMotor};

// #define IR_PIN 23

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
Task alternate_rotation_direction(
    1 * TASK_SECOND,
    TASK_FOREVER,
    []()
    {
      current_direction = reverse(current_direction);
    });

Task change_speed{
    10 * TASK_MILLISECOND,
    TASK_FOREVER,
    []()
    {
      auto speed = (millis() % 1000 / 1000.0) * variation(current_direction);
      Vector movement{0, speed * 0.5};
      wheels.setMovement(movement);
    }};

Task collect_ultrasound_distance_and_print_to_serial(
    100 * TASK_MILLISECOND,
    TASK_FOREVER,
    []()
    {
      float distance;
      ultrasound.sample(distance);
        Serial.println("this is the distance! " + String(distance) + "mm");
    });

Task health_check(
    1 * TASK_SECOND,
    TASK_FOREVER,
    []()
    {
      Serial.println("im alive");
    });

Task process_remote_command(
  1*TASK_MILLISECOND,
  TASK_FOREVER,
  [](){
    REMOTE_BUTTON_CODES code;
    if (!getCodeFromRemote(code)) {
      return;
    } 
    Serial.println(getButtonName(code));
  }
);

void setup()
{
  Serial.begin(115200);
  wheels.begin();
  ultrasound.begin();
  initRemote(4);
  ts.addTask(alternate_rotation_direction);
  // ts.addTask(change_speed);
  // ts.addTask(collect_ultrasound_distance_and_print_to_serial);
  ts.addTask(process_remote_command);
  ts.addTask(health_check);
  ts.enableAll();
}

void loop()
{
  ts.execute();
}

#endif