#include "Aria.h"
#include <vector>
#include <iostream>
#include <algorithm>

#include "ObstacleAvoidance.cpp"
#include "WallFollower.cpp"

using namespace std;

int main(int argc, char **argv)
{
	Aria::init();
	ArRobot robot;
	ArArgumentParser argParser(&argc, argv);
	argParser.loadDefaultArguments();
	ArRobotConnector robotConnector(&argParser, &robot);
	

	if (robotConnector.connectRobot())
		std::cout << " Robot connected!" << std::endl;
	robot.runAsync(0);
	robot.lock();
	robot.enableMotors();
	robot.unlock();
	
	/* create input memebership function for sensor 7 and sensor 6*/
	FollowWallController::S1.set_name("Sensor7");
	FollowWallController::S1.set_memval({ 0,500,200,800,500,1000 });
	FollowWallController::S2.set_name("Sensor6");
	FollowWallController::S2.set_memval({ 0,500,200,800,500,1000 });
	//cout << S1.Near.values[1] << endl;
	//cout << S2.Far.values[0] << endl;

	/* create output membership function for left wheel and right wheel*/
	FollowWallController::w1.set_name("Left Wheel");
	FollowWallController::w1.set_memval({ 0,100,100,200,200,250 });
	FollowWallController::w2.set_name("Right Wheel");
	FollowWallController::w2.set_memval({ 0,100,100,200,200,250 });
	//cout << w1.Slow.values[1] << endl;
	//cout << w2.Fast.values[0] << endl;
	
	/* create input memebership function for sensor 7 and sensor 6*/
	OAController::Front.set_memval({ 0,500,400,800,700,1000 });
	OAController::Left.set_memval({ 0,500,400,800,700,1000 });
	OAController::Right.set_memval({ 0,500,400,800,700,1000 });

	//cout << S1.Near.values[1] << endl;
	//cout << S2.Far.values[0] << endl;

	/* create output membership function for left wheel and right wheel*/
	OAController::w1.set_name("Left Wheel");
	OAController::w1.set_memval({ 0,100,100,200,300,350 });
	OAController::w2.set_name("Right Wheel");
	OAController::w2.set_memval({ 0,100,100,200,300,350 });
	//cout << w1.Slow.values[1] << endl;
	//cout << w2.Fast.values[0] << endl;
	
	ArSensorReading* sonarSensor[8];
	int sonarRange[8];

	while (true)
	{
		
		// GET SONAR RANGE
		for (int i = 0; i <= 7; i++)
		{
			sonarSensor[i] = robot.getSonarReading(i);
			sonarRange[i] = sonarSensor[i]->getRange();
			//std::cout << "sonarRange " << i << ' ' << sonarRange[i] << '\n';
		}


		if ( sonarRange[2] <= 2000 || sonarRange[3] <= 2000 || sonarRange[4] <= 2000 || sonarRange[5] <=2000 )
		{
			cout << " avoiding obstacles!!" << endl;
			OAController::AvoidObstacles(sonarRange, robot);
		}

		else
		{
			cout << " following the wall" << endl;
			FollowWallController::FollowWall(sonarRange, robot);
		}
	}
	// stop the robot

	robot.lock();
	robot.stop();
	robot.unlock();
   // terminate all threads and exit
	Aria::exit();
}
