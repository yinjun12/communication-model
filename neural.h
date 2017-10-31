#ifndef NEURAL_H
#define NEURAL_H

#include <string>

#define Data  165   /*��������*/
#define In 42  /*ÿ�������ж��ٸ��������*/
#define Out 1 /*ÿ�������ж��ٸ��������*/
#define Neuron 45 /*��Ԫ����*/
#define TrainC 20000  //ѵ������
#define A  0.2
#define B  0.4
#define a  0.2
#define b  0.3


/* d_in[Data][In] �洢 Data ��������ÿ�������� In �����롣
*d_out[Data][Out] �洢 Data ��������ÿ�������� Out �������
*w[Neuron][In]  ��ʾĳ�������ĳ����Ԫ��Ȩ�أ�v[Out][Neuron] ����ʾĳ����Ԫ��ĳ
*�������Ȩ�أ���֮��Ӧ�ı����������������������� dw[Neuron][In]
*�� dv[Out][Neuron]������ o[Neuron] ��¼������Ԫͨ���������
*��������OutputData[Out]  �洢BP������������
*/
class Neural {
private:
	double d_in[Data][In], d_out[Data][Out];
	double w[Neuron][In], o[Neuron], v[Out][Neuron];
	double Maxin[In], Minin[In], Maxout[Out], Minout[Out];
	double OutputData[Out];
	double dv[Out][Neuron], dw[Neuron][In];
	double e;

	std::string m_datePath;/*date path*/
	std::string m_neuralPath;/*file to save neural*/
	std::string m_minMaxPath;/*file to save min and max*/

private:
	void readData();/*read dates*/

	void writeNeuron();/*write neuron to file*/
	void readNeuron();

	void writeMinAndMax();
	void readMinAndMax();

	void initBPNework();
	void computO(int var);
	void backUpdate(int var);
	void  trainNetwork();

public:
	void setDatePath(const std::string&);
	void setNeuralPath(const std::string&);
	void setMinAndMaxPath(const std::string&);

	void trainToDates();

	void readFileToDates();

	double result(double input[]);

};
#endif