#include "pch.h"
#include "recipient.h"

Recipient::Recipient(std::string IPV4_PORT)
{
	//Нахождение разделителя
	int midlIndex = 0;
	midlIndex = IPV4_PORT.find(':', 0);
	//выделение и установка адреса
	std::string address = IPV4_PORT.substr(0, midlIndex);
	SetAddress(address);
	//Выделение и установка порта
	std::string port = IPV4_PORT.substr(midlIndex + 1, IPV4_PORT.size() - midlIndex);
	SetPortRecepient(port);
}

Recipient::Recipient(std::string IPV4, std::string port)
{
	SetAddress(IPV4);
	SetPortRecepient(port);
}

Recipient::Recipient()
{
}

void Recipient::SetAddress(std::string address)
{
	_address = address;
}

void Recipient::SetPortRecepient(std::string port)
{
	_port = port;
}

void Recipient::SetAddInfo(std::string addInfo)
{
	_add_info = addInfo;
}

std::string Recipient::GetAddInfo()
{
	return _add_info;
}

std::string Recipient::GetAddress()
{
	if (_address == "") throw std::exception("Exception! Not set Address recipient");
	return _address;
}

std::string Recipient::GetPort()
{
	if (_port == "") throw std::exception("Exception! Not set Port recipient");
	return _port;
}

bool Recipient::CheckList(std::vector<int> rule, std::vector<int> group)
{

	//Проверяем для всех пар
	for (auto iter = _pairList.begin(); iter != _pairList.end(); iter++) {
		//Если хотя бы одна пара подходит
		if (ChekPair(*iter, rule, group)) {
			return true;
		}
	}

	return false;
}

void Recipient::SetSendServer(SendServer* server)
{
	_sendMess = server;
}

void Recipient::SendMess(Message message)
{
	//Если нет сервера
	if (_sendMess == NULL)
		//Выкинуть исключение
		throw std::exception("Exception! SendsServer is NULL!");
	//Добавление к сообщению доп информации
	message.AddInfo(_add_info);
	//Отправление сообщения
	
	_sendMess->operator()(message, _address, _port);
	//std::thread t(*_sendMess, message, _address, _port);
	//t.detach();
}

void Recipient::AddPair(grPair pair)
{
	//Добавление новой пары
	_pairList.push_back(pair);
}

void Recipient::AddPair(std::vector<int> group, std::vector<int> rule)
{
	//Создаётся новая пара, и к ней добавляются элементы
	grPair newPair;
	for (auto iter = group.begin(); iter != group.end(); iter++) newPair.AddGroup(*iter);
	for (auto iter = rule.begin(); iter != rule.end(); iter++) newPair.AddRule(*iter);
	//Добавления пары в коллекцию
	AddPair(newPair);
}

bool Recipient::HasErrorMessage()
{
	if (_sendMess->ErrorMessageSend()) return true;
	return false;
}

bool Recipient::ChekPair(grPair pair, std::vector<int> id_rule_list, std::vector<int> id_group_list)
{
	//Проверка, подходят ли правила
	bool HasRule = false;
	//Проверка, подходят ли группы
	bool HasGroup = false;

	//Проверка правил
	if (pair.AnyRule()) {
		HasRule = true;
	}
	else {
		//Если есть у пары доступ к любому правилу
		for (auto iter = id_rule_list.begin(); iter != id_rule_list.end(); iter++) {
			if (pair.HasRule(*iter)) {
				HasRule = true;
				break;
			}
		}
	}

	//Если не подошло по правилу, нет смысла проверять далее
	if (!HasRule) return false;

	if (pair.AnyGroup()) {
		HasGroup = true;
	}
	else {
		//Проврека групп
		for (auto iter = id_group_list.begin(); iter != id_group_list.end(); iter++) {
			if (pair.HasGroup(*iter)) {
				HasGroup = true;
				break;
			}
		}

	}
	//Если оба условия подходят
	if (HasRule && HasGroup) {
		//То означает, что пара подходит
		return true;
	}

	return false;
}
