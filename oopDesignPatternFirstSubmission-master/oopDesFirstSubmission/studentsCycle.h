#pragma once
#include"smartPtr.h"
#include"student.h"
class StudentsCycle{
private:
    int startYear;
    int numOfStarted;//init to 0
    int numOfStudents;//init to 0
    int numOfFinished;//init to 0
    nodeType<Student>* studentsList;
    nodeType<Student>* finishedStudents;
    void checkGraduates();
public:
	StudentsCycle(int start);
    string getStudentDepartment(const string Id);
	~StudentsCycle();
    int getStartYear();
    void addStudent(RCPtr<Student>& nStudent);//add student to cycle
    bool isExist(const string Id);
    void deleteStudent(const string Id);
    void printCycleDetailes(ostream& out, const string& department);
};

