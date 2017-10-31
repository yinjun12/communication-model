#ifndef NEURAL_H
#define NEURAL_H

#include <string>

#define Data  165   /*样本数量*/
#define In 42  /*每个样本有多少个输入变量*/
#define Out 1 /*每个样本有多少个输出变量*/
#define Neuron 45 /*神经元数量*/
#define TrainC 20000  //训练次数
#define A  0.2
#define B  0.4
#define a  0.2
#define b  0.3


/* d_in[Data][In] 存储 Data 个样本，每个样本的 In 个输入。
*d_out[Data][Out] 存储 Data 个样本，每个样本的 Out 个输出。
*w[Neuron][In]  表示某个输入对某个神经元的权重，v[Out][Neuron] 来表示某个神经元对某
*个输出的权重；与之对应的保存它们两个修正量的数组 dw[Neuron][In]
*和 dv[Out][Neuron]。数组 o[Neuron] 记录的是神经元通过激活函数对
*外的输出，OutputData[Out]  存储BP神经网络的输出。
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