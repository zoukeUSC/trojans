#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

#define SIZE 3

struct Profit {
    double amount;  //dollar amount
    int weeks;              //duration of profit
    Profit() {
        amount ={0};
        weeks ={0};
    }
    Profit(double amt, int wks) {
        amount = amt;
        weeks = wks;
    }
};

class KWP {
private:
    Profit profit[SIZE];  //array of type struct Profit
    int U_percentage; //percentage paid out to Kourosh
    int totalWeeks;
    int Z;


public:

    KWP() {
        U_percentage = 0;
        totalWeeks = 0;
        Z = 0;
        ofstream myFile;
        myFile.open("output.txt",ios::trunc);
        myFile << "Entering KWP Constructor"<<endl;
        myFile<< "Attributes Initialized"<<endl;
        myFile.close();
    }

    KWP(string dataFileName) {
        U_percentage = 0;
        totalWeeks = 0;
        Z = 0;
        loadData(dataFileName);
        ofstream myFile;
        myFile.open("output.txt", ios::trunc);
        myFile << "Entering KWP Constructor"<<endl;
        myFile<< "Attributes Initialized and Data loaded"<<endl;
        myFile.close();
    }

    ~KWP() {
        cout << "inside destructor" << endl;
        ofstream myFile;
        myFile.open("output.txt", ios::app);
        myFile << "Entering KWP Destructor"<<endl;
        myFile.close();
    }

    int getU() {
        return U_percentage;
    }

    void fetchProfitData(string infile, int index) {
        istringstream strStream(infile);
        int weeks = 0;
        double  amount = 0;
        strStream >> weeks;
        strStream >> amount;
        Profit newProfit(amount, weeks);
        profit[index] = newProfit;
        totalWeeks += weeks;
    }

    int getZ() {
        return Z;
    }

    void setZ(int z) {
        Z = z;
    }

    void loadData(string fileName) {
        ifstream infile(fileName);
        if (infile.is_open()) {
            int index = 0;
            for (string line; getline(infile, line); ) {
                if (line.at(0) != '/') {
                    if (index < SIZE) {
                        fetchProfitData(line, index);
                    }
                    else {
                        U_percentage = stoi(line);
                        break;
                    }
                    index++;
                }
            }
            infile.close();
        }
    }
    

    double GetProfit1() {
        double totalProfit = 0;
        for (int i = 0; i < SIZE; i++) {
            totalProfit += profit[i].amount * profit[i].weeks * (1 - U_percentage / 100.0);
        }
        double avgPerWeek = totalProfit / totalWeeks;
        return Z * avgPerWeek;
    }
    double GetProfit(int cycle) {
        if ((cycle - 1) < 0) {
            return 0;
        }
        double interMediate = profit[cycle - 1].amount * profit[cycle - 1].weeks * (1-U_percentage / 100.0);
        return  interMediate + GetProfit(cycle - 1);;
    }
    double getAverageProfit() {
        double avgPerWeek = GetProfit(SIZE) / totalWeeks;
        return Z * avgPerWeek;
    }
    void SetProfit(int amount) {
        U_percentage = amount;
    }
};

class KYP {
private:
    Profit* profit;  //array of type struct Profit
    int U_percentage; //percentage paid out to Kourosh
    int totalWeeks;
    int Z;
public:
    KYP() {
        profit = new Profit[SIZE];
        U_percentage = 0;
        totalWeeks = 0;
        Z = 0;
        ofstream myFile;
        myFile.open("output.txt",ios::trunc);
        myFile << "Entering KYP Constructor"<<endl;
        myFile<< "Attributes Initialized"<<endl;
        myFile.close();
    }
    KYP(string dataFileName) {
        profit = new Profit[SIZE];
        U_percentage = 0;
        totalWeeks = 0;
        Z = 0;
        loadData(dataFileName);
        ofstream myFile;
        myFile.open("output.txt",ios::trunc);
        myFile << "Entering KYP Constructor"<<endl;
        myFile<< "Attributes Initialized and Data loading"<<endl;
        myFile.close();
        
    }

    ~KYP() {
        //free allocated memory
        delete[] profit;
        ofstream myFile;
        myFile.open("output.txt", ios::app);
        myFile << "Entering KYP Destructor"<<endl;
        myFile.close();
    }

    int getU() {
        return U_percentage;
    }
    void fetchProfitData(string infile, int index) {
        istringstream strStream(infile);
        int weeks = 0;
        double  amount = 0;
        strStream >> weeks;
        strStream >> amount;
        Profit newProfit(amount, weeks);
        profit[index] = newProfit;
        totalWeeks += weeks;
    }

    int getZ() {
        return Z;
    }
    void setZ(int z) {
        Z = z;
    }
    
    
    void loadData(string fileName) {
        ifstream infile(fileName);
        if (infile.is_open()) {
            int index = 0;
            for (string line; getline(infile, line); ) {
                if (line.at(0) != '/') {
                    if (index < SIZE) {
                        fetchProfitData(line, index);
                    }
                    else {
                        U_percentage = stoi(line);
                        break;
                    }
                    index++;
                }
            }
            infile.close();
        }
    }
    

    

    double GetProfit(int cycle) {   //recursive function to calc profit
        if ((cycle - 1) < 0) {
            return 0;
        }
        double interMediate = profit[cycle-1].amount * profit[cycle-1].weeks * (U_percentage / 100.0);
        return  interMediate  + GetProfit(cycle - 1);;
    }
    double getAverageProfit() {
        double avgPerWeek = GetProfit(SIZE) / totalWeeks;
        return Z * avgPerWeek;
    }
    void SetProfit(int amount) {
        U_percentage = amount;
    }
};

int main() {
    KWP kayneProfit;
    KYP kouroshProfit;
    kayneProfit.loadData("input.txt");
    kouroshProfit.loadData("input.txt");
    cout << "Enter Z weeks (0-52): ";
    int z;
    cin >> z;
    kayneProfit.setZ(z);
    kouroshProfit.setZ(z);
    cout << fixed << setprecision(2);
    cout << "KW's profit for " << kayneProfit.getZ() << " number of weeks in average is estimated $" <<
        kayneProfit.getAverageProfit() << ", out of which " << kayneProfit.getU() << "%, i.e., $" <<
        kouroshProfit.getAverageProfit() << " is KYs" << endl;

    return 0;
}
