#include <bits/stdc++.h>
using namespace std;

int intInput(int maxlim, int mini)
{
    int op;
    while (!(cin >> op && op > mini && op < maxlim))
    {
        cout << "Invalid input!" << endl;
        cout << "Enter Again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return op;
}
double doubleInput()
{
    int op;
    while (!(cin >> op))
    {
        cout << "Invalid input!" << endl;
        cout << "Enter Again: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return op;
}

void createUser()
{
    string userID, password;
    double initialBalance, loanAmount;

    cout << "Enter New User ID: ";
    cin >> userID;
    cout << "Enter Password for the User: ";
    cin >> password;
    cout << "Enter Initial Balance: ";
    initialBalance = doubleInput();
    cout << "Enter Loan Amount: ";
    loanAmount = doubleInput();

    ofstream userFile(userID + ".data");
    if (userFile.is_open())
    {
        userFile << password << endl;
        userFile << initialBalance << endl;
        userFile << loanAmount << endl;
        userFile.close();

        ofstream usersList("users_list.data", ios::app);
        usersList << userID << endl;
        usersList.close();

        cout << "User Created Successfully!" << endl;
    }
    else
    {
        cout << "Error creating user file!" << endl;
    }
}
void deleteUser()
{
    string userID;
    cout << "Enter User ID to Delete: ";
    cin >> userID;

    if (remove((userID + ".data").c_str()) == 0)
    {
        ifstream usersList("users_list.data");
        ofstream tempFile("temp.data");
        string existingID;

        if (usersList.is_open() && tempFile.is_open())
        {
            while (getline(usersList, existingID))
            {
                if (existingID != userID)
                {
                    tempFile << existingID << endl;
                }
            }
            usersList.close();
            tempFile.close();

            remove("users_list.data");
            rename("temp.data", "users_list.data");
            cout << "User Deleted Successfully!" << endl;
        }
        else
        {
            cout << "Error updating users list!" << endl;
        }
    }
    else
    {
        cout << "Error deleting user file! User may not exist." << endl;
    }
}

void viewUser()
{
    string userID;
    cout << "Enter User ID to View Details: ";
    cin >> userID;

    ifstream userFile(userID + ".data");
    if (userFile.is_open())
    {
        string line;
        cout << "--------------------------------------" << endl;
        cout << "      Details for User ID: " << userID << endl;
        cout << "--------------------------------------" << endl;
        while (getline(userFile, line))
        {
            cout << line << endl;
        }
        cout << "--------------------------------------" << endl;
        userFile.close();
    }
    else
    {
        cout << "User file not found!" << endl;
    }
}

void viewAll()
{
    ifstream usersList("users_list.data");
    if (usersList.is_open())
    {
        string userID;
        cout << "######################################" << endl;
        cout << "         Existing Users                " << endl;
        cout << "######################################" << endl;
        while (getline(usersList, userID))
        {
            cout << "ID: " << userID << endl;
        }
        cout << "---------------------------------------" << endl;
        usersList.close();
    }
    else
    {
        cout << "No users found!" << endl;
    }
    cout << "######################################" << endl;
}

void userLogin()
{
    string userID, password;
    cout << "Enter User ID: ";
    cin >> userID;
    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "Enter Password: ";
    cin >> password;

    ifstream userFile(userID + ".data");
    if (userFile.is_open())
    {
        string storedPassword, userCategory;
        double balance, loanAmount;

        getline(userFile, storedPassword);
        getline(userFile, userCategory);
        userFile >> balance >> loanAmount;
        userFile.close();

        if (password == storedPassword)
        {
            cout << "++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "         Welcome, " << userID << "!" << endl;
            cout << "++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "Category: " << userCategory << endl;
            cout << "-------------------------------------" << endl;
            cout << "Balance: " << balance << endl;
            cout << "-------------------------------------" << endl;
            cout << "Loan Amount: " << loanAmount << endl;
            cout << "++++++++++++++++++++++++++++++++++++++" << endl;

            int choice;
            while (true)
            {
                cout << "1. Withdraw\n2. Deposit\n3. Show Balance \n4. Log-Out \n Enter your choice: ";
                choice = intInput(5, 0);
                if (choice == 1)
                {
                    double amount;
                    cout << "Enter amount to withdraw: ";
                    amount = doubleInput();
                    if (amount <= balance)
                    {
                        balance -= amount;
                        cout << "Withdrawal successful! New Balance: " << balance << endl;
                        ofstream userFile(userID + ".data");
                    if (userFile.is_open())
                    {
                        userFile << storedPassword << endl;
                        userFile << userCategory << endl;
                        userFile << balance << endl;
                        userFile << loanAmount << endl;
                       
                    }
                           
                
                    }
                    else
                    {
                        cout << "Insufficient balance!" << endl;
                    }
                }
                else if (choice == 2)
                {
                    double amount;
                    cout << "Enter amount to deposit: ";
                    amount = doubleInput();
                    balance += amount;
                    cout << "Deposit successful! New Balance: " << balance << endl;
                     ofstream userFile(userID + ".data");
                    if (userFile.is_open())
                    {
                        userFile << storedPassword << endl;
                        userFile << userCategory << endl;
                        userFile << balance << endl;
                        userFile << loanAmount << endl;
                        
                    }
                }
                else if (choice == 3)
                {

                    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                    cout << "         Welcome, " << userID << "!" << endl;
                    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                    cout << "Category: " << userCategory << endl;
                    cout << "-------------------------------------" << endl;
                    cout << "Balance: " << balance << endl;
                    cout << "-------------------------------------" << endl;
                    cout << "Loan Amount: " << loanAmount << endl;
                    cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                }
                else if (choice == 4)
                {
                    ofstream userFile(userID + ".data");
                    if (userFile.is_open())
                    {
                        userFile << storedPassword << endl;
                        userFile << userCategory << endl;
                        userFile << balance << endl;
                        userFile << loanAmount << endl;
                        userFile.close();
                    }
                    cout << "Logged out successfully!" << endl;
                    break;
                }
                else
                {
                    cout << "Invalid choice! Try again." << endl;
                }
            }
        }
        else
        {
            cout << "Incorrect User ID/Password!" << endl;
        }
    }
    else
    {
        cout << "User not found!" << endl;
    }
}

int admin()
{
    long long int adminID, pin;
    cout << "Enter Admin ID: ";
    cin >> adminID;
    cout << "Enter PIN: ";
    cin >> pin;

    if (adminID == 223071019 && pin == 12345678)
    {
        int step;
        while (true)
        {
            cout << "--------------------------------------" << endl;
            cout << "         WELCOME BACK ADMIN           " << endl;
            cout << "--------------------------------------" << endl;
            cout << "1. View User \n2. Create New User\n3. All Users\n4. Delete User \n5. Log-out" << endl;
            cout << "Enter your choice: ";
            step = intInput(6, 0);

            if (step == 1)
            {
                viewUser();
            }
            else if (step == 2)
            {
                createUser();
            }
            else if (step == 3)
            {
                viewAll();
            }
            else if (step == 4)
            {
                deleteUser();
            }
            else if (step == 5)
            {
                cout << "Logged out successfully!" << endl;
                break;
            }
            else
            {
                cout << "Invalid option!" << endl;
            }
        }
    }
    else
    {
        cout << "Invalid Admin ID or PIN!" << endl;
    }
    return 4;
}

int main()
{
    system("color 6");
    while (true)
    {
        int op;
        cout << "***********************************************************" << endl;
        cout << "-------------------WELCOME TO BankSphere-------------------" << endl;
        cout << "***********************************************************" << endl;
        cout << "1. Admin Login\n2. User Login" << endl;
        cout << "Enter your choice: ";
        op = intInput(3, 0);

        if (op == 1)
        {
            admin();
        }
        else if (op == 2)
        {
            userLogin();
        }
        else
        {
            cout << "Invalid choice!" << endl;
        }
    }
    return 0;
}
