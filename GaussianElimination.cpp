#include "GaussianElimination.h"

GaussianElimination::GaussianElimination(vector<double> & nput)
{
    rows = nput[0];
    cols = nput[0];
    SetMatrices(rows, cols, nput);
    Solve();
}

void GaussianElimination::SetMatrices(int rows, int cols, vector<double> & mtxData)
{
    vector<double> shifter;
    mtxSize = rows * cols;
    int aLimit = mtxSize + 2 ; // Add 2 to accomodate for rows and cols in input
    unsigned short int r = 0;
    unsigned short int c = 0;

    ///Put values into A
    //cout << "A:" << endl;
    for (int i = 2; i < aLimit; i++)
    {
        //cout << mtxData[i] << "             " << r << c << "\n" ;
        shifter.push_back(mtxData[i]);
        c++;
        if (c == cols)
        {
            c = 0;
            mtxA.push_back(shifter);
            shifter.clear();
            r++;
        }

    }
    ///Put Values into b
    //cout << "\nB:" << endl;
    for (int i = aLimit; i<aLimit+rows; i++)
    {
        //cout << mtxData[i] << endl;
        mtxB.push_back(mtxData[i]);
       // cout << "head" << endl;
    }
}



void GaussianElimination::Solve()
{
    AugmentedMatrix  * ag = new AugmentedMatrix(mtxA,mtxB);
    mtxB = ag->RREF();

}

void GaussianElimination::Output()
{

  cout << "\n Output file saved to 'GaussianElimination.txt'" << endl;

  ofstream myfile ("GaussianElimination.txt");
  if (myfile.is_open())
  {
    for(int i = 0; i < mtxB.size(); i++)
    {
        myfile << mtxB[i] << " ";
    }
    myfile.close();
  }
  else cout << "Unable to open file";

}




