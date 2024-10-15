#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <Windows.h>
using namespace std;

class Exception {
public:
	Exception(const string&s, const int& err)
		:error_message(s)
		,error_id(err)
	{}
	virtual void what() {}
	virtual void errorid() {}
protected:
	string error_message;
	int error_id;
};

class SQLException : public Exception {
public:
	SQLException(const string& s, const int& err)
		:Exception(s, err)
	{}
	virtual void what() {
		cout << "SQLException: " << error_message << endl;
	}
	virtual void errorid() {
		cout << "error_id: " << error_id << endl;
	}
};

class DataHandlerException : public Exception {
public:
	DataHandlerException(const string& s, const int& err)
		:Exception(s, err)
	{}
	virtual void what() {
		cout << "DataHandlerException: " << error_message << endl;
	}
	virtual void errorid() {
		cout << "error_id: " << error_id << endl;
	}
};

class WebsiteResponseException : public Exception {
public:
	WebsiteResponseException(const string& s, const int& err)
		:Exception(s, err)
	{}
	virtual void what() {
		cout << "WebsiteResponseException: " << error_message << endl;
	}
	virtual void errorid() {
		cout << "error_id: " << error_id << endl;
	}
};

void sqlConnection() {
	srand((unsigned int)time(0));					// ģ�������ͳ������
	int error = rand();
	if (error % 2 == 0) {
		throw SQLException("���ݿ����Ӵ���", -1);	// ����������׸�������գ�ִ��������д������
	}
	else {
		cout << "���ݿ����ӳɹ�" << endl;
	}
	Sleep(1000);
	cout << endl;
}

void dataHandle() {
	srand((unsigned int)time(0));
	int error = rand();
	if (error % 3 != 0) {
		cout << "�����������ɹ�" << endl;
	}
	else {
		throw DataHandlerException("��������������", -2);
	}
	Sleep(1000);
	cout << endl;
}

void websiteResponse() {
	srand((unsigned int)time(0));
	int error = rand();
	if (error % 4 == 0) {
		throw WebsiteResponseException("�������", -3);
	}
	else {
		cout << "�������ӳɹ�" << endl;
	}
	Sleep(1000);
	cout << endl;
}

// ����ָ��
template<class T>
class Smart_ptr {
public:
	Smart_ptr(T* p)
		:ptr(p)
	{}
	~Smart_ptr() {
		cout << "ptr�ɹ�����" << endl;
		delete ptr;
	}
	T& operator*() {
		return *ptr;
	}
	T* operator->() {
		return ptr;
	}
private:
	T* ptr;
};