#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream MyFile("22850034.txt");
    string myText;

    // Use a while loop together with the getline() function to read the file line by line
    while (getline (MyFile, myText)) {
        // Output the text from the file
        cout << myText;
        cout << "hello guys";
    }

    // Close the file
    MyFile.close();
}