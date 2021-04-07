// For Part 1 Problem 4
//
// (Real, Imag)
// (A, B) * (C, D) = (R, I)
// A, B, C, D are all two dimension int array to represent Matrix
// n means the n*n Matrix
void(int** A, int** B, int** C, int** D, int** R, int** I, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            for(int k = 0; k < n; k++)
            {
                R[i][j] += A[i][k] * C[k][j] - B[i][k] * D[k][j];
                I[i][j] += A[i][k] * D[k][j] + B[i][k] * C[k][j];
            }
        }
    }
}