#include "college.h"
#include<fstream>
using namespace std;
bool initSystem(const string& initFileName, College& col);
bool simulation(const string& simulationFileName, College&col,ostream& out);
int main(int argc, char *argv[]) {
    College col;
    ofstream out(argv[3]);
    try { initSystem(argv[1], col); }
    catch(exception){

    }
    simulation(argv[2], col, (out.is_open() ? out:cout));
    out.close();
    return 0;

}
bool simulation(const string& simulationFileName, College&col,ostream& out) {
    ifstream simulationFile(simulationFileName);
    string line, parameter[6];
    int identifier;
    size_t lastDelimiter, start, end, i;
    if(!simulationFile.is_open())
        throw exception("can't find simulation file");
    while (getline(simulationFile, line)) {
        if (line[0] == '\n' ||line[0]=='\0'|| line[0] == '#')
            continue;
        i = 0;
        identifier = stoi(line.substr(0, lastDelimiter = line.find(',', 0)));
        start = lastDelimiter + 1;
        end = line.find(',', start);
        while (end!=-1) {
            parameter[i] = line.substr(start, end - start);
            start = end + 1;
            end = line.find(',', start);
            ++i;
        }
        parameter[i] = line.substr(start);
        switch (identifier) {
        case 1:
            col.addStudent(parameter[0], parameter[1], parameter[2], stoi(parameter[4]), parameter[3], parameter[5]);
            break;
        case 2:
            col.signUpCourse(parameter[0], stoi(parameter[1]));
            break;
        case 3:
            col.completionCourse(stoi(parameter[0]));
            break;
        case 4:
            col.graduateStudent(parameter[0], stoi(parameter[1]));
            break;
        case 5:
            col.removeStudent(parameter[0], stoi(parameter[1]));
            break;
        case 6:
            col.deleteStudent(parameter[0], stoi(parameter[1]));
            break;
        case 7:
            col.printDepartmentCycleDetailses(out, parameter[0], stoi(parameter[1]));
            break;
        case 8:
            col.printCourseDetails(out,stoi(parameter[0]));
            break;
        default:
            out << "invalid operation code" << endl;
            break;
        }
    }
    simulationFile.close();
    return true;
}
bool initSystem(const string& initFileName,College& col) {
    ifstream initFile(initFileName);
    string line,identifier,parameter[4];
    size_t lastDelimiter,start,end,i;
    if (!initFile.is_open())
        throw exception("can't find initialization file");
    while (getline(initFile, line)) {
        if (line[0] == '\n' || line[0] == '#')
            continue;
        identifier = line.substr(0, lastDelimiter = line.find(':', 0));
        if (identifier=="College") {
            parameter[0] = line.substr(lastDelimiter+1);
            col.updateCollegeName(parameter[0]);
        }
        else if(identifier=="Departments"){
            start = lastDelimiter+1;
            end = line.find(',', start);
            
            while(end!=-1){
                parameter[0] = line.substr(start, end - start);
                col.addDepartment(parameter[0]);
                start = end + 1;
                end = line.find(',', start);
            }
            parameter[0] = line.substr(start);
            col.addDepartment(parameter[0]);   
        }
        else if (identifier == "CollageCoursesList") {
            start = lastDelimiter + 1;
            end = line.find(',', start);
            while (end != -1) {
                parameter[0] = line.substr(start, end - start);
                col.addCourse(stoi(parameter[0]));
                start = end + 1;
                end = line.find(',', start);
            }
            parameter[0] = line.substr(start);
            col.addCourse(stoi(parameter[0]));
        }
        else if (identifier == "CourseDetails") {
            start = lastDelimiter + 1;
            end = line.find(',', start);
            i = 0;
            while (end != -1) {
                parameter[i]= line.substr(start, end - start);
                start = end + 1;
                end = line.find(',', start);
                ++i;
            }
            parameter[i] = line.substr(start);
            col.updateCourseDetails(stoi(parameter[0]), stoi(parameter[2]), parameter[3], parameter[1]);
        }
    }
    initFile.close();
    return true;
}
