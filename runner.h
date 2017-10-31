#ifndef RUNNER_H
#define RUNNER_H

#include <stdint.h>
#include <vector>
#include <memory>

#define MAX_X	(1)	/*x�᷶Χ���ֵ*/
#define MAX_Y	(1)	/*y�᷶Χ���ֵ*/

#define CURE_TIME (5) /*����ʱ��*/

#define END_TIME (100) /*����ʱ��*/


class PersonFactory;
class Person;
struct Location;

enum class BPResult {
	SUCCESS=1,
	FAILED=2,
	UNKNOW=3
};

/*1:ͨ��û��ʱ�䣬��1�������п�ͨ�ŵĶ�����Ⱦ
2������ȫ������Ⱦ
3�����ϸ�Ⱦ�Ĺ��ɣ������Ⱦ������Ȼ���б�����ǲ��Ǵ�����ֵ��*/

class BaseService {
public:
	void moveOneSeconds(std::shared_ptr<Person>& person);
	bool isInRange(const Location&location);
	/*����Ϊ����ҿ�,[start,end)*/
	void setInputArrary(double* input, const std::shared_ptr<Person>& Aperson, const std::shared_ptr<Person>& Bperson);
	void writeToFile(double *rate,const std::string& path);

	/*A��B˵�����������б�����*/
	BPResult meetBPNetWork(const std::shared_ptr<Person>& Aperson, const std::shared_ptr<Person>& Bperson);
	virtual void process() = 0;
};

class OnlineService:public BaseService {
private:
	double m_threhsoldValue;
	uint32_t m_time;
	int m_onlineInfectCounts;
	int m_onlineUnInfectCounts;

	std::vector<std::shared_ptr<Person>> m_onlineInfectPersons;
	std::vector<std::shared_ptr<Person>>m_onlineUninfectPersons;
	std::shared_ptr<PersonFactory> m_personFactory;
public:
	OnlineService(int onCnt = 100, int offCnt = 20);
	void allPersonMoveOneSecond();
	void personCommunicate();
	void infectCure();
	double computeInfectRate();
	void process() override;
};

class OnlineAndOfflineService:public BaseService {
private:

	double m_communDistance;
	double m_threhsoldValue;
	uint32_t m_time;
	int m_onlineCounts;
	int m_offlineCounts;


	std::vector<std::shared_ptr<Person>> m_onlineInfectPersons;
	std::vector <std::shared_ptr<Person>> m_offlineInfectPersons;
	std::vector<std::shared_ptr<Person>>m_onlineUninfectPersons;
public:

	OnlineAndOfflineService(double commDis, double threhsold, uint32_t time, int onCnt, int offCnt);

	void setOfflineInfectPerson(const std::vector<std::shared_ptr<Person>>& offlinePerson);

	void setOnlineUninfectPerson(const std::vector<std::shared_ptr<Person>>& onlinePerson);

	int getOfflineCounts();
	
	int getOnlineCounts();

	void setOfflineCounts(int onlineCounts);
	
	void setOnlineCounts(int offlineCounts);

	void personMoveOneSecond();//�������ƶ�һ��

	void personCommunicate();//һ���߳��б��Ƿ���Ը�Ⱦ���ñ�־λ��

	void infectCure();	

	bool meetCommunicationDistance
	(const std::shared_ptr<Person>& lperson, const std::shared_ptr<Person>& rperson);

	double computeInfectRate();


	void process() override;

};
#endif // RUNNER_H