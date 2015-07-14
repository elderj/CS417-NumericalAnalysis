#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "Jacobi.h"
#include "GaussSiedel.h"
#include "SuccessiveOverRelaxation.h"
#include "GaussianElimination.h"
#include "LUDecomposition.h"
#include "Bisection.h"
#include "Regula.h"
#include "Newton.h"

using namespace std;

vector<double> MatrixFileStream();


int main ()
{
    cout << "CS 417" << endl;

    cout << "\n1:Jacobi Iteration" << endl;
    cout << "2:Gauss-Siedel Iteration" << endl;
    cout << "3:Successive Over Relaxation" << endl;
    cout << "4:Gaussian Elimination" << endl;
    cout << "5:LU Decomposition" << endl;
    cout << "6:Bisection" << endl;
    cout << "7:Regular Falsi" << endl;
    cout << "8:Newton's Method" << endl;

    unsigned short int method;
    vector<double> dataStream;
    cout << "\nSelect Method:" ; cin >> method;

    if(method == 1)
    {
        cout << "\nJacobi Iteration" << endl;
        dataStream = MatrixFileStream();
        Jacobi j(dataStream);
    }
    if(method == 2)
    {
        cout << "\nGauss Siedel Iteration" << endl;
        dataStream = MatrixFileStream();
        GaussSiedel gs(dataStream);
    }
    if(method == 3)
    {
        cout << "\nSuccessive Over-Relaxtion" << endl;
        dataStream = MatrixFileStream();
        SuccessiveOverRelaxation sor(dataStream);
    }
    if(method == 4)
    {
        cout << "\nGaussian Elimination" << endl;
        dataStream = MatrixFileStream();
        GaussianElimination ge(dataStream);
        ge.Output();
    }
    if(method == 5)
    {
        cout << "\nLU Decomposition Method" << endl;
        dataStream = MatrixFileStream();
        LUDecomposition lud(dataStream);
    }
    if(method == 6)
    {
        cout << "\nBisection Method" << endl;
        Bisection b;
    }
    if(method == 7)
    {
        cout << "\nRegula Falsi Method" << endl;
        Regula r;
    }
    if(method == 8)
    {
        cout << "\nNewton's Method" << endl;
        Newton n;
    }
    if(method > 8 || method < 1)
    {
        cout << "\nSelection is not valid." << endl;
        cout << "Enter the integer to   " << endl;
        cout << "the left of the method " << endl;
        cout << "you wish to use.       " << endl;
    }

    return 0;
}

vector<double> MatrixFileStream()
{
    vector<double> ds;
    string filename, line;
    double temp;
    ifstream myfile;
    cout << "\nSelect Datafile: ";
    cin >> filename;
    myfile.open(filename.c_str());

   if (myfile.is_open())
    {
        while ( getline(myfile, line) )
        {
            istringstream iss(line);
            do
            {
                string sub;
                iss >> sub;
                if (sub != "")
                {
                    stringstream(sub) >> temp;
                    ds.push_back(temp);
                }
            }
            while (iss);
        }
        myfile.close();

    }
    else
    {
        cout << "\nError File was mispelled, does not exist, or is not in the correct directory." << endl;
    }
    return ds;

}
