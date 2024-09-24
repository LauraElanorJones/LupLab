#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

// Maximum number of rows for the 2D array
const int MAX_ROWS = 50;
// Maximum number of columns for the 2D array
const int MAX_COLS = 26;

float averageOfColumn(int, float array[][MAX_COLS]);
void AveragesAfterGapYear(float array[][MAX_COLS]);
void averagePerYear(int, float data[][MAX_COLS]);

int main()
{
    ifstream file("FakeStudentRecords.csv");
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    float data[MAX_ROWS][MAX_COLS];
    string line;
    int row = 0;
    while (getline(file, line) && row < MAX_ROWS) {
        stringstream ss(line);
        string cell;
        int col = 0;
        float cellFloat;
        while (getline(ss, cell, ',') && col < MAX_COLS) {
            cellFloat = stof(cell);
            data[row][col] = cellFloat;
            col++;
        }
        row++;
    }
    file.close();
    
    AveragesAfterGapYear(data);
    averagePerYear(2021, data);
    return 0;
}

float averageOfColumn(int column, float col[][MAX_COLS]) {
    float average = 0;
    for (int i = 0; i < MAX_ROWS; i++) {
        average = average + col[i][column];
    }
    average = average / MAX_ROWS;
    return average;
}


void AveragesAfterGapYear(float data[][MAX_COLS]) {
    int quarters[8] = { 8, 1, 3, 8, 1, 3, 8, 1 };
    int startPointQ = 0;
    float csGPAaverage = 0;
    float GPAaverage = 0;
    float csUnitAverage = 0;
    float unitAverage = 0; 
    float gapsTaken = 0;
    float peopleTakingGaps = 0;


    for (int i = 0; i < MAX_ROWS; i++) {
        int startQ = static_cast<int>(data[i][1]) % 10;
        for (int j = 0; j < size(quarters); j++) {
            if (startQ == quarters[j]) {
                int startPointQ = j;
            }
        }
        int endQ = static_cast<int>(data[i][21]) % 10;
        if (quarters[startPointQ+5] != endQ) {                  //Assumes that the amount of quarters taken off is not divisable by 3
            peopleTakingGaps++;
            for (int j = 1; j < MAX_COLS; j += 5) {
                int compareQ1 = static_cast<int>(data[i][j]) % 10;
                int compareQ2 = static_cast<int>(data[i][j+5]) % 10;
                int compareQ1point = 0;
                int compareQ2point = 0;
                for (int k = 0; k < size(quarters); k++) {
                    if (compareQ1 == quarters[k]) {
                        compareQ1point = k;
                        break;
                    }
                }
                
                for (int k = 0; k < size(quarters); k++) {
                    if (compareQ2 == quarters[k]) {
                        compareQ2point = k;
                        break;
                    }
                }
                
                
                if (quarters[compareQ1point + 1] != quarters[compareQ2point]) {
                    gapsTaken++;
                    csGPAaverage += data[i][j + 1];
                    GPAaverage += data[i][j + 2];
                    csUnitAverage += data[i][j + 3];
                    unitAverage += data[i][j + 4];
                }
            }
        }
    }
    csGPAaverage = csGPAaverage / gapsTaken;
    GPAaverage = GPAaverage / gapsTaken;
    csUnitAverage = csUnitAverage / gapsTaken;
    unitAverage = unitAverage / gapsTaken;
    float gapsPerPerson = gapsTaken / peopleTakingGaps;
}

//Takes in a year and prints out the average of units cs and total
// and the average GPA for the year given.
void averagePerYear(int year, float data[][MAX_COLS]) {
    int peopleInYear = 0;
    float csGPAaverage[5] = {0};
    float GPAaverage[5] = { 0 };
    float csUnitAverage[5] = { 0 };
    float unitAverage[5] = { 0 };


    for (int i=0; i < MAX_ROWS; i++) {
        int yearOfData = static_cast<int>(data[i][1]) / 100;
        if (year == yearOfData) {
            peopleInYear++;
            int k = 0;
            for (int j = 1; j < MAX_COLS; j += 5) {
                csGPAaverage[k] += data[i][j + 1];
                GPAaverage[k] += data[i][j + 2];
                csUnitAverage[k] += data[i][j + 3];
                unitAverage[k] += data[i][j + 4];
                k++;
            }
        }
    }
    for (int k = 0; k < size(csGPAaverage); k++) {
        csGPAaverage[k] /= peopleInYear;
        GPAaverage[k] /= peopleInYear;
        csUnitAverage[k] /= peopleInYear;
        unitAverage[k] /= peopleInYear;
    }

    cout << "Cs GPA Average For " << year << ": ";
    for (int i = 0; i < size(csGPAaverage); i++)
        cout << csGPAaverage[i] << " ";
    cout << endl;

    cout << "Total GPA Average For " << year << ": ";
    for (int i = 0; i < size(csGPAaverage); i++)
        cout << GPAaverage[i] << " ";
    cout << endl;

    cout << "Cs Unit Average For " << year << ": ";
    for (int i = 0; i < size(csGPAaverage); i++)
        cout << csUnitAverage[i] << " ";
    cout << endl;

    cout << "Total Unit Average For " << year << ": ";
    for (int i = 0; i < size(csGPAaverage); i++)
        cout << unitAverage[i] << " ";
    cout << endl;
}
