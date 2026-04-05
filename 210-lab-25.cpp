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
int vecRead(vector <string> &v);
int listRead(list <string> &l);
int setRead(set <string> &s);
int vecSort(vector <string> &v);
int listSort(list <string> &l);
int setSort(set <string> &s);
int vecInsert();
int listInsert();
int setInsert();
int vecDelete();
int listDelete();
int setDelete();

int main() {
    vector < string > v;
    list < string > l;
    set < string > s;

    int vecReadDuration = vecRead(v);
    int listReadDuration = listRead(l);
    int setReadDuration = setRead(s);
// Begin sorting race.
    int vecSortDuration;
    int listSortDuration;
    int setSortDuration;
// Sort the vector using algorithm header since <vector> does not have a sort method built-in.
    auto sortStart = high_resolution_clock::now(); // Need different variables for each race to avoid confusion.
    sort(v.begin(), v.end());
    auto sortEnd = high_resolution_clock::now();
    vecSortDuration = duration_cast < nanoseconds > (sortEnd - sortStart).count();
    // Sort the list using its built-in sort method.
    sortStart = high_resolution_clock::now();
    l.sort(); // Sort the list using its built-in sort method.
    sortEnd = high_resolution_clock::now();
    listSortDuration = duration_cast < nanoseconds > (sortEnd - sortStart).count();
    // Set are automatically sorted.
    setSortDuration = -1; // Set to -1 since it is already sorted.
    //Begin race for inserting "TESTCODE" in middle of each container, or into set.
    int vecInsertDuration;
    int listInsertDuration;
    int setInsertDuration;
    // Insert "TESTCODE" into middle of vector using insert method.
    auto insertStart = high_resolution_clock::now();
    v.insert(v.begin() + v.size() / 2, "TESTCODE"); // Middle is found by dividing vector.size by 2. Pretty fast.
    auto insertEnd = high_resolution_clock::now();
    vecInsertDuration = duration_cast < nanoseconds > (insertEnd - insertStart).count();
    // Insert "TESTCODE" into middle of list using insert method. Need to use an iterator to find the middle of the list.
    insertStart = high_resolution_clock::now();
    auto it_list = l.begin();
    advance(it_list, l.size() / 2); // Move the iterator to the middle of the list. Slower since it moves from beginning to middle.
    l.insert(it_list, "TESTCODE");
    insertEnd = high_resolution_clock::now();
    listInsertDuration = duration_cast < nanoseconds > (insertEnd - insertStart).count();
    // Insert "TESTCODE" into set using insert method. Set will automatically place it in the correct position.
    insertStart = high_resolution_clock::now();
    s.insert("TESTCODE");
    insertEnd = high_resolution_clock::now();
    setInsertDuration = duration_cast < nanoseconds > (insertEnd - insertStart).count();
    // Begin race for deleting middle element from each container.
    int vecDeleteDuration;
    int listDeleteDuration;
    int setDeleteDuration;
    // Delete middle element from vector using erase method.
    auto deleteStart = high_resolution_clock::now();
    v.erase(v.begin() + v.size() / 2); // Same method as insert but deleting instead. Still pretty fast.
    auto deleteEnd = high_resolution_clock::now();
    vecDeleteDuration = duration_cast < nanoseconds > (deleteEnd - deleteStart).count();
    // Delete middle element from list using erase method. Need to use an iterator to find the middle of the list.
    deleteStart = high_resolution_clock::now();
    it_list = l.begin();
    advance(it_list, l.size() / 2); // Move the iterator to the middle of list to delete middle element.
    l.erase(it_list);
    deleteEnd = high_resolution_clock::now();
    listDeleteDuration = duration_cast < nanoseconds > (deleteEnd - deleteStart).count();
    // Delete middle element from set using erase method.
    deleteStart = high_resolution_clock::now();
    auto it_set = s.begin();
    advance(it_set, s.size() / 2); // Move the iterator to the middle of set to delete middle element.
    s.erase(it_set);
    deleteEnd = high_resolution_clock::now();
    setDeleteDuration = duration_cast < nanoseconds > (deleteEnd - deleteStart).count();
    // Output results in a table format using iomanip for formatting.
    cout << left << setw(20) << "Operation" << setw(20) << "Vector (ns)" << setw(20) << "List (ns)" << setw(20) << "Set (ns)" << endl;
    cout << left << setw(20) << "Read" << setw(20) << vecReadDuration << setw(20) << listReadDuration << setw(20) << setReadDuration << endl;
    cout << left << setw(20) << "Sort" << setw(20) << vecSortDuration << setw(20) << listSortDuration << setw(20) << setSortDuration << endl;
    cout << left << setw(20) << "Insert" << setw(20) << vecInsertDuration << setw(20) << listInsertDuration << setw(20) << setInsertDuration << endl;
    cout << left << setw(20) << "Delete" << setw(20) << vecDeleteDuration << setw(20) << listDeleteDuration << setw(20) << setDeleteDuration << endl;

    return 0;
}
// This will also cut out need for resetting EOF flag and resetting file pointer to beginning of file.
int vecRead(vector <string> &v) {
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
    inFile.close();
    return time;
}

int listRead(list <string> &l) {
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

int setRead(set <string> &s) {
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
        s.insert(word);
    }
    auto end = high_resolution_clock::now();
    int time = duration_cast < nanoseconds > (end - start).count();
    inFile.close();
    return time;
}

int vecSort(vector <string> &v) {
    auto start = high_resolution_clock::now(); // Starts the timer for sorting vector
    sort(v.begin(), v.end());
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