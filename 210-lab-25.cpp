#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;

const int MAXSIZE = 20000;

int main() {
    vector<string> v;
    list<string> l;
    set<string> s;

    int vecReadDuration;
    int listReadDuration;
    int setReadDuration;

    ifstream inFile("words.txt");
    if (!inFile) { // check if file opened successfully
        cerr << "Unable to open file words.txt" << endl;
        return 1;
    }
    // read words into vector and list, and time the operations, making sure to reset the file pointer back to the beginning of file.
    string word;
    auto start = high_resolution_clock::now(); // Starts the timer for reading into vector
    while (inFile >> word) {
        v.push_back(word);
    }
    auto end = high_resolution_clock::now();
    vecReadDuration = duration_cast<nanoseconds>(end - start).count();
    // This will be done between each container in each race.
    inFile.clear(); // Clear the EOF flag
    inFile.seekg(0); // Move the file pointer back to the beginning

    start = high_resolution_clock::now(); // Starts the timer for reading into list
    while (inFile >> word) {
        l.push_back(word);
    }
    end = high_resolution_clock::now();
    listReadDuration = duration_cast<nanoseconds>(end - start).count();
    inFile.clear();
    inFile.seekg(0);

    start = high_resolution_clock::now(); // Starts the timer for reading into set
    while (inFile >> word) {
        s.insert(word);
    }
    end = high_resolution_clock::now();
    setReadDuration = duration_cast<nanoseconds>(end - start).count();
    inFile.close(); // End of reading race between containers. May consider making functions for scalability.
// Begin sorting race.
    int vecSortDuration;
    int listSortDuration;
    int setSortDuration;

    auto sortStart = high_resolution_clock::now(); // Need different variables for each race to avoid confusion.
    sort(v.begin(), v.end()); // Sort the vector using the built-in sort function
    auto sortEnd = high_resolution_clock::now();
    vecSortDuration = duration_cast<nanoseconds>(sortEnd - sortStart).count();


    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/