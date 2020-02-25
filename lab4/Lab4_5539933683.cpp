#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#define ROWS 20
#define COLS 10

class BuildMatrix{
	private:
		int value[ROWS][COLS];
		int repeat_row_index = -1;
		int first_number = -1;
		int iteration =0;
	public:
		int get_first_number(){
			return first_number;
		}
		int get_repeat_row_index(){
			return repeat_row_index;
		}
		int get_iteration(){
			return iteration;
		}
		void clear_iteration(){
			iteration =0;
		}
		void sort_row(int row){
			for(int i=0; i<COLS; i++){
				int colum = -1;
				int min = value[row][i];
				for(int j=i+1; j<COLS; j++){
					if(value[row][j]<min){
						min = value[row][j];
						colum=j;
					}
				}
				if(colum >= 0){
					int temp = value[row][i];
					value[row][i] = value[row][colum];
					value[row][colum] = temp;
				}
			}
		}
		int binary_search(int row){
			//cout << first_number <<endl;
			int min =0;
			int max =COLS-1;
			int mid = (max - min)/2;
			while(min < max){
				iteration ++;
				if(value[row][mid]==first_number){
					return mid;
				}
				else if(value[row][mid] > first_number){
					max = mid-1;
				}
				else{
					min = mid+1;
				}
				mid = (max-min)/2;
			}
			return -1;
		}
		int linear_search(){
			int iteration = 0;
			for(int i = 0; i<ROWS; i++){
				for(int j=0; j<COLS; j++){
					iteration++;

					if(!(i==0 && j==0) && value[i][j]==first_number){
						repeat_row_index= i;
						return iteration;	
					}								
				}
			}
			return -1;
		}
		void load_data(string fname){
			ifstream myReadFile; //creates and object of the file
			myReadFile.open(fname);//open the file "fname"
			if(myReadFile.is_open()){ //read file after checking if open
				for(int i =0; i<ROWS; i++){
					for(int j=0; j<COLS; j++){
						myReadFile >> value[i][j];
					}

				}
				first_number = value[0][0];
				myReadFile.close();//after file reading close it
			}	
		}
		// displays the row
		void displayRow(int row, ofstream& myWriteFile){
			for(int i=0; i<COLS; i++){
				myWriteFile <<value[row][i] <<" ";
			}
			myWriteFile <<endl;
		}
		void displayMatrix(){
			for(int i=0; i<ROWS; i++){
				for(int j=0; j <COLS; j++){
					cout << value[i][j] <<" ";
				}
			}
			cout << endl;
		}
		

};

int main(){
	BuildMatrix mat;
	
	mat.load_data("input.txt");
	clock_t begin = clock();
	int iteration = mat.linear_search();
	int row = mat.get_repeat_row_index();

	clock_t end = clock();
	double elapsed_secs = double(end-begin)/CLOCKS_PER_SEC;

	ofstream myWriteFile;

	myWriteFile.open("output.txt");
	if (myWriteFile.is_open()) {
		myWriteFile << "/******************************/"<<endl;

		int colum;
		myWriteFile << elapsed_secs << endl;
		myWriteFile << iteration << endl;

		mat.sort_row(row);
		mat.displayRow(row, myWriteFile);
		myWriteFile << mat.binary_search(row) << endl;
		myWriteFile << (row + 1) << endl;
		myWriteFile << "/******************************/"<<endl;

		myWriteFile.close();		
	}
	
	return 0;
}



