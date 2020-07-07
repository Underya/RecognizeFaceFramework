#include "information_menu.h"
#include "questions_user.h"
#include "camera_menu.h"
#include "employee_menu.h"
#include "group_menu.h"
#include "rule_menu.h"
#include "premise_menu.h"
#include "receive_menu.h"

void information_menu::SwitchInformMenu(db_user* user)
{
	_user = user;
	questions_user q;
	try {
		//Вывод главного меню
		while (true)
		{
			q.ClearConsole();

			int res = q.SendQuestInt("Объект информации", { "Камеры", "Сотрудники", "Группы", "Правила", "Помещения", "Получатели", "Выход" });

			res = ParseAnswer(res);
			//Если вернулось значение -1 - конце цикла
			if (res == -1) break;
		}
	}
	catch (...) {
		std::cout << "Произошла неизвестная ошибка!";
	}
}

int information_menu::ParseAnswer(int number)
{
	if (number == 1) {
		camera_menu camera;
		camera.Switch(_user);
	}

	if (number == 2) {
		employee_menu emp;
		emp.Switch(_user);
	}

	if (number == 3) {
		group_menu group;
		group.Switch(_user);
	}

	if (number == 4) {
		rule_menu rule;
		rule.Switch(_user);
	}

	if (number == 5) {
		premise_menu pm;
		pm.Switch(_user);
	}

	if (number == 6) {
		recipients_list rm;
		rm.Switch(_user);
	}

	if (number == 7) {
		return -1;
	}

	return 1;
}
