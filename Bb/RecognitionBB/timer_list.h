
#pragma once
#include <list>
#include <time.h>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//Список, из которго объекты пропадают через указанное время
template <typename T>
class RECOGNITIONBB_API timer_list {
public:

	//Количество секунд, которые должно провести объекты в списке
	timer_list<T>(double second = 10) {
		_second = second;
	}

	~timer_list<T>() {

	}

	//Добавление нового объекта в список, не зависимо от того, есть ли там такой же
	void AddNewObject(T obj) {
		//Создание точки отсчёта
		clock_t start_time = clock();
		std::pair<clock_t, T> p;
		p.first = start_time;
		p.second = obj;
		//Добавление объекта
		list.push_back(p);
	}

	//Проверка, есть ли объект в списке, без учёта времени
	bool CheckObj(T obj) {
		//Цикл по всем элементам 
		for (auto iter = list.begin(); iter != list.end(); iter++) {
			if (iter->second == obj) return true;
		}
		return false;
	}

	//Проверка, закончилось ли время нахождения в списке, или нет
	bool EndTimeToObj(T obj) {
		TimerUpdate();
		//Если объекта не было в списке, он добавляется в список, но его можно использовать
		if (!CheckObj(obj)) {
			//Добавить в список
			AddNewObject(obj);
			//Только попал в список, то не надо ждать его повторного ипользования
			return true;
		}
		//Иначе, объект есть в списке, его нельзя повторно использовать
		return false;
	}

private:
	
	void TimerUpdate() {
		//Для всех объектов обновление времени
	//Если оно истекло - выкинуть из списка
		clock_t curTime = clock();
		double duration = 0.0;
		//Если объект был в списке, проверка, истекло ли его время
		for (auto iter = list.begin(); iter != list.end(); iter++) {
			duration = (double)(curTime - iter->first) / CLOCKS_PER_SEC;
			if (duration > _second) {
				//Выкинуть объект из списка
				list.remove(*iter);
				iter = list.begin();
			}
		}
	}

	//Список, который состоит из пар объектов
	//Первая часть - время добавления элемента в список
	//Вторая - Сам объект
	std::list<std::pair<clock_t, T>> list;

	//Количество секунд, через сколько объекты покидают список
	double _second = 0.0;
};

/*
template<typename T>
inline timer_list<T>::timer_list(double second)
{
	
}

template<typename T>
inline timer_list<T>::~timer_list()
{
}

template<typename T>
inline void timer_list<T>::AddNewObject(T obj)
{
	//Создание точки отсчёта
	clock_t start_time = clock();
	std::pair<clock_t, T> p;
	p.first = start_time;
	p.second = obj;
	//Добавление объекта
	list.push_back(p);
}

template<typename T>
inline bool timer_list<T>::CheckObj(T obj)
{
	//Цикл по всем элементам 
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter->second  == obj) return true;
	}
	return false;
}

template<typename T>
inline bool timer_list<T>::EndTimeToObj(T obj)
{
	TimerUpdate();
	//Если объекта не было в списке, он добавляется в список, но его можно использовать
	if (!CheckObj(obj)) {
		//Добавить в список
		AddNewObject(obj);
		//Только попал в список, то не надо ждать его повторного ипользования
		return true;
	} 
	//Иначе, объект есть в списке, его нельзя повторно использовать
	return false;

	/*else {
		clock_t curTime = clock();
		//Если объект был в списке, проверка, истекло ли его время
		for (auto iter = list.begin(); iter != list.end(); iter++) {
			if (iter->second == obj) {

				double duration = (double)(curTime - iter->first) / CLOCKS_PER_SEC;
 				if (duration > _second) {
					//Выкинуть объект из списка
					list.remove(*iter);
					//Вернуть истину
					return true;
				}

			}
		}

		//Если время не вышло, вернуть false
		return false;
	}
}

template<typename T>
inline void timer_list<T>::TimerUpdate()
{
	//Для всех объектов обновление времени
	//Если оно истекло - выкинуть из списка
	clock_t curTime = clock();
	double duration = 0.0;
	//Если объект был в списке, проверка, истекло ли его время
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		duration = (double)(curTime - iter->first) / CLOCKS_PER_SEC;
		if (duration > _second) {
			//Выкинуть объект из списка
			list.remove(*iter);
			iter = list.begin();
		}
	}
}

*/