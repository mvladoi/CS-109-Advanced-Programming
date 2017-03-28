#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>


class Inventory
{
public:
    Inventory();                             // Default Constructor
    bool checkItem(int productId);           // Check if a product is in Inventory
    int nrItemsPerProduct(int productId);    //How many products per product ID
    int nrProductsPerColor(int color);       // How many products per Color
    bool checkedInProduct(int ProductId, int color); // Check in a new product
    bool checkedOutProduct(int ProductId, int color); // Check out a product
    bool checkProductOfColor(int ProductId, int color); // Check a product of a specific ID and Color
    int nrProductsForId( int ProductId);                // How many Products for a particular ID
    int nrProductsForSpecificId (int ProductId, int color);// How many Products for a particular ID and Color
    int nrProductsType();    // How many products Type in Inventory
    void printInventory();   // Print the inventory
    virtual ~Inventory();    // Destructor

private:
    const int nrProducts = 256;  // nr of products
    const int nrColors = 8;      // nr of colors
    unsigned char** products;    // a 2 d Array 8 by 256 chars (1 char = 1 byte) to store the inventory


};

#endif // INVENTORY_H
