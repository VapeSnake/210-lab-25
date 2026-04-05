#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <fstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

const int MAXSIZE = 20000;

void readingRace();
void sortingRace(); // Calling any of these functions will
void insertMiddleRace();
void deleteMiddleRace();

int main() {

    


    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/