#ifndef SINGLE_H
#define SINGLE_H


#include<memory>
#include <mutex>

/*万能的单例模型！
1：需要静态的私有成员和静态的公有函数，且构造函数为私有的
2：多线程安全，则 需要double check
3:模板类里有模板包，可以符合万能的构造参数！*/
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