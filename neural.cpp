#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <Windows.h>

#include "neural.h"

void Neural::setDatePath(const std::string& path) {
	m_datePath = path;
}

void Neural::setNeuralPath(const std::string& path) {
	m_neuralPath = path;
}

void Neural::setMinAndMaxPath(const std::string&path) {
	m_minMaxPath = path;
}

void Neural::readData() {
	std::fstream in;
	in.open(m_datePath.c_str());
	if (!in) {
		std::cout<< "open dates failed!" << std::endl;
		exit(0);
	}
	std::string line = "";
	int dataNum = 0;
	while (dataNum < Data && getline(in, line)) {
		replace(line.begin(), line.end(), ',', ' ');
		std::stringstream ss(line);
		int InCnt = 0;
		ss >> d_out[dataNum][0];
		while (InCnt<In&&ss >> d_in[dataNum][InCnt]) {
			InCnt++;
		}
		dataNum++;
	}
	in.close();
}

/*����Ԫ�����������*/
void Neural::writeNeuron()
{
	/*
	FILE *fp1;
	int i, j;
	if ((fp1 = fopen("G:\\neuron.txt", "w")) == NULL)
	{
		printf("can not open the neuron file\n");
		exit(0);
	}
	for (i = 0; i < Neuron; ++i)
		for (j = 0; j < In; ++j) {
			fprintf(fp1, "%lf ", w[i][j]);
		}
	fprintf(fp1, "\n\n\n\n");

	for (i = 0; i < Neuron; ++i)
		for (j = 0; j < Out; ++j) {
			fprintf(fp1, "%lf ", v[j][i]);
		}

	fclose(fp1);*/
	std::ofstream out;
	out.open(m_neuralPath.c_str());
	if (!out) {
		std::cout << "open neural files failed!" << std::endl;
		exit(0);
	}
	for (int i = 0; i < Neuron; ++i)
		for (int j = 0; j < In; ++j) {
			out << w[i][j] << " ";
		}
	out << std::endl;
	out << std::endl;

	for (int i = 0; i < Neuron; ++i)
		for (int j = 0; j < Out; ++j) {
			out << v[j][i] << " ";
		}

	out.close();
}

void Neural::readNeuron() {
	std::fstream in;
	in.open(m_neuralPath);
	if (!in) {
		std::cout << "failed to open neural file!" << std::endl;
		exit(0);
	}
	for (int i = 0; i < Neuron; ++i)
	{
		for (int j = 0; j < In; ++j) {
			in >> w[i][j];
		}
	}
	for (int i = 0; i < Neuron; ++i)
		for (int j = 0; j < Out; ++j) {
			in >> v[j][i];
		}
	in.close();
}

void Neural::writeMinAndMax() {
	std::ofstream out(m_minMaxPath);
	if (!out) {
		std::cout << "failed to open min_max file!" << std::endl;
		exit(0);
	}
	for (int i = 0; i < In; i++) {
		out << Minin[i] << " ";
	}
	out << std::endl;

	for (int i = 0; i < In; i++) {
		out << Maxin[i] << " ";
	}
	out << std::endl;

	for (int i = 0; i < Out; i++) {
		out << Minout[i] << " ";
	}
	out << std::endl;

	for (int i = 0; i < Out; i++) {
		out << Maxout[i] << " ";
	}
	out.close();

}

void Neural::readMinAndMax() {
	std::fstream in(m_minMaxPath);
	if (!in) {
		std::cout << "failed to open min_max file!" << std::endl;
		exit(0);
	}
	for (int i = 0; i < In; i++) {
		in >> Minin[i];
	}

	for (int i = 0; i < In; i++) {
		in >> Maxin[i];
	}

	for (int i = 0; i < Out; i++) {
		in >> Minout[i];
	}

	for (int i = 0; i < Out; i++) {
		in >> Maxout[i];
	}
	in.close();
}

void Neural::initBPNework() {

	int i, j;

	for (i = 0; i < In; i++) {
		Minin[i] = Maxin[i] = d_in[0][i];
		for (j = 0; j < Data; j++)
		{
			Maxin[i] = Maxin[i] > d_in[j][i] ? Maxin[i] : d_in[j][i];
			Minin[i] = Minin[i] < d_in[j][i] ? Minin[i] : d_in[j][i];
		}
	}

	for (i = 0; i < Out; i++) {
		Minout[i] = Maxout[i] = d_out[0][i];
		for (j = 0; j < Data; j++)
		{
			Maxout[i] = Maxout[i] > d_out[j][i] ? Maxout[i] : d_out[j][i];
			Minout[i] = Minout[i] < d_out[j][i] ? Minout[i] : d_out[j][i];
		}
	}

	for (i = 0; i < In; i++)
		for (j = 0; j < Data; j++)
			d_in[j][i] = (d_in[j][i] - Minin[i] + 1) / (Maxin[i] - Minin[i] + 1);

	for (i = 0; i < Out; i++)
		for (j = 0; j < Data; j++)
			d_out[j][i] = (d_out[j][i] - Minout[i] + 1) / (Maxout[i] - Minout[i] + 1);

	for (i = 0; i < Neuron; ++i)
		for (j = 0; j < In; ++j) {
			w[i][j] = rand()*2.0 / RAND_MAX - 1;
			dw[i][j] = 0;
		}

	for (i = 0; i < Neuron; ++i)
		for (j = 0; j < Out; ++j) {
			v[j][i] = rand()*2.0 / RAND_MAX - 1;
			dv[j][i] = 0;
		}
}

void Neural::computO(int var) {

	int i, j;
	double sum, y;
	for (i = 0; i < Neuron; ++i) {
		sum = 0;
		for (j = 0; j < In; ++j)
			sum += w[i][j] * d_in[var][j];
		o[i] = 1 / (1 + exp(-1 * sum));
	}

	for (i = 0; i < Out; ++i) {
		sum = 0;
		for (j = 0; j < Neuron; ++j)
			sum += v[i][j] * o[j];

		OutputData[i] = sum;
	}
}

/*�Ǹ���Ԥ��ĵ� i ������������������Ȩ�ؽ��и��£�e���������*/
void Neural::backUpdate(int var)
{
	int i, j;
	double t;
	for (i = 0; i < Neuron; ++i)
	{
		t = 0;
		for (j = 0; j < Out; ++j) {
			t += (OutputData[j] - d_out[var][j])*v[j][i];

			dv[j][i] = A*dv[j][i] + B*(OutputData[j] - d_out[var][j])*o[i];
			v[j][i] -= dv[j][i];
		}

		for (j = 0; j < In; ++j) {
			dw[i][j] = a*dw[i][j] + b*t*o[i] * (1 - o[i])*d_in[var][j];
			w[i][j] -= dw[i][j];
		}
	}
}

/*ѵ��������*/
void  Neural::trainNetwork() {

	int i, c = 0, j;
	do {
		e = 0;
		for (i = 0; i < Data; ++i) {
			computO(i);
			for (j = 0; j < Out; ++j)
				e += fabs((OutputData[j] - d_out[i][j]) / d_out[i][j]);
			backUpdate(i);
		}
		printf("ѵ��������%d  ���ȣ�%lf\n", c, e / Data);
		c++;
	} while (c<TrainC && e / Data>0.01);

	printf("**********************************\n");
	printf("*����С��0.01,���Ͼ���Ҫ��*\n");
	printf("**********************************\n");
}

double Neural::result(double input[]) {
	int i, j;
	double sum, y;
	for (i = 0; i < In; i++) {
		input[i] = (input[i] - Minin[i] + 1) / (Maxin[i] - Minin[i] + 1);
	}

	for (i = 0; i < Neuron; ++i) {
		sum = 0;
		for (j = 0; j < In; j++) {
			sum += w[i][j] * input[j];
		}
		o[i] = 1 / (1 + exp(-1 * sum));
	}

	sum = 0;
	for (j = 0; j < Neuron; ++j)
		sum += v[0][j] * o[j];

	return sum*(Maxout[0] - Minout[0] + 1) + Minout[0] - 1;
}

void Neural::trainToDates() {
	setNeuralPath("G:\\neuron.txt");
	setMinAndMaxPath("G:\\min_max.txt");
	setDatePath("G:\\data2.csv");
	readData();
	initBPNework();
	trainNetwork();
	writeNeuron();
	writeMinAndMax();
}

void Neural::readFileToDates() {
	setNeuralPath("G:\\neuron.txt");
	setMinAndMaxPath("G:\\min_max.txt");
	readNeuron();
	readMinAndMax();
	std::cout << std::endl;
	std::cout << "*���ڴӱ��ض�ȡ�����ݡ���" << std::endl;
	std::cout << std::endl;
	Sleep(2000);
	std::cout << "****************" << std::endl;
	std::cout << "*��ȡ������ϣ�*" << std::endl;
	std::cout << "****************" << std::endl;
}