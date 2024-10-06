#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <bits/stdc++.h>

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


// Function to print the convolved matrix
void printConvolvedMatrix(vector< vector<double> > matrix){
        for(int i=0;i<matrix.size();i++){
	  for(int j=0;j<matrix[i].size();j++){
            cout<<matrix[i][j]<<" ";
          }
          cout<<"\n";
	}

}

// Function to print the input tensor
void printInputMatrix(vector< vector<int> > matrix){
	for(int i=0;i<matrix.size();i++){
          for(int j=0;j<matrix[0].size();j++){
            cout<<matrix[i][j]<<" "; 
	  }
          cout<<"\n";
	}

}

// Function to convolve a 3x3 gaussian filter over the input tensor
vector<vector<double> > convolve(vector<vector<int> > matrix, vector<vector<double> > filter){

    int m = matrix.size();
    int n = matrix[0].size();
    int f = filter.size();
    int diff = f / 2;
    vector<vector<double>> result(m, vector<double>(n, 0.0));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            double sum = 0.0;
            for (int fi = 0; fi < f; ++fi) {
                for (int fj = 0; fj < f; ++fj) {
                    int mi = i + fi - diff;
                    int mj = j + fj - diff;
                    if (mi >= 0 && mi < m && mj >= 0 && mj < n) {
                        sum += matrix[mi][mj] * filter[fi][fj];
                    }
                }
            }
            result[i][j] = sum;
        }
    }
    return result;

}

int main (int argc, char* argv[]) {
	string filename;
	vector<vector<double>> filter =
        {
          {0.0625,0.125,0.0625},
          {0.125,0.25,0.125},
          {0.0625,0.125,0.0625},
        };
	if (argc < 3) {
		filename = "2000.in";
	} else {
		filename = argv[2];
	}
	vector<vector<int> >  tensor = readMatrix (filename);
        //cout<<"\nInput Tensor :: \n";
        //printInputMatrix(tensor);
        //Begin recording memory
        parsec_roi_begin();
        // Convolve the input matrix with the 3x3 Gaussian filter
	vector<vector<double> > convolved = convolve(tensor,filter);
        parsec_roi_end();
        //End recording memory
        //cout<<"\n\nConvolved Tensor :: \n";
        //printConvolvedMatrix(convolved);
	return 0;
}
