#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <string>
#include <fstream>
#include <time.h>
#include <windows.h>
#define ll long long int
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
    void showBalance(); // To show balance only
    int accountNo();    // To return account Number to match with flie inorder to open it
    int accountPass();  // To return account Password(PIN) to match with flie inorder to open it
    string accountName();
};

int ATM::accountNo()
{
    return ACCNO;
}

int ATM::accountPass()
{
    return PIN;
}

string ATM::accountName()
{
    return NAME;
}

void ATM::newRegistration()
{
    BALANCE = 0.0;
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

    cout << "Do you want to deposit money (y/n) : "; // Ask to Deposit Money while creating account
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
        depositMoney();
    else if (ch == 'n' || ch == 'N')
        ;
    // return;

    system("cls");
    showInformation();
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
    ll depositAmount;
    cout << "Enter amount to deposit:  ";
    cin >> depositAmount;
    BALANCE += depositAmount;

    system("cls");
    showBalance();
}

void ATM::withdrawMoney()
{
    ll withdrawAmount;
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
    fstream details;
    int pos;
    ATM user;
    srand(time(0));

    int actionchoice;
    while (1)
    {
        system("cls");
        cout << "\n\n\t\t\t\tWELCOME TO BANK OF KIRTESH\n\n";

        cout << "\nEnter:\n";
        cout << "1. To create new account\n";
        cout << "2. To login to your account\n";
        cout << "3. To EXIT\n";
        cin >> actionchoice;
        system("cls");
        switch (actionchoice)
        {
        case 1:
            user.newRegistration();
            details.open("accountDetails.dat", ios::app | ios::binary);
            details.write((char *)&user, sizeof(user));
            details.close();
            break;

        case 2:
        AGAIN:
            details.open("accountDetails.dat", ios::in | ios::out | ios::binary);
            ll accNo;
            int pin;
            cout << "Enter your account number:  ";
            cin >> accNo;
            cout << "Enter 4 digit pin:  ";
            cin >> pin;
            details.seekg(0);
            while (details.read((char *)&user, sizeof(user)))
            {
                pos = details.tellg();
                if (user.accountNo() == accNo && user.accountPass() == pin)
                {
                    while (1)
                    {
                        system("cls");
                        int choice;
                        cout << "\n\t\t    BANK OF KIRTESH\n\n";
                        string name = user.accountName();
                        cout << "\t\tWelcome " << name << "!!";
                        cout << "\n\nEnter:\n";
                        cout << "1. To see account details\n";
                        cout << "2. To deposit Money\n";
                        cout << "3. To withdraw Money\n";
                        cout << "4. To see account Balance\n";
                        cout << "5. To Exit\n";
                        cin >> choice;

                        system("cls");
                        switch (choice)
                        {
                        case 1:
                            user.showInformation();
                            break;

                        case 2:
                            user.depositMoney();
                            details.seekg(pos - sizeof(user));
                            details.write((char *)&user, sizeof(user));
                            break;

                        case 3:
                            user.withdrawMoney();
                            details.seekg(pos - sizeof(user));
                            details.write((char *)&user, sizeof(user));
                            break;

                        case 4:
                            user.showBalance();
                            break;

                        case 5:
                            details.close();
                            goto EXIT;

                        default:
                            cout << "Please make a valid choice\n";
                            Sleep(2000);
                        }
                    }
                    details.close();
                }
            }
            system("cls");
            if (details.end)
                cout << "\nINVALID ACCOUNT NUMBER OR PASSWORD\n";
            Sleep(2000);
            details.close();
            system("cls");
            cout << "Enter again or Exit (y/n) : ";
            char ch;
            cin >> ch;
            if (ch == 'y' || ch == 'Y')
            {
                system("cls");
                goto AGAIN;
            }
            else if (ch == 'n' || ch == 'N')
                break;
        EXIT:
            break;

        case 3:
            exit(0);

        default:
            cout << "Please make a valid choice\n";
            Sleep(2000);
        }
    }

    return 0;
}