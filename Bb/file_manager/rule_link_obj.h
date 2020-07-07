#pragma once
#include "file_parametr.h"
#include <list>
#include <vector>

//Объекты скрываются в пространстве имён, для упрощения работы с модулем
namespace rule_link_obj {

	//Связь правила с объектом
	class FILEMANAGER_API rule_link_obj :
		public file_parametr
	{
	public:

		//Создание объекта, который находится в указаном файле
		rule_link_obj(std::string file_name);

		//Пустой объект
		rule_link_obj();

		~rule_link_obj();

		//Добавление новой связи правила с чем то
		void AddNewLink(int rule_id, int id);

		//Удаление связи правила с чем то
		void DeletLink(int rule_id, int id);

		//Все правила, связанные с объектом
		std::vector<int> GetLinkedId(int id_obj);

	protected:

		//Связь правила и другого объекта
		std::list<std::pair<int, int>> linked;

		//Чтение содержимого файла и инициализация объекта
		void ReceivInfo();

		//Получение всех связей  виде текста для сохранения в файл
		std::string GetContentList() override;

	};

}
