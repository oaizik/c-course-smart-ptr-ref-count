#include "student.h"
using namespace std;


Student:: Student(const string fName, const string lName, const string iD, const int rYear, const string studentAdd,
    const string dep, const int CredSum ) :
    firstName(fName),lastName(lName),id(iD),studentAddress(studentAdd),
    regYear(rYear),department(dep),
    sumOfCredits ((CredSum < 0 ? 0 : CredSum)),graduate(false){}

Student::~Student()
{
}
void Student::addCredits(const int amount) {
    sumOfCredits += amount;
}
string Student::getStudentId() { return id; }
string Student::getStudentDepartment() { return department; }
int Student:: getCredits() {
    return sumOfCredits;
}
bool Student:: getGraduate(){
    return graduate;
}
void Student:: setGraduate(){
    graduate = true;
}
void Student::printStudentDetails(ostream& out) {
    out << "first name:"<< firstName<<endl
        << "last name:"<< lastName<< endl
        << "ID:"<<id <<endl
        << "Year of registration:"<< regYear<<endl
        << "address:"<< studentAddress<<endl
        << "department:"<< department<<endl
        << "credits:"<< sumOfCredits<<endl;
}
