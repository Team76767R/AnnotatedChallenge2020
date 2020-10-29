#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
triport Expander1 = triport(PORT1);
triport Expander2 = triport(PORT2);
motor LeftFrontMotor = motor(PORT19, ratio18_1, false);
motor LeftBackMotor = motor(PORT20, ratio18_1, false);
motor RightFrontMotor = motor(PORT12, ratio18_1, true);
motor RightBackMotor = motor(PORT21, ratio18_1, true);
controller Controller1 = controller(primary);
motor RightRoller = motor(PORT13, ratio18_1, false);
motor LeftRoller = motor(PORT14, ratio18_1, true);
motor IntakeMotor = motor(PORT11, ratio18_1, false);
motor Indexer = motor(PORT17, ratio18_1, false);
inertial Inertial = inertial(PORT15);
encoder SideEncoder = encoder(Expander1.A);
encoder FwdEncoder = encoder(Expander1.C);
bumper BumperHigh = bumper(Expander1.G);
bumper BumperLow = bumper(Expander1.H);
bumper BumperLow2 = bumper(Expander2.A);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}