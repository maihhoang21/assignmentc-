#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>

using namespace std;

struct Record {
    string date;
    double open;
    double adjClose;
    double percentChange;
};

int main() {
    
    ifstream file("/Users/maihoang/Desktop/YahooProject/TSLA.csv");  

    string line;
    vector<Record> records;

    // Skip header line
    getline(file, line);

    // Read data from the file
    while (getline(file, line)) {
        stringstream ss(line);
        string date, openStr, adjCloseStr;
        double open, adjClose;

        getline(ss, date, ','); 
        getline(ss, openStr, ',');  
        getline(ss, adjCloseStr, ',');  

        //  strings to doubles
        try {
            open = stod(openStr);
            adjClose = stod(adjCloseStr);
        } catch (const invalid_argument& e) {
            cout << "Error: Invalid data at line: " << line << endl;
            continue; 
        }

        //  percent change The percent change is defined as follows:(adjusted close price – open price) / open price 
        double percentChange = ((adjClose - open) / open) * 100;

        // the record
        records.push_back({date, open, adjClose, percentChange});
    }

    // check data if there is not found 
    if (records.empty()) {
        cout << "No valid data found!" << endl;
        return 1;
    }

    //  date range 
    cout << "This program will analyze TSLA" << endl;  
    cout << "from " << records.front().date << " to " << records.back().date << endl;
    cout << records.size() << " trading day(s) exist in the file." << endl;

    // input the reocord 
    int numRecords;
    cout << "How many increase records do you want to find? ";
    cin >> numRecords;

    // input
    while (cin.fail() || numRecords <= 0) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Please enter a valid number of records: ";
        cin >> numRecords;
    }

    // if no records 
    while (numRecords > records.size()) {
        cout << "The file does not contain enough trading days." << endl;
        cout << "There are only " << records.size() << " trading day(s)." << endl;

        // record available 
        cout << "File Preview:" << endl;
        for (int i = 0; i < records.size(); i++) {
            cout << records[i].date << "\t"
                 << fixed << setprecision(2) << records[i].open << "\t"
                 << fixed << setprecision(2) << records[i].adjClose << "\t"
                 << fixed << setprecision(2) << records[i].percentChange << "%" << endl;
        }

        // run again 
        cout << "How many increase records do you want to find? ";
        cin >> numRecords;

        // input second time 
        while (cin.fail() || numRecords <= 0) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Please enter a valid number of records: ";
            cin >> numRecords;
        }
    }

    // descending order
    sort(records.begin(), records.end(), [](const Record& a, const Record& b) {
        return a.percentChange > b.percentChange;
    });

    // Output 
    cout << "\nDate\t\tOpen\tAdjusted Close\tPercent Change" << endl;
    cout << "--------------------------------------------------------" << endl;

    for (int i = 0; i < numRecords && i < records.size(); i++) {
        cout << left << setw(12) << records[i].date
             << setw(10) << fixed << setprecision(2) << records[i].open
             << setw(15) << fixed << setprecision(2) << records[i].adjClose
             << setw(12) << fixed << setprecision(2) << records[i].percentChange << "%" << endl;
    }

    
    cout << "\nPress any key to continue..." << endl;
    cin.ignore();  
    cin.get();     

   
}
