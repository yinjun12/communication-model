#pragma once

#include <memory>
#include <vector>

class PersonFactory;


class Bridge {
protected:
	std::shared_ptr<PersonFactory> personFactory_;
public:
	void setFactory(const std::shared_ptr<PersonFactory>& se);
	virtual void display() = 0;
	virtual void run() = 0;
};

class OnlineAndOfflineBridge:public Bridge {
	public:
		void display() override;
		void run() override;
};

class OnlineBridge :public Bridge {
public :
	void display() override;
	void run() override;
};

class Runner {
private:
	std::vector<std::shared_ptr<Bridge>> bridgeVec_;
public:
	void selectStrategy();
	void addBridge(const std::shared_ptr<Bridge>& br);
	void run();
};