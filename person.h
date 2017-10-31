#ifndef PERSON_H
#define PERSON_H

#include <stdint.h>
#include <string>

#define STATIC_SPEED (0)	/*静止速度*/
#define WALK_SPEED (0.001)	/*慢走速度*/
#define RAPIDWALK_SPEED (0.003)	/*快走速度*/
#define RUN_SPEED (0.007)	/*跑步速度*/


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
	m_veryGoodMood = 1,/*心情极好*/
	m_goodlMood = 2,/*心情不错*/
	m_ordinaryMood = 3,/*心情平淡*/
	m_badMood = 4,/*心情有点差*/
	m_veryBadMood = 5,/*心情很差*/
	m_terribleMood=6,
	m_immune = 7/*心情不爱影响*/
};

enum class Weather {
	m_cold = 1,/*寒风刺骨*/
	m_hot = 2,/*烈日炎炎*/
	m_bigRainy = 3,/*瓢泼大雨*/
	m_smallRainy = 4,/*细雨绵绵*/
	m_snowy = 5,/*雪花瓢瓢*/
	m_windy = 6,/*凉风习习*/
	m_goodWeather = 7,/*鸟语花香*/
	m_immune = 8/*天气不会影响*/
};

enum class Time {
	m_morning=1,/*清晨*/
	m_forenoon=2,/*上午*/
	m_noon=3,/*中午*/
	m_afternoon=4,/*下午*/
	m_night=5,/*晚上*/
	m_immune=6,/*时间不会影响*/
};

enum class PersonCount {
		m_mostPerson=1,/*人挤人*/
		m_manyPerson=2,/*很多人*/
		m_fewPerson=3,/*人很少*/
		m_onePerson=4,/*只有你一个*/
		m_immune=5/*人群密度不会影响*/
};

enum class ActivityStatus {
	m_static = 1,/*静止*/
	m_walk = 2,/*散步*/
	m_rapidWalk = 3,/*快走*/
	m_run = 4,/*跑步*/
};

enum class Transportaion {
	m_bike = 1,/*骑自行车*/
	m_electrombile = 2,/*骑电动车*/
	m_every = 3/*任何运动都行*/
};

enum class Attitude {
	m_polite = 1,/*彬彬有礼*/
	m_common = 2,/*态度一般*/
	m_impolite = 3,/*态度恶劣*/
	m_immune = 4,/*态度不影响*/
};

struct Location {
	double m_x;
	double m_y;
};
#endif
struct Mood {
	bool m_veryGoodMood;/*心情极好*/
	bool m_goodlMood;/*心情不错*/
	bool m_ordinaryMood;/*心情平淡*/
	bool m_badMood;/*心情有点差*/
	bool m_veryBadMood; /*心情很差*/
	bool m_terribleMood;/*心情极差*/
	bool m_immune;/*心情不爱影响*/
};

struct Weather {
	bool m_cold;/*寒风刺骨*/
	bool m_hot;/*烈日炎炎*/
	bool m_bigRainy;/*瓢泼大雨*/
	bool m_smallRainy;/*细雨绵绵*/
	bool m_snowy;/*雪花瓢瓢*/
	bool m_windy;/*凉风习习*/
	bool m_goodWeather;/*鸟语花香*/
	bool m_immune;/*天气不会影响*/
};

struct Time {
	bool m_morning;/*清晨*/
	bool m_forenoon;/*上午*/
	bool m_noon;/*中午*/
	bool m_afternoon;/*下午*/
	bool m_night;/*晚上*/
	bool m_immune;/*时间不会影响*/
};

struct PersonCount {
	bool m_mostPerson;/*人挤人*/
	bool m_manyPerson;/*很多人*/
	bool m_fewPerson;/*人很少*/
	bool m_onePerson;/*只有你一个*/
	bool m_immune;/*人群密度不会影响*/
};

struct ActivityStatus {
	bool m_static;/*静止*/
	bool m_walk;/*散步*/
	bool m_rapidWalk;/*快走*/
	bool m_run;/*跑步*/
};

struct Transportaion {
	bool m_bike;/*骑自行车*/
	bool m_electrombile;/*骑电动车*/
	bool m_every;/*任何运动都行*/
};

struct Attitude {
	bool m_polite;/*彬彬有礼*/
	bool m_common;/*态度一般*/
	bool m_impolite;/*态度恶劣*/
	bool m_immune;;/*态度不影响*/
};

struct Location {
	double m_x;
	double m_y;
};

struct  Person {

	/*自己的属性*/
	std::string m_stuNum;/*学号*/

	//TODO:线上和感染两个字段可以丢弃

	bool m_online;/*是否在线上*/
	bool m_infective;/*是否感染*/
	double m_speed;/*移动速度*/
	double m_angel;/*360度方向，随机产生*/
	Location m_location;/*在校园位置*/
	int m_cureTime;/*治愈时间*/
	Gender m_gen;/*性别*/
	Grade m_gra;/*年级*/
	Character m_chara;/*性格*/
	Apperance m_appe;/*长相*/
	OtherGender m_otherGen;/*它人性别*/
	OtherApper m_otherApp;/*他人外貌*/

	/*在何种情况下，愿意与别人交流*/
	Mood m_mood;/*心情*/
	Weather m_weather;/*天气*/
	Time m_time;/*时间*/
	PersonCount m_pc;/*人流密度*/
	ActivityStatus m_acStatus;/*运动状态*/
	Transportaion m_tran;/*交通工具*/
	Attitude m_attitude;/*询问态度*/
	
};
#endif