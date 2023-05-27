/*
   Project #3: Sequence Alignment
   Description: Analyze two DNA sequences and perform alignment using Needleman-Wunsch
                algorithm. The output of this program is the optimal alignment of the
                sequences.
   Developed By: Gustavo A. Rassi Fuentes
   Course: Design & Analysis of Algorithms
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    /* Clear the terminal before the program is executed. */
    system("clear"); // For macOS version of vscode
    //system("cls"); // For windows version of vscode

    /* Open the input file. */
    ifstream inFile("sample.txt");
    if(!inFile.is_open())
    {
        cout << "Could not open file." << endl;
        return 0;
    }

    /* Set the variables to read the input file. */
    int length_X, length_Y, gap_cost, mismatch_cost;
    string X, Y;

    /* Read values from the file. */
    inFile >> length_X >> length_Y;

    /* Store sequences in the strings. */
    X.resize(length_X);
    Y.resize(length_Y);

    /* Set gap and mismatch cost. */
    inFile >> gap_cost >> mismatch_cost;

    /* Read sequences and store them in strings. */
    inFile >> X >> Y;

    /* Create two-dimensional array. */
    int A[length_X + 1][length_Y + 1];

    /* Initialize with base cases (using 0 characters from either string). */
    for(int i = 0; i <= length_X; i++)
        A[i][0] = i * gap_cost;
    for(int j = 0; j <= length_Y; j++)
        A[0][j] = j * gap_cost;
    
    int match;

    /* Main loop. */
    for(int i = 1; i <= length_X; i++)
        for(int j = 1; j <= length_Y; j++)
        {
            /* If there's no match, then set the mismatch penalty. */
            if(X[i - 1] == Y[j - 1])
                match = 0;
            else
                match = mismatch_cost;
            /* Use the smallest value of the three cases. */
                              // Case 1            // Case 2              // Case 3
            A[i][j] = min(min(A[i-1][j-1] + match, A[i-1][j] + gap_cost), A[i][j-1] + gap_cost);
        }

    /* Reconstruction */
    string Xaligned = "";
    string Yaligned = "";
    int i = length_X;
    int j = length_Y;

    while(i > 0 && j > 0)
    {
        /* If both string sequences aren't equal, set mismatch penalty. */
        if (X == Y)
            match = 0;
        else
            match = mismatch_cost;

        if (A[i][j] == A[i - 1][j - 1] + mismatch_cost || X[i - 1] == Y[j - 1]) /* Case 1 was used. */
        {
            Xaligned = X[i - 1] + Xaligned;
            Yaligned = Y[j - 1] + Yaligned;
            i--;
            j--;
        }
        else if(A[i][j] == A[i-1][j] + gap_cost) /* Case 2 was used. */
        {
            Xaligned = X[i - 1] + Xaligned;
            Yaligned = '-' + Yaligned;
            i--;
        }
        else /* Case 3 was used. */
        {
            Xaligned = '-' + Yaligned;
            Yaligned = Y[i - 1] + Yaligned;
            j--;
        }
    }

    /* At least one of the two strings is empty, so at most one of the
    two following loops will execute. */
    while(i > 0)
    {
        Xaligned = X[i-1] + Xaligned;
        Yaligned = '-' + Yaligned;
        i--;
    }
    while(j > 0)
    {
        Xaligned = '-' + Xaligned;
        Yaligned = Y[j-1] + Yaligned;
        j--;
    }

    /* Print NW score and optimal alignment. */
    cout << A[length_X][length_Y] << endl;
    cout << Xaligned << endl;
    cout << Yaligned << endl;

    /* Close the input file. */
    inFile.close();

    return 0;
}