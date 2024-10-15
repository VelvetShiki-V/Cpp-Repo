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
	srand((unsigned int)time(0));					// 模拟正常和出错情况
	int error = rand();
	if (error % 2 == 0) {
		throw SQLException("数据库链接错误", -1);	// 将子类对象抛给父类接收，执行子类重写错误函数
	}
	else {
		cout << "数据库链接成功" << endl;
	}
	Sleep(1000);
	cout << endl;
}

void dataHandle() {
	srand((unsigned int)time(0));
	int error = rand();
	if (error % 3 != 0) {
		cout << "参数包解析成功" << endl;
	}
	else {
		throw DataHandlerException("参数包解析出错", -2);
	}
	Sleep(1000);
	cout << endl;
}

void websiteResponse() {
	srand((unsigned int)time(0));
	int error = rand();
	if (error % 4 == 0) {
		throw WebsiteResponseException("网络错误", -3);
	}
	else {
		cout << "网络连接成功" << endl;
	}
	Sleep(1000);
	cout << endl;
}

// 智能指针
template<class T>
class Smart_ptr {
public:
	Smart_ptr(T* p)
		:ptr(p)
	{}
	~Smart_ptr() {
		cout << "ptr成功析构" << endl;
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