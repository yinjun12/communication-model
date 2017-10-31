#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>

#include "runner.h"
#include "neural.h"
#include "Singelon.h"
#include "tools.h"
#include "person.h"
#include "factory.h"

OnlineService::OnlineService(int unCnt, int inCnt ):m_threhsoldValue(0.5),m_time(0),
m_onlineInfectCounts(inCnt),m_onlineUnInfectCounts(unCnt) {
	m_personFactory = std::make_shared<PersonFactory>();
	m_personFactory->setOnLineCounts(m_onlineUnInfectCounts);
	m_personFactory->setOfflineCounts(m_onlineInfectCounts);
	m_personFactory->randomGeneratePerson();
}

void OnlineService::allPersonMoveOneSecond() {
	for (auto record : m_onlineInfectPersons) {
		moveOneSeconds(record);
	}

	for (auto record : m_onlineUninfectPersons) {
		moveOneSeconds(record);
	}
}

void OnlineService::personCommunicate() {

	/*线上感染线上*/
	if (!m_onlineUninfectPersons.empty()) {
		int infectCnts = m_onlineInfectPersons.size();
		for (int i = 0; i < infectCnts; i++) {
			int randIndex = generateIntRandom(0, m_onlineUninfectPersons.size() - 1);
			//std::cout<<"size: "<<m_onlineUninfectPersons.size() << "   randIndex: " << randIndex << std::endl;
			double randRate = generateDoubleRandom(0, 1);
			if (randRate > m_threhsoldValue) {
				m_onlineUninfectPersons.at(randIndex)->m_infective = true;
			}
		}
	}

	/*将感染的对象从未感染队列移到感染队列中*/
	for (auto it = m_onlineUninfectPersons.begin(); it != m_onlineUninfectPersons.end();) {
		if (((*it)->m_infective)) {
			m_onlineInfectPersons.push_back(*it);
			it = m_onlineUninfectPersons.erase(it);
		}
		else {
			it++;
		}
	}
}

void OnlineService::infectCure() {
	for (auto record = m_onlineInfectPersons.begin(); record != m_onlineInfectPersons.end();) {
		std::string stuNum = (*record)->m_stuNum;
		if ((stuNum.find("offline") == std::string::npos)&&(*record)->m_cureTime == CURE_TIME) {
			(*record)->m_cureTime = 0;
			(*record)->m_infective = false;
			m_onlineUninfectPersons.push_back((*record));
			record = m_onlineInfectPersons.erase(record);
			continue;
		}
		++(*record)->m_cureTime;
		record++;
	}
}

double OnlineService::computeInfectRate() {
	int infectiveCnts =  m_onlineInfectPersons.size();
	int allCnts = m_onlineUnInfectCounts + m_onlineUnInfectCounts;
	double rate = static_cast<double>(infectiveCnts) / allCnts;
	return  rate;
}

void OnlineService::process() {
	double rate[END_TIME];
	std::cout << "start only online infect..." << std::endl;
	while (m_time < END_TIME) {
		personCommunicate();
		//std::cout << "========time: " << m_time << "==============" << std::endl;
		//std::cout <<"before cure:"<< m_onlineInfectPersons.size() << "  " << m_onlineUninfectPersons.size() << std::endl;
		infectCure();
		//std::cout << "after cure:" << m_onlineInfectPersons.size() << "  " << m_onlineUninfectPersons.size() << std::endl;
		rate[m_time] = computeInfectRate();

		allPersonMoveOneSecond();
		m_time++;
	}
	std::cout << "end infect." << std::endl;

	writeToFile(rate, "G:\\online_rate.csv");

}

OnlineAndOfflineService::OnlineAndOfflineService(double commDis,double threhsold,uint32_t time,int onCnt,int offCnt)
	:m_communDistance(commDis), m_threhsoldValue(threhsold), m_time(time),m_onlineCounts(onCnt), m_offlineCounts(offCnt) {

}

int OnlineAndOfflineService::getOfflineCounts() {
	return m_offlineCounts;
}

int OnlineAndOfflineService::getOnlineCounts() {
	return m_onlineCounts;
}

void OnlineAndOfflineService::setOfflineCounts(int offlineCounts) {
	m_offlineCounts = offlineCounts;
}

void OnlineAndOfflineService::setOnlineCounts(int onlineCounts){
	m_onlineCounts = onlineCounts;
}

void OnlineAndOfflineService::setOfflineInfectPerson(const std::vector<std::shared_ptr<Person>>& offlinePerson) {
	m_offlineInfectPersons = offlinePerson;
}

void OnlineAndOfflineService::setOnlineUninfectPerson(const std::vector<std::shared_ptr<Person>>& onlinePerson) {
	m_onlineUninfectPersons = onlinePerson;
}

void OnlineAndOfflineService::personMoveOneSecond() {
	for (auto online : m_onlineInfectPersons) {
		moveOneSeconds(online);
	}

	for (auto offline : m_offlineInfectPersons) {
		moveOneSeconds(offline);
	}

	for (auto offline : m_onlineUninfectPersons) {
		moveOneSeconds(offline);
	}

}

//TODO：速度不确定
/*先计算移动一秒的距离，判断是否在范围内，若在范围内则移动，不在范围内则随机生成角度，继续移动，直到成功为止*/
void BaseService::moveOneSeconds( std::shared_ptr<Person>& person) {
	while (true)
	{
		Location lo = person->m_location;
		double moveDistance = person->m_speed * 1;
		lo.m_x = lo.m_x + moveDistance*cos(person->m_angel);
		lo.m_y = lo.m_y + moveDistance*sin(person->m_angel);
		if (isInRange(lo)) {
			person->m_location = lo;
			break;
		}
		person->m_angel = randomAngle();
	}
}

bool BaseService::isInRange(const Location&location) {
	if (location.m_x <= MAX_X&&location.m_y <= MAX_Y) {
		return true;
	}
	return false;
}

bool OnlineAndOfflineService::meetCommunicationDistance(const std::shared_ptr<Person>& lperson, const std::shared_ptr<Person>& rperson) {
	double xDis = lperson->m_location.m_x - rperson->m_location.m_x;
	xDis *= xDis;
	double yDis = lperson->m_location.m_y - rperson->m_location.m_y;
	yDis *= yDis;
	double tmpDouble = sqrt(xDis+yDis);
	if (tmpDouble <= m_communDistance)
		return true;
	return false;
}

/*TODO*/
/*当某个对象被感染时，只置感染标记不删除，可以让同一个人可以被感染多次*/
void OnlineAndOfflineService::personCommunicate() {

	/*线上感染线下*/
	for (auto& offlineInfect:m_offlineInfectPersons) {
		for (auto& onlineUninfect : m_onlineUninfectPersons) {
			if (meetCommunicationDistance(offlineInfect, onlineUninfect) &&
				meetBPNetWork(offlineInfect, onlineUninfect) == BPResult::SUCCESS) {
					onlineUninfect->m_infective = true;
				//tempInfect.push_back(*onlineUninfect);
				// onlineUninfect = m_onlineUninfectPersons.erase(onlineUninfect);
			}
		}
	}

	/*线上感染线上*/
	if (!m_onlineUninfectPersons.empty()) {
		int infectCnts = m_onlineInfectPersons.size();
		for (int i = 0; i < infectCnts; i++) {
			int randIndex = generateIntRandom(0, m_onlineUninfectPersons.size() - 1);
			//std::cout<<"size: "<<m_onlineUninfectPersons.size() << "   randIndex: " << randIndex << std::endl;
			double randRate = generateDoubleRandom(0, 1);
			if (randRate > m_threhsoldValue) {
				m_onlineUninfectPersons.at(randIndex)->m_infective = true;
			}
		}
	}

	/*将感染的对象从未感染队列移到感染队列中*/
	for (auto it = m_onlineUninfectPersons.begin(); it != m_onlineUninfectPersons.end();) {
		if (((*it)->m_infective)) {
			m_onlineInfectPersons.push_back(*it);
			it = m_onlineUninfectPersons.erase(it);
		}
		else {
			it++;
		}
	}
}

void OnlineAndOfflineService::infectCure() {
	for (auto record = m_onlineInfectPersons.begin(); record != m_onlineInfectPersons.end();) {
		if ((*record)->m_cureTime == CURE_TIME) {
			(*record)->m_cureTime = 0;
			(*record)->m_infective = false;
			m_onlineUninfectPersons.push_back((*record));
			record = m_onlineInfectPersons.erase(record);
			continue;
		}
		++(*record)->m_cureTime;
		record++;
	}
}

/*A找B通信的神经网络判别*/
BPResult BaseService::meetBPNetWork(const std::shared_ptr<Person>& Aperson, const std::shared_ptr<Person>& Bperson) {
	double input[42];
	setInputArrary(input, Aperson, Bperson);
	std::shared_ptr<Neural> neural = Singelon<Neural>::instance();
	/*利用神经网络训练后的数据来预测是否可以通信*/
	double bpResult = neural->result(input);
	if ((bpResult > 0.9) && (bpResult < 1.1))
		return BPResult::SUCCESS;
	if ((bpResult > (-0.1)) && (bpResult < 0.1))
		return BPResult::FAILED;
	return BPResult::UNKNOW;
}



void BaseService::setInputArrary(double* input,const std::shared_ptr<Person>& Aperson,
	const std::shared_ptr<Person>& Bperson) {
	input[0] = static_cast<double>(Bperson->m_gen);
	input[1] = static_cast<double>(Bperson->m_gra);
	input[2] = static_cast<double>(Bperson->m_chara);
	Bperson->m_otherGen == OtherGender::BOTH ? input[3] = static_cast<double>(OtherGender::BOTH) :
		input[3] = static_cast<double>(Aperson->m_gen);
	Bperson->m_otherApp == OtherApper::NOREQUIRE ? input[4] = static_cast<double>(OtherApper::NOREQUIRE) :
		input[4] = static_cast<double>(Aperson->m_appe);
	
	/*心情*/
	input[5] = static_cast<double>(Bperson->m_mood.m_veryBadMood);
	input[6] = static_cast<double>(Bperson->m_mood.m_goodlMood);
	input[7] = static_cast<double>(Bperson->m_mood.m_ordinaryMood);
	input[8] = static_cast<double>(Bperson->m_mood.m_badMood);
	input[9] = static_cast<double>(Bperson->m_mood.m_veryBadMood);
	input[10] = static_cast<double>(Bperson->m_mood.m_terribleMood);
	input[11] = static_cast<double>(Bperson->m_mood.m_immune);

	/*天气*/
	input[12] = static_cast<double>(Bperson->m_weather.m_cold);
	input[13] = static_cast<double>(Bperson->m_weather.m_hot);
	input[14] = static_cast<double>(Bperson->m_weather.m_bigRainy);
	input[15] = static_cast<double>(Bperson->m_weather.m_smallRainy);
	input[16] = static_cast<double>(Bperson->m_weather.m_snowy);
	input[17] = static_cast<double>(Bperson->m_weather.m_windy);
	input[18] = static_cast<double>(Bperson->m_weather.m_goodWeather);
	input[19] = static_cast<double>(Bperson->m_weather.m_immune);

	/*时间*/
	input[20] = static_cast<double>(Bperson->m_time.m_morning);
	input[21] = static_cast<double>(Bperson->m_time.m_forenoon);
	input[22] = static_cast<double>(Bperson->m_time.m_noon);
	input[23] = static_cast<double>(Bperson->m_time.m_afternoon);
	input[24] = static_cast<double>(Bperson->m_time.m_night);
	input[25] = static_cast<double>(Bperson->m_time.m_immune);

	/*人流密度*/
	input[26] = static_cast<double>(Bperson->m_pc.m_mostPerson);
	input[27] = static_cast<double>(Bperson->m_pc.m_manyPerson);
	input[28] = static_cast<double>(Bperson->m_pc.m_fewPerson);
	input[29] = static_cast<double>(Bperson->m_pc.m_onePerson);
	input[30] = static_cast<double>(Bperson->m_pc.m_immune);

	/*运动状态*/
	input[31] = static_cast<double>(Bperson->m_acStatus.m_static);
	input[32] = static_cast<double>(Bperson->m_acStatus.m_walk);
	input[33] = static_cast<double>(Bperson->m_acStatus.m_rapidWalk);
	input[34] = static_cast<double>(Bperson->m_acStatus.m_run);

	/*交通工具*/
	input[35] = static_cast<double>(Bperson->m_tran.m_bike);
	input[36] = static_cast<double>(Bperson->m_tran.m_electrombile);
	input[37] = static_cast<double>(Bperson->m_tran.m_every);

	/*态度*/
	input[38] = static_cast<double>(Aperson->m_attitude.m_polite);
	input[39] = static_cast<double>(Aperson->m_attitude.m_common);
	input[40] = static_cast<double>(Aperson->m_attitude.m_impolite);
	input[41] = static_cast<double>(Aperson->m_attitude.m_immune);
}

double OnlineAndOfflineService::computeInfectRate() {
	int infectiveCnts = m_offlineInfectPersons.size() + m_onlineInfectPersons.size();
	int allCnts = m_onlineCounts + m_offlineCounts;
	double rate = static_cast<double>(infectiveCnts) / allCnts;
	return  rate;
}


void BaseService::writeToFile(double *rate,const std::string& path) {
	std::ofstream out(path.c_str());
	if (!out) {
		std::cout << "open the rate.csv file error!" << std::endl;
		exit(0);
	}
	out.precision(3);
	std::cout.precision(3);
	std::cout << "start to write infective rate to"<<path<<"..." << std::endl;

	out << "时间" << "," << "感染率" << std::endl;
	std::cout << std::setfill('=') << std::setw(6) << "时间" << std::setfill('=')
		<< std::setw(9) << "感染率" << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(3));


	for (int i = 0; i < END_TIME; i++) {

		out << i+1 << "," << rate[i] << std::endl;/*写到文件中*/

		/*写到输出中*/
		std::cout << std::setfill(' ') << std::setw(2) << "|" << std::setw(3)
			<< i+1 << std::setw(3) << "|" << std::setw(5) << rate[i] << std::setw(2) << "|" << std::endl;
	}
	std::cout << "end to write infective rate to " <<path<< std::endl;
	std::cout << std::endl;
}


void OnlineAndOfflineService::process() {
	//selectStrategy();
	double rate[END_TIME];
	std::cout << "start infect..." << std::endl;
	while (m_time < END_TIME) {
		personCommunicate();
		//std::cout << "========time: " << m_time << "==============" << std::endl;
		//std::cout <<"before cure:"<< m_onlineInfectPersons.size() << "  " << m_onlineUninfectPersons.size() << std::endl;
		infectCure();
		//std::cout << "after cure:" << m_onlineInfectPersons.size() << "  " << m_onlineUninfectPersons.size() << std::endl;
		rate[m_time] = computeInfectRate();

		personMoveOneSecond();
		m_time++;
	}
	std::cout << "end infect." << std::endl;

	writeToFile(rate, "G:\\online_offline_rate.csv");
	
}