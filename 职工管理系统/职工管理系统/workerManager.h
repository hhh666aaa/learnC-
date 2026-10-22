#pragma once
#include <iostream>
using namespace std;
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include<fstream>
#define FILENAME "empFile.txt"

class WorkerManager {
public:

	
	void Show_Menu();

	void exitSystem();

	void Add_Emp();

	void save();

	int get_EmpNum();

	void init_Emp();

	void Show_Emp();

	void Del_Emp();

	int IsExist(int id);

	void Mod_Emp();

	bool Id_IS_Repeat(int id);

	void Find_Emp();

	void Sort_Emp();

	void Clean_File();

	WorkerManager();

	~WorkerManager();

	int m_EmpNum;
	Worker** m_EmpArray;
	bool m_FileIsEmpty;
};
