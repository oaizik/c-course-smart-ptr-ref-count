#pragma once
#include <string>
#include"smartPtr.h"
using namespace std;
class Student:public RCObject {
private:
    string firstName;
    string lastName;
    string id;
    int regYear;
    string studentAddress;
    string department;
    int sumOfCredits;
    bool graduate;
public:
	Student(const string fName, const string lName,const string iD,const int rYear,
        const string studentAdd,const string dep,const int CredSum=0);
	~Student();
    void addCredits(const int amount);
    string getStudentId();
    string getStudentDepartment();
    int getCredits();
    bool getGraduate();
    void setGraduate();
    void printStudentDetails(ostream& out);
};

