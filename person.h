#ifndef PERSON_H
#define PERSON_H

#include <stdint.h>
#include <string>

#define STATIC_SPEED (0)	/*��ֹ�ٶ�*/
#define WALK_SPEED (0.001)	/*�����ٶ�*/
#define RAPIDWALK_SPEED (0.003)	/*�����ٶ�*/
#define RUN_SPEED (0.007)	/*�ܲ��ٶ�*/


const double Speed[4] = { STATIC_SPEED ,WALK_SPEED ,
RAPIDWALK_SPEED ,RUN_SPEED };

enum class Gender {
	BOY = 1, GIRL = 2
};

enum class Grade {
	FRESHMAN = 1,
	SOPHOMORE = 2,
	JUNIOR = 3,
	SENIOR = 4,
	MASTER_ONE = 5,
	MASTER_TWO = 6,
	MASTER_THREE = 7
};

enum class Character {
	DIFFIDENCE = 1,
	OUTGOING = 2,
	OBSERVING = 3,
	RATIONAL = 4,
	SENSE = 5
};

enum class Apperance {
	GOOD = 1,
	BAD = 2
};

enum class OtherGender {
	MAN = 1,
	FEMALE = 2,
	BOTH = 3
};

enum class OtherApper {
	TASTE = 1,
	NOTASTE = 2,
	NOREQUIRE = 3
};

#if 0
enum class Mood {
	m_veryGoodMood = 1,/*���鼫��*/
	m_goodlMood = 2,/*���鲻��*/
	m_ordinaryMood = 3,/*����ƽ��*/
	m_badMood = 4,/*�����е��*/
	m_veryBadMood = 5,/*����ܲ�*/
	m_terribleMood=6,
	m_immune = 7/*���鲻��Ӱ��*/
};

enum class Weather {
	m_cold = 1,/*����̹�*/
	m_hot = 2,/*��������*/
	m_bigRainy = 3,/*ư�ô���*/
	m_smallRainy = 4,/*ϸ������*/
	m_snowy = 5,/*ѩ��ưư*/
	m_windy = 6,/*����ϰϰ*/
	m_goodWeather = 7,/*���ﻨ��*/
	m_immune = 8/*��������Ӱ��*/
};

enum class Time {
	m_morning=1,/*�峿*/
	m_forenoon=2,/*����*/
	m_noon=3,/*����*/
	m_afternoon=4,/*����*/
	m_night=5,/*����*/
	m_immune=6,/*ʱ�䲻��Ӱ��*/
};

enum class PersonCount {
		m_mostPerson=1,/*�˼���*/
		m_manyPerson=2,/*�ܶ���*/
		m_fewPerson=3,/*�˺���*/
		m_onePerson=4,/*ֻ����һ��*/
		m_immune=5/*��Ⱥ�ܶȲ���Ӱ��*/
};

enum class ActivityStatus {
	m_static = 1,/*��ֹ*/
	m_walk = 2,/*ɢ��*/
	m_rapidWalk = 3,/*����*/
	m_run = 4,/*�ܲ�*/
};

enum class Transportaion {
	m_bike = 1,/*�����г�*/
	m_electrombile = 2,/*��綯��*/
	m_every = 3/*�κ��˶�����*/
};

enum class Attitude {
	m_polite = 1,/*�������*/
	m_common = 2,/*̬��һ��*/
	m_impolite = 3,/*̬�ȶ���*/
	m_immune = 4,/*̬�Ȳ�Ӱ��*/
};

struct Location {
	double m_x;
	double m_y;
};
#endif
struct Mood {
	bool m_veryGoodMood;/*���鼫��*/
	bool m_goodlMood;/*���鲻��*/
	bool m_ordinaryMood;/*����ƽ��*/
	bool m_badMood;/*�����е��*/
	bool m_veryBadMood; /*����ܲ�*/
	bool m_terribleMood;/*���鼫��*/
	bool m_immune;/*���鲻��Ӱ��*/
};

struct Weather {
	bool m_cold;/*����̹�*/
	bool m_hot;/*��������*/
	bool m_bigRainy;/*ư�ô���*/
	bool m_smallRainy;/*ϸ������*/
	bool m_snowy;/*ѩ��ưư*/
	bool m_windy;/*����ϰϰ*/
	bool m_goodWeather;/*���ﻨ��*/
	bool m_immune;/*��������Ӱ��*/
};

struct Time {
	bool m_morning;/*�峿*/
	bool m_forenoon;/*����*/
	bool m_noon;/*����*/
	bool m_afternoon;/*����*/
	bool m_night;/*����*/
	bool m_immune;/*ʱ�䲻��Ӱ��*/
};

struct PersonCount {
	bool m_mostPerson;/*�˼���*/
	bool m_manyPerson;/*�ܶ���*/
	bool m_fewPerson;/*�˺���*/
	bool m_onePerson;/*ֻ����һ��*/
	bool m_immune;/*��Ⱥ�ܶȲ���Ӱ��*/
};

struct ActivityStatus {
	bool m_static;/*��ֹ*/
	bool m_walk;/*ɢ��*/
	bool m_rapidWalk;/*����*/
	bool m_run;/*�ܲ�*/
};

struct Transportaion {
	bool m_bike;/*�����г�*/
	bool m_electrombile;/*��綯��*/
	bool m_every;/*�κ��˶�����*/
};

struct Attitude {
	bool m_polite;/*�������*/
	bool m_common;/*̬��һ��*/
	bool m_impolite;/*̬�ȶ���*/
	bool m_immune;;/*̬�Ȳ�Ӱ��*/
};

struct Location {
	double m_x;
	double m_y;
};

struct  Person {

	/*�Լ�������*/
	std::string m_stuNum;/*ѧ��*/

	//TODO:���Ϻ͸�Ⱦ�����ֶο��Զ���

	bool m_online;/*�Ƿ�������*/
	bool m_infective;/*�Ƿ��Ⱦ*/
	double m_speed;/*�ƶ��ٶ�*/
	double m_angel;/*360�ȷ����������*/
	Location m_location;/*��У԰λ��*/
	int m_cureTime;/*����ʱ��*/
	Gender m_gen;/*�Ա�*/
	Grade m_gra;/*�꼶*/
	Character m_chara;/*�Ը�*/
	Apperance m_appe;/*����*/
	OtherGender m_otherGen;/*�����Ա�*/
	OtherApper m_otherApp;/*������ò*/

	/*�ں�������£�Ը������˽���*/
	Mood m_mood;/*����*/
	Weather m_weather;/*����*/
	Time m_time;/*ʱ��*/
	PersonCount m_pc;/*�����ܶ�*/
	ActivityStatus m_acStatus;/*�˶�״̬*/
	Transportaion m_tran;/*��ͨ����*/
	Attitude m_attitude;/*ѯ��̬��*/
	
};
#endif