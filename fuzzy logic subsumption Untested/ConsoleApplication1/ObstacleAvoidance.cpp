#include "Aria.h"
#include <vector>
#include <iostream>
#include <algorithm>

namespace OAController
{
	using namespace std;
	vector <double> mem_valS1;
	vector <double> mem_valS2;
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

	}Front, Left, Right;

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
			vector <double> s2_far,
			vector <double> s3_near,
			vector <double> s3_med,
			vector <double> s3_far)
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
					mem_valNear = falling_edge(s1_med[0], s1_near[1], sensor_val);
					mem_valMed = rising_edge(s1_med[0], s1_near[1], sensor_val);
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
					mem_valMed = falling_edge(s1_near[1], s1_med[1], sensor_val);
					mem_valFar = rising_edge(s1_near[1], s1_med[1], sensor_val);
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
					mem_valNear = falling_edge(s2_med[0], s2_near[1], sensor_val);
					mem_valMed = rising_edge(s2_med[0], s2_near[1], sensor_val);
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
					mem_valMed = falling_edge(s2_near[1], s2_med[1], sensor_val);
					mem_valFar = rising_edge(s2_near[1], s2_med[1], sensor_val);
				}
				else if (sensor_val >= s2_med[1])
				{
					mem_valNear = 0;
					mem_valMed = 0;
					mem_valFar = 1;
				}
				return{ mem_valNear,mem_valMed,mem_valFar };
			}

			if (key == 2)
			{
				if (sensor_val >= s3_near[0] && sensor_val <= s3_med[0])
				{
					mem_valNear = 1;
					mem_valMed = 0;
					mem_valFar = 0;
				}
				else if (sensor_val > s3_med[0] && sensor_val < s3_near[1])
				{
					mem_valNear = falling_edge(s3_med[0], s3_near[1], sensor_val);
					mem_valMed = rising_edge(s3_med[0], s3_near[1], sensor_val);
					mem_valFar = 0;
				}
				else if (sensor_val == s3_near[1])
				{
					mem_valNear = 0;
					mem_valMed = 1;
					mem_valFar = 0;
				}
				else if (sensor_val > s3_near[1] && sensor_val < s3_med[1])
				{
					mem_valNear = 0;
					mem_valMed = falling_edge(s3_near[1], s3_med[1], sensor_val);
					mem_valFar = rising_edge(s3_near[1], s3_med[1], sensor_val);
				}
				else if (sensor_val >= s3_med[1])
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
		double c1, c2, c3, c4, c5;
	}r1, r2, r3, r4, r5, r6, r7, r8, r9, r10, r11, r12, r13, r14, r15, r16, r17, r18, r19,
		r20, r21, r22, r23, r24, r25, r26, r27;

	class defuzzification
	{
	public:

		void create_rule_table(vector<double> mem_valFront, vector <double> mem_valLeft, vector <double> mem_valRight)
		{
			r1.c1 = mem_valFront[0]; // front close
			r1.c2 = mem_valLeft[0];  // left close
			r1.c3 = mem_valRight[0]; // right close
			r1.c4 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // lw sslow
			r1.c5 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw Fast

			r2.c1 = mem_valFront[0]; // front close
			r2.c2 = mem_valLeft[0];  // left close
			r2.c3 = mem_valRight[1]; // right med
			r2.c4 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw med
			r2.c5 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw slow

			r3.c1 = mem_valFront[0]; // front close
			r3.c2 = mem_valLeft[0];  // left close
			r3.c3 = mem_valRight[2]; // right far
			r3.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // lw fast
			r3.c5 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw slow

			r4.c1 = mem_valFront[0]; // front close
			r4.c2 = mem_valLeft[1];  // left med
			r4.c3 = mem_valRight[2]; // right far
			r4.c4 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw med
			r4.c5 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw slow

			r5.c1 = mem_valFront[0]; // front close
			r5.c2 = mem_valLeft[2];  // left Far
			r5.c3 = mem_valRight[1]; // right med
			r5.c4 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // lw slow
			r5.c5 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw Fast

			r6.c1 = mem_valFront[0]; // front close
			r6.c2 = mem_valLeft[2];  // left far
			r6.c3 = mem_valRight[2]; // right far
			r6.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // lw fast
			r6.c5 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw slow

			r7.c1 = mem_valFront[0]; // front close
			r7.c2 = mem_valLeft[0];  // left med
			r7.c3 = mem_valRight[0]; // right med
			r7.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // lw Fast
			r7.c5 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw slow

			r8.c1 = mem_valFront[0]; // front close
			r8.c2 = mem_valLeft[1];  // left  med
			r8.c3 = mem_valRight[0]; // right close
			r8.c4 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // lw slow
			r8.c5 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw Fast

			r9.c1 = mem_valFront[0]; // front close
			r9.c2 = mem_valLeft[2];  // left far
			r9.c3 = mem_valRight[0]; // right close
			r9.c4 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // lw slow
			r9.c5 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // rw med

			r10.c1 = mem_valFront[1]; // front med
			r10.c2 = mem_valLeft[1];  // left med
			r10.c3 = mem_valRight[1]; // right med
			r10.c4 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // lw slow
			r10.c5 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw slow

			r11.c1 = mem_valFront[1]; // front med
			r11.c2 = mem_valLeft[1];  // left med
			r11.c3 = mem_valRight[0]; // right close
			r11.c4 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // lw slow
			r11.c5 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // rw med

			r12.c1 = mem_valFront[1]; // front med
			r12.c2 = mem_valLeft[1];  // left med
			r12.c3 = mem_valRight[2]; // right far
			r12.c4 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw med
			r12.c5 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw fast

			r13.c1 = mem_valFront[1]; // front med
			r13.c2 = mem_valLeft[2];  // left far
			r13.c3 = mem_valRight[2]; // right far
			r13.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // lw fast
			r13.c5 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // rw med

			r14.c1 = mem_valFront[1]; // front med
			r14.c2 = mem_valLeft[0];  // left close
			r14.c3 = mem_valRight[0]; // right close
			r14.c4 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // lw slow
			r14.c5 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw slow

			r15.c1 = mem_valFront[1]; // front med
			r15.c2 = mem_valLeft[2];  // left far
			r15.c3 = mem_valRight[0]; // right close
			r15.c4 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw med
			r15.c5 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw fast

			r16.c1 = mem_valFront[1]; // front med
			r16.c2 = mem_valLeft[0];  // left close
			r16.c3 = mem_valRight[2]; // right far
			r16.c4 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw med
			r16.c5 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw slow

			r17.c1 = mem_valFront[1]; // front med
			r17.c2 = mem_valLeft[0];  // left  close
			r17.c3 = mem_valRight[1]; // right med
			r17.c4 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw med
			r17.c5 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw slow

			r18.c1 = mem_valFront[1]; // front med
			r18.c2 = mem_valLeft[2];  // left far
			r18.c3 = mem_valRight[1]; // right med
			r18.c4 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // lw slow
			r18.c5 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // rw med

			r19.c1 = mem_valFront[2]; // front far
			r19.c2 = mem_valLeft[2];  // left far
			r19.c3 = mem_valRight[2]; // right far
			r19.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // lw fast
			r19.c5 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw Fast

			r20.c1 = mem_valFront[2]; // front far
			r20.c2 = mem_valLeft[2];  // left far
			r20.c3 = mem_valRight[0]; // right close
			r20.c4 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw med
			r20.c5 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw fast

			r21.c1 = mem_valFront[2]; // front far
			r21.c2 = mem_valLeft[2];  // left far
			r21.c3 = mem_valRight[1]; // right med
			r21.c4 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw med
			r21.c5 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw fast

			r22.c1 = mem_valFront[2]; // front far
			r22.c2 = mem_valLeft[1];  // left med
			r22.c3 = mem_valRight[1]; // right med
			r22.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // lw fast
			r22.c5 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // rw fast

			r23.c1 = mem_valFront[2]; // front far
			r23.c2 = mem_valLeft[0];  // left close
			r23.c3 = mem_valRight[0]; // right close
			r23.c4 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // lw med
			r23.c5 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // rw med

			r24.c1 = mem_valFront[2]; // front far
			r24.c2 = mem_valLeft[1];  // left med
			r24.c3 = mem_valRight[0]; // right close
			r24.c4 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // lw slow
			r24.c5 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // rw med

			r25.c1 = mem_valFront[2]; // front far
			r25.c2 = mem_valLeft[0];  // left close
			r25.c3 = mem_valRight[1]; // right med
			r25.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // lw Fast
			r25.c5 = ((w1.Med.values[0] + w1.Med.values[1]) / 2); // rw med

			r26.c1 = mem_valFront[2]; // front far
			r26.c2 = mem_valLeft[1];  // left  med
			r26.c3 = mem_valRight[2]; // right far
			r26.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // lw fast
			r26.c5 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw med --> changed to slow

			r27.c1 = mem_valFront[2]; // front far
			r27.c2 = mem_valLeft[0];  // left close
			r27.c3 = mem_valRight[2]; // right far
			r27.c4 = ((w1.Fast.values[0] + w1.Fast.values[1]) / 2); // lw fast
			r27.c5 = ((w1.Slow.values[0] + w1.Slow.values[1]) / 2); // rw med --> changed to slow
		}

		vector<double> crisp_out()
		{

			double sum_min = min(min(r1.c1, r1.c2), r1.c3) + min(min(r2.c1, r2.c2), r2.c3) + min(min(r3.c1, r3.c2), r3.c3) +
				min(min(r4.c1, r4.c2), r4.c3) + min(min(r5.c1, r5.c2), r5.c3) + min(min(r6.c1, r6.c2), r6.c3) +
				min(min(r7.c1, r7.c2), r7.c3) + min(min(r8.c1, r8.c2), r8.c3) + min(min(r9.c1, r9.c2), r9.c3) +
				min(min(r10.c1, r10.c2), r10.c3) + min(min(r11.c1, r11.c2), r11.c3) + min(min(r12.c1, r12.c2), r12.c3) +
				min(min(r13.c1, r13.c2), r13.c3) + min(min(r14.c1, r14.c2), r14.c3) + min(min(r15.c1, r15.c2), r15.c3) +
				min(min(r16.c1, r16.c2), r16.c3) + min(min(r17.c1, r17.c2), r17.c3) + min(min(r18.c1, r18.c2), r18.c3) +
				min(min(r19.c1, r19.c2), r19.c3) + min(min(r20.c1, r20.c2), r20.c3) + min(min(r21.c1, r21.c2), r21.c3) +
				min(min(r22.c1, r22.c2), r22.c3) + min(min(r23.c1, r23.c2), r23.c3) + min(min(r24.c1, r24.c2), r24.c3) +
				min(min(r25.c1, r25.c2), r25.c3) + min(min(r26.c1, r26.c2), r26.c3) + min(min(r27.c1, r27.c2), r27.c3);

			double leftWheelSpeed = min(min(r1.c1, r1.c2), r1.c3)*r1.c4 + min(min(r2.c1, r2.c2), r2.c3)*r2.c4 + min(min(r3.c1, r3.c2), r3.c3)*r3.c4 +
				min(min(r4.c1, r4.c2), r4.c3)*r4.c4 + min(min(r5.c1, r5.c2), r5.c3)*r5.c4 + min(min(r6.c1, r6.c2), r6.c3)*r6.c4 +
				min(min(r7.c1, r7.c2), r7.c3)*r7.c4 + min(min(r8.c1, r8.c2), r8.c3)*r8.c4 + min(min(r9.c1, r9.c2), r9.c3)*r9.c4 +
				min(min(r10.c1, r10.c2), r10.c3)*r10.c4 + min(min(r11.c1, r11.c2), r11.c3)*r11.c4 + min(min(r12.c1, r12.c2), r12.c3)*r12.c4 +
				min(min(r13.c1, r13.c2), r13.c3)*r13.c4 + min(min(r14.c1, r14.c2), r14.c3)*r14.c4 + min(min(r15.c1, r15.c2), r15.c3)*r15.c4 +
				min(min(r16.c1, r16.c2), r16.c3)*r16.c4 + min(min(r17.c1, r17.c2), r17.c3)*r17.c4 + min(min(r18.c1, r18.c2), r18.c3)*r18.c4 +
				min(min(r19.c1, r19.c2), r19.c3)*r19.c4 + min(min(r20.c1, r20.c2), r20.c3)*r20.c4 + min(min(r21.c1, r21.c2), r21.c3)*r21.c4 +
				min(min(r22.c1, r22.c2), r22.c3)*r22.c4 + min(min(r23.c1, r23.c2), r23.c3)*r23.c4 + min(min(r24.c1, r24.c2), r24.c3)*r24.c4 +
				min(min(r25.c1, r25.c2), r25.c3)*r25.c4 + min(min(r26.c1, r26.c2), r26.c3)*r26.c4 + min(min(r27.c1, r27.c2), r27.c3)*r27.c4;


			double rightWheelSpeed = min(min(r1.c1, r1.c2), r1.c3)*r1.c5 + min(min(r2.c1, r2.c2), r2.c3)*r2.c5 + min(min(r3.c1, r3.c2), r3.c3)*r3.c5 +
				min(min(r4.c1, r4.c2), r4.c3)*r4.c5 + min(min(r5.c1, r5.c2), r5.c3)*r5.c5 + min(min(r6.c1, r6.c2), r6.c3)*r6.c5 +
				min(min(r7.c1, r7.c2), r7.c3)*r7.c5 + min(min(r8.c1, r8.c2), r8.c3)*r8.c5 + min(min(r9.c1, r9.c2), r9.c3)*r9.c5 +
				min(min(r10.c1, r10.c2), r10.c3)*r10.c5 + min(min(r11.c1, r11.c2), r11.c3)*r11.c5 + min(min(r12.c1, r12.c2), r12.c3)*r12.c5 +
				min(min(r13.c1, r13.c2), r13.c3)*r13.c5 + min(min(r14.c1, r14.c2), r14.c3)*r14.c5 + min(min(r15.c1, r15.c2), r15.c3)*r15.c5 +
				min(min(r16.c1, r16.c2), r16.c3)*r16.c5 + min(min(r17.c1, r17.c2), r17.c3)*r17.c5 + min(min(r18.c1, r18.c2), r18.c3)*r18.c5 +
				min(min(r19.c1, r19.c2), r19.c3)*r19.c5 + min(min(r20.c1, r20.c2), r20.c3)*r20.c5 + min(min(r21.c1, r21.c2), r21.c3)*r21.c5 +
				min(min(r22.c1, r22.c2), r22.c3)*r22.c5 + min(min(r23.c1, r23.c2), r23.c3)*r23.c5 + min(min(r24.c1, r24.c2), r24.c3)*r24.c5 +
				min(min(r25.c1, r25.c2), r25.c3)*r25.c5 + min(min(r26.c1, r26.c2), r26.c3)*r26.c5 + min(min(r27.c1, r27.c2), r27.c3)*r27.c5;

			//cout << sum_min << endl;

			return{ leftWheelSpeed / sum_min,rightWheelSpeed / sum_min };

		}
	}output;

	void AvoidObstacles(int *sonarRange, ArRobot &robot)
	{
		vector <double> mem_valFront = mf.calc_mem_val(0, (sonarRange[3] + sonarRange[4]) / 2, Front.Near.values, Front.Good.values, Front.Far.values, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
		vector <double> mem_valLeft = mf.calc_mem_val(1, sonarRange[2], { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, Left.Near.values, Left.Good.values, Left.Far.values, { 0,0,0 }, { 0,0,0 }, { 0,0,0 });
		vector <double> mem_valRight = mf.calc_mem_val(2, sonarRange[5], { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }, Right.Near.values, Right.Good.values, Right.Far.values);
		output.create_rule_table(mem_valFront, mem_valLeft, mem_valRight);
		out = output.crisp_out();
		robot.setVel2(out[0], out[1]);
		cout << (sonarRange[4] + sonarRange[3]) / 2 << " " << sonarRange[5] << " " << sonarRange[2] << endl;
		cout << out[0] << " " << out[1] << endl;
	}
}