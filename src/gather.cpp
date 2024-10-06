#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

void parsec_roi_begin() 
{

}

void parsec_roi_end() 
{

}


// Function to read the input matrix from the input filename
vector<vector<int> > readMatrix(string filename) {
	vector< vector<int> > matrix;
	string line;
	ifstream infile;
	infile.open (filename.c_str());

	int i = 0;
	while (getline(infile, line) && !line.empty()) {
		istringstream iss(line);
		matrix.resize(matrix.size() + 1);
		int a, j = 0;
		while (iss >> a) {
			matrix[i].push_back(a);
			j++;
		}
		i++;
	}

	infile.close();
	return matrix;
}

// Function to generate a random value
int generateRandomNumber(int maximumVal){
  return rand()%maximumVal;
}

// Function to gather numSteps values into the input matrix
void gather(vector< vector<int> > tensor, int numSteps) {
	int n = tensor.size();
        // Result set to return numSteps gathered values
        vector<int> gatheredData;
        // Loop to scatter numSteps values into the tensor
	for(int i=0;i<numSteps;i++){
          // Generate random row and random column
          int randomRow = generateRandomNumber(n);
          int randomColumn = generateRandomNumber(n);
          // Fetch the value at randomRow and randomCol and add to result set
          gatheredData.push_back(tensor[randomRow][randomColumn]);
        }
        //cout<<"\nGathered Data from the Tensor :: \n";
        // Printing the gathered data
	//for(int i=0;i<gatheredData.size();i++){
	  //cout<<gatheredData[i]<<" ";
	//}
	//cout<<"\n";
}


// Function to print the input matrix
void printMatrix(vector< vector<int> > matrix) {
	vector< vector<int> >::iterator it;
	vector<int>::iterator inner;
	for (it=matrix.begin(); it != matrix.end(); it++) {
		for (inner = it->begin(); inner != it->end(); inner++) {
			cout << *inner;
			if(inner+1 != it->end()) {
				cout << "\t";
			}
		}
		cout << endl;
	}
}

int main (int argc, char* argv[]) {
	string filename;
	if (argc < 3) {
		filename = "2000.in";
	} else {
		filename = argv[2];
	}
	vector<vector<int> >  tensor = readMatrix (filename);
        //cout<<"\nInput Tensor :: \n";
        //printMatrix(tensor);
        //Begin recording memory
        parsec_roi_begin();
        // Gather 1000 random values from the input tensor
	gather(tensor,1000);
        parsec_roi_end();
        //End recording memory
	return 0;
}
