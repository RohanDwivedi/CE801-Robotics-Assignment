#include "Aria.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;



namespace FollowWallController
{
	
	vector <double> out;

struct Member
{
	vector <double> values{ 2 };
};

class InFuzzySet
{

public:
	Member Near, Good, Far;
	string setname;

	void set_name(string name)
	{
		/* set name of the fuzzy set*/
		setname = name;
	}

	void set_memval(vector <double> val)
	{
		/* to get the membership values for near, good ,far*/
		Near.values = { val[0], val[1] };
		Good.values = { val[2], val[3] };
		Far.values = { val[4], val[5] };
	}

}S1, S2;

class OutFuzzySet
{
public:
	Member Slow, Med, Fast;

	void set_name(string name)
	{
		/* set name of the fuzzy set*/
		setname = name;
	}

	void set_memval(vector <double> val)
	{
		/* to get the membership values for near, good ,far*/
		Slow.values = { val[0], val[1] };
		Med.values = { val[2], val[3] };
		Fast.values = { val[4], val[5] };
	}

private:
	string setname;

}w1, w2;

class mem_func
{
private:
	double val;

public:
	double mem_valNear, mem_valMed, mem_valFar;

	double rising_edge(double a, double b, double x)
	{
		val = (x - a) / (b - a);
		return val;
	}

	double falling_edge(double a, double b, double x)
	{
		val = (b - x) / (b - a);
		return val;
	}

	vector <double> calc_mem_val(int key, double sensor_val,
		vector <double> s1_near,
		vector <double> s1_med,
		vector <double> s1_far,
		vector <double> s2_near,
		vector <double> s2_med,
		vector <double> s2_far)
	{
		if (key == 0)
		{
			if (sensor_val >= s1_near[0] && sensor_val <= s1_med[0])
			{
				mem_valNear = 1;
				mem_valMed = 0;
				mem_valFar = 0;
			}
			else if (sensor_val > s1_med[0] && sensor_val < s1_near[1])
			{
				mem_valNear = falling_edge(200, s1_near[1], sensor_val);
				mem_valMed = rising_edge(200, s1_near[1], sensor_val);
				mem_valFar = 0;
			}
			else if (sensor_val == s1_near[1])
			{
				mem_valNear = 0;
				mem_valMed = 1;
				mem_valFar = 0;
			}
			else if (sensor_val > s1_near[1] && sensor_val < s1_med[1])
			{
				mem_valNear = 0;
				mem_valMed = falling_edge(500, s1_med[1], sensor_val);
				mem_valFar = rising_edge(500, s1_med[1], sensor_val);
			}
			else if (sensor_val >= s1_med[1])
			{
				mem_valNear = 0;
				mem_valMed = 0;
				mem_valFar = 1;
			}
			return{ mem_valNear,mem_valMed,mem_valFar };
		}

		if (key == 1)
		{
			if (sensor_val >= s2_near[0] && sensor_val <= s2_med[0])
			{
				mem_valNear = 1;
				mem_valMed = 0;
				mem_valFar = 0;
			}
			else if (sensor_val > s2_med[0] && sensor_val < s2_near[1])
			{
				mem_valNear = falling_edge(200, s2_near[1], sensor_val);
				mem_valMed = rising_edge(200, s2_near[1], sensor_val);
				mem_valFar = 0;
			}
			else if (sensor_val == s2_near[1])
			{
				mem_valNear = 0;
				mem_valMed = 1;
				mem_valFar = 0;
			}
			else if (sensor_val > s2_near[1] && sensor_val < s2_med[1])
			{
				mem_valNear = 0;
				mem_valMed = falling_edge(500, s2_med[1], sensor_val);
				mem_valFar = rising_edge(500, s2_med[1], sensor_val);
			}
			else if (sensor_val >= s2_med[1])
			{
				mem_valNear = 0;
				mem_valMed = 0;
				mem_valFar = 1;
			}
			return{ mem_valNear,mem_valMed,mem_valFar };
		}
	}
}mf;

struct rules
{
	double c1, c2, c3, c4;
}r1, r2, r3, r4, r5, r6, r7, r8, r9;

class defuzzification
{
public:

	void create_rule_table(vector<double> mem_valS1, vector <double> mem_valS2)
	{
		r1.c1 = mem_valS1[0]; // s1 near
		r1.c2 = mem_valS2[0]; // s2 near
		r1.c3 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw Med
		r1.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw Fast

		r2.c1 = mem_valS1[0]; // s1 near
		r2.c2 = mem_valS2[1]; // s2 med
		r2.c3 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // lw slow
		r2.c4 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // rw med

		r3.c1 = mem_valS1[0]; // s1 near
		r3.c2 = mem_valS2[2]; // s2 far
		r3.c3 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // lw slow
		r3.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw Fast

		r4.c1 = mem_valS1[1]; // s1 med
		r4.c2 = mem_valS2[0]; // s2 near
		r4.c3 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // lw Fast
		r4.c4 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw slow

		r5.c1 = mem_valS1[1]; // s1 med
		r5.c2 = mem_valS2[1]; // s2 med
		r5.c3 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw Med
		r5.c4 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // rw Med

		r6.c1 = mem_valS1[1]; // s1 med
		r6.c2 = mem_valS2[2]; // s2 Far
		r6.c3 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw Med
		r6.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw Fast

		r7.c1 = mem_valS1[2]; // s1 far
		r7.c2 = mem_valS2[0]; // s2 near
		r7.c3 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // lw slow
		r7.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw fast

		r8.c1 = mem_valS1[2]; // s1 far
		r8.c2 = mem_valS2[2]; // s2 med
		r8.c3 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw Med
		r8.c4 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw slow

		r9.c1 = mem_valS1[2]; // s1 far
		r9.c2 = mem_valS2[2]; // s2 far
		r9.c3 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // lw Fast
		r9.c4 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // rw med
	}

	vector<double> crisp_out()
	{
		double sum_min = (min(r1.c1, r1.c2) + min(r2.c1, r2.c2) + min(r3.c1, r3.c2)
			+ min(r4.c1, r4.c2) + min(r5.c1, r5.c2) + min(r6.c1, r6.c2) + min(r7.c1, r7.c2)
			+ min(r8.c1, r8.c2) + min(r9.c1, r9.c2));

		double leftWheelSpeed = (min(r1.c1, r1.c2) * r1.c3 + min(r2.c1, r2.c2) * r2.c3 + min(r3.c1, r3.c2) * r3.c3
			+ min(r4.c1, r4.c2) * r4.c3 + min(r5.c1, r5.c2) * r5.c3 + min(r6.c1, r6.c2) * r6.c3 + min(r7.c1, r7.c2) * r7.c3
			+ min(r8.c1, r8.c2) * r8.c3 + min(r9.c1, r9.c2) * r9.c3);

		double rightWheelSpeed = (min(r1.c1, r1.c2) * r1.c4 + min(r2.c1, r2.c2) * r2.c4 + min(r3.c1, r3.c2) * r3.c4
			+ min(r4.c1, r4.c2) * r4.c4 + min(r5.c1, r5.c2) * r5.c4 + min(r6.c1, r6.c2) * r6.c4 + min(r7.c1, r7.c2) * r7.c4
			+ min(r8.c1, r8.c2) * r8.c4 + min(r9.c1, r9.c2) * r9.c4);

		//cout << sum_min << endl;

		return{ leftWheelSpeed / sum_min,rightWheelSpeed / sum_min };

	}
}output;

void FollowWall( int *sonarRange, ArRobot &robot)
{
		
		vector <double> mem_valS1 = mf.calc_mem_val(0, sonarRange[7], S1.Near.values, S1.Good.values, S1.Far.values, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
		vector <double> mem_valS2 = mf.calc_mem_val(1, sonarRange[6], { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, S2.Near.values, S2.Good.values, S2.Far.values); 
		output.create_rule_table(mem_valS1, mem_valS2);
		out = output.crisp_out();
		robot.setVel2(out[0], out[1]);
		cout << sonarRange[7] << " " << sonarRange[6] << endl;
		cout << out[0] << " " << out[1] << endl;

}

}