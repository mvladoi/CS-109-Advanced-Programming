
#include <iostream>
#include <limits>
#include <cstdlib>

#include "Classroom.h"







int main()
{
    Classroom Classes;

    bool value = true;
    int option;


    std::cout << "There are 8 classes available.\n"
              << "Each Classroom has 256 students.\n"
              << "Each student has an ID from 1 to 256.\n"
              << "Each Classroom support the following functionality:\n"
              << "0. Exit the program.\n"
              << "1. Check in Student.\n"
              << "2. Check out Student.\n"
              << "3. Check if the Student is in any class.\n"
              << "4. How many Students are in class Number#.\n"
              << "5. How many available Seats are in class .\n"
              << "6. Print the students Id that are in the class.\n\n";

    while (value)
    {
        std::cout   << "\nType the number between 0-6 to choose your option: ";
        std::cin >> option;
        if (std::cin.fail())
        {
            std::cerr << "Error, wrong input.\n";
            break;
        }

        if (option < 0 || option > 6)
        {
            std::cout << "Please enter an option between 0 and 6.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if(option == 0)
        {
            break;

        }

        else if(option == 1)
        {
            std::cout << "Please enter the class Number (1-8): ";
            int classNr;
            std::cin >> classNr;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }
            while (classNr < 1 || classNr > 8)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the class Number (1-8) to check in: ";
                std::cin >> classNr;

            }

            std::cout << "Please enter the student Id to check in (1-256): ";
            int id;
            std::cin >> id;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }
            while (id < 1 || id > 256)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the studentId (1-256) to check in: ";
                std::cin >> id;

            }




            if ( Classes.isOccupaied(classNr, id) )
            {
                std::cout << "The Student Id:" << id << " is already in the Class Nr:"
                          << classNr << ".\n";
            }
            else
            {
                int cls = 0;

                if(!Classes.isStudentInAnyClass(id, cls))
                {
                    Classes.checkInStudent(classNr,id);
                    std::cout << "The Student Id:" << id << " check in the Class Nr:"
                              << classNr << ".\n";
                }
                else
                {
                    std::cout << "The Student Id:" << id << " is already in the Class Nr:"
                              << cls << ". Can not check in again.\n";
                }
            }

        }
        else if(option == 2)
        {
            std::cout << "Please enter the class Number (1-8): ";
            int classNr;
            std::cin >> classNr;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }
            while (classNr < 1 || classNr > 8)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the class Number (1-8) to check in: ";
                std::cin >> classNr;

            }

            std::cout << "Please enter the student Id to check out(1-256): ";
            int id;
            std::cin >> id;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }
            while (id < 1 || id > 256)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the studentId (1-256) to check in: ";
                std::cin >> id;

            }

            if ( !Classes.isOccupaied(classNr, id) )
            {
                std::cout << "The Student Id:" << id << " is not in the Class Nr:"
                          << classNr << ".\n";
            }
            else
            {
                Classes.checkOutStudent(classNr,id);
                std::cout << "The Student Id:" << id << " check out the Class Nr:"
                          << classNr << ".\n";
            }

        }


        else if(option == 3)
        {


            std::cout << "Please enter the student Id to check if is present in any class(1-256): ";
            int id;
            std::cin >> id;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }
            while (id < 1 || id > 256)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the studentId (1-256) to check in: ";
                std::cin >> id;

            }



            int cls = 0;
            if ( Classes.isStudentInAnyClass (id, cls) )
            {
                std::cout << "The Student Id:" << id << " is already in the Class Nr:"
                          << cls << ".\n";
            }
            else
            {

                std::cout << "The Student Id:" << id << "is not in the any Class.\n";

            }

        }

        else if(option == 4)
        {

            std::cout << "Please enter the class Number (1-8) to check how many students there are in class: ";
            int classNr;
            std::cin >> classNr;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }
            while (classNr < 1 || classNr > 8)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the class Number (1-8) to check how many students there are in class: ";
                std::cin >> classNr;

            }

            std::cout << "There are " << Classes.nrStudentsInClassNr(classNr)
                      << " students in Class nr:" << classNr << ".\n";
        }
        /*
                else if (option == 5)
                {
                    std::cout << "In the History Class there are " << history.nrOpenSeats()
                              << " open seats.\n";
                }
                */

        else if (option == 6)
        {
            Classes.printClass();
        }


    }

    return 0;
}
