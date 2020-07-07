#include "RecognitionBB.h"


 RecognitionBB::RecognitionBB() {

}

 RecognitionBB::~RecognitionBB() {

}

 void RecognitionBB::m1_Connect_to_db(std::string host, std::string port, std::string user_name, std::string password, std::string address_db) {
	//���������� ������� ��, ������ ����� ������� ����������
	db_manager::SetConnectInfo(host, port, user_name, password, address_db, false);
}

 void RecognitionBB::m2_Authorization(std::string login) {
	_user = db_user::LoginToUser(login);
}

 void RecognitionBB::m2_Authorization() {
	Ipcofnig ipconfig;
	//std::cout << "ip address:" << ipconfig.GetIpV4() << "\n";
	_user = db_user::LoginToUser(ipconfig.GetIpV4());
}

 void RecognitionBB::m3_LoadGroupAndCamera() {
	//��������� ��� ������
	db_group::LoadedAllGroup(_user->GetId());
	//�������� ���� �����
	_listCamInfo = db_vcam::GetAllLinkVcam(_user->GetId());
	//�������� ����� �� ������
	for (auto iter = _listCamInfo.begin(); iter != _listCamInfo.end(); iter++) {
		information_camera ic(iter->GetAddress(), iter->GetAddress());
		if(ic.IsUsbCam())
		{
			int num = atoi(iter->GetAddress().c_str());
			Parralel_Scaner_camera psc(num, ic);
			psc.SetId(iter->GetId());
			_listCam.push_back(psc);
		}
		else  {
			Parralel_Scaner_camera psc(iter->GetAddress(), ic);
			psc.SetId(iter->GetId());
			_listCam.push_back(psc);
		}

	}
}

 void  RecognitionBB::m4_LoadEmployeeAndFace() {
	//�������� ���� �������������
	std::vector<db_employee>* buff = db_employee::GetEmployeeWithCondition(db_group::GetAllGroup());
	_listEmployee = *buff;
	delete buff;

	_faces = new sharead_face_manager();
	for (auto iter = _listEmployee.begin(); iter != _listEmployee.end(); iter++) {

		//���������� ������ ����
		_faces->AddNewFace(iter->GetId(), iter->GetFirstName(), iter->GetLastName(), iter->GetMidleName(), iter->GetDescrInfo());

		if (iter->GetListDescr().size() > 0) {
			list<db_face> fl = iter->GetListDescr();
			for (auto desc = fl.begin(); desc != fl.end(); desc++) {
				_faces->AddDescriptor(iter->GetId(), desc->GetDescriptor());
			}
		}
		//��������� ���� �����, ��������� � �����������
		auto list_grup = db_group::GetSnapGoup(iter->GetId());

		group_load_face* glf = new  group_load_face();

		for (auto iter = list_grup.begin(); iter != list_grup.end(); iter++) {
			glf->AddGroup(iter->GetId(), iter->GetName());
		}

		
		//���������� ������ �����
		_faces->AddLoad(iter->GetId(), glf);
	}

}

 void RecognitionBB::m5_CreateRecognizerAndHandler(int countThread, double SecToFile, double SecToDB) {

	pc = new PremiseCheck();
	db_manager_parralel* dbmp = new db_manager_parralel();
	//��� ������ ������
	for (auto iter = _listCam.begin(); iter != _listCam.end(); iter++) {

		//��������� ����� ������ ������
		rules_collection coll;
		coll.LoadAlRuleLinkCam(iter->GetId());

		//��������� ����� ������ ���������
		db_vcam cam(iter->GetId());
		std::vector<string> listPremise;
		listPremise.push_back(cam.GetPremise().GetName());
		std::vector<db_premise> prem = cam.GetPremise().GetAllParent();
		for (auto iPrem = prem.begin(); iPrem != prem.end(); iPrem++)
			listPremise.push_back(iPrem->GetName());

		//�������� ���� ���������������
		distribute_recognitor* dr = new distribute_recognitor(_faces, countThread);
		dr->SetId(iter->GetId());
		//� ��� �� ����� ������������
		dbRecognitionHandler* drh = new dbRecognitionHandler(iter->GetId(), SecToDB);
		drh->SetPremisesList(listPremise);
		drh->SetRulesList(coll.GetAllRule());

		std::string camName = "Recognition_level.txt";
		//camName += std::to_string(13);
		fileRecognitionHandler* frh = new fileRecognitionHandler(camName, iter->GetId(), 1);
		frh->SetRulesList(coll.GetAllRule());
		frh->SetPremisesList(listPremise);
		
		PremiseCheck* pcc = new PremiseCheck();
		pcc->SetCurrIdCam(iter->GetId());
		pcc->SetPremisesList(listPremise);

		//������ ��� �������� ��������� �����������

		//�����, � ������� �������� ���������� ����� ���� � ��
		dr->SetDBSource(dbmp);
		//���� ��������
		Detecter* d = new Detecter();
		iter->SetDetecter(d);
		//����������� ������� �������������
		dr->AddRecognitionHandler(drh);
		dr->AddRecognitionHandler(frh);
		dr->AddRecognitionHandler(pcc);
		//���������� ���������
		_listRecognitior.push_back(dr);
		iter->SetRecognitor(dr);
	}

}

 void RecognitionBB::m6_AddReceiver(std::vector<std::string> listFileName) {

	for (auto iter = _listRecognitior.begin(); iter != _listRecognitior.end(); iter++) {
		messageHandler* mh = new messageHandler("127.0.0.2", "8000");
		mh->AddNewRecipient(listFileName);

		//��������� ��������� ��������
		rules_collection rulcol;
		rulcol.LoadAlRuleLinkCam((*iter)->_id_cam);

		//��������� ����� ������ ���������
		db_vcam cam((*iter)->_id_cam);
		std::vector<string> listPremise;
		listPremise.push_back(cam.GetPremise().GetName());
		std::vector<db_premise> prem = cam.GetPremise().GetAllParent();
		for (auto iPrem = prem.begin(); iPrem != prem.end(); iPrem++)
			listPremise.push_back((iPrem)->GetName());

		//��� ������� ����� �������� ���� ����������
		mh->SetRulesList(rulcol.GetAllRule());
		mh->SetPremisesList(listPremise);
		(*iter)->AddRecognitionHandler(mh);
	}

}

 void RecognitionBB::m7_addHandler(IRecognitionHandler* handler) {
	for (auto iter = _listRecognitior.begin(); iter != _listRecognitior.end(); iter++) {

		//��������� ��������� ��������
		rules_collection rulcol;
		rulcol.LoadAlRuleLinkCam((*iter)->_id_cam);

		// ��������� ����� ������ ���������
		db_vcam cam((*iter)->_id_cam);
		std::vector<string> listPremise;
		listPremise.push_back(cam.GetPremise().GetName());
		std::vector<db_premise> prem = cam.GetPremise().GetAllParent();
		for (auto iPrem = prem.begin(); iPrem != prem.end(); iPrem++)
			listPremise.push_back((iPrem)->GetName());


		handler->SetRulesList(rulcol.GetAllRule());
		handler->SetPremisesList( listPremise);
		(*iter)->AddRecognitionHandler(handler);
	}
}

 void RecognitionBB::m8_Start() {
	for (auto iter = _listCam.begin(); iter != _listCam.end(); iter++) {
		iter->StartWork();
		//iter->StartShow();
	}
}

 void RecognitionBB::m10_startShow()
 {
	 for (auto iter = _listCam.begin(); iter != _listCam.end(); iter++) {
		 iter->StartShow();
	 }
 }

 void RecognitionBB::m10_endShow()
 {
	 for (auto iter = _listCam.begin(); iter != _listCam.end(); iter++) {
		 iter->EndShow();
	 }
 }

 std::vector<std::pair<std::string, std::vector<std::string>>> RecognitionBB::m11_GetPrimeseInEmployee()
 {
	 return pc->GetPremiseEmplyee();
 }

 void RecognitionBB::m9_end() {
	for (auto iter = _listCam.begin(); iter != _listCam.end(); iter++) {
		iter->EndShow();
		iter->EndWork();
	}
	std::this_thread::sleep_for(15s);
}
