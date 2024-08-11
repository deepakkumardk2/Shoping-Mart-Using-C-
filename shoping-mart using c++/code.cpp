#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

class Shopping
{
private:
    int pcode;
    float price;
    float dis;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();
};

void Shopping::menu()
{
m:
    int choice;
    string email;
    string password;
    cout << "\t\t\t\t____________________________________\n";
    cout << "\t\t\t\t                                     \n";
    cout << "\t\t\t\t   SuperMarket  Main Menu            \n";
    cout << "\t\t\t\t                                     \n";
    cout << "\t\t\t\t____________________________________\n";
    cout << "\t\t\t\t                                     \n";
    cout << "\t\t\t\t|  1) Administrator          |\n";
    cout << "\t\t\t\t|                           |\n";
    cout << "\t\t\t\t|   2) Buyer                |\n";
    cout << "\t\t\t\t|                           |\n";
    cout << "\t\t\t\t|   3) Exit                 |\n";
    cout << "\t\t\t\t|                           |\n";
    cout << "\t\t\t\t|     Please Select         |\n";
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "\t\t\t\t|  Please Login  |\n";
        cout << "\t\t\t\t|  Enter Email   |\n";
        cin >> email;
        cout << "\t\t\t\t|  Password      |\n";
        cin >> password;
        if (email == "dk79944@gmail.com" && password == "Dk79944@123")
        {
            administrator();
        }
        else
        {
            cout << "Invalid email/password\n";
        }
        break;

    case 2:
        buyer();
        break;

    case 3:
        exit(0);

    default:
        cout << "Please select from the given options\n";
    }

    goto m;
}

void Shopping::administrator()
{
m:
    int choice;
    cout << "\n\n\n\t\t\t Administrator menu";
    cout << "\n\t\t\t\t|  1) Add the product          |\n";
    cout << "\n\t\t\t\t|  2) Modify the product       |\n";
    cout << "\n\t\t\t\t|  3) Delete the product       |\n";
    cout << "\n\t\t\t\t|  4) Back to main menu        |\n";
    cout << "\n\t\t\t\t  Please Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        add();
        break;
    case 2:
        edit();
        break;
    case 3:
        rem();
        break;
    case 4:
        menu();
        break;

    default:
        cout << " Invalid choice! ";
    }
    goto m;
}

void Shopping::buyer()
{
m:
    int choice;
    cout << "\t\t\t Buyer \n";
    cout << "\t\t\t 1) Buy product \n";
    cout << "\t\t\t 2) Go back \n";
    cout << "\t\t\t Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        receipt();
        break;
    case 2:
        menu();
        break;
    default:
        cout << "Invalid choice\n";
    }
    goto m;
}

void Shopping::add()
{
m:
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;
    cout << "\n\t\t\t Add new product";
    cout << "\n\t\t\t Product code of the product: ";
    cin >> pcode;
    cout << "\n\t\t\t Name of the product: ";
    cin >> pname;
    cout << "\n\t\t\t Price of the product: ";
    cin >> price;
    cout << "\n\t\t\t Discount on the product: ";
    cin >> dis;

    data.open("database.txt", ios::in);
    if (!data)
    {
        data.open("database.txt", ios::app | ios::out);
        data << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
    }
    else
    {
        data >> c >> n >> p >> d;
        while (!data.eof())
        {
            if (c == pcode)
            {
                token++;
                break;
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        if (token == 1)
        {
            cout << "\nProduct code already exists. Try again!";
            goto m;
        }
        else
        {
            data.open("database.txt", ios::app | ios::out);
            data << pcode << " " << pname << " " << price << " " << dis << "\n";
            data.close();
        }
    }
    cout << "\n\n\n\t\t Record inserted!";
}

void Shopping::edit()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;
    cout << "\n\n\t\t\t Modify the record";
    cout << "\n\t\t\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\nFile doesn't exist!";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pkey == pcode)
            {
                cout << "\n\t\t Product new code: ";
                cin >> c;
                cout << "\n\t\t Name of the product: ";
                cin >> n;
                cout << "\n\t\t Price: ";
                cin >> p;
                cout << "\n\t\t Discount: ";
                cin >> d;
                data1 << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t\tRecord edited";
                token++;
            }
            else
            {
                data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");
        if (token == 0)
        {
            cout << "\n\nRecord not found. Sorry!";
        }
    }
}

void Shopping::rem()
{
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << "\n\n\t Delete product";
    cout << "\n\n\t Product code: ";
    cin >> pkey;
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "File doesn't exist";
    }
    else
    {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof())
        {
            if (pcode == pkey)
            {
                cout << "\n\n\t Product deleted successfully";
                token++;
            }
            else
            {
                data1 << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");
        if (token == 0)
        {
            cout << "\n\nRecord not found";
        }
    }
}

void Shopping::list()
{
    fstream data;
    data.open("database.txt", ios::in);
    cout << "\n\n|_______________________________________\n";
    cout << "ProNo\t\tName\t\tPrice\n";
    cout << "\n\n|_______________________________________\n";
    data >> pcode >> pname >> price >> dis;
    while (!data.eof())
    {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void Shopping::receipt()
{
    fstream data;
    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float dis = 0;
    float total = 0;
    cout << "\n\n\t\t\t\t Receipt";
    data.open("database.txt", ios::in);
    if (!data)
    {
        cout << "\n\n Empty database";
    }
    else
    {
        data.close();
        list();
        cout << "\n_________________________________________________________\n";
        cout << "\n|                                                         \n";
        cout << "\n         Please place the order                           \n";
        cout << "\n                                                           \n";
        do
        {
            cout << "\n\n Enter the pcode :";
            cin >> arrc[c];
        }
    
