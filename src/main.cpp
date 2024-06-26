/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       nikkasouza                                                */
/*    Created:      6/25/2024, 1:58:31 PM                                     */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;
brain Brain;

// define your global instances of motors and other devices here

controller Controller = controller(primary);

motor LeftMotor = motor(PORT2, ratio18_1, true); // Blue motor 18-1 ratio, true for reversed (idk i assembled it wonky)
motor_group LeftMotorGroup = motor_group(LeftMotor);

motor RightMotor = motor(PORT1, ratio18_1, true); 
motor_group RightMotorGroup = motor_group(RightMotor);

drivetrain Drivetrain = drivetrain(LeftMotorGroup, RightMotorGroup, 12.5664, 10, 6.5, inches, 1.0);

bumper Bumper = bumper(Brain.ThreeWirePort.A);

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  return;
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  Drivetrain.drive(forward);
  waitUntil(Bumper.pressing());
  Drivetrain.drive(reverse);
  wait(2, seconds);
  Drivetrain.stop();

  return;
}

void usercontrol(void) {
  // User control code here, inside the loop

  while (1) {
    Drivetrain.setTurnVelocity(abs(Controller.Axis4.position()), percent);
    Drivetrain.setDriveVelocity(abs(Controller.Axis2.position()), percent);


    if (Controller.Axis2.position() > 0) {
      Drivetrain.drive(forward);
    } else if (Controller.Axis2.position() < 0) {
      Drivetrain.drive(reverse);
    }

    if (Controller.Axis4.position() > 0) {
      Drivetrain.turn(left);
    } else if (Controller.Axis4.position() < 0) {
      Drivetrain.turn(right);
    }

    wait(20, msec);
  }

  return;
}


int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
