#include <iostream>
#include "src/md5.cpp"

using namespace std;

int main() {
    cout << "your password: ";
    string password;
    getline( cin, password );

    DWORD res;
    password = md( password, &res ); // ** hashing function **

    cout << "repeat your password: ";
    string password2;
    getline( cin, password2 );

    password2 = md( password2, &res );

    if (password == password2) {
        cout << "\nwow, good memory)\n";
    }
    else {
        cout << "\nerr: password mismatch\n";
    }
}

