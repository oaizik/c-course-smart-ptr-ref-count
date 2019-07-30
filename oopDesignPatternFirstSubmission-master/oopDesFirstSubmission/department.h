#pragma once
#include "course.h"
#include"smartPtr.h"
class Department{
private:
    string departmentName;
    nodeType<Course>* coursesList;//list of courses
    nodeType<Student>* studentsList;//list of shared poiter to students
public:
	Department(string depNmae);
	~Department();
    string getDepartmentName();
    bool addCourse(RCPtr<Course>& newCourse);//add course
    RCPtr<Student>& addStudent(const string fName, const string lName, const string ID, const int rYear, const string studAd, const string dep, const int sumOfCred=0);//add student
    void signUpCourse(const string Id, const int courseId);//try&catch, add student to course
    bool isExist(const string Id);
    void deleteStudent(const string Id);//remove student by ID -the function must contain remove from all the courses
};

