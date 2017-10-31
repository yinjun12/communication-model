#include "bridge.h"
#include "factory.h"

int main() {
#ifdef DEBUG_NEURAL
	std::shared_ptr<Neural> pe = Singelon<Neural>::instance();
	pe->setNeuralPath("G:\\neuron.txt");
	pe->setMinAndMaxPath("G:\\min_max.txt");
	pe->setDatePath("G:\\data2.csv");

	pe->readData();
	pe->initBPNework();
	pe->trainNetwork();
	pe->writeNeuron();
	pe->writeMinAndMax();

	double input1[] = { 1,	5,	2,	3,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,
		0,	0,	0,	1,	0,	1,	1,	0,	0,	0,	0,	1,	1,	1,	0,	0,	1,	1,	0,
		0,	0,	0,	0,	1,	0,	0,	0,
	};
	printf("%lf \n", pe->result(input1));

	double input2[] = { 2,	6,	4,	3,	1,	0,	0,	0,	0,	1,	1,	0,	1,	0,	0,	0,
		0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	1,	0,	0,	0,	1,	1,	0,
		0,	0,	0,	0,	1,	0,
	};

	double input3[] = { 2,	5,	1,	3,	3,	0,	0,	0,	0,	1,	1,	0,	1,	0,	1,	0,
		1,	0,	0,	0,	1,	0,	1,	0,	0,	0,	1,	0,	0,	1,	0,	0,	0,	1,	0,	0,
		0,	0,	0,	0,	1,	0,
	};
	printf("%lf \n", pe->result(input2));
	printf("%lf \n", pe->result(input3));
#endif
#ifdef DEBUG_FACTORY
	PersonFactory pf;
	for(int i=0;i<20;i++)
	std::cout << pf.generateIntRandom(0,1) << std::endl;
#endif
	/*PersonFactory pf;
	pf.randomGeneratePerson();*/
	std::shared_ptr<Bridge>pOOb(new OnlineAndOfflineBridge());
	std::shared_ptr<PersonFactory>pBs(new PersonFactory());
	pOOb->setFactory(pBs);

	/*std::shared_ptr<Bridge>pOb(new OnlineBridge());
	std::shared_ptr<BaseService>pOs(new OnlineService());
	pOb->setService(pOs);*/

	Runner r;
	r.addBridge(pOOb);
	/*r.addBridge(pOb);*/
	r.run();
	return 0;
}