#include <iostream>
#include <vector>
#include <algorithm> // for sort function for vector.
#include <list>
#include <set>
#include <fstream>
#include <chrono>
#include <iomanip>
using namespace std;
using namespace std::chrono;
// Functions to help clean space in main.
int vecRead(vector < string > & v);
int listRead(list < string > & l);
int setRead(set < string > & s);
int vecSort(vector < string > & v);
int listSort(list < string > & l);
int vecInsert(vector < string > & v, string word); // Now functions can insert any string as test code.
int listInsert(list < string > & l, string word);
int setInsert(set < string > & s, string word);
int vecDelete(vector < string > & v); // Functions will delete middle element, no need to pass string.
int listDelete(list < string > & l);
int setDelete(set < string > & s);

int main() {
    vector < string > v;
    list < string > l;
    set < string > s;

    int vecReadDuration = vecRead(v);
    int listReadDuration = listRead(l);
    int setReadDuration = setRead(s);
    // Begin sorting race.
    int vecSortDuration = vecSort(v);
    int listSortDuration = listSort(l);
    int setSortDuration = -1; // Set is already sorted, set as -1.
    //Begin race for inserting "TESTCODE" in middle of each container, or into set.

    int vecInsertDuration = vecInsert(v, "TESTCODE");
    int listInsertDuration = listInsert(l, "TESTCODE");
    int setInsertDuration = setInsert(s, "TESTCODE");
    // Begin race for deleting middle element from each container.
    int vecDeleteDuration = vecDelete(v);
    int listDeleteDuration = listDelete(l);
    int setDeleteDuration = setDelete(s);

    // Output results in a table format using iomanip for formatting.
    cout << left << setw(20) << "Operation" << setw(20) << "Vector (ns)" << setw(20) << "List (ns)" << setw(20) << "Set (ns)" << endl;
    cout << left << setw(20) << "Read" << setw(20) << vecReadDuration << setw(20) << listReadDuration << setw(20) << setReadDuration << endl;
    cout << left << setw(20) << "Sort" << setw(20) << vecSortDuration << setw(20) << listSortDuration << setw(20) << setSortDuration << endl;
    cout << left << setw(20) << "Insert" << setw(20) << vecInsertDuration << setw(20) << listInsertDuration << setw(20) << setInsertDuration << endl;
    cout << left << setw(20) << "Delete" << setw(20) << vecDeleteDuration << setw(20) << listDeleteDuration << setw(20) << setDeleteDuration << endl;

    return 0;
}
// This will also cut out need for resetting EOF flag and resetting file pointer to beginning of file.
int vecRead(vector < string > & v) {
    // Function to read words into vector and time the operation. Will be used in main for scalability.
    ifstream inFile("codes.txt");
    if (!inFile) { // check if file opened successfully
        cerr << "Unable to open file codes.txt" << endl;
        return 1;
    }
    // read words into vector and list, and time the operations, making sure to reset the file pointer back to the beginning of file.
    string word;
    auto start = high_resolution_clock::now(); // Starts the timer for reading into vector
    while (inFile >> word) {
        v.push_back(word);
    }
    auto end = high_resolution_clock::now();
    int time = duration_cast < nanoseconds > (end - start).count();
    inFile.close(); // Close the file after reading. Good habit, but files close once function ends anyways.
    return time; // Returns time taken to read into vector.
}

int listRead(list < string > & l) {
    // Function to read words into list and time the operation. Will be used in main for scalability.
    ifstream inFile("codes.txt");
    if (!inFile) { // check if file opened successfully
        cerr << "Unable to open file codes.txt" << endl;
        return 1;
    }
    // read words into vector and list, and time the operations, making sure to reset the file pointer back to the beginning of file.
    string word;
    auto start = high_resolution_clock::now(); // Starts the timer for reading into list
    while (inFile >> word) {
        l.push_back(word);
    }
    auto end = high_resolution_clock::now();
    int time = duration_cast < nanoseconds > (end - start).count();
    inFile.close();
    return time;
}

int setRead(set < string > & s) {
    // Function to read words into set and time the operation. Will be used in main for scalability.
    ifstream inFile("codes.txt");
    if (!inFile) { // check if file opened successfully
        cerr << "Unable to open file codes.txt" << endl;
        return 1;
    }
    // read words into vector and set, and time the operations, making sure to reset the file pointer back to the beginning of file.
    string word;
    auto start = high_resolution_clock::now(); // Starts the timer for reading into set
    while (inFile >> word) {
        s.insert(word); // Insert function for set will automatically place string in right place.
    }
    auto end = high_resolution_clock::now();
    int time = duration_cast < nanoseconds > (end - start).count();
    inFile.close();
    return time;
}

int vecSort(vector < string > & v) {
    auto start = high_resolution_clock::now(); // Starts the timer for sorting vector
    sort(v.begin(), v.end()); // Uses sort function from algorithm library.
    auto end = high_resolution_clock::now();
    int time = duration_cast < nanoseconds > (end - start).count();
    return time;
}

int listSort(list < string > & l) {
    auto start = high_resolution_clock::now(); // Starts the timer for sorting list
    l.sort();
    auto end = high_resolution_clock::now();
    int time = duration_cast < nanoseconds > (end - start).count();
    return time;
}

int vecInsert(vector < string > & v, string word) {
    auto start = high_resolution_clock::now();
    v.insert(v.begin() + v.size() / 2, word); // Middle is found by dividing vector.size by 2. Pretty fast.
    auto end = high_resolution_clock::now();
    int time = duration_cast < nanoseconds > (end - start).count();
    return time;
}

int listInsert(list < string > & l, string word) {
    auto start = high_resolution_clock::now();
    auto it_list = l.begin(); // Iterator created that starts at beginning.
    advance(it_list, l.size() / 2); // Move the iterator to the middle of the list. Slower since it moves from beginning to middle.
    l.insert(it_list, word);
    auto end = high_resolution_clock::now();
    int time = duration_cast < nanoseconds > (end - start).count();
    return time;
}

int setInsert(set < string > & s, string word) {
    auto start = high_resolution_clock::now();
    s.insert(word);
    auto end = high_resolution_clock::now();
    int time = duration_cast < nanoseconds > (end - start).count();
    return time;
}

int vecDelete(vector < string > & v) {
    auto start = high_resolution_clock::now();
    v.erase(v.begin() + v.size() / 2); // Same method as insert but deleting instead. Still pretty fast.
    auto end = high_resolution_clock::now();
    int time = duration_cast < nanoseconds > (end - start).count();
    return time;
}

int listDelete(list < string > & l) {
    auto start = high_resolution_clock::now();
    auto it_list = l.begin(); // Iterator created that starts at beginning.
    advance(it_list, l.size() / 2); // Move the iterator to the middle of the list.
    l.erase(it_list); // Takes iterator as argument to delete middle element.
    auto end = high_resolution_clock::now();
    int time = duration_cast < nanoseconds > (end - start).count();
    return time;
}

int setDelete(set < string > & s) {
    auto start = high_resolution_clock::now();
    s.erase( * s.begin()); // Erase the first element in the set.
    auto end = high_resolution_clock::now();
    int time = duration_cast < nanoseconds > (end - start).count();
    return time;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/