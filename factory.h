#ifndef FACTORY_H
#define FACTORY_H

#include <vector>
#include <mutex>



//TODO：可以改为抽象工厂
/*按照要求产生线上和线下人物属性*/

class BaseService;
class Person;
struct Location;


class PersonFactory
{
 private:
	std::vector<std::shared_ptr<Person>> m_vecOnlinePersons;
	std::vector<std::shared_ptr<Person>> m_vecOfflinePersons;
	int m_onlineCounts;
	int m_offlineCounts;

 private:
	 std::shared_ptr<Person> randomGenerateOnePerson(bool online, int stunum);
	 Location randomGenerateLocation();


 public:
	 PersonFactory() :m_offlineCounts(20), m_onlineCounts(100) {
		 m_vecOnlinePersons.clear();
		 m_vecOfflinePersons.clear();
	 }
	 void setOnLineCounts(int);
	 void setOfflineCounts(int);
	 std::vector<std::shared_ptr<Person>> getOnlinePersons();
	 std::vector<std::shared_ptr<Person>> getOfflinePersons();

	std::shared_ptr<BaseService> accquireService();
	 void randomGeneratePerson();
};
#endif