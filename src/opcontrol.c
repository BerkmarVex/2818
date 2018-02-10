#include "main.h"
#include "pid.h"
#include "dualzone.h"
#include "toggle.h"

bool liftUp;
bool liftMid;
bool liftDown;
bool goalUp;
bool goalDown;
bool clawUp;
bool clawDown;
int tankRightDrive;
int verticalJoyLeft;
int horizontalJoyRight;
int tankLeftDrive;

void update() {
	liftUp     = joystickGetDigital(1, 5, JOY_UP);
	liftMid    = joystickGetDigital(1, 5, JOY_RIGHT);
	liftDown   = joystickGetDigital(1, 5, JOY_DOWN);
	goalUp     = joystickGetDigital(1, 6, JOY_UP);
	goalDown   = joystickGetDigital(1, 6, JOY_DOWN);
	clawUp     = joystickGetDigital(1, 8, JOY_UP);
	clawDown   = joystickGetDigital(1, 8, JOY_DOWN);

}

void tank() {

  tankRightDrive = joystickGetAnalog(1, 2);
	tankLeftDrive  = joystickGetAnalog(1, 3);

	if(abs(tankRightDrive) > 10 || abs(tankLeftDrive) > 10){
		motorSet(DRIVELEFT, tankLeftDrive);
		motorSet(DRIVERIGHT, -tankRightDrive);
	}

	else if(abs(tankRightDrive) <= 10 || abs(tankLeftDrive) <= 10){
		motorStop(DRIVELEFT);
		motorStop(DRIVERIGHT);
	}
}

void arcade() {
  verticalJoyLeft    = joystickGetAnalog(1, 3);
  horizontalJoyRight = joystickGetAnalog(1, 1);

  motorSet(DRIVELEFT, (horizontalJoyRight) + verticalJoyLeft);
	motorSet(DRIVERIGHT, (horizontalJoyRight) - verticalJoyLeft);
}

void operatorControl() {
  encoderReset(one);
	while (1) {
		update();
		if(liftUp ^ liftDown ^liftMid){
			if (liftUp) {
				motorSet(LIFT, 100);
			}

      else if(liftMid){
        motorSet(LIFT, pidDo(&lift));
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

    //tank();
    arcade();
		delay(20);
	}
}
