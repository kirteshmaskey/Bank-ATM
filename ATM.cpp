#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <time.h>
#include <windows.h>
using namespace std;

class ATM
{
private:
    double BALANCE = 0.0;
    long long ACCNO = 0000000;
    string NAME = "NULL";
    int PIN = 0000;

public:
    void newRegistration();
    void showInformation();
    void depositMoney();
    void withdrawMoney();
    void showBalance();
};

void ATM::newRegistration()
{
    system("cls");
    cin.ignore();
    cout << "Your Full Name : ";
    getline(cin, NAME);

    cout << "CREATE PIN FOR YOUR ACCOUNT (Be Carefull): \n";
    cout << "Create 4 digit PIN: ";
    cin >> PIN;

    ACCNO = rand();
    system("cls");
    cout << "Account created sucessfully!!\n\n";

    showInformation();
    system("cls");

    cout << "Do you want to deposit money (y/n)\n";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
        depositMoney();
    else if (ch == 'n' || ch == 'N')
        return;
}

void ATM::showInformation()
{

    cout << "Your account details are:\n";
    cout << "Account Name:  " << NAME;
    cout << "\nAccount number:  " << ACCNO;
    cout << "\nAccount Balance:  " << BALANCE;
    Sleep(7000);
    return;
}

void ATM::depositMoney()
{
    long long int depositAmount;
    cout << "Enter amount to deposit:  ";
    cin >> depositAmount;
    BALANCE += depositAmount;
    system("cls");
    showBalance();
}

void ATM::withdrawMoney()
{
    long long int withdrawAmount;
    cout << "Enter amount to withdraw:  ";
    cin >> withdrawAmount;
    if (withdrawAmount <= BALANCE)
    {
        system("cls");
        BALANCE -= withdrawAmount;
        cout << "Please collect your cash\n\n";
        showBalance();
    }
    else
    {
        cout << "\nInsufficient Balance\n";
        cout << "Do you want to see account balance?? (y/n)\n";
        char ch;
        cin >> ch;
        if (ch == 'y' || ch == 'Y')
            showBalance();
        else if (ch == 'n' || ch == 'N')
            ;
        system("cls");
        withdrawMoney();
    }
}

void ATM::showBalance()
{
    cout << "Your account balance:  " << BALANCE;
    Sleep(4000);
}
int main()
{
    ATM user;
    srand(time(0));
    
    int actionchoice;
    while (1)
    {
        system("cls");
        cout << "\n\n\t\t\t\tWELCOME TO BANK OF KIRTESH\n\n";

        cout << "\nEnter:\n";
        cout << "1. To create new account\n";
        cout << "2. To show your account details\n";
        cout << "3. to deposit money into your account\n";
        cout << "4. To withdraw money from your account\n";
        cout << "5. To display account balance\n";
        cout << "6. To EXIT\n";
        cin >> actionchoice;
        system("cls");
        switch (actionchoice)
        {
        case 1:
            user.newRegistration();
            break;

        case 2:
            user.showInformation();
            break;

        case 3:
            user.depositMoney();
            break;

        case 4:
            user.withdrawMoney();
            break;

        case 5:
            user.showBalance();
            break;

        case 6:
            exit(0);
        default:
            break;
        }
    }

    return 0;
}