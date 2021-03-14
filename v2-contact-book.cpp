#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <cstdio>

using namespace std;

string userFile = "Uzytkownicy.txt";
string contactsFile = "Adresaci.txt";

struct User {
    int userID = 0;
    string login = "";
    string password = "";
};

void addUserToFile (User info) {

    fstream file;
    file.open(userFile.c_str(), ios::out | ios::app);

    if (file.good() == true) {
        file << info.userID << '|';
        file << info.login << '|';
        file << info.password << '|' << endl;

        file.close();

        cout << endl << "Konto zalozone" << endl;
        system("pause");
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

void registration (vector <User> &userData) {

    User info;

    system("cls");
    if (userData.empty() == true) {
        info.userID = 1;
    } else {
        info.userID = userData.back().userID + 1;
    }

    cout << "Podaj nazwe uzytkownika: ";
    cin >> info.login;

    if (userData.empty() == false) {
        for (vector <User> ::iterator  itr = userData.begin(); itr != userData.end(); itr++) {
            if (itr -> login == info.login) {
                cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
                cin >> info.login;
            }
        }
    }
    cout << "Podaj haslo: ";
    cin >> info.password;

    userData.push_back(info);
    addUserToFile(info);
}

User assignToUser (string line) {

    User info;
    string word = "";
    string separateWords[3];
    int k = 0;

    for (int i = 0; i <= line.size(); i++) {

        if (line[i] != '|') {
            word += line[i];
        } else {
            separateWords[k] = word;
            k++;
            word = "";
        }
    }
    info.userID = atoi(separateWords[0].c_str());
    info.login = separateWords[1];
    info.password = separateWords[2];

    return info;
}

void loadUsersFromFile (vector <User> &userData) {

    User info;
    string line = "";

    fstream file;
    file.open(userFile.c_str(), ios::in);

    if (file.good() == true) {

        while(!file.eof()) {
            getline(file, line);

            info = assignToUser(line);
            userData.push_back(info);
        }
        userData.erase(userData.end());
    }
    file.close();
}

int logIn (vector <User> &userData) {

    User info;

    cout << "Podaj login: ";
    cin >> info.login;

    for (int i = 0; i < userData.size(); ++i) {
        if (userData[i].login == info.login) {

            for (int j=0; j<3; j++) {
                cout << "Podaj haslo, pozostalo prob " << 3-j << ": ";
                cin >> info.password;
                if (userData[i].password == info.password) {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return userData[i].userID;
                }
            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 sek przed kolejna proba." << endl;
            Sleep(3000);
            return 0;
        }
    }
    cout << "Nie ma uzytkownika o takiej nazwie" << endl;
    Sleep(2000);
    return 0;
}

struct Person {
    int id = 0;
    int userID = 0;
    string name = "";
    string surname = "";
    string email = "";
    string adress = "";
    string telephoneNumber = "";
};

Person assignToStructure (string line) {

    Person contactDetails;
    string word = "";
    string separateWords[7];
    int k = 0;

    for (int i = 0; i <= line.size(); i++) {

        if (line[i] != '|') {
            word += line[i];
        } else {
            separateWords[k] = word;
            k++;
            word = "";
        }
    }
    contactDetails.id = atoi(separateWords[0].c_str());
    contactDetails.userID = atoi(separateWords[1].c_str());
    contactDetails.name = separateWords[2];
    contactDetails.surname = separateWords[3];
    contactDetails.telephoneNumber = separateWords[4];
    contactDetails.email = separateWords[5];
    contactDetails.adress = separateWords[6];

    return contactDetails;
}

void loadContactsFromFile (vector <Person> &contacts, int &userID) {

    Person contactDetails;
    string line = "";

    fstream file;
    file.open(contactsFile.c_str(), ios::in);

    if (file.good() == true) {

        while(!file.eof()) {
            getline(file, line);
            contactDetails = assignToStructure(line);
            if (contactDetails.userID == userID) {
                contacts.push_back(contactDetails);
            }
        }
    }
    file.close();
}

void addPersonToFile (Person contactDetails) {

    fstream file;
    file.open(contactsFile.c_str(), ios::out | ios::app);

    if (file.good() == true) {
        file << contactDetails.id << '|';
        file << contactDetails.userID << '|';
        file << contactDetails.name << '|';
        file << contactDetails.surname << '|';
        file << contactDetails.telephoneNumber << '|';
        file << contactDetails.email << '|';
        file << contactDetails.adress << '|' << endl;
        file.close();

        cout << endl << "Kontakt zostal zapisany" << endl;
        system("pause");
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

int countContats () {

    vector <Person> amount;
    Person contactDetails;
    string line = "";

    fstream file;
    file.open(contactsFile.c_str(), ios::in);

    if (file.good()== false) {
        return (0);
    }

    if (file.good() == true) {
        while(!file.eof()) {
            getline(file, line);
            contactDetails = assignToStructure(line);
            amount.push_back(contactDetails);
        }
        amount.erase(amount.end());
        return amount.back().id;
    }
    file.close();
}

void addPerson (vector <Person> &contacts, int &userID) {

    Person contactDetails;

    contactDetails.id = countContats();

    system("cls");
    if (contactDetails.id == 0) {
        contactDetails.id = 1;
    } else {
        contactDetails.id += 1;
    }

    contactDetails.userID = userID;

    cout << "Wrowadz imie: ";
    cin >> contactDetails.name;

    cout << "Wrowadz nazwisko: ";
    cin >> contactDetails.surname;

    cout << "Wrowadz numer telefonu: ";
    cin.sync();
    getline (cin, contactDetails.telephoneNumber);

    cout << "Wrowadz e-mail: ";
    cin >> contactDetails.email;

    cout << "Wrowadz adres: ";
    cin.sync();
    getline(cin, contactDetails.adress);

    contacts.push_back(contactDetails);
    addPersonToFile (contactDetails);
}

void searchByName(vector <Person> &contacts) {

    string name;

    cout << "Wprowadz imie: ";
    cin >> name;

    for (int i = 0; i < contacts.size(); i++) {

        if (contacts[i].name == name) {
            cout << contacts[i].id << "|" << contacts[i].userID << "|" << contacts[i].name << "|" << contacts[i].surname << "|" << contacts[i].telephoneNumber << "|" << contacts[i].email << "|" << contacts[i].adress << "|" << endl;
        }
    }
    cout << endl;
}

void searchBySurname(vector <Person> &contacts) {

    string surname;

    cout << "Wprowadz nazwisko: ";
    cin >> surname;

    for(int i = 0; i < contacts.size(); i++) {

        if (contacts[i].surname == surname) {
            cout << contacts[i].id << "|" << contacts[i].userID << "|" << contacts[i].name << "|" << contacts[i].surname << "|" << contacts[i].telephoneNumber << "|" << contacts[i].email << "|" << contacts[i].adress << "|" << endl;
        }
    }
    cout << endl;
}

void schowAllContacts(vector <Person> &contacts) {

    system("cls");
    if (!contacts.empty()) {
        for (vector<Person>::iterator itr = contacts.begin(); itr != contacts.end(); itr++) {
            cout << itr->id << '|';
            cout << itr->userID << '|';
            cout << itr->name << '|';
            cout << itr->surname << '|';
            cout << itr->telephoneNumber << '|';
            cout << itr->email << '|';
            cout << itr->adress <<'|' << endl;
        }
        cout << endl;
    } else {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
}

int stringToInt (string line) {

    int number = 0;
    string numer ="";
    int i=0;

    while (line[i] != '|') {
        numer += line[i];
        i++;
    }
    number = atoi(numer.c_str());

    return number;
}

void editData (int numberID, vector <Person> &contacts) {

    Person contactDetails;
    string temporaryFile = "AdresaciTymczasowi.txt";
    int lineID;
    string line;

    ifstream in(contactsFile);

    fstream out;
    out.open(temporaryFile.c_str(), ios::out | ios::app);

    while (getline(in, line)) {
        lineID = stringToInt(line);
        if (lineID != numberID) {
            out << line << endl;
        } else {
            for (int i = 0; i < contacts.size(); ++i) {
                if (contacts[i].id == lineID){
                    out << contacts[i].id << '|';
                    out << contacts[i].userID << '|';
                    out << contacts[i].name << '|';
                    out << contacts[i].surname << '|';
                    out << contacts[i].telephoneNumber << '|';
                    out << contacts[i].email << '|';
                    out << contacts[i].adress << '|' << endl;
                }
            }
        }
    }
    out.close();
    in.close();

    remove("Adresaci.txt");
    rename("AdresaciTymczasowi.txt", "Adresaci.txt");
}

void deleteContact (vector <Person> &contacts) {

    int personID;
    char yes;

    cout << "Kontakty obecnie zapisane w ksiazce:" << endl;
    schowAllContacts(contacts);
    cout << endl;
    cout << "Podaj ID kontaktu do usuniecia: ";
    cin >> personID;

    cout << "Jesli jestes pewnien, ze chcesz usunac kontakt wybierz 't' z klawiatury: ";
    cin >> yes;

    if (yes == 't') {
        for (int i = 0 ; i < contacts.size(); i++) {
            if (personID == contacts[i].id) {
                contacts.erase(contacts.begin()+ i);
                editData(contacts[i].id, contacts);
            }
        }
        cout << "Kontakt zostal usuniety." << endl;
    } else
        cout << "Kontak nie zostal usuniety!" << endl;
}

void editContact (vector <Person> &contacts) {

    Person contactDetails;
    char option;
    int personID;

    cout << "Kontakty obecnie zapisane w ksiazce:" << endl;
    schowAllContacts(contacts);
    cout << endl;
    cout << "Podaj ID kontaktu do edycji: ";
    cin >> personID;

    for (int i = 0 ; i < contacts.size(); i++) {

        if (personID == contacts[i].id ) {

            system("cls");
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - email" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl;

            cout << "Wybierz cyfre z menu, ktore dane chcesz edytowac: ";
            cin >> option;

            if (option == '1') {
                cout << "Wpisz nowe imie: ";
                cin >> contacts[i].name;
                editData(contacts[i].id, contacts);
            } else if (option == '2') {
                cout << "Wpisz nowe nazwisko: ";
                cin >> contacts[i].surname;
                editData(contacts[i].id, contacts);
            } else if (option == '3') {
                cout << "Wpisz nowy numer telefonu: ";
                cin.sync();
                getline(cin, contacts[i].telephoneNumber);
                editData(contacts[i].id, contacts);
            } else if (option == '4') {
                cout << "Wpisz nowy e-mail: ";
                cin >> contacts[i].email;
                editData(contacts[i].id, contacts);
            } else if (option == '5') {
                cout << "Wpisz nowy adres: ";
                cin.sync();
                getline(cin, contacts[i].adress);
                editData(contacts[i].id, contacts);
            } else if (option == '6') {
                getchar();
            }
        }
    }
}

void editUserData (string path, vector <User> &userData) {

    vector <string> temporary;

    ifstream in(path);
    string line;
    while (getline(in, line))
        temporary.push_back(line);
    in.close();

    ofstream out(path);
    for (int i = 0; i < userData.size(); ++i) {
        out << userData[i].userID << '|';
        out << userData[i].login << '|';
        out << userData[i].password << '|' << endl;
    }
    out.close();
}

void changePassword (vector <User> &userData, int ID) {

    for (int i=0; i<userData.size() ; i++) {

        if (ID == userData[i].userID) {
            cout << "Podaj nowe haslo:" << endl;
            cin >> userData[i].password;
            editUserData (userFile.c_str(), userData);
        }
    }
}

void logMenu (int &userIdNumber, vector <User> &userData) {

    vector <Person> contacts;
    int contactID = 0;
    char choice;

    loadContactsFromFile(contacts, userIdNumber);

    while(1) {

        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        //
        cout << "7. Zmien haslo" << endl;
        //
        cout << "9. Wyloguj sie" << endl;
        cout << "Twoj wybor: ";
        cin >> choice;

        if (choice == '1') {
            addPerson(contacts, userIdNumber);
            system("pause");
        } else if (choice == '2') {
            searchByName(contacts);
            system("pause");
        } else if (choice == '3') {
            searchBySurname(contacts);
            system("pause");
        } else if (choice == '4') {
            schowAllContacts(contacts);
            system("pause");
        } else if (choice == '5') {
            deleteContact(contacts);
            system("pause");
        } else if (choice == '6') {
            editContact(contacts);
            system("pause");
        } else if (choice == '7') {
            changePassword (userData, userIdNumber);
        } else if (choice == '9') {
            return;
        }
    }
}

int main() {
    vector <User> userData;
    User identities;
    int amountOfUsers = 0;
    char choice;

    loadUsersFromFile(userData);

    while(1) {

        system("cls");
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "9. Zamknij program" << endl;
        cout << "Twoj wybor: ";
        cin >> choice;

        if (choice == '1') {
            identities.userID = logIn(userData);
            if (identities.userID != 0) {
                logMenu(identities.userID, userData);
            }
        } else if (choice == '2') {
            registration(userData);
        } else if (choice == '9') {
            exit(0);
        }
    }

    return 0;
}
