#include "vex.h"

//Function to convert inches(input) into rotations (for the robot)
double inRotations(double inches){
  double revolutions = inches/(10.21);
  return revolutions;
}

class Holonomic {
  //Access Specifier
  public:

  //Data Members used in any callings, can add variables with new commands that require more variables.
  double length;
  double Time;
  double maxSpeed;

  //List of Commands with Holonomic, will define outside class using ::  
  void goForward(double amount, double maxSpeed);
  //Moving in other directions
  void goBackward(double amount, double maxSpeed);
  void goRight(double amount, double speed);
  void goLeft(double amount, double speed);
  //Turning
  void turnLeft(double amount, double speed);
  void turnRight(double amount, double speed);
  //Intaking
  void startRollers();
  void stopRollers();
  void intake(double amount);
};

//Starts the rollers 
void Holonomic::startRollers() 
{ 
  RightRoller.spin(reverse);
  LeftRoller.spin(reverse);
}

//Stops the rollers
void Holonomic::stopRollers()
{
  RightRoller.stop();
  LeftRoller.stop();
}

//Code to intake a certain amount using bumpers
void Holonomic::intake(double amount)
{
  //Intake to the bottom level
  if (amount == 1)
  {
    while(!BumperLow.pressing())
    { 
    IntakeMotor.spin(forward);
    Indexer.spin(forward);  
    }
  IntakeMotor.stop(brakeType::brake);
  Indexer.stop(brakeType::brake);
  }

  //Intake to the middle
  else if (amount == 2){
    while(!BumperHigh.pressing()){ 
    IntakeMotor.spin(forward);
    Indexer.spin(forward);  
  }
  IntakeMotor.stop(brakeType::brake);
  Indexer.stop(brakeType::brake);
  }

  //Intake and shoot
  else if (amount == 3)
  {
    do
    {
    IntakeMotor.spin(forward);
    Indexer.spin(forward);  
    }
    while(BumperHigh.pressing());
  vex::task::sleep(750);
  IntakeMotor.stop(brakeType::brake);
  Indexer.stop(brakeType::brake);
  }

}

//Below are the instructions for driving 
void Holonomic::goForward(double amount, double speed) 
{
  //Sets current rotation to 0 for accurate distances
  FwdEncoder.resetRotation();

  //Converts inches(input) into wheel rotations
  double revolutions = inRotations(amount);
  while(FwdEncoder.rotation(rev) < revolutions)
  {
    LeftFrontMotor.spin(forward);
    LeftBackMotor.spin(forward);
    RightFrontMotor.spin(forward);
    RightBackMotor.spin(forward);
  }

  //Stopping
  LeftFrontMotor.stop(brakeType::brake);
  LeftBackMotor.stop(brakeType::brake);
  RightFrontMotor.stop(brakeType::brake);
  RightBackMotor.stop(brakeType::brake);
}

//Follows the same structure but sign of encoder is flipped
void Holonomic::goBackward(double amount, double speed){
  FwdEncoder.resetRotation();

  double revolutions = inRotations(amount);
  while(FwdEncoder.rotation(rev) < revolutions)
  {
    LeftFrontMotor.spin(forward);
    LeftBackMotor.spin(forward);
    RightFrontMotor.spin(forward);
    RightBackMotor.spin(forward);
  }

  LeftFrontMotor.stop(brakeType::brake);
  LeftBackMotor.stop(brakeType::brake);
  RightFrontMotor.stop(brakeType::brake);
  RightBackMotor.stop(brakeType::brake);
}

//Same structure but uses the sideways encoder
void Holonomic::goRight(double amount, double speed) {
  
  SideEncoder.resetRotation();

  double revolutions = inRotations(amount);
  while(SideEncoder.rotation(rev) < revolutions){
    LeftFrontMotor.spin(forward);
    LeftBackMotor.spin(reverse);
    RightFrontMotor.spin(reverse);
    RightBackMotor.spin(forward);
  }

  LeftFrontMotor.stop(brakeType::brake);
  LeftBackMotor.stop(brakeType::brake);
  RightFrontMotor.stop(brakeType::brake);
  RightBackMotor.stop(brakeType::brake);
}

//Same as right, but encoder value is flipped
void Holonomic::goLeft(double amount, double speed) {
  SideEncoder.resetRotation();

  double revolutions = inRotations(amount);
  while(-(SideEncoder.rotation(rev)) < revolutions){
    LeftFrontMotor.spin(reverse);
    LeftBackMotor.spin(forward);
    RightFrontMotor.spin(forward);
    RightBackMotor.spin(reverse);
  }

  LeftFrontMotor.stop(brakeType::brake);
  LeftBackMotor.stop(brakeType::brake);
  RightFrontMotor.stop(brakeType::brake);
  RightBackMotor.stop(brakeType::brake);
}

//Code for turning
void Holonomic::turnLeft(double amount, double speed){
  Inertial.setHeading(0, deg); //Reset Inertial sensor
  //Turns while the inertial sensor hasn't reached the turning amount
  while (Inertial.heading(deg) > 360-amount) 
  {
    LeftFrontMotor.spin(directionType::rev, speed, velocityUnits::pct);
    LeftBackMotor.spin(directionType::rev, speed, velocityUnits::pct);
    RightFrontMotor.spin(directionType::fwd, speed, velocityUnits::pct);
    RightBackMotor.spin(directionType::fwd, speed, velocityUnits::pct);
  }
  LeftFrontMotor.stop();
  LeftBackMotor.stop();
  RightFrontMotor.stop();
  RightBackMotor.stop();
}

//Same code as the turn in the other direction with some sign changes
void Holonomic::turnRight(double amount, double speed){
  Inertial.setHeading(0, deg); //Reset Inertial sensor
  while (Inertial.heading(deg) < amount) {
    Brain.Screen.newLine();
    Brain.Screen.print( Inertial.heading());
    LeftFrontMotor.spin(directionType::fwd, 10, velocityUnits::pct);
    LeftBackMotor.spin(directionType::fwd, 10, velocityUnits::pct);
    RightFrontMotor.spin(directionType::rev, 10, velocityUnits::pct);
    RightBackMotor.spin(directionType::rev, 10, velocityUnits::pct);
  }
  LeftFrontMotor.stop();
  LeftBackMotor.stop();
  RightFrontMotor.stop();
  RightBackMotor.stop();
  
}
