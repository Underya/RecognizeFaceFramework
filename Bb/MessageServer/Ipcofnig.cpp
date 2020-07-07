#include "pch.h"
#include "Ipcofnig.h"

using namespace std;

Ipcofnig::Ipcofnig()
{
}

Ipcofnig::~Ipcofnig()
{
}

std::string Ipcofnig::GetIpV4()
{
	//Вызов функции, которая вернёт подходящий IP
	return GetIp(4);
}

std::string Ipcofnig::GetIpV6()
{
	return GetIp(6);
}

std::string Ipcofnig::GetIp(int ver)
{
	//Строка, в которую будет записан ответ
	string result = "";
	//Все IP
	vector<pair<string, int>> vec = GetMyIp();
	//Поиск только подходящий версии
	for (auto iter = vec.begin(); iter != vec.end(); iter++) {
		//Если версия подходит
		if (iter->second == ver)
			//То возвращается адерс
			return iter->first;
	}

	return result;
}

std::vector < std::pair<std::string, int>> Ipcofnig::GetMyIp()
{
	//Получение имени хоста устройства
	char cbuff[200];
	if (gethostname(cbuff, sizeof(cbuff)) == SOCKET_ERROR) {
		throw std::exception("Exception! Not get host name!");
	}
	//Критерии поиска адерсов
	addrinfo inf;
	//Результат поиска
	addrinfo* res;
	//Указать на следующий элементв в списке
	addrinfo* next = NULL;

	//Очищение памяти
	memset(&inf, 0, sizeof(inf));
	//Указание, что нам интересны только V4 адреса
	inf.ai_protocol = IPPROTO_IPV4;

	//Получение списка адресов
	int erro_code = getaddrinfo(cbuff, NULL, &inf, &res);

	//Разбор ошибок, которые могли возникнуть
	if (erro_code != 0) {
		std::string error_text;
		error_text = "Exception! Not receive address! Error code:" + std::to_string(erro_code);
		throw std::exception(error_text.c_str());
	}

	//Переменная для хранения всех результатов
	vector<pair<string, int>> vec;

	//Буффер для просмотра промежуточных результатов
	std::string buffer;

	//Просмотр всего списка
	next = res;

	while (next != NULL) {
		//Получение структуры адреса для текущего варианта
		sockaddr_in* adr = (sockaddr_in*)next->ai_addr;
		//Получение адреса в виде переменной
		inet_ntop(adr->sin_family, &(adr->sin_addr), cbuff, sizeof(cbuff));
		//Сохранения адреса в виде стринг структуры
		buffer = cbuff;
		//Если адрес не пустой
		if (!IsEmptyAddr(buffer)) {
			//То он добавляется в список адресов
			vec.push_back({ buffer, GetV(adr) });
		}
		//Переход к следующему обеъекту в списке
		next = next->ai_next;
	}

	return vec;
}

int Ipcofnig::GetV(sockaddr_in* addr)
{
	if (addr->sin_family == AF_INET) return 4;
	if (addr->sin_family == AF_INET6) return 6;
	return 0;
}

bool Ipcofnig::IsEmptyAddr(std::string addr)
{
	if (addr.size() < 2) return true;
	if (addr[0] == ':' && addr[1] == ':') return true;
	return false;
}
