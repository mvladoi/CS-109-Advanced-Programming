


#include <iostream>
#include <limits>
#include <cstdlib>

#include "Inventory.h"



int main()
{
    Inventory inventory;
    bool value = true;
    int option;

    std::cout << "The Inventory has 256 products.\n"
              << "Each product has an ID from 0 to 255.\n"
              << "Each product has 6 colors \n ( red = 0, green = 1, yellow = 2,"
              << "orange = 3, blue = 4, purple = 5, black = 6, white = 7)\n"
              << "The Inventory support the following functionality:\n";


    while (value)
    {

        std::cout << "\n0. Exit the program.\n"
                  << "1. Check in Product.\n"
                  << "2. Check out Product.\n"
                  << "3. Checks if a specific product and/or color exists in the inventory.\n"
                  << "4. How many items exist for a specific product ID.\n"
                  << "5. How many items exist for a specific product ID of a specific color.\n"
                  << "6. How many items exist for a specific product color; cross products.\n"
                  << "7. Number of product types having stock in the inventory.\n"
                  << "8. Print the Inventory.\n\n";



        std::cout   << "\nType the number between 0-8 to choose your option: ";
        std::cin >> option;
        if (std::cin.fail())
        {
            std::cerr << "Error, wrong input.\n";
            break;
        }

        if (option < 0 || option > 8)
        {
            std::cout << "Please enter an option between 0 and 8.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if(option == 0)
        {
            value = false;
            break;
        }

        else if(option == 1)
        {
            std::cout << "Please enter the Product ID (0-255) to check in: ";
            int product;
            std::cin >> product;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }
            while (product < 0 || product > 255)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the Product ID (0-255) to check in: ";
                std::cin >> product;

            }

            std::cout << "Please enter the color of Product (0-7)\n"
                      <<  "(red = 0, green = 1, yellow = 2, orange = 3, blue = 4, purple = 5, black = 6, white = 7) to check in: ";
            int a = -1;
            std::cin >> a;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }

            while (a < 0 || a > 7)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the color of Product\n"
                          <<  "(red, green, yellow, orange, blue, purple,black,white) to check in: ";
                std::cin >> a;

            }


            if (inventory.checkedInProduct(product,a))
            {
                std::cout << "The Product Id:" << product << " has been added to the inventory.\n";
            }
            else
            {
                std::cout << "The Product Id:" << product << " has not been added to the inventory.\n";
            }
        }

        else if(option == 2)
        {
            std::cout << "Please enter the Product ID (0-255) to check out: ";
            int product;
            std::cin >> product;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }
            while (product < 0 || product > 255)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the Product ID (0-255) to check out: ";
                std::cin >> product;

            }
            std::cout << "Please enter the color of Product (0-7)\n"
                      <<  "(red = 0, green = 1, yellow = 2, orange = 3, blue = 4, purple = 5, black = 6, white = 7) to check in: ";
            int a = -1;
            std::cin >> a;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }

            while (a < 0 || a > 7)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the color of Product\n"
                          <<  "(red, green, yellow, orange, blue, purple,black,white) to check in: ";
                std::cin >> a;

            }
            if ( inventory.checkedOutProduct(product,a))
            {
                std::cout << "The Product Id:" << product << " has been removed from the Inventory.\n";
            }
            else
            {

                std::cout << "The Product Id:" << product << " has not been removed from the Inventory.\n";
            }

        }

        else if(option == 3)
        {
            std::cout << "Please enter the Product ID (0-255) that you want to check: ";
            int product;
            std::cin >> product;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }
            while (product < 0 || product > 255)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the Product ID (0-255) to check out: ";
                std::cin >> product;

            }
            std::cout << "Please enter the color of Product (0-7)\n"
                      <<  "(red = 0, green = 1, yellow = 2, orange = 3, blue = 4, purple = 5, black = 6, white = 7) to check in: ";
            int a = -1;
            std::cin >> a;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }

            while (a < 0 || a > 7)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the color of Product\n"
                          <<  "(red, green, yellow, orange, blue, purple,black,white) to check in: ";
                std::cin >> a;
            }

            if (inventory.checkProductOfColor(product,a))
            {
                std::cout << "The Product Id:" << product << " of color " << a << " is part of the inventory.\n";
            }
            else
            {
                std::cout << "The Product Id:" << product << " of color " << a << " is not part of the inventory.\n";
            }



        }

        else if(option == 4)
        {

            std::cout << "Please enter the Product ID (0-255) to check the nr of items in Inventory: ";
            int product;
            std::cin >> product;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }
            while (product < 0 || product > 255)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the Product ID (0-255) to check the nr of items in Inventory: ";
                std::cin >> product;

            }

            std::cout << "The product ID:" << product << " has "
                      << inventory.nrProductsForId(product) << " items in Inventory.\n";

        }

        else if (option == 5)
        {
            std::cout << "Please enter the Product ID (0-255) to check nr of items: ";
            int product;
            std::cin >> product;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }
            while (product < 0 || product > 255)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Please enter the Product ID (0-255) to check nr of items: ";
                std::cin >> product;

            }
            std::cout << "Please enter the color of Product (0-7)\n"
                      <<  "(red = 0, green = 1, yellow = 2, orange = 3, blue = 4, purple = 5, black = 6, white = 7) to check in: ";
            int a = -1;
            std::cin >> a;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }

            std::cout << "The product ID:" << product << " of color:" << a <<  " has "
                      << inventory.nrProductsForSpecificId(product,a) << " items in Inventory.\n";


        }


        else if(option == 6)
        {

            std::cout << "Please enter the color of Product (0-7) to check the nr of products per color\n"
                      <<  "(red = 0, green = 1, yellow = 2, orange = 3, blue = 4, purple = 5, black = 6, white = 7) to check in: ";
            int a = -1;
            std::cin >> a;
            if (std::cin.fail())
            {
                std::cerr << "Error, wrong input.\n";
                break;
            }

            std::cout << "The color:" << a << " has "
                      << inventory.nrProductsPerColor(a) << " items in Inventory.\n";

        }

        else if (option == 7)
        {
            std::cout << "There are " << inventory.nrProductsType() << " products type in Inventory./n";

        }


        else if(option == 8)
        {
            inventory.printInventory();
        }

    }


    return 0;
}
