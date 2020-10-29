// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftFrontMotor       motor         19              
// LeftBackMotor        motor         20              
// RightFrontMotor      motor         12              
// RightBackMotor       motor         21              
// Controller1          controller                    
// RightRoller          motor         13              
// LeftRoller           motor         14              
// IntakeMotor          motor         11              
// Indexer              motor         17              
// Inertial             inertial      15              
// Expander1            triport       1               
// SideEncoder          encoder       A, B            
// FwdEncoder           encoder       C, D            
// BumperHigh           bumper        G               
// BumperLow            bumper        H               
// BumperLow2           bumper        A               
// Expander2            triport       2               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "HolonomicClass.h"

using namespace vex;

// A global instance of competition
competition Competition;




// define your global instances of motors and other devices here

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
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
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
  //Declaring Speeds for Intake and Rollers
  double rollerSpeed = 70;
  double intakeSpeed = 95;
  LeftRoller.setVelocity(rollerSpeed, pct);
  RightRoller.setVelocity(rollerSpeed, pct);
  IntakeMotor.setVelocity(intakeSpeed, pct);
  Indexer.setVelocity(intakeSpeed, pct);

  Holonomic robot; //declaration of robot in Holonomic Class

  //Sleep allowing robot to calibrate
  vex::task::sleep(500);

  //Ball #1
  //Picks up first ball, goes to 1st position
  robot.startRollers();
  robot.goForward(7, 20);
  robot.intake(1);
  robot.stopRollers();
  robot.goForward(28, 20);
  //Turns
  robot.turnRight(136.5, 20);
  //Goes forward to goal
  robot.goForward(34.5, 20);
  //score
  robot.intake(3);
  
  //Ball #2
  //moves back
  robot.goBackward(15.75, 20);
  //Turns
  robot.turnRight(45.3, 20);
  //Goes to goal
  robot.goRight(30, 20);
  //Goes into goal
  robot.goForward(16, 20);
  //Scores
  robot.intake(3);

  //Ball #3
  //Goes back
  robot.goBackward(6, 20);
  //Turns
  robot.turnRight(90.15, 20);
  //Slightly move left to align with balll
  robot.goLeft(2, 20);
  //Goes forward, picks up ball
  robot.startRollers();
  robot.goForward(50, 20);
  robot.stopRollers();
  //Intakes to bottom
  robot.intake(1);
  //Turns toward goal
  robot.turnLeft(44.85, 20);
  //Goes into goal
  robot.goForward(7.75, 20);
  //Scores
  robot.intake(3);

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  double deadZone = 5;
  while (1) {
  //Drive Code
    if(Controller1.Axis1.value() > deadZone || Controller1.Axis2.value() > deadZone || Controller1.Axis4.value() > deadZone ||
    Controller1.Axis1.value() < -deadZone || Controller1.Axis2.value() < -deadZone || Controller1.Axis4.value() < -deadZone)
    {
    LeftFrontMotor.spin(vex::directionType::fwd, Controller1.Axis1.value() + Controller1.Axis2.value() + Controller1.Axis4.value(), vex::velocityUnits::pct);
    LeftBackMotor.spin(vex::directionType::fwd, -(Controller1.Axis1.value()) + Controller1.Axis2.value() + Controller1.Axis4.value(), vex::velocityUnits::pct);
    RightFrontMotor.spin(vex::directionType::fwd, -(Controller1.Axis1.value()) + Controller1.Axis2.value() - Controller1.Axis4.value(), vex::velocityUnits::pct);
    RightBackMotor.spin(vex::directionType::fwd, Controller1.Axis1.value() + Controller1.Axis2.value() - Controller1.Axis4.value(), vex::velocityUnits::pct);
    }

    else{
      LeftFrontMotor.stop(brakeType::brake);
      LeftBackMotor.stop(brakeType::brake);
      RightFrontMotor.stop(brakeType::brake);
      RightBackMotor.stop(brakeType::brake);
    }
    //Rollers
    int clawSpeed = 95;
        if(Controller1.ButtonR1.pressing()) {
            LeftRoller.spin(directionType::rev, clawSpeed, velocityUnits::pct);
            RightRoller.spin(directionType::rev, clawSpeed, velocityUnits::pct);
            
        }
        else if(Controller1.ButtonR2.pressing()) {
            LeftRoller.spin(directionType::fwd, clawSpeed, velocityUnits::pct);
            RightRoller.spin(directionType::fwd, clawSpeed, velocityUnits::pct);
        }
        else {
            LeftRoller.stop(brakeType::coast);
            RightRoller.stop(brakeType::coast); 
        }

    //Intake
    int intakeSpeed = 95;
        if(Controller1.ButtonL1.pressing()) {
            IntakeMotor.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);   
            Indexer.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);
        }
        else if(Controller1.ButtonL2.pressing()) {
            IntakeMotor.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
            Indexer.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
        }
        else {
            IntakeMotor.stop(brakeType::coast);
            Indexer.stop(brakeType::coast);
        }

        if(Controller1.ButtonUp.pressing()) {
            IntakeMotor.spin(directionType::fwd, intakeSpeed, velocityUnits::pct);   
            Indexer.spin(directionType::rev, intakeSpeed, velocityUnits::pct);
        }



    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
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