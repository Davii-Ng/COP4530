#include <iostream>
#include <string>
using namespace std;

// Person is the common base class for everyone in the university model.
class Person {
public:
    string name;
    string email;
    string gender;
};

// A faculty member is a person who works for a department.
class Faculty : public Person {
public:
    string employeeID;
    string department;
};

// A student is a person with academic information.
class Student : public Person {
public:
    string major;
    string minor;
    float GPA;
    string studentID;
};

// An undergraduate student is a student with a class standing.
class UndergraduateStudent : public Student {
public:
    string standing;   // Freshman, Sophomore, Junior, or Senior
};

// A graduate student is a student with a research area.
class GraduateStudent : public Student {
public:
    string researchArea;
};

// A professor is faculty with an academic rank and research specialty.
class Professor : public Faculty {
public:
    string rank;          // Assistant, Associate, or Full Professor
    string researchArea;
};

// An instructor is faculty with a list of courses taught.
class Instructor : public Faculty {
public:
    string coursesTaught;
};

int main() {
    // The class declarations are the deliverable for this section. These
    // objects verify that every requested type can be instantiated.
    Person person;
    Student student;
    Faculty faculty;
    UndergraduateStudent undergraduate;
    GraduateStudent graduate;
    Professor professor;
    Instructor instructor;

    (void)person;
    (void)student;
    (void)faculty;
    (void)undergraduate;
    (void)graduate;
    (void)professor;
    (void)instructor;

    return 0;
}
