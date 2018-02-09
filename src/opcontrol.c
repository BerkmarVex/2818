static const int CALVINPUTTHEPOSITIONHERE = 0;

/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Any copyright is dedicated to the Public Domain.
 * http://creativecommons.org/publicdomain/zero/1.0/
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"
#include "pid.h"
#include "dualzone.h"


void DEGUG(){
  printf("%d\n", encoderGet(one));
}
/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

 bool liftUp;
 bool liftMid
 bool liftDown;
 bool goalUp;
 bool goalDown;
 bool clawUp;
 bool clawDown;
 int rightDrive;
 int leftDrive;

	void update(){
		liftUp = joystickGetDigital(1, 5, JOY_UP);
    liftMid = joystickGetDigital(1, 5, JOY_RIGHT);
		liftDown = joystickGetDigital(1, 5, JOY_DOWN);
		goalUp = joystickGetDigital(1, 6, JOY_UP);
		goalDown = joystickGetDigital(1, 6, JOY_DOWN);
		clawUp = joystickGetDigital(1, 7, JOY_UP);
		clawDown = joystickGetDigital(1, 7, JOY_DOWN);
		rightDrive = joystickGetAnalog(1, 2);
		leftDrive = joystickGetAnalog(1, 3);
	}



void operatorControl() {
  lift.target = CALVINPUTTHEPOSITIONHERE;
  encoderReset(one);
	while (1) {
    DEBUG();
		update();
		if(liftUp ^ liftDown ^liftMid){
			if (liftUp) {
				motorSet(LIFT, 100);
			}

      else if(liftMid){
        motorSet(LIFT, singlePid(&lift));
      }

      else {
				motorSet(LIFT, -100);
			}
		}


		else{
			motorStop(LIFT);
		}

		if(goalDown ^ goalUp){
			if (goalDown) {
				motorSet(LIFTGOAL, 100);
			} else {
				motorSet(LIFTGOAL, -100);
			}
		}

		else{
			motorStop(LIFTGOAL);
		}

		if(clawUp ^ clawDown){
			if(clawUp){
				motorSet(CLAW, 100);
			} else {
				motorSet(CLAW, -100);
			}
		}

		else {
			motorStop(CLAW);
		}

		if(abs(rightDrive) > 10 || abs(leftDrive) > 10){
			motorSet(DRIVELEFT, leftDrive);
			motorSet(DRIVERIGHT, -rightDrive);
		}

		else if(abs(rightDrive) <= 10 || abs(leftDrive) <= 10){
			motorStop(DRIVELEFT);
			motorStop(DRIVERIGHT);
		}
		delay(20);
	}
}
