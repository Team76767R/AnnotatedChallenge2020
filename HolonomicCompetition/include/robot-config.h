using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor LeftFrontMotor;
extern motor LeftBackMotor;
extern motor RightFrontMotor;
extern motor RightBackMotor;
extern controller Controller1;
extern motor RightRoller;
extern motor LeftRoller;
extern motor IntakeMotor;
extern motor Indexer;
extern inertial Inertial;
extern triport Expander1;
extern encoder SideEncoder;
extern encoder FwdEncoder;
extern bumper BumperHigh;
extern bumper BumperLow;
extern bumper BumperLow2;
extern triport Expander2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );