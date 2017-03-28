#include "Classroom.h"

Classroom::Classroom()
{

    classPtr = new bool* [nrOfClasses+1];
    for (int i = 0; i <= nrOfClasses; i++){

    classPtr[i] = new bool [classSize+1];
    for (int j = 0; j <= classSize; j++)
    {
        classPtr [i][j] = false;
    }
    }
    nrStudents = 0;
}

Classroom::~Classroom()
{

    for (int i = 0; i <= nrOfClasses; i++){

     delete [] classPtr[i];
    }

    delete []classPtr;
}



void Classroom::printClass()
{


    for (int i = 1; i <= nrOfClasses; i++)
    {
        std:: cout << "ClassNr: " << i << " ";
        std::cout << "[ ";
        for (int j = 0 ; j < classSize; j++)
        {
            if(classPtr[i][j])
            std::cout << j << " ";
        }
      std::cout << "]";
      std::cout << "\n";
    }
    std::cout << "\n";
}


void Classroom::checkInStudent(int classNumber, int studentId)
{
    if (classNumber < 1 || classNumber > 8)
    {
        std::cerr << "Class Nr out of bounds.\n";
        exit(EXIT_FAILURE);
    }

    if (studentId < 1 || studentId > 256){
        std::cerr << "Student Id out of bounds.\n";
        exit(EXIT_FAILURE);
    }
    if (isOccupaied(classNumber, studentId)){
        std::cerr << "The student: " << studentId << " ID "
        << "is already in class: " << classNumber << ".\n";
        nrStudents--;
    }

    classPtr[classNumber][studentId] = true;
    nrStudents++;

}

bool Classroom::isOccupaied (int classNumber, int studentId)
{
    if (classNumber < 1 || classNumber > 8)
    {
        std::cerr << "Class Nr out of bounds.\n";
        exit(EXIT_FAILURE);
    }

    if (studentId < 1 || studentId > 256){
        std::cerr << "Student Id out of bounds.\n";
        exit(EXIT_FAILURE);
    }
    return classPtr[classNumber][studentId];
}



void Classroom::checkOutStudent ( int classNumber,int studentId)
{
   if (classNumber < 1 || classNumber > 8)
    {
        std::cerr << "Class Nr out of bounds.\n";
        exit(EXIT_FAILURE);
    }

    if (studentId < 1 || studentId > 256){
        std::cerr << "Student Id out of bounds.\n";
        exit(EXIT_FAILURE);
    }
    if (!isOccupaied(classNumber, studentId)){
        std::cerr << "The student: " << studentId << " ID "
        << "is not in class: " << classNumber << ".\n";
        nrStudents++;
    }



        classPtr[classNumber][studentId] = false;
        nrStudents--;
    }


bool Classroom::isStudentInAnyClass(int studentId, int&cls){

if (studentId < 1 || studentId > 256){
        std::cerr << "Student Id out of bounds.\n";
        exit(EXIT_FAILURE);
    }
    bool result = false;
    for(int i = 1; i <= nrOfClasses; i++){
        result = result || isOccupaied(i,studentId);
        if(result){
        cls = i;
        return result;
        }
    }
    return false;


}

int Classroom::nrStudentsInAllClasses()
{
    return nrStudents;
}


int Classroom::nrStudentsInClassNr(int classNr){
if (classNr < 1 || classNr > 8)
    {
        std::cerr << "Class Nr out of bounds.\n";
        exit(EXIT_FAILURE);
    }
int nrStudents = 0;
for (int i = 1; i < classSize; i++){
    if(classPtr[classNr][i])
        nrStudents++;
}
return nrStudents;

}

/*
int Classroom::nrOpenSeats()
{
    return (size - nrStudents);
}


void Classroom::printClass()
{
    std::cout << "[ ";
    for (int i = 0; i < nrOfClasses; i++)
    {
        //if (students[i])
        for (int j = 0 ; j < ClassSize; j++)
        {
            std::cout << classPtr[i][j] << " ";
        }
      std::cout << "]";
    }
    std::cout << "\n";
}
*/
