#include "daq.h"

DAQ::DAQ() {

}

double DAQ::emgProcess(double AI, int i)
{
	double clip1 = 0.5; // Motion artefacts
	double clip2 = 0.02; // Signal noise

	return lowpass2(abs(noiseLimEMG(clipLimEMG(lowpass1(highpass1(AI, i), i), clip1), clip2)),i);
}

double DAQ::lowpass1(double X_in, int emg)
{
	double a1 = -0.043134450881076;
	double a2 = 0.171901801714236;
	double k = 0.282191837708290;

	low_para1.x[0][emg] = X_in;

	low_para1.y[0][emg] = k*(low_para1.x[0][emg] + 2 * low_para1.x[1][emg] + low_para1.x[2][emg]) - a1*low_para1.y[1][emg] - a2*low_para1.y[2][emg];

	for (int i = 2; i>0; i--)
	{
		low_para1.x[i][emg] = low_para1.x[i - 1][emg];
		low_para1.y[i][emg] = low_para1.y[i - 1][emg];
	}
	return low_para1.y[0][emg];
}

double DAQ::lowpass2(double X_in, int emg)
{
	double a1 = -1.991322548359169;
	double a2 = 0.991360035149071;
	double k = 9.371697475252239e-06;

	low_para2.x[0][emg] = X_in;

	low_para2.y[0][emg] = k*(low_para2.x[0][emg] + 2 * low_para2.x[1][emg] + low_para2.x[2][emg]) - a1*low_para2.y[1][emg] - a2*low_para2.y[2][emg];

	for (int i = 2; i>0; i--)
	{
		low_para2.x[i][emg] = low_para2.x[i - 1][emg];
		low_para2.y[i][emg] = low_para2.y[i - 1][emg];
	}
	return low_para2.y[0][emg];
}

double DAQ::highpass1(double X_in, int emg)
{
	double a1 = -1.783787708559230;
	double a2 = 0.804982594421399;
	double k = 0.897192575745157;

	high_para1.x[0][emg] = X_in;

	high_para1.y[0][emg] = k * (high_para1.x[0][emg] - 2 * high_para1.x[1][emg] + high_para1.x[2][emg]) - a1 * high_para1.y[1][emg] - a2 * high_para1.y[2][emg];

	for (int i = 2; i > 0; i--)
	{
		high_para1.x[i][emg] = high_para1.x[i - 1][emg];
		high_para1.y[i][emg] = high_para1.y[i - 1][emg];
	}
	return high_para1.y[0][emg];
}

double DAQ::clipLimEMG(double emg, double lim) {
	if (abs(emg) > lim) {
		emg = 0;
	}
	return emg;
}

double DAQ::noiseLimEMG(double emg, double lim) {
	if (abs(emg) < lim) {
		emg = 0;
	}
	return emg;
}
