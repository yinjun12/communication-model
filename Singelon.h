#ifndef SINGLE_H
#define SINGLE_H


#include<memory>
#include <mutex>

/*���ܵĵ���ģ�ͣ�
1����Ҫ��̬��˽�г�Ա�;�̬�Ĺ��к������ҹ��캯��Ϊ˽�е�
2�����̰߳�ȫ���� ��Ҫdouble check
3:ģ��������ģ��������Է������ܵĹ��������*/
template<typename T>
class Singelon {
private:
	Singelon() = default;
	virtual ~Singelon() = default;
	Singelon(const Singelon&) = default;
	Singelon& operator=(const Singelon&) = default;
	static std::shared_ptr<T> m_instance;
	static std::mutex m_instanceMutex;

public:
	template <typename ...Args>static inline std::shared_ptr<T> instance(Args&& ...args) {
		if (m_instance == nullptr) {
			std::unique_lock<std::mutex>lck(m_instanceMutex);
			if (m_instance == nullptr) {
				m_instance.reset(new T(std::forward<Args>(args)...));
			}
		}
		return m_instance;
	}	
};

template<typename T>
std::shared_ptr<T> Singelon<T>::m_instance;
template <typename T>
std::mutex Singelon<T>::m_instanceMutex;
#endif // 