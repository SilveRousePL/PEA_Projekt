//
// Created by darek on 27.01.18.
//

#pragma once
#include <iostream>

class Exception {
protected:
	std::string c;

public:
	Exception(std::string comment) :
			c(comment) {
	}
	virtual ~Exception() = default;

	std::string what() const {
		return c;
	}

	virtual void sysWindow() const = 0;
};

class NullPointerException: public Exception {
public:
	NullPointerException(std::string comment) :
			Exception(comment) {
	}
	void sysWindow() const override {
		//TO-DO MessageBox "Exception occurred and application will be closed."
	}
};

class RangeExceeded: public Exception {
public:
	RangeExceeded(std::string comment) :
			Exception(comment) {
	}
	void sysWindow() const override {
		//TO-DO MessageBox "Exception occurred and application will be closed."
	}
};

class FileException: public Exception {
public:
	FileException(std::string comment) :
			Exception(comment) {
	}
	void sysWindow() const override {
		//TO-DO MessageBox "Exception occurred and application will be closed."
	}
};

class NotImplemented: public Exception {
public:
	NotImplemented(std::string comment) :
			Exception(comment) {
	}
	void sysWindow() const override {
		//TO-DO MessageBox "Exception occurred and application will be closed."
	}
};

/*class CriticalException : public Exception {
 public:
 CriticalException(std::string comment): Exception(comment) {}
 void sysWindow() const override {
 //TO-DO MessageBox "Exception occurred and application will be closed."
 }
 };*/
