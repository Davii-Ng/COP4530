#include <iostream>
#include <string>
using namespace std;

// Person is the base class.
// It contains information that is common to every person.
class Person {
public:
    string name;
    string email;
    string gender;
};

// Faculty is derived from Person.
// A Faculty member IS-A Person, so it inherits name, email, and gender.
// Faculty adds information specific to university employees.
class Faculty : public Person {
public:
    string employeeID;
    string department;
};

// Student is also derived from Person.
// A Student IS-A Person and inherits the common Person variables.
// Student adds academic information.
class Student : public Person {
public:
    string major;
    string minor;
    float GPA;
    string studentID;
};

// UndergraduateStudent is derived from Student.
// An UndergraduateStudent IS-A Student, so it also indirectly inherits
// all variables from Person.
class UndergraduateStudent : public Student {
public:
    string standing;   // Freshman, Sophomore, Junior, or Senior
};

// GraduateStudent is derived from Student.
// A GraduateStudent IS-A Student and may have a specific research area.
class GraduateStudent : public Student {
public:
    string researchArea;
};

// Professor is derived from Faculty.
// A Professor IS-A Faculty member and therefore also IS-A Person.
// Professors may have an academic rank and a research specialty.
class Professor : public Faculty {
public:
    string rank;          // Assistant, Associate, or Full Professor
    string researchArea;
};

// Instructor is derived from Faculty.
// An Instructor IS-A Faculty member and inherits Faculty and Person data.
// The instructor-specific variable stores the courses they teach.
class Instructor : public Faculty {
public:
    string coursesTaught;
};

int main() {
    return 0;
}