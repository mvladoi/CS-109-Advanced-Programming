#include "Inventory.h"
#include <iostream>



Inventory::Inventory()
{
    products = new unsigned char* [nrColors];
    for (int i= 0; i < nrColors; i++)
    {
        products[i] = new unsigned char [nrProducts];
    }

    for (int i= 0; i < nrColors; i++)
    {
        for (int j = 0; j < nrProducts; j++)
        {
            products[i][j] = 0;
        }
    }


}






Inventory::~Inventory()
{
    for (int i= 0; i < nrColors; i++)
    {

        delete [] products[i];

    }
    delete [] products;
}








void Inventory::printInventory()
{
    for (int i = 0; i < nrColors; i++)
    {
        std::cout << i << ": [ ";

        for (int j = 0; j < nrProducts; j++)
        {
            if(products[i][j] != 0)
            {
                std::cout << "ID:" << j << "=" << (int) products[i][j] << " ";

            }
        }
        std:: cout << "]\n";
    }
}








bool Inventory::checkedInProduct(int productId, int color)
{
    if (productId < 0 || productId > 255)
    {
        std::cerr << "Product Id " << productId << " has illegal value, can not checked in.\n";
        return false;
    }

    if (color < 0 || color > 7)
    {
        std::cerr << "color has illegal value, can not checked in.\n";
        return false;
    }

    if( (int)products[color][productId] == 255)
    {

        std::cerr << "The inventory has maximum  capacity (255) for this product, can not checked in.\n";
        return false;
    }


    products[color][productId]++;
    return true;
}







int Inventory::nrProductsPerColor(int color)
{
    int result = 0;;
    for (int i = 0; i < nrProducts; i++)
    {
        if(products[color][i] != 0)
        {
            result++;
        }
    }
    return result;
}






bool Inventory::checkedOutProduct(int productId, int color)
{
    if (productId < 0 || productId > 255)
    {
        std::cerr << "Product Id " << productId << " has illegal value, can not checked in.\n";
        return false;
    }

    if (color < 0 || color > 7)
    {
        std::cerr << "color has illegal value, can not checked in.\n";
        return false;
    }

    if( (int)products[color][productId] == 0)
    {

        std::cerr << "The inventory has minimum  capacity (0) for this product, can not checked in.\n";
        return false;
    }
    products[color][productId]--;
    return true;


}






bool Inventory::checkProductOfColor(int productId, int color)
{

    if (productId < 0 || productId > 255)
    {
        std::cerr << "Product Id " << productId << " has illegal value, can not checked in.\n";
        return false;
    }

    if (color < 0 || color > 7)
    {
        std::cerr << "color has illegal value, can not checked in.\n";
        return false;
    }

    return  (int) products[color][productId];

}






int Inventory::nrProductsForId(int productId)
{
    if (productId < 0 || productId > 255)
    {
        std::cerr << "Product Id " << productId << " has illegal value, can not checked in.\n";
        return false;
    }
    int sum = 0;
    for (int i = 0; i < nrColors; i++)
    {
        sum += (int)products[i][productId];
    }
    return sum;

}







int Inventory::nrProductsForSpecificId(int productId, int color)
{
    if (productId < 0 || productId > 255)
    {
        std::cerr << "Product Id " << productId << " has illegal value, can not checked in.\n";
        return false;
    }


    if (color < 0 || color > 7)
    {
        std::cerr << "color has illegal value, can not checked in.\n";
        return false;
    }


    return (int) products[color][productId];

}






int Inventory::nrProductsType()
{
    int sum = 0;

    for (int i = 0 ; i < nrColors; i++)
    {
        sum += nrProductsPerColor(i);
    }
    return sum ;
}



