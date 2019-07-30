#pragma once
#include <string>
#include "student.h"
#include"smartPtr.h"
using namespace std;

class Course: public RCObject{
private:
    int courseId;
    int numOfCredits;
    string courseName;
    string department;
    nodeType<Student>* list;//list of students
public:
    string getCourseDepartment();
    void printCourseDetails(ostream& out);
	Course(const int cID);
	~Course();
    int getCourseId();
    void updateCourseDetails(const int courseId, const int numOfCred, const string courseName, const string depName);
    void addStudent( RCPtr<Student>& NStudent);//try&catch
    void endOfCourse();
    void graduateStudent(const string Id, bool graduate);
};

