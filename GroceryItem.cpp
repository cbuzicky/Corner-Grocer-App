#include "GroceryItem.h"
#include <string>
#include <iostream>

using namespace std;



GroceryItem::GroceryItem(std::string& name)
{
	this->name = name;
}

GroceryItem::GroceryItem(std::string& name, int quantity)
{
	this->name = name;
	this->quantity = quantity;
}

std::string GroceryItem::getName() const
{
	return name;
}

int GroceryItem::getQuantity() const
{
	return quantity;
}

//Adds one to the current quantity of a grocery item
void GroceryItem::addItem()
{
	quantity += 1;
	return;
}

//Removes one from the current quantity of a grocery item
void GroceryItem::removeItem()
{
	quantity -= 1;
	return;
}
//Compares current item name with existing names 
bool GroceryItem::operator<(const GroceryItem& other) const {
	
	return name.compare(other.getName()) < 0;
}