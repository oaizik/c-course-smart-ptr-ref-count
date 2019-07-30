#include "studentsCycle.h"



StudentsCycle::StudentsCycle(int start) :startYear(start),
numOfStarted(0),numOfStudents(0),
numOfFinished(0),studentsList(0), finishedStudents(0)
{}
StudentsCycle::~StudentsCycle() {
    nodeType<Student>*toDeleteStudent;
    while (studentsList != 0) {
        toDeleteStudent = studentsList;
        studentsList = studentsList->next;
        delete toDeleteStudent;
    }
    while (finishedStudents != 0) {
        toDeleteStudent = finishedStudents;
        finishedStudents = finishedStudents->next;
        delete toDeleteStudent;
    }
}
int StudentsCycle::getStartYear() {
    return startYear;
}

void StudentsCycle:: addStudent(RCPtr<Student>& nStudent) {
    nodeType<Student>* newStudent=new nodeType<Student>(nStudent,studentsList);
    if (newStudent != 0)
        studentsList = newStudent;
    numOfStarted++;
    numOfStudents++;
}

string StudentsCycle:: getStudentDepartment(const string Id) {
    nodeType<Student>* cur = studentsList;
    while (cur != 0) {
        if (cur->Val->getStudentId() == Id)
            return cur->Val->getStudentDepartment();
        cur = cur->next;
    }
    return "";
}
bool StudentsCycle::isExist(const string Id) {
    nodeType<Student>* cur = studentsList;
    while (cur != 0) {
        if (cur->Val->getStudentId() == Id)
            return true;
        cur = cur->next;
    }
    return false;
}

void StudentsCycle::deleteStudent(const string Id) {
    if (studentsList == 0)
        return;
    bool studentFound = false;
    nodeType<Student>  *prev = studentsList,*cur=studentsList->next;
    if (prev->Val->getStudentId() == Id) {
        studentsList = cur;
        delete prev;
        studentFound = true;
    }
    else {
        while (cur != 0)
        {
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
    --numOfStudents;
}
void StudentsCycle::checkGraduates() {
    if (studentsList == 0)
        return;
    nodeType<Student>* prev = studentsList, *cur =prev->next;
    while(prev != 0 && prev->Val->getCredits() >= 160) {
        studentsList = cur;
        prev->next = finishedStudents;
        finishedStudents = prev;
        prev = studentsList;
        if(prev!=0)
            cur = prev->next;
        --numOfStudents;
    }
    if (studentsList == 0)
        return;
    
    while (cur!=0){
        if (cur->Val->getCredits() >= 160)
        {
            prev->next = cur->next;
            cur->next = finishedStudents;
            finishedStudents = cur;
            cur = prev->next;
            --numOfStudents;
        }
        prev = cur;
        cur = cur->next;
    }

}
void StudentsCycle::printCycleDetailes(ostream& out, const string& department) {
    checkGraduates();
    nodeType<Student>*cur = finishedStudents;
    int finish = 0;
    while (cur!=0){
        if (cur->Val->getStudentDepartment() == department)
            ++finish;
        cur = cur->next;
    }
    out << "number of students who started:"  << numOfStarted  << "." << endl
        << "number of student  who learning:" << numOfStudents << "." << endl
        << "number of students who finished:" << finish << "."        << endl;
}

