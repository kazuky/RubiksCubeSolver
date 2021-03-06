#pragma config(Sensor, S4,     color,          sensorCOLORFULL)
#pragma config(Motor,  motorA,          flipper,       tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorB,          table,         tmotorNXT, PIDControl, encoder)
#pragma config(Motor,  motorC,          spinner,       tmotorNXT, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#include "variables.h"
#include "BasicMovements.h"
#include "SolvingMovements.h"
#include "ScanFunctions.h"
#include "SolveFunctions.h"
#include "Steps.h"

task main()
{
	nMotorEncoder[table]   = 0;
	nMotorEncoder[flipper] = 0;
	nMotorEncoder[spinner] = 0;

	while(true){
		scanFaces();
		if(solvabler()) break;
		redCount = 0;
		solving = false;
		power = 30;
	}
	solve();
}
