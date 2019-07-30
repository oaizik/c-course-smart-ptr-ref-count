#include "department.h"



Department::Department(string depName)
:departmentName(depName),coursesList(0),studentsList(0){}
Department::~Department(){
    nodeType<Course>* toDelete ;
    while (coursesList != 0) {
        toDelete = coursesList;
        coursesList = coursesList->next;
        delete toDelete;
    }
    nodeType<Student>* toDeleteStudent ;
    while (studentsList != 0) {
        toDeleteStudent = studentsList;
        studentsList = studentsList->next;
        delete toDeleteStudent;
    }
}
string Department::getDepartmentName() {
    return departmentName;
}
bool Department::addCourse(RCPtr<Course>& newCourse) {
    nodeType<Course>* newNode = new nodeType<Course>(newCourse, coursesList);
    if (newNode != 0) {
        coursesList = newNode;
        return true;
    }
    return false;
}
RCPtr<Student>& Department:: addStudent(const string fName, const string lName, const string ID, const int rYear, const string studAd, const string dep, const int sumOfCred) {
    Student* nStudent = new Student(fName, lName, ID, rYear, studAd, dep);
    nodeType<Student>*newNode = 0;
    if (nStudent != 0) {
        newNode = new nodeType<Student>(nStudent, studentsList);
        if (newNode != 0) {
            studentsList = newNode;
            return newNode->Val;
        }
    }   
}
void Department::signUpCourse(const string Id, const int courseId) {
    nodeType<Course>*curCourse = coursesList;
    bool courseFound = false;
    while (curCourse) {
        if (curCourse->Val->getCourseId() == courseId) {
            courseFound = true;
            break;
        }
        curCourse = curCourse->next;
    }
    if (!courseFound)
        throw exception();
    nodeType<Student>*curStudent = studentsList;
    bool studentFound = false;
    while (curStudent) {
        if (curStudent->Val->getStudentId() == Id) {
            studentFound = true;
            break;
        }
        curStudent = curStudent->next;
    }
    if (!studentFound)
        throw exception();
    try {
        curCourse->Val->addStudent(curStudent->Val);
    }
    catch (exception_ptr()) {
        return;
    }
}
bool Department::isExist(const string Id) {
    nodeType<Student>* cur = studentsList;
    while (cur!=0)
    {
        if (cur->Val->getStudentId()==Id)
        {
            return true;
        }
        cur = cur->next;
    }
    return false;
}
void Department::deleteStudent(const string Id) {
    if (studentsList == 0)
        return;
    nodeType<Student>* cur = studentsList->next , *prev = studentsList;
    bool studentFound = false;
    if (prev->Val->getStudentId() == Id) {
        studentsList = cur;
        delete prev;
        studentFound = true; 
    }
    else{
        while (cur != 0) {
            if (cur->Val->getStudentId() == Id) {
                prev->next = cur->next;
                delete cur;
                studentFound = true;
                break;
            }
            prev = cur;
            cur = cur->next;
        }
    }
    if (!studentFound)
        return;
    nodeType<Course>*curCourse = coursesList;
    while (curCourse != 0) {
        curCourse->Val->graduateStudent(Id, false);
        curCourse = curCourse->next;
    }
}

