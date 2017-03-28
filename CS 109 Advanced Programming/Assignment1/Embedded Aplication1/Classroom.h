#ifndef CLASSROOM_H
#define CLASSROOM_H

#include <iostream>
#include <cstdlib>


class Classroom
{
public:
    Classroom();
    void checkInStudent (int classNumber, int studentId);
    void checkOutStudent (int classNumber, int studentId);
    bool isOccupaied (int classNumber, int studentId);
    bool isStudentInAnyClass(int id, int& cls);
    int nrOpenSeats ();
    int nrStudentsInClassNr(int classNr);
    int nrStudentsInAllClasses();
    void printClass();
    virtual ~Classroom();

private:
    const int classSize = 256;
    const int nrOfClasses = 8;
    bool** classPtr;
    int nrStudents;
};

#endif // CLASSROOM_H
