#include <stdio.h>
#include <stdlib.h>



void printmatrix(double** matr, int ylength, int xlength) {

    
    for (int i = 0; i < ylength; i++) {
        for (int j = 0; j < xlength; j++) {
            printf("%6lf%s", matr[i][j], (j < xlength - 1) ? " " : "\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
        }
    }
            
        }
    }
}

void printvector(double* yvec, int length) {
    for (int i = 0; i < length; i++) {
        printf("%.0lf\n", yvec[i]);
    }
}


void deletematrix(double** matrix, int rows) {
    for (int i=0; i<rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

void matrixmult(double** mat1, double** mat2, double** answermatrix, int y1, int x1, int y2, int x2) {
    for (int i = 0; i < y1; i++) {
        for (int j = 0; j < x2; j++) {
            double sum = 0;
            for (int k = 0; k < y2; k++) {
                sum += mat1[i][k] * mat2[k][j];
            }
            answermatrix[i][j] = sum;
        }
    }
}


void matrixvectormult(double** mat1, double* vector, double* output, int y1, int x1) {
    for (int i = 0; i < y1; i++) {
        output[i] = 0;
        for (int j = 0; j < x1; j++) {
            output[i] += mat1[i][j] * vector[j];
        }
    }
}

void calculateinverse(double** matrix, double** answermatrix, int sidelength) {
    
    for (int i = 0; i < sidelength; i++) {
        double pivot = matrix[i][i];
        for (int j = 0; j < sidelength; j++) {
            matrix[i][j] /= pivot;
            answermatrix[i][j] /= pivot;
        }

        for (int k = 0; k < sidelength; k++) {
            if (k == i) {
                continue;
            }

            double factor = matrix[k][i];
            for (int m = 0; m < sidelength; m++) {
                matrix[k][m] -= factor * matrix[i][m];
                answermatrix[k][m] -= factor * answermatrix[i][m];
            }
        }
    }

    
    for (int i = sidelength - 1; i >= 0; i--) {
        for (int j = i - 1; j >= 0; j--) {
            double factor = matrix[j][i];
            for (int k = 0; k < sidelength; k++) {
                matrix[j][k] -= factor * matrix[i][k];
                answermatrix[j][k] -= factor * answermatrix[i][k];
            }
        }
    }
}

int main(int argc, char* argv[]) {
for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
        
        }
    }
    
    FILE* fp;
    fp = fopen(argv[1], "r");
for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
           
        }
    }
    int datapoints; // m
    int features; // n

    fscanf(fp, "train\n%d", &features);
    features++;
    fscanf(fp, "%d", &datapoints);

   double** Xmatrix = (double**)malloc(datapoints * sizeof(double*));
for (int i = 0; i < datapoints; i++) {
    Xmatrix[i] = (double*)calloc(features, sizeof(double));
    Xmatrix[i][0] = 1;
}
    double* Yvector = (double*)malloc(datapoints*sizeof(double));

    for (int i=0; i<datapoints; i++) {
        for (int j=1; j<features+1; j++) { 
            if (j==features){
                fscanf(fp, "%lf", &Yvector[i]);
                continue;
            }
            fscanf(fp, "%lf", &Xmatrix[i][j]);
        }
    }


   
    double** trans = (double**)malloc(features * sizeof(double*));
        for (int i = 0; i < features; i++) {
            trans[i] = (double*)malloc(datapoints * sizeof(double));
        for (int j = 0; j < datapoints; j++) {
        trans[i][j] = Xmatrix[j][i];
    }
}

for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            
        }
    }


    double** XTX = (double**)malloc(features*sizeof(double*));
    for (int i=0; i<features; i++) {
        XTX[i] = (double*)malloc(features*sizeof(double));
    }

    matrixmult(trans, Xmatrix, XTX, features, datapoints, datapoints, features);
   
    double** XTXinv = (double**)malloc(features*sizeof(double*));
    for (int i=0; i<features; i++) {
        XTXinv[i] = (double*)malloc(features*sizeof(double));
    }

    for (int i=0; i<features; i++) {
        for (int j=0; j<features; j++) {
            if (i==j) {XTXinv[i][j] = 1;}
            else {XTXinv[i][j] = 0;}
        }
    }

    calculateinverse(XTX, XTXinv, features);

    
    double** XTXinvtrans = (double**)malloc(features * sizeof(double*));
        for (int i = 0; i < features; i++) {
    XTXinvtrans[i] = (double*)malloc(datapoints * sizeof(double));
    for (int j = 0; j < datapoints; j++) {
    
        XTXinvtrans[i][j] = 0.0; 
    }
}
    matrixmult(XTXinv, trans, XTXinvtrans, features, features, features, datapoints);

    double* finalW = (double*)malloc(features*sizeof(double));

    matrixvectormult(XTXinvtrans, Yvector, finalW, features, datapoints);

    fclose(fp);


    FILE* fp2;
    fp2 = fopen(argv[2], "r");

    int datapointsT; 
    int featuresT; 

    fscanf(fp2, "data\n%d", &featuresT);
    featuresT++;
    fscanf(fp2, "%d", &datapointsT);
    

  double** Xtest = (double**)malloc(datapointsT*sizeof(double*));
    for (int i=0; i<datapointsT; i++) {
        Xtest[i] = (double*)malloc(featuresT*sizeof(double));
        Xtest[i][0] = 1;
    }


    for (int i=0; i<datapointsT; i++) {
        for (int j=1; j<featuresT; j++) {
            fscanf(fp2, "%lf", &Xtest[i][j]);
        }
    }

    fclose(fp2);

    double* finalprices = (double*)malloc(datapointsT*sizeof(double));

    matrixvectormult(Xtest, finalW, finalprices, datapointsT, featuresT);
for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
        }
    }

    printvector(finalprices, datapointsT);

for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
        }
    }
    deletematrix(Xmatrix, datapoints);
    deletematrix(trans, features);
    deletematrix(XTX, features);
    deletematrix(XTXinv, features);
    deletematrix(XTXinvtrans, features);
    deletematrix(Xtest, datapointsT);
    free(Yvector);
    free(finalW);
    free(finalprices);

    return 0;
}