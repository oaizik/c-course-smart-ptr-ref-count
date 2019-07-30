#pragma once
#include<iostream>
#include<string>
#include"smartPtr.h"
#include"department.h"
#include"course.h"
#include"student.h"
#include"studentsCycle.h"
#include<vector>
using namespace std;
class College{
private:
    string collegeName;
    nodeType<Course>* coursesList;
    vector<Department> departments;
    vector<StudentsCycle> cycles;//student cycle vector
    string findCourseDepartment(const int& courseId);
    nodeType<Course>* getCourseById(const int courseId);
public:
	College(const string name="");
    void updateCollegeName(const string& name);
	~College();
    void addDepartment(string depName);//add department
    void addStudent(const string fName, const string lName, const string ID,const int rYear, const string studAd, const string dep,const int sumOfCred=0);//add student
    void addCourse(const int courseId);//add course
    bool updateCourseDetails(const int courseId,const int numOfCred,const string courseName,const string depName);//update course detailes and chaining to the relevant department
    void signUpCourse(const string id, const int courseId);//sign up student
    void completionCourse(const int courseId);
    void graduateStudent(const string Id, const int courseId);
    void removeStudent(const string Id, const int courseId);
    void deleteStudent(const string Id,const int cycle);
    void printDepartmentCycleDetailses(ostream& out, const string& department, int cycle);
    void printCourseDetails(ostream& out,const int);
};

