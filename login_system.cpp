#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

void registerUser();
void loginUser();
void userMenu(const string &username);

string dbFolder = "users"; // folder to store all user files

int main()
{
    filesystem::create_directory(dbFolder); // ensure folder exists

    int choice;
    do
    {
        cout << "\n======== LOGIN & REGISTRATION SYSTEM ========\n";
        cout << "1) Register\n";
        cout << "2) Login\n";
        cout << "3) Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            cout << "Exiting system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}

void registerUser()
{
    string username, password;
    cout << "\n--- Register New User ---\n";

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    string userFile = dbFolder + "/" + username + ".txt";

    ifstream check(userFile);
    if (check.is_open())
    {
        cout << "❌ Username already exists! Try another.\n";
        return;
    }

    ofstream out(userFile);
    out << username << " " << password << endl;
    out.close();

    cout << "✅ Registration successful! User file created.\n";
}

void loginUser()
{
    string username, password;
    cout << "\n--- Login ---\n";

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    string userFile = dbFolder + "/" + username + ".txt";
    ifstream in(userFile);

    if (!in.is_open())
    {
        cout << "❌ User not found! Register first.\n";
        return;
    }

    string storedUser, storedPass;
    in >> storedUser >> storedPass;
    in.close();

    if (username == storedUser && password == storedPass)
    {
        cout << "✅ Login successful! Welcome, " << username << "\n";
        userMenu(username);
    }
    else
    {
        cout << "❌ Wrong password!\n";
    }
}

void userMenu(const string &username)
{
    int choice;
    string note;
    string userFile = dbFolder + "/" + username + ".txt";

    do
    {
        cout << "\n--- User Dashboard (" << username << ") ---\n";
        cout << "1) Add personal note\n";
        cout << "2) View notes\n";
        cout << "3) Logout\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
        {
            cout << "Write your note (single line): ";
            cin.ignore();
            getline(cin, note);

            ofstream out(userFile, ios::app);
            out << "Note: " << note << endl;
            out.close();
            cout << "✅ Note saved!\n";
        }
        else if (choice == 2)
        {
            cout << "\n---- Your Notes ----\n";
            ifstream in(userFile);
            string line;
            getline(in, line); // skip first line (credentials)
            while (getline(in, line))
                cout << line << endl;
        }
    } while (choice != 3);

    cout << "🔓 Logged out successfully!\n";
}
