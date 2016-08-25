#ifndef OBSERVERS_H
#define OBSERVERS_H

#include <vector>
#include <memory>

namespace si {
	class Observable;

	class Observer {
	public:
		Observer(){};
		virtual void notify (Observable& subject, std::string type)=0;
	};

	class Observable : Observer {
	public:
		Observable(){};
		std::vector <std::shared_ptr<Observer>> observers;
		virtual void notifyObservers(std::string type)=0;
		virtual void registerObserver(std::shared_ptr<Observer> observer)=0;
	};
}

#endif /* OBSERVERS_H */