#include "Aria.h"
#include "stdio.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

double ePrev = 0.0;
double err_P = 0.0;
double err_I = 0.0;
double err_D = 0.0;
double kP = 0.7; // 0.6 - 0.8 ideal range kP = 0.1 for simulator
double kI = 0.025; // 0.0 - 0.3   ideal range kI = 0 for simulator
double kD = 0.85; // 0.4 - 0.6 ideal range kD = 0.2 for simulator
int x = 0;
std::vector <double> e_past {50};

double err_update(double err)
{
	float sum = 0;
	for (int i = 1; i < e_past.size(); i++)	e_past[i] = e_past[i - 1];
	e_past[0] = err;
	for (int i = 0; i < e_past.size(); i++) sum += e_past[i];
	return sum;
}

int main(int argc, char **argv)

{
	
	// step 1 : create instances
	Aria::init();
	ArRobot robot;

	// parse command line arguments
	ArArgumentParser argParser(&argc, argv);
	argParser.loadDefaultArguments();

	// step 2 : connect robot
	ArRobotConnector
		robotConnector(&argParser, &robot);

	if (robotConnector.connectRobot())
		std::cout << " Robot connected!" << std::endl;
	robot.runAsync(false);
	robot.lock();
	robot.enableMotors();
	robot.unlock();

	// code logic goes here PID CONTROLLER
	while (true)
	{

		ArSensorReading* sonarSensor[8];
		int sonarRange[8];

		// GET SONAR RANGE
		for (int i = 0; i <= 7; i++)
		{
			sonarSensor[i] = robot.getSonarReading(i);
			sonarRange[i] = sonarSensor[i]->getRange();
			//std::cout << "sonarRange " << i << ' ' << sonarRange[i] << '\n';
		}

		// Effective distance 
		double S0 = sonarRange[5] / 2.0;    
		double S1 = sonarRange[6] / 1.305;	  
		double S2 = sonarRange[7] / 1.0;     

		//std::cout << Eff_Dist << '\n';

		// PID output
		for (int i = 5; i < 8; i++)
		{
			if (sonarRange[i] > 1000) sonarRange[i] = sonarRange[i] = 1000;
			err_P = err_P + (800 - (sonarRange[i]));
		}
		err_P = err_P / 3;
		 
		 // err = desired distance - Current distance i.e reference distance is 500.0
		 //std::cout << "err: " << err << '\n';
		 err_I = err_update(err_P);
		 err_D = err_P - ePrev;
		 ePrev = err_P;
		 double U = (kP*err_P) + (kI*err_I) + (kD*err_D); // U is the PID control signal / correction
		//std::cout << "U: " << U << '\n';
	    
		// Velocities
		double LeftVel = 100.0 - U ;
		double RightVel = 100.0;

		// set velocity
		robot.setVel2(LeftVel, RightVel);

	}

	// stop the robot

	robot.lock();
	robot.stop();
	robot.unlock();
	// terminate all threads and exit
	Aria::exit();
}