
#pragma once
#include <list>
#include <time.h>

#ifdef RECOGNITIONBB_EXPORTS
#define RECOGNITIONBB_API __declspec(dllexport)
#else
#define RECOGNITIONBB_API __declspec(dllimport)
#endif


//������, �� ������� ������� ��������� ����� ��������� �����
template <typename T>
class RECOGNITIONBB_API timer_list {
public:

	//���������� ������, ������� ������ �������� ������� � ������
	timer_list<T>(double second = 10) {
		_second = second;
	}

	~timer_list<T>() {

	}

	//���������� ������ ������� � ������, �� �������� �� ����, ���� �� ��� ����� ��
	void AddNewObject(T obj) {
		//�������� ����� �������
		clock_t start_time = clock();
		std::pair<clock_t, T> p;
		p.first = start_time;
		p.second = obj;
		//���������� �������
		list.push_back(p);
	}

	//��������, ���� �� ������ � ������, ��� ����� �������
	bool CheckObj(T obj) {
		//���� �� ���� ��������� 
		for (auto iter = list.begin(); iter != list.end(); iter++) {
			if (iter->second == obj) return true;
		}
		return false;
	}

	//��������, ����������� �� ����� ���������� � ������, ��� ���
	bool EndTimeToObj(T obj) {
		TimerUpdate();
		//���� ������� �� ���� � ������, �� ����������� � ������, �� ��� ����� ������������
		if (!CheckObj(obj)) {
			//�������� � ������
			AddNewObject(obj);
			//������ ����� � ������, �� �� ���� ����� ��� ���������� ������������
			return true;
		}
		//�����, ������ ���� � ������, ��� ������ �������� ������������
		return false;
	}

private:
	
	void TimerUpdate() {
		//��� ���� �������� ���������� �������
	//���� ��� ������� - �������� �� ������
		clock_t curTime = clock();
		double duration = 0.0;
		//���� ������ ��� � ������, ��������, ������� �� ��� �����
		for (auto iter = list.begin(); iter != list.end(); iter++) {
			duration = (double)(curTime - iter->first) / CLOCKS_PER_SEC;
			if (duration > _second) {
				//�������� ������ �� ������
				list.remove(*iter);
				iter = list.begin();
			}
		}
	}

	//������, ������� ������� �� ��� ��������
	//������ ����� - ����� ���������� �������� � ������
	//������ - ��� ������
	std::list<std::pair<clock_t, T>> list;

	//���������� ������, ����� ������� ������� �������� ������
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
	//�������� ����� �������
	clock_t start_time = clock();
	std::pair<clock_t, T> p;
	p.first = start_time;
	p.second = obj;
	//���������� �������
	list.push_back(p);
}

template<typename T>
inline bool timer_list<T>::CheckObj(T obj)
{
	//���� �� ���� ��������� 
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		if (iter->second  == obj) return true;
	}
	return false;
}

template<typename T>
inline bool timer_list<T>::EndTimeToObj(T obj)
{
	TimerUpdate();
	//���� ������� �� ���� � ������, �� ����������� � ������, �� ��� ����� ������������
	if (!CheckObj(obj)) {
		//�������� � ������
		AddNewObject(obj);
		//������ ����� � ������, �� �� ���� ����� ��� ���������� ������������
		return true;
	} 
	//�����, ������ ���� � ������, ��� ������ �������� ������������
	return false;

	/*else {
		clock_t curTime = clock();
		//���� ������ ��� � ������, ��������, ������� �� ��� �����
		for (auto iter = list.begin(); iter != list.end(); iter++) {
			if (iter->second == obj) {

				double duration = (double)(curTime - iter->first) / CLOCKS_PER_SEC;
 				if (duration > _second) {
					//�������� ������ �� ������
					list.remove(*iter);
					//������� ������
					return true;
				}

			}
		}

		//���� ����� �� �����, ������� false
		return false;
	}
}

template<typename T>
inline void timer_list<T>::TimerUpdate()
{
	//��� ���� �������� ���������� �������
	//���� ��� ������� - �������� �� ������
	clock_t curTime = clock();
	double duration = 0.0;
	//���� ������ ��� � ������, ��������, ������� �� ��� �����
	for (auto iter = list.begin(); iter != list.end(); iter++) {
		duration = (double)(curTime - iter->first) / CLOCKS_PER_SEC;
		if (duration > _second) {
			//�������� ������ �� ������
			list.remove(*iter);
			iter = list.begin();
		}
	}
}

*/