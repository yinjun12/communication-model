#include <memory>

#include "factory.h"
#include "tools.h"
#include "person.h"
#include "runner.h"

void PersonFactory::setOfflineCounts(int num) {
	m_offlineCounts = num;
}

void PersonFactory::setOnLineCounts(int num) {
	m_onlineCounts = num;
}

void PersonFactory::randomGeneratePerson() {
	/*生成线上人物*/
	for (int i = 0; i < m_onlineCounts; i++) {
		m_vecOnlinePersons.push_back(randomGenerateOnePerson(true, i));
	}

	/*生成线下人物*/
	for (int i = 0; i < m_offlineCounts; i++) {
		m_vecOfflinePersons.push_back(randomGenerateOnePerson(false, i));
	}
}

std::shared_ptr<Person> PersonFactory::randomGenerateOnePerson(bool online,int i) {
	std::shared_ptr<Person>record = std::make_shared<Person>();
	if (online) {
		record->m_stuNum = std::string("online-") + std::to_string(i + 1);
		record->m_online = true;
		record->m_infective = false;
	}
	else {
		record->m_stuNum = std::string("offline-") + std::to_string(i + 1);
		record->m_online = false;
		record->m_infective = true;
	}
	
	int speedIndex = generateIntRandom(0, 3);
	record->m_speed = Speed[speedIndex];

	record->m_angel = randomAngle();

	record->m_location = randomGenerateLocation();
	record->m_cureTime = 0;

	/*神经网络输入*/
	record->m_gen = static_cast<Gender>(generateIntRandom(1, 2));
	record->m_gra = static_cast<Grade>(generateIntRandom(1, 7));
	record->m_chara = static_cast<Character>(generateIntRandom(1, 5));
	record->m_appe = static_cast<Apperance>(generateIntRandom(1, 2));
	record->m_otherGen = static_cast<OtherGender>(generateIntRandom(1, 3));
	record->m_otherApp = static_cast<OtherApper>(generateIntRandom(1, 3));

#if 0
	record->m_mood = static_cast<Mood>(generateIntRandom(1, 7));

	record->m_weather = static_cast<Weather>(generateIntRandom(1, 8));

	record->m_time = static_cast<Time>(generateIntRandom(1, 6));

	record->m_pc = static_cast<PersonCount>(generateIntRandom(1, 5));

	record->m_acStatus = static_cast<ActivityStatus>(generateIntRandom(1, 4));

	record->m_tran = static_cast<Transportaion>(generateIntRandom(1, 3));

	record->m_attitude = static_cast<Attitude>(generateIntRandom(1, 4));
#endif

	/*心情*/
	record->m_mood.m_veryGoodMood = static_cast<bool>(generateIntRandom(0, 1));
	record->m_mood.m_goodlMood = static_cast<bool>(generateIntRandom(0, 1));
	record->m_mood.m_ordinaryMood = static_cast<bool>(generateIntRandom(0, 1));
	record->m_mood.m_badMood = static_cast<bool>(generateIntRandom(0, 1));
	record->m_mood.m_veryBadMood = static_cast<bool>(generateIntRandom(0, 1));
	record->m_mood.m_terribleMood= static_cast<bool>(generateIntRandom(0, 1));
	record->m_mood.m_immune = static_cast<bool>(generateIntRandom(0, 1));

	/*天气*/
	record->m_weather.m_cold = static_cast<bool>(generateIntRandom(0, 1));
	record->m_weather.m_hot = static_cast<bool>(generateIntRandom(0, 1));
	record->m_weather.m_bigRainy = static_cast<bool>(generateIntRandom(0, 1));
	record->m_weather.m_smallRainy = static_cast<bool>(generateIntRandom(0, 1));
	record->m_weather.m_snowy = static_cast<bool>(generateIntRandom(0, 1));
	record->m_weather.m_windy = static_cast<bool>(generateIntRandom(0, 1));
	record->m_weather.m_goodWeather = static_cast<bool>(generateIntRandom(0, 1));
	record->m_weather.m_immune = static_cast<bool>(generateIntRandom(0, 1));

	/*时间*/
	record->m_time.m_morning = static_cast<bool>(generateIntRandom(0, 1));
	record->m_time.m_forenoon = static_cast<bool>(generateIntRandom(0, 1));
	record->m_time.m_noon = static_cast<bool>(generateIntRandom(0, 1));
	record->m_time.m_afternoon = static_cast<bool>(generateIntRandom(0, 1));
	record->m_time.m_night = static_cast<bool>(generateIntRandom(0, 1));

	/*人流密度*///TODO:产生的跟要求不一致
	record->m_pc.m_mostPerson = static_cast<bool>(generateIntRandom(0, 1));
	record->m_pc.m_manyPerson = static_cast<bool>(generateIntRandom(0, 1));
	record->m_pc.m_fewPerson = static_cast<bool>(generateIntRandom(0, 1));
	record->m_pc.m_onePerson = static_cast<bool>(generateIntRandom(0, 1));
	record->m_pc.m_immune = static_cast<bool>(generateIntRandom(0, 1));

	/*运动状态*/
	record->m_acStatus.m_static = static_cast<bool>(generateIntRandom(0, 1));
	record->m_acStatus.m_walk = static_cast<bool>(generateIntRandom(0, 1));
	record->m_acStatus.m_rapidWalk = static_cast<bool>(generateIntRandom(0, 1));
	record->m_acStatus.m_run = static_cast<bool>(generateIntRandom(0, 1));

	/*交通工具*/
	record->m_tran.m_bike = static_cast<bool>(generateIntRandom(0, 1));
	record->m_tran.m_electrombile = static_cast<bool>(generateIntRandom(0, 1));
	record->m_tran.m_every = static_cast<bool>(generateIntRandom(0, 1));

	/*态度*/
	record->m_attitude.m_polite = static_cast<bool>(generateIntRandom(0, 1));
	record->m_attitude.m_common = static_cast<bool>(generateIntRandom(0, 1));
	record->m_attitude.m_impolite = static_cast<bool>(generateIntRandom(0, 1));
	record->m_attitude.m_immune = static_cast<bool>(generateIntRandom(0, 1));
	return record;
}


Location PersonFactory::randomGenerateLocation() {
	Location lo;
	lo.m_x = generateDoubleRandom(0, 1);
	lo.m_y = generateDoubleRandom(0, 1);
	return lo;
}

std::vector<std::shared_ptr<Person>> PersonFactory::getOnlinePersons() {
	return m_vecOnlinePersons;
}

std::vector<std::shared_ptr<Person>> PersonFactory::getOfflinePersons() {
	return m_vecOfflinePersons;
}

std::shared_ptr<BaseService> PersonFactory::accquireService() {
	std::shared_ptr<OnlineAndOfflineService> service = std::make_shared<OnlineAndOfflineService>(0.1, 0.5, 0, 100, 20);

	setOnLineCounts(service->getOnlineCounts());
	setOfflineCounts(service->getOfflineCounts());

	randomGeneratePerson();

	service->setOfflineInfectPerson(getOfflinePersons());
	service->setOnlineUninfectPerson(getOnlinePersons());

	return service;
}