#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Contact {
    string name;
    string phoneNumber;
    string emailAddress;
};

const string FILENAME = "contacts.txt";

// Function to load contacts from file
vector<Contact> loadContacts() {
    vector<Contact> contacts;
    ifstream file(FILENAME);
    if (file.is_open()) {
        string name, phoneNumber, emailAddress;
        while (getline(file, name) && getline(file, phoneNumber) && getline(file, emailAddress)) {
            contacts.push_back({name, phoneNumber, emailAddress});
        }
        file.close();
    }
    return contacts;
}

// Function to save contacts to file
void saveContacts(const vector<Contact>& contacts) {
    ofstream file(FILENAME);
    if (file.is_open()) {
        for (const auto& contact : contacts) {
            file << contact.name << '\n'
                 << contact.phoneNumber << '\n'
                 << contact.emailAddress << '\n';
        }
        file.close();
    }
}

// Function to add a new contact
void addContact(vector<Contact>& contacts) {
    Contact newContact;
    cout << "Enter name: ";
    getline(cin, newContact.name);
    cout << "Enter phone number: ";
    getline(cin, newContact.phoneNumber);
    cout << "Enter email address: ";
    getline(cin, newContact.emailAddress);
    contacts.push_back(newContact);
    saveContacts(contacts);
}

// Function to view all contacts
void viewContacts(const vector<Contact>& contacts) {
    for (const auto& contact : contacts) {
        cout << "Name: " << contact.name << '\n'
             << "Phone Number: " << contact.phoneNumber << '\n'
             << "Email Address: " << contact.emailAddress << "\n\n";
    }
}

// Function to edit a contact
void editContact(vector<Contact>& contacts) {
    string name;
    cout << "Enter the name of the contact to edit: ";
    getline(cin, name);

    for (auto& contact : contacts) {
        if (contact.name == name) {
            cout << "Enter new phone number: ";
            getline(cin, contact.phoneNumber);
            cout << "Enter new email address: ";
            getline(cin, contact.emailAddress);
            saveContacts(contacts);
            return;
        }
    }
    cout << "Contact not found.\n";
}

// Function to delete a contact
void deleteContact(vector<Contact>& contacts) {
    string name;
    cout << "Enter the name of the contact to delete: ";
    getline(cin, name);

    auto it = remove_if(contacts.begin(), contacts.end(), [&](const Contact& contact) {
        return contact.name == name;
    });

    if (it != contacts.end()) {
        contacts.erase(it, contacts.end());
        saveContacts(contacts);
        cout << "Contact deleted.\n";
    } else {
        cout << "Contact not found.\n";
    }
}

// Main function
int main() {
    vector<Contact> contacts = loadContacts();
    int choice;

    do {
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Edit Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // Ignore newline character left in the buffer

        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts(contacts);
                break;
            case 3:
                editContact(contacts);
                break;
            case 4:
                deleteContact(contacts);
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
