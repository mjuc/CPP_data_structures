#include "Menu.h"
#include "Encoder.h"
 
using namespace std;

Menu::Menu() {}
void Menu::menu()
{
    int choice;
    vector<string> temp;
    cout << "Menu: " << endl;
    cout << "1. Generate password" << endl;
    cout << "2. Encode password" << endl;
    cout << "3. Read password" << endl;
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        break;
    }   
    case 2:
    {
        break;
    }
    default:
        break;
    }
}
