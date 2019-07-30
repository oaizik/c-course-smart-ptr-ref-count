#include "course.h"



Course::Course(const int cID):courseId(cID),list(0)//list must point to null if there is no elements in the list
{
}



Course::~Course(){
    nodeType<Student>* toDelete;
    while (list != 0) {
        toDelete = list;
        list = list->next;
        delete list;
    }
}
int Course::getCourseId() {
    return courseId;
}
void Course:: endOfCourse(){
    nodeType<Student>*curNode ,*nextNode;
    curNode = list;
    while(curNode) {
        curNode->Val->addCredits(numOfCredits);
        nextNode = curNode->next;
        delete curNode;
        curNode = nextNode;
    }
    list = 0;
}
void Course:: addStudent( RCPtr<Student>& NStudent) {
    nodeType<Student>* newNode = new nodeType<Student>(NStudent,list);
    if (newNode != 0)//in case of successful allocation
        list = newNode;
    else
        throw exception_ptr();
}
void Course::updateCourseDetails(const int courseId, const int numOfCred, const string courseName, const string depName) {
    numOfCredits = numOfCred;
    this->courseName = courseName;
    department = depName;
}
string Course:: getCourseDepartment() {
    return department;}
void Course:: graduateStudent(const string Id,bool graduate) {
    if (list == 0)
        return;
    nodeType<Student>* prev, *cur;
    if (Id == list->Val->getStudentId()) {
        cur = list;
        list = list->next;
    }
    else {
        prev = list;
        cur = prev->next;
        while (cur != 0) {
            if (cur->Val->getStudentId() == Id) {
                break;
            }
            prev = cur;
            cur = cur->next;
        }
        if (cur == 0)
            return;
    }
    if (graduate == true) {
        cur->Val->addCredits(numOfCredits);
    }
    delete cur;

}
void Course::printCourseDetails(ostream& out) {
    out << "course name:" << courseName << endl
        << "course department" << department << endl
        << "course ID:" << courseId << endl
        << "number of credits:" << numOfCredits << endl
        << "students:" << endl;
    nodeType<Student>* cur = list;
    if (cur == 0) {
        out << "There are no students enrolled in this course" << endl;
    }
    else {
        while (cur != 0) {
            cur->Val->printStudentDetails(out);
            cur = cur->next;
        }
    }
}
