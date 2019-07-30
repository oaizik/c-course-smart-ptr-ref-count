#include "college.h"



College::College(const string name):collegeName(name),coursesList(0){}

void College::addDepartment(string depName) {
    departments.push_back(Department(depName));
}
void College:: addCourse(const int courseId) {
    Course* ptr = new Course(courseId);
    if (ptr != 0) {
        nodeType<Course>* nNode = new nodeType<Course>(ptr, coursesList);
        coursesList = nNode;
    }
}
bool College::updateCourseDetails(const int courseId, const int numOfCred, const string courseName, const string depName) {
    nodeType<Course>* cur = coursesList;
    size_t i,size;
    while (cur != 0) {
        if (courseId == cur->Val->getCourseId()) {
            cur->Val->updateCourseDetails(courseId, numOfCred, courseName, depName);
            for (i = 0, size = departments.size(); i < size; ++i) {//find the department
                if (departments[i].getDepartmentName() == depName) {
                    departments[i].addCourse(cur->Val);//chain the course to the head of the depattment's courses list
                    return true;
                }
            }
        }
        cur = cur->next;
    }
    return false;
}

College::~College()
{
    nodeType<Course>* curCourseList, *nextCourseList;
    curCourseList = coursesList;
    while (curCourseList)
    {
        nextCourseList = curCourseList->next;
        delete curCourseList;
        curCourseList = nextCourseList;
    }
    
}
void College::addStudent(const string fName, const string lName, const string ID, const int rYear, const string studAd, const string dep, const int sumOfCred) {
    size_t i, size;
    bool addedTodep = false,addedTocyc=false;
    for (i = 0, size = departments.size(); i < size;++i){//add to department
        if (departments[i].getDepartmentName() == dep) {
            addedTodep = true;
            break;
        }
    }
    if (!addedTodep)
        return;
    RCPtr<Student>&nStudent = departments[i].addStudent(fName, lName, ID, rYear, studAd, dep, sumOfCred);
    for (i = 0, size = cycles.size(); i < size; ++i) {//add to student cycle
        if (rYear == cycles[i].getStartYear()) {
            cycles[i].addStudent(nStudent);
            addedTocyc = true;
            break;
        }
    }
    if (!addedTocyc) {
        cycles.push_back(rYear);
        cycles[cycles.size() - 1].addStudent(nStudent);
    }
}
string College::findCourseDepartment(const int& courseId) {
    nodeType<Course>* cur = coursesList;
    while (cur != 0) {
        if (cur->Val->getCourseId() == courseId)
            return cur->Val->getCourseDepartment();

        cur = cur->next;
    }
    return "";//empty string course is not exist;

}
void College::signUpCourse(const string id, const int courseId) {
    string courseDepartment = findCourseDepartment(courseId);
    if (courseDepartment == "")
        return;
    bool departmentFound = false;
    size_t i, size;
    for (i=0,size=departments.size();i<size;++i) {
        if (departments[i].getDepartmentName() == courseDepartment) {
            departmentFound = true;
            break;
        }
    }
    if (!departmentFound)
        return;
    try{
        departments[i].signUpCourse(id, courseId);
    }
    catch (exception()) {
        return;
    }

}
nodeType<Course>* College::getCourseById(const int courseId) {
    nodeType<Course>* curCourse = coursesList;
    while (curCourse != 0) {
        if (curCourse->Val->getCourseId() == courseId)
            return curCourse;
        curCourse = curCourse->next;
    }
    return 0;
}
void College:: completionCourse(const int courseId) {
    nodeType<Course>* curCourse = getCourseById(courseId);
    if (!curCourse)
        return;
    curCourse->Val->endOfCourse();
}
void College:: graduateStudent(const string Id, const int courseId) {
    nodeType<Course>* curCourse = getCourseById(courseId);
    if (!curCourse)
        return;
    curCourse->Val->graduateStudent(Id, true);
}
void College:: removeStudent(const string Id, const int courseId) {
    nodeType<Course>* curCourse = getCourseById(courseId);
    if (!curCourse)
        return;
    curCourse->Val->graduateStudent(Id, false);
}
void College:: deleteStudent(const string Id, const int cycle) {
    size_t i,j, cyclesSize,depatrmentsSize;
    string studentDepartment = "";
    for (i = 0, cyclesSize = cycles.size(); i < cyclesSize; ++i) {
        if (cycles[i].getStartYear() == cycle) {
            if (cycles[i].isExist(Id)) {
                studentDepartment = cycles[i].getStudentDepartment(Id);
                break;
            }
        }
    }
    if (studentDepartment == "")//in case the student is not exist in the cycle or the cycle is not exist
        return;
    cycles[i].deleteStudent(Id);
    for (j = 0, depatrmentsSize =departments.size(); j < depatrmentsSize; ++j) {
        if (departments[j].isExist(Id) == true) {
            departments[j].deleteStudent(Id);
            break;
        }
    }
}
void College::printDepartmentCycleDetailses(ostream& out, const string& department, int cycle) {
    size_t i ,size;
    for (i = 0, size = cycles.size(); i < size; ++i) {
        if (cycles[i].getStartYear() == cycle) {
            cycles[i].printCycleDetailes(out, department);
            return;
        }
    }
    out << "cycle "<<cycle<<" is not found"<<endl;
}
void College:: printCourseDetails(ostream& out, const int courseId) {
    nodeType<Course>* cur = coursesList;
    while (cur != 0) {
        if (cur->Val->getCourseId() == courseId) {
            cur->Val->printCourseDetails(out);
            return;
        }
        cur = cur->next;
    }
    out << "can't find this course ID" << endl;
}
void College::updateCollegeName(const string& name) { collegeName = name; }

