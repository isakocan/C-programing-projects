#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>

double f(double x);
double df(double x);
void bisection();
void RegulaFalsi();
void NewtonRaphson();
void findNumaricalDerivative();
double simphson_1_3(float a, float b, int n);
double simphson_3_8(float a, float b, int n);
void Simphson();
void Trapezoidal();
float** createMatrix(int size);
float** getsMatrix(int size);
void writeMatrix(float** matrix, int n);
void freeMatrix(float** matrix, int size);
float determinant(float** matrix, int size);
float** cofactor(float** matrix, int size);
float** tranpose(float** matrix, int size);
float** inverseMatrix(float** matrix, int size);
void findInverseMatrix();
void getsEquations(float** coef_matrix, float* res_matrix, int unknown_count);
void writeGaussEl(float** coef_matrix, float* res_matrix, int size);
void writeArray(float* array, int size);
void replaceRow(float** matrix, float* array, int row, int col, int size);
void GaussElimination();
void GaussSeidel();
void diffTable(float* x, float* y, float* delta_y, int size);
int fact(int n);
void GregoryNewton();






int main(){
	
	int menu;
	
	do{
		system("CLS");
		printf("-___Menu___-\n\nQuit: 0\nBisection: 1\nRegula-Falsi: 2\nNewton-Raphson: 3\nInverse Matrix: 4\nGauss Elimination: 5\nGauss-Seidel: 6\nNumerical Derivative: 7\nSimpson's Rule: 8\nTrapezoidal Rule: 9\nGregory-Newton: 10\n\nYour Choice: ");
		scanf("%d", &menu);
		
		switch(menu){
			case 0:
				printf("\n\n\n\nQuitting...");
				return 0;
				break;
			case 1:
				do{
					system("CLS");
					printf("Finding Equation Root by Bisection Method\n");
					printf("-------------------- O ------------------\n\n\n");
					bisection();
					printf("\n\nPress 1 to continue this operation.\nPress 0 to go to the menu.\n\nYour choice: ");
					scanf("%d", &menu);
				}while(menu != 0);
				break;
			case 2:
				do{
					system("CLS");
					printf("Finding Equation Root by Regula-Falsi Method\n");
					printf("--------------------- O --------------------\n\n\n");
					RegulaFalsi();
					printf("\n\nPress 1 to continue this operation.\nPress 0 to go to the menu.\n\nYour choice: ");
					scanf("%d", &menu);
				}while(menu != 0);
				break;
			case 3:
				do{
					system("CLS");
					printf("Finding Equation Root by Newton-Raphson Method\n");
					printf("---------------------- O ---------------------\n\n\n");
					NewtonRaphson();
					printf("\n\nPress 1 to continue this operation.\nPress 0 to go to the menu.\n\nYour choice: ");
					scanf("%d", &menu);
				}while(menu != 0);
				break;
			case 4:
				do{
					system("CLS");
					printf("Finding the Inverse of a Matrix\n");
					printf("-------------- O --------------\n\n\n");
					findInverseMatrix();
					printf("\n\nPress 1 to continue this operation.\nPress 0 to go to the menu.\n\nYour choice: ");
					scanf("%d", &menu);
				}while(menu != 0);
				break;
			case 5:
				do{
					system("CLS");
					printf("Solving equations with Gauss Elimination method\n");
					printf("----------------------- O ---------------------\n\n\n");
					GaussElimination();
					printf("\n\nPress 1 to continue this operation.\nPress 0 to go to the menu.\n\nYour choice: ");
					scanf("%d", &menu);
				}while(menu != 0);
				
				break;
			case 6:
				do{
					system("CLS");
					printf("Solving equations with Gauss-Seidel Iteration method\n");
					printf("----------------------- O ---------------------\n\n\n");
					GaussSeidel();
					printf("\n\nPress 1 to continue this operation.\nPress 0 to go to the menu.\n\nYour choice: ");
					scanf("%d", &menu);
				}while(menu != 0);

				break;
			case 7:
				do{
					system("CLS");
					printf("Calculating Function Derivative with Numerical Derivative\n");
					printf("-------------------------- O ------------------------\n\n\n");
					findNumaricalDerivative();
					printf("\n\nPress 1 to continue this operation.\nPress 0 to go to the menu.\n\nYour choice: ");
					scanf("%d", &menu);
				}while(menu != 0);
				break;
			case 8:
				do{
					system("CLS");
					printf("Integral Calculation with Simphson's Rule\n");
					printf("-------------------- O ------------------\n\n\n");
					Simphson();
					printf("\n\nPress 1 to continue this operation.\nPress 0 to go to the menu.\n\nYour choice: ");
					scanf("%d", &menu);
				}while(menu != 0);
				break;
			case 9:
				do{
					system("CLS");
					printf("Integral Calculation with Trapezoidal Rule\n");
					printf("--------------------- O ------------------\n\n\n");
					Trapezoidal();
					printf("\n\nPress 1 to continue this operation.\nPress 0 to go to the menu.\n\nYour choice: ");
					scanf("%d", &menu);
				}while(menu != 0);
				break;
			case 10:
				do{
					system("CLS");
					printf("Gregory-Newton Interpolation Method\n");
					printf("---------------- O ----------------\n\n\n");
					GregoryNewton();
					printf("\n\nPress 1 to continue this operation.\nPress 0 to go to the menu.\n\nYour choice: ");
					scanf("%d", &menu);
				}while(menu != 0);
				break;
				break;
			default:
				system("CLS");
				printf("[i]-> Invalid choice!\nPlease try again.\n\n\n\n");
				break;
		}
	}
	while(1);
}


double f(double x){
	return (double) 2*sin(x*pow(2.71828182846, x));
}


double df(double x){
	float h = 0.000001;
	return (f(x+h) - f(x-h)) / (2*h);
}


void bisection(){
	int iter=0, flag=0;
	float a, b, c, tolerance, error;
	printf("Enter starting values.\na: ");
	scanf("%f", &a);
	printf("b: ");
	scanf("%f", &b);
	printf("Enter the error value that you can tolerate: ");
	scanf("%f", &tolerance);
	
	error = fabs(b-a)/pow(2,iter);
	
	while(error>=tolerance && iter<100){

        c = (a+b)/2.0;
		
        if(f(a) * f(c) < 0){
            b = c;
        }
		else{
            a = c;
        }
        iter++;
        error = fabs(b-a)/pow(2,iter);
    }
	
	printf("\n\nThe root of your equation is x: %f \nError: %f\nIteration: %d\n", c, error, iter);
	
}


void RegulaFalsi(){
	int iter=0, flag=0;
	float a, b, c, tolerance, error;
	printf("Enter starting values.\na: ");
	scanf("%f", &a);
	printf("b: ");
	scanf("%f", &b);
	printf("Enter the error value that you can tolerate: ");
	scanf("%f", &tolerance);
	
	error = fabs(b-a)/pow(2,iter);
	
	while(error>=tolerance && iter<100){

        c = ((b*f(a))-(a*f(b))) / (f(a)-f(b));
		
        if(f(a) * f(c) < 0){
            b = c;
        }
		else{
            a = c;
        }
        iter++;
        error = fabs(b-a)/pow(2,iter);
    }
	
	printf("\n\nThe root of your equation is x: %f \nError: %f\nIteration: %d\n", c, error, iter);
}


void NewtonRaphson(){
	int iter=0;
	float x0, x1, tolerance, error;
	printf("Enter the starting value.\nx0: ");
	scanf("%f", &x0);
	printf("Enter the error value that you can tolerate: ");
	scanf("%f", &tolerance);
	
	do{
        x1 = x0 - (f(x0) / df(x0));
        error = fabs(x1-x0);
        x0 = x1;
        iter++;
		
	}while(error>=tolerance && iter<100);
		
	printf("\n\nThe root of your equation is x: %f \nError: %f\nIteration: %d\n", x1, error, iter);
}


void findNumaricalDerivative(){
	
	float x, h;
	float forward_diff, backward_diff, central_diff;
	printf("Enter the x: ");
	scanf("%f", &x);
	printf("Enter the error value that you can tolerate: ");
	scanf("%f", &h);
	
	forward_diff = (f(x+h)-f(x))/h;
	backward_diff = (f(x)-f(x-h))/h;
	central_diff = (f(x+h)-f(x-h))/(2*h);
	
	printf("\nNumerical derivative with forward difference: %f\n", forward_diff);
    printf("Numerical derivative with backward difference: %f\n", backward_diff);
    printf("Numerical derivative with central difference: %f\n", central_diff);
}



double simphson_1_3(float a, float b, int n){
	n = n*2;
	float h = (b-a) / n;
	float sum = f(a) + f(b);
	int i;
	for(i=1;i<n;i+=2){
        sum += 4 * f(a+(i*h));
    }
    for(i=2;i<n-1;i+=2){
        sum += 2 * f(a+(i*h));
    }
    return (h/3.0)*sum;
}


double simphson_3_8(float a, float b, int n){
	n = n*3;
	float h = (b-a) / n;
	float sum = f(a) + f(b);
	int i;
	for(i=1;i<n;i++) {
        if(i % 3 == 0){
            sum += 2 * f(a+(i*h));
        }
		else{
            sum += 3 * f(a+(i*h));
        }
    }
    return (3*h/8.0)*sum;
}


void Simphson(){
	int n;
	float a, b, res1_3, res3_8;
	printf("Enter starting values.\na: ");
	scanf("%f", &a);
	printf("b: ");
	scanf("%f", &b);
	printf("How many pieces? n: ");
	scanf("%d", &n);
	res1_3 = simphson_1_3(a, b, n);
	res3_8 = simphson_3_8(a, b, n);
	printf("\n\nResult of the Integral\n---------------------\n");
	printf("Simphson 1/3: %f\n", res1_3);
	printf("Simphson 3/8: %f\n\n", res3_8);
}


void Trapezoidal(){
	int n, i;
	float a, b, h, sum;
	printf("Enter starting values.\na: ");
	scanf("%f", &a);
	printf("b: ");
	scanf("%f", &b);
	printf("How many pieces? n: ");
	scanf("%d", &n);
	
	h = (b-a)/n;
	sum = 0.5 * (f(a)+f(b));
	for(i=1;i<n;i++) {
        sum += f(a+(i*h));
    }
    sum = h*sum;
    printf("\n\nResult of the Integral\n---------------------\n");
    printf("Trapezoidal rule: %f\n\n", sum);
}


float** createMatrix(int size){
	float** matrix;
	int i;
	matrix = (float**)malloc(size*sizeof(float*));
	for(i=0;i<size;i++){
		matrix[i] = (float*)malloc(size*sizeof(float));
	}	
	return matrix;
}


float** getsMatrix(int size){
	int i,j;
	float** matrix = createMatrix(size);
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			printf("\n->Enter the element of your matrix in row %d, column %d.\na%d,%d: ", i+1,j+1,i+1,j+1);
			scanf("%f", &matrix[i][j]);
		}
	}
	return matrix;
}


void writeMatrix(float** matrix, int n){
	if(matrix != NULL){ 
		printf("\n\n");
		int i,j;
		for(i=0;i<n;i++){
			printf("| ");
			for(j=0;j<n;j++){
				if(matrix[i][j] == 0) printf(" %.6f   ", abs(matrix[i][j]));
				else if(matrix[i][j]<10 && matrix[i][j]>0) printf(" %.6f   ", matrix[i][j]);
				else if(matrix[i][j]<=0 && matrix[i][j]>(-10)) printf("%.6f   ", matrix[i][j]);			
				else if (matrix[i][j]<100 && matrix[i][j]>0) printf(" %.6f  ", matrix[i][j]);
				else if(matrix[i][j]<=0 && matrix[i][j]>(-100)) printf("%.6f  ", matrix[i][j]);
				else if (matrix[i][j]<1000 && matrix[i][j]>0) printf(" %.6f ", matrix[i][j]);
				else printf("%.6f ", matrix[i][j]);
			}
			printf("|\n");
		}
	}
}



void freeMatrix(float** matrix, int size){
	if(matrix != NULL){
		int i;
		for(i=0;i<size;i++){
			free(matrix[i]);
		}
		free(matrix);
	}
}



float determinant(float** matrix, int size){
    if (size == 1) return matrix[0][0];
	
	float coef, det=0, tmpdet;
	int sign, i ,j, k ,l ,m;
	
	if(size > 2){
		float** tmp = createMatrix(size-1);
		for(k=0;k<size;k++){
			for(i=0;i<(size-1);i++){
				l=0;
				for(j=0;j<(size-1);j++){
					if(j==k) l++;
					tmp[i][j] = matrix[i+1][l];
					l++;
				}
			}
			tmpdet = determinant(tmp, (size-1));
			coef = matrix[0][k];
			sign = pow((-1), (2+k));
			det += sign*coef*tmpdet;
		}
		freeMatrix(tmp, size-1);
		return det;
	}
	else{
		det = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
		return det;
	}
}


float** cofactor(float** matrix, int size){
	
	int i,j,k,l,m,n, sign;
	float tmpdet;
	float** cofmatrix = createMatrix(size);
	float** tmp = createMatrix(size-1);
	
	for(k=0;k<size;k++){
		for(l=0;l<size;l++){
			m=0;
			for(i=0;i<size-1;i++){
				if(i==k) m++;
				n=0;
				for(j=0;j<size-1;j++){
					if(j==l) n++;
					tmp[i][j] = matrix[m][n];
					n++;
				}
				m++;
			}
			tmpdet = determinant(tmp, size-1);
			sign = pow(-1, k+l+2);
			cofmatrix[k][l] = sign*tmpdet; 
		}
	}
	freeMatrix(tmp, size-1);
	
	return cofmatrix;
}


float** tranpose(float** matrix, int size){
	float** tmatrix = createMatrix(size);
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			tmatrix[i][j] = matrix[j][i];
		}
	}
	return tmatrix;
}

float** inverseMatrix(float** matrix, int size){
	
	float det = determinant(matrix, size);
	if(det == 0){
		printf("\n\n[i]-> Your matrix has no inverse because its determinant is 0.\n\n");
		return NULL;
	}

	float** invmatrix = createMatrix(size);
	if(size == 1){
		invmatrix[0][0] = (float) 1.0 / matrix[0][0];
		return invmatrix;
	}
	
	float** cofmatrix = cofactor(matrix, size);
	float** adjmatrix = tranpose(cofmatrix, size);
	
	int i,j;
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			invmatrix[i][j] = (float) adjmatrix[i][j] / det;
		}
	}
	freeMatrix(cofmatrix, size);
	freeMatrix(adjmatrix, size);
	return  invmatrix;
}


void findInverseMatrix(){
	int size;
	printf("What is the size of your matrix: ");
	scanf("%d", &size);
	float** matrix = getsMatrix(size);
	system("CLS");
	printf("Your matrix: ");
	writeMatrix(matrix,size);
	printf("\n\n\n\nYour matrixes inverse:");
	float** inverse_matrix = inverseMatrix(matrix, size);
	writeMatrix(inverse_matrix, size);
	freeMatrix(matrix, size);
	freeMatrix(inverse_matrix, size);
}



void getsEquations(float** coef_matrix, float* res_matrix, int unknown_count){
	int i,j;
	for(i=0;i<unknown_count;i++){
		for(j=0;j<unknown_count;j++){
			printf("Enter the %d. coefficient of your %d. equation: ", i+1, j+1);
			scanf("%f", &coef_matrix[i][j]);
		}
		printf("Enter the result of your %d. equation: ", i+1);
		scanf("%f", &res_matrix[i]);
		printf("\n\n");
	}
}



void writeGaussEl(float** coef_matrix, float* res_matrix, int size){
	int i,j;
	for(i=0;i<size;i++){
		printf("|  ");
		for(j=0;j<size;j++){
			if(coef_matrix[i][j] == 0) printf(" %.4f   ", abs(coef_matrix[i][j]));
			else if(coef_matrix[i][j]<10 && coef_matrix[i][j]>0) printf(" %.4f   ", coef_matrix[i][j]);
			else if(coef_matrix[i][j]<=0 && coef_matrix[i][j]>(-10)) printf("%.4f   ", coef_matrix[i][j]);			
			else if (coef_matrix[i][j]<100 && coef_matrix[i][j]>0) printf(" %.4f  ", coef_matrix[i][j]);
			else if(coef_matrix[i][j]<=0 && coef_matrix[i][j]>(-100)) printf("%.4f  ", coef_matrix[i][j]);
			else if (coef_matrix[i][j]<1000 && coef_matrix[i][j]>0) printf(" %.4f ", coef_matrix[i][j]);
			else printf("%.4f ", coef_matrix[i][j]);
		}
		if(res_matrix[i] == 0) printf("|   |  %.4f   |\n", abs(res_matrix[i]));
		else if(res_matrix[i]<10 && res_matrix[i]>0) printf("|   |  %.4f   |\n", res_matrix[i]);
		else if(res_matrix[i]<=0 && res_matrix[i]>(-10)) printf("|   | %.4f   |\n", res_matrix[i]);			
		else if (res_matrix[i]<100 && res_matrix[i]>0) printf("|   |  %.4f  |\n", res_matrix[i]);
		else if(res_matrix[i]<=0 && res_matrix[i]>(-100)) printf("|   | %.4f  |\n", res_matrix[i]);
		else if (res_matrix[i]<1000 && res_matrix[i]>0) printf("|   |  %.4f |\n", res_matrix[i]);
		else printf("|   |  %.4f |\n", res_matrix[i]);		
	}
	printf("\n\n\n");	
}



void writeArray(float* array, int size){
	int i;
	for(i=0;i<size;i++){
    	if(array[i] == 0) printf("|   %.4f   |\n", abs(array[i]));
		else if(array[i]<10 && array[i]>0) printf("|   %.4f   |\n", array[i]);
		else if(array[i]<=0 && array[i]>(-10)) printf("|  %.4f   |\n", array[i]);			
		else if (array[i]<100 && array[i]>0) printf("|   %.4f  |\n", array[i]);
		else if(array[i]<=0 && array[i]>(-100)) printf("|  %.4f  |\n", array[i]);
		else if (array[i]<1000 && array[i]>0) printf("|   %.4f |\n", array[i]);
		else printf("|  %.4f |\n", array[i]);
	}
	
}



void replaceRow(float** matrix, float* array, int row, int col, int size){
	int i=row+1, j, tmp;
	while(matrix[i][col] == 0) i++;
	tmp = array[i];
	array[i] = array[row];
	array[row] = tmp;
	for(j=0;j<size;j++){
		tmp = matrix[i][j];
		matrix[i][j] = matrix[row][j];
		matrix[row][j] = tmp; 
	}	
}



void GaussElimination(){
	int unknown_count, i,j,k;
	printf("How many unknowns do your equations contain: ");
	scanf("%d", &unknown_count);
	float** coef_matrix = createMatrix(unknown_count);
	float* res_matrix = (float*)malloc(unknown_count*sizeof(float));
	float* solution = (float*)calloc(unknown_count,sizeof(float));
	getsEquations(coef_matrix, res_matrix, unknown_count); 
	printf("Coefficients and result matrix of your equations:\n\n");
	writeGaussEl(coef_matrix, res_matrix, unknown_count);
	
	for(i=0;i<unknown_count;i++){
		if(coef_matrix[i][i] == 0) {
			replaceRow(coef_matrix, res_matrix, i, i, unknown_count);
		}
		res_matrix[i] = (float) res_matrix[i] / coef_matrix[i][i];
		for(j=unknown_count;j>=i;j--){
			coef_matrix[i][j] = (float) coef_matrix[i][j] / coef_matrix[i][i];	
		}
		k=i+1;
		while(unknown_count-k > 0){
			if(coef_matrix[k][i] != 0){
				res_matrix[k] = (float) res_matrix[k] / coef_matrix[k][i];
				res_matrix[k] -= res_matrix[i];
				res_matrix[k] *= coef_matrix[k][i];
				for(j=unknown_count;j>=i;j--){
					coef_matrix[k][j] = (float) coef_matrix[k][j] / coef_matrix[k][i];
					coef_matrix[k][j] -= coef_matrix[i][j];
					coef_matrix[k][j] *= coef_matrix[k][i];
				}
			}
			k++;	
		}
	}
    writeGaussEl(coef_matrix, res_matrix, unknown_count);
    
    for(i=unknown_count-1;i>=0;i--){
    	for(j=unknown_count-1;j>i;j--){
    		solution[i] += coef_matrix[i][j]*solution[j];
		}
		solution[i] = res_matrix[i] - solution[i];
    	solution[i] = (float) solution[i] / coef_matrix[i][j]; 	
	}
	
    printf("Result matrix:\n\n");
	writeArray(solution, unknown_count);
	freeMatrix(coef_matrix, unknown_count);
	free(res_matrix);
	free(solution);
}



void GaussSeidel(){
	
	int size, iter=0, flag, i, j;
	float error, tolerance, sum, tmperror;
	printf("How many unknowns do your equations contain: ");
	scanf("%d", &size);
	float** coef_matrix = createMatrix(size);
	float* res_matrix = (float*)malloc(size*sizeof(float));
	float* solution = (float*)malloc(size*sizeof(float));
	float* tmp = (float*)malloc(size*sizeof(float));
	printf("[i]-> Enter your equations in the order in which the diagonals are the largest.\n\n");
	getsEquations(coef_matrix, res_matrix, size);
	
 
	printf("Enter starting values.\n");
	for(i=0;i<size;i++){
		printf("Enter the value of x%d: ", i+1);
		scanf("%f", &solution[i]);
	}
	printf("\nEnter the error value that you can tolerate: ");
	scanf("%f", &tolerance);

	for(i = 0;i<size;i++) {
		tmp[i] = solution[i];
	}
	
	do{
		flag=0;
    	for(i=0;i<size;i++){
           	sum = 0.0;
			for(j=0;j<size;j++){
				if(j!=i){
					sum += coef_matrix[i][j] * tmp[j];
				}
			}
       	    tmp[i] = (float) (res_matrix[i] - sum) / coef_matrix[i][i];
   	    }

   	    error = 0.0;
        for (i=0;i<size;i++){
        	tmperror = fabs(tmp[i] - solution[i]);
           	if(tmperror > error) {
           		error = tmperror;
			}
           	solution[i] = tmp[i];
   	    }
  
        iter++;
    }while(error>tolerance && iter<50);	
	
	writeGaussEl(coef_matrix, res_matrix, size);
	printf("Result matrix that formed %d. iteration\n", iter);
	printf("Error value: %f\n\n", error);
	printf("Result values of your equations\n--------------------------------\n");
	writeArray(solution, size);
	
	freeMatrix(coef_matrix, size);
	free(res_matrix);
	free(solution);
	free(tmp);
}



void diffTable(float* x, float* y, float* delta_y, int size){
	
	int i, j;
	float h = x[1] - x[0];
	float** diff_table;
	diff_table = (float**)calloc(size,sizeof(float*));
	for(i=0;i<size;i++){
		diff_table[i] = (float*)calloc(size,sizeof(float));
	}
    for(i=0;i<size;i++) {
        diff_table[i][0] = y[i];
    }
    for(j=1;j<size;j++){
        for(i=0;i<size-j;i++){
            diff_table[i][j] = diff_table[i+1][j-1] - diff_table[i][j-1];
        }
    }
	
	printf("\nForward Difference Table\n--------------------------\n\nX");
    printf("\t\tY\t\tD Y");
	for(i=2;i<size;i++){
    	printf("\t\tD^%d Y", i);
	}
	printf("\n");
	for(i=0;i<=size;i++){
		printf("-------\t\t");
	}
	printf("\n");
	for(i=0;i<size;i++){
        printf("%f\t%f", x[i], diff_table[i][0]);
        for(j=1;j<size-i;j++){
            printf("\t%f", diff_table[i][j]);
        }
        printf("\n");
    }
    
    for(i=0;i<size;i++){
		delta_y[i] = diff_table[0][i];
	}
    freeMatrix(diff_table, size);
    
    printf("\n\nGregory-Newton Interpolation polynomial:\n------------------------------------\n");
    printf("F(x) = %.2f ", delta_y[0]);
    for(i=1;i<size;i++){
        if(delta_y[i] != 0){
            printf("+ %.2f*[(x-%.2f)", delta_y[i], x[0]);
            for(j=1;j<i;j++){
                printf("*(x-%.2f)", x[j]);
            }
            printf("/(%d!*%.2f))] ", i, h);
        }
    }
	printf("\n\n");
}



int fact(int n) {
    int i, fact = 1;
	for(i=1;i<=n;i++){
        fact *= i;
    }
    return fact;
}



void GregoryNewton(){
	
	int size, i;
	float value;
		
	printf("Enter the number of data points: ");
    scanf("%d", &size);
	
	float* x = (float*)malloc(size*sizeof(float));
	float* y = (float*)malloc(size*sizeof(float));
	float* delta_y = (float*)malloc(size*sizeof(float));
	
	for (i=0;i<size;i++){
    	printf("Enter x%d: ", i);
	    scanf("%f", &x[i]);
    	printf("Enter y%d: ", i);
	    scanf("%f", &y[i]);
	}
		
	diffTable(x, y, delta_y, size);
	
	int flag;
	float h = x[1] - x[0];
	float result, pol, polterm;
	do{
		result = delta_y[0];
		printf("\nEnter the value to interpolate: ");
    	scanf("%f", &value);
    	pol = (float) (value - x[0]) / h;
    	polterm = 1;
		for (i=1;i<size;i++){
        	polterm *= (pol - (i-1));
        	result += (float) (polterm * delta_y[i]) / fact(i);	
		}
		printf("F(%f) = %f\n\n", value, result);
		printf("Would you like to find another value?\nYes: 1 | No: 2\nYour choice: ");
		scanf("%d", &flag);
		
	}while(flag==1);
	
	free(x);
	free(y);
	free(delta_y);
	
}


/*
typedef struct output {
    double num;
    char op;
    struct output* next;
}OUTPUT;

typedef struct stack {
    char op;
    struct stack* next;
}STACK;

int precedence(char op) {
    if (op == '(' || op == ')') return 5;
    else if (op == 's' || op == 'c' || op == 't') return 4;
    else if (op == 'v' || op == 'y' || op == 'z') return 4;
    else if (op == 'l') return 4;
    else if (op == '^') return 3;
    else if (op == '*' || op == '/') return 2;
    else if (op == '+' || op == '-') return 1;
    else return 0;
}

double log_x(double base, double value){	
	return (double) log(value) / log(base);
}


double readNum(char* strnum) {
    int i = 0;
    double num = 0.0, k = 1.0;
    while (strnum[i] <= '9' && strnum[i] >= '0') {
        num = num * 10;
        num = num + (strnum[i] - '0');
        i++;
    }
    if (strnum[i] == '.') {
        i++;
        while (strnum[i] <= '9' && strnum[i] >= '0') {
            k = k * 10.0;
            num = num + (double)(strnum[i] - '0') / k;
            i++;
        }
    }
    return num;
}

OUTPUT* createOutput() {
    OUTPUT* newNode = (OUTPUT*)malloc(sizeof(OUTPUT));
    newNode->next = NULL;
    newNode->op = '\0';
    return newNode;
}

STACK* createStack() {
    STACK* newNode = (STACK*)malloc(sizeof(STACK));
    newNode->next = NULL;
    newNode->op = '\0';
    return newNode;
}

void addHeadNum(OUTPUT** head, double num) {
    OUTPUT* tmp = createOutput();
    tmp->num = num;
    tmp->op = '\0';
    tmp->next = *head;
    *head = tmp;
}

void addHeadOpOutput(OUTPUT** head, char op) {
    OUTPUT* tmp = createOutput();
    tmp->op = op;
    tmp->next = *head;
    *head = tmp;
}

void addHeadOpStack(STACK** head, char op) {
    STACK* tmp = createStack();
    tmp->op = op;
    tmp->next = *head;
    *head = tmp;
}

void processOp(STACK** stack, OUTPUT** output, char op) {
    STACK* temp = createStack();

    if((*stack)->next == '\0' && (*stack)->op == '\0') {
        (*stack)->op = op;
    } 
	else{
        while((*stack)->next != NULL && precedence(op) <= precedence((*stack)->op) && (*stack)->op != '(') {
            addHeadOpOutput(output, (*stack)->op);
            temp = (*stack)->next;
            free(*stack);
            *stack = temp;
        }
        addHeadOpStack(stack, op);
    }
    free(temp);
}


void printReverse(OUTPUT* head) {
    if(head->next != NULL){
    		printReverse(head->next);
    }
		if (head->op == '\0') {
    	    printf("%lf ", head->num);
    	} 
		else{
			printf("%c ", head->op);
		}   
}


OUTPUT* shuntingYard(char* expression) {
    int len = strlen(expression);
    OUTPUT* output = createOutput();
    OUTPUT* timp = createOutput();
    STACK* stack = createStack();
    STACK* temp = createStack();
    int i, iter;
    char tmp[50];
    double num;

    for (i = 0; i < len; i++) {
    	printReverse(output);
    	printf("\n\n");
        if (expression[0] == '-' && i == 0) {
            i++;
            iter = 0;
            while (isdigit(expression[i + iter]) || expression[i + iter] == '.') {
                tmp[iter] = expression[i + iter];
                iter++;
            }
            tmp[iter] = '\0';
            num = readNum(tmp);
            num = num * (-1);
            i = i + iter - 1;
            addHeadNum(&output, num);
        } 
		else if (isdigit(expression[i])) {
            iter = 0;
            while (isdigit(expression[i + iter]) || expression[i + iter] == '.') {
                tmp[iter] = expression[i + iter];
                iter++;
            }
            tmp[iter] = '\0';
            num = readNum(tmp);
            i = i + iter - 1;
            addHeadNum(&output, num);
        } 
		else if(expression[i] == 'e') addHeadNum(&output, 2.71828182846);
		else if (expression[i] == 'x') addHeadOpOutput(&output, 'x');
        else if (expression[i] == '+') processOp(&stack, &output, '+');
        else if (expression[i] == '-') processOp(&stack, &output, '-');
        else if (expression[i] == '*') processOp(&stack, &output, '*');   
        else if (expression[i] == '/') processOp(&stack, &output, '/');
        else if (expression[i] == '^') processOp(&stack, &output, '^'); 
        else if (expression[i] == 's' && expression[i + 1] == 'i' && expression[i + 2] == 'n') {
            processOp(&stack, &output, 's');
            i = i + 2;
        } 
		else if (expression[i] == 'c' && expression[i + 1] == 'o' && expression[i + 2] == 's') {
            processOp(&stack, &output, 'c');
            i = i + 2;
        } 
		else if (expression[i] == 't' && expression[i + 1] == 'a' && expression[i + 2] == 'n') {
            processOp(&stack, &output, 't');
            i = i + 2;
        } 
		else if (expression[i] == 'a' && expression[i + 1] == 'r' && expression[i + 2] == 'c' && expression[i + 3] == 's' && expression[i + 4] == 'i' && expression[i + 5] == 'n') {
            processOp(&stack, &output, 'v');
            i = i + 5;
        }
		else if (expression[i] == 'a' && expression[i + 1] == 'r' && expression[i + 2] == 'c' && expression[i + 3] == 'c' && expression[i + 4] == 'o' && expression[i + 5] == 's') {
            processOp(&stack, &output, 'y');
            i = i + 5;
        } 
		else if (expression[i] == 'a' && expression[i + 1] == 'r' && expression[i + 2] == 'c' && expression[i + 3] == 't' && expression[i + 4] == 'a' && expression[i + 5] == 'n') {
            processOp(&stack, &output, 'z');
            i = i + 5;
        } 
		else if (expression[i] == 'l' && expression[i + 1] == 'o' && expression[i + 2] == 'g' && expression[i + 3] == '_') {
            processOp(&stack, &output, 'l');
            i = i + 3;
        } 
		else if (expression[i] == '(') addHeadOpStack(&stack, '('); 
        else if (expression[i] == ')') {
            while (stack->op != '(') {
                addHeadOpOutput(&output, stack->op);
                temp = stack;
                stack = stack->next;
            }
            temp = stack;
            stack = stack->next;
        }
    }

    while (stack != NULL && stack->op != '\0') {
        if (stack->op != '(' && stack->op != ')') {
            addHeadOpOutput(&output, stack->op);
        }
        temp = stack;
        stack = stack->next;
        
    }
    
    timp = output;
    while(output->next->next != NULL){
    	output = output->next;
	}
	
	output->next = NULL;
	free(output->next);
    output = timp;
    
	free(temp);
	free(timp);
	free(stack);
	
	
	
    return output;
}








double evaluate(OUTPUT** output, double x) {
    
	OUTPUT* head = *output;
	OUTPUT* tmp = createOutput();
	double num1, num2, res;
	
	while((*output)->next != NULL){
		
		if((*output)->op == 'x'){
			(*output)->op = '\0';
			(*output)->num = x;
			(*output) = (*output)->next;
		}
		else{
			(*output) = (*output)->next;
		}
	}
	
	if((*output)->op == 'x'){
		(*output)->op = '\0';
		(*output)->num = x;
		(*output) = (*output)->next;
	}
	else{
		(*output) = (*output)->next;
	}
	
	(*output) = head;
	printf("\n\n");
	printReverse(head);
	
    while((*output)->next != NULL){
    	
    	if((*output)->op != '\0'){
    		if((*output)->op == 's' || (*output)->op == 'c' || (*output)->op == 't' || (*output)->op == 'v' || (*output)->op == 'y' || (*output)->op == 'z'){
				if((*output)->next->op == '\0'){
    				num2 = (*output)->next->num;
    				if((*output)->op == 's') res = sin(num2);
					else if ((*output)->op == 'c') res = cos(num2);
					else if ((*output)->op == 't') res = tan(num2);
					else if ((*output)->op == 'v') res = asin(num2);
					else if ((*output)->op == 'y') res = acos(num2);
					else if ((*output)->op == 'z') res = acos(num2);
    				
					(*output)->op = '\0';
					(*output)->num = res;
					if((*output)->next->next == NULL){
						(*output)->next = NULL;
						free((*output)->next);
						(*output) = head;
					}
					else{
						tmp = (*output)->next->next;
						(*output)->next = NULL;
						free((*output)->next);
						(*output)->next = tmp;
						(*output) = head;
					}
					printf("\n\n");
					printReverse((*output));
	
				}
				else{
					
					(*output) = (*output)->next;
					printf("\n\n");
					printReverse((*output));
				}
			}
			else{
				if((*output)->next->op == '\0'){
					if((*output)->next->next->op == '\0'){
						num1 = (*output)->next->next->num;
						num2 = (*output)->next->num;
					if((*output)->op == '+') res = num1+num2;
					else if ((*output)->op == '-') res = num1-num2;
					else if ((*output)->op == '*') res = num1*num2;
					else if ((*output)->op == '/') res = num1/num2;
					else if ((*output)->op == '^') res = pow(num1,num2);
					else if ((*output)->op == 'l') res = log_x(num1,num2);
					(*output)->op = '\0';
					(*output)->num = res;
					
					if((*output)->next->next->next == NULL){
						free((*output)->next->next);
						free((*output)->next);
						(*output) = head;
					}
					else{
						tmp = (*output)->next->next->next;
						(*output)->next->next = NULL;
						free((*output)->next->next);
						(*output)->next = NULL;
						free((*output)->next);
						(*output)->next = tmp;
						(*output) = head;
					}
					printf("\n\n");
					printReverse((*output));	
					}
					else{
						(*output) = (*output)->next;
						printf("\n\n");
					printReverse((*output));
					}
				}
			}
		}
		else{
			(*output) = (*output)->next;
			printf("\n\n");
					printReverse((*output));
		}
		
    }

    return (*output)->num;
}






*/


