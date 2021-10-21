#include <bits/stdc++.h>
#include <iostream>
#include <string>
using namespace std;

//strassen matrix

int** initialize_matrix(int n) {
    int** mat = new int*[n];
    for (int i = 0; i < n; i++)
        mat[i] = new int[n];
    return mat;
}

void input_matrix(int** mat, int n) {
    cout << "Enter matrix: \n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> mat[i][j];
}

void display_matrix(int** mat, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << mat[i][j] << " ";
        cout << '\n';
    }
    cout << '\n';
}


int** add_matrix(int** mat1, int** mat2, int n) {
    int** res = initialize_matrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][j] = mat1[i][j] + mat2[i][j];
    return res;
}

int** subtract_matrix(int** mat1, int** mat2, int n) {
    int** res = initialize_matrix(n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            res[i][j] = mat1[i][j] - mat2[i][j];
    return res;
}

int** strassen_multiply(int** A, int** B, int n) {
    if (n == 1) {
        int** Z = initialize_matrix(1);
        Z[0][0] = A[0][0] * B[0][0];
        return Z;
    }
    int** Z = initialize_matrix(n);
    int k = n / 2;

    int** A11 = initialize_matrix(k);
    int** A12 = initialize_matrix(k);
    int** A21 = initialize_matrix(k);
    int** A22 = initialize_matrix(k);

    int** B11 = initialize_matrix(k);
    int** B12 = initialize_matrix(k);
    int** B21 = initialize_matrix(k);
    int** B22 = initialize_matrix(k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][k + j];
            A21[i][j] = A[k + i][j];
            A22[i][j] = A[k + i][k + j];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][k + j];
            B21[i][j] = B[k + i][j];
            B22[i][j] = B[k + i][k + j];
        }
    }

    int** P1 = strassen_multiply(A11, subtract_matrix(B12, B22, k), k);
    int** P2 = strassen_multiply(add_matrix(A11, A12, k), B22, k);
    int** P3 = strassen_multiply(add_matrix(A21, A22, k), B11, k);
    int** P4 = strassen_multiply(A22, subtract_matrix(B21, B11, k), k);
    int** P5 = strassen_multiply(add_matrix(A11, A22, k), add_matrix(B11, B22, k), k);
    int** P6 = strassen_multiply(subtract_matrix(A12, A22, k), add_matrix(B21, B22, k), k);
    int** P7 = strassen_multiply(subtract_matrix(A11, A21, k), add_matrix(B11, B12, k), k);

    int** Z11 = subtract_matrix(add_matrix(add_matrix(P5, P4, k), P6, k), P2, k);
    int** Z12 = add_matrix(P1, P2, k);
    int** Z21 = add_matrix(P3, P4, k);
    int** Z22 = subtract_matrix(subtract_matrix(add_matrix(P5, P1, k), P3, k), P7, k);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            Z[i][j] = Z11[i][j];
            Z[i][j + k] = Z12[i][j];
            Z[k + i][j] = Z21[i][j];
            Z[k + i][k + j] = Z22[i][j];
        }
    }

    for (int i = 0; i < k; i++) {
        delete[] A11[i];
        delete[] A12[i];
        delete[] A21[i];
        delete[] A22[i];
        delete[] B11[i];
        delete[] B12[i];
        delete[] B21[i];
        delete[] B22[i];
        delete[] P1[i];
        delete[] P2[i];
        delete[] P3[i];
        delete[] P4[i];
        delete[] P5[i];
        delete[] P6[i];
        delete[] P7[i];
        delete[] Z11[i];
        delete[] Z12[i];
        delete[] Z21[i];
        delete[] Z22[i];
    }

    delete[] A11;
    delete[] A12;
    delete[] A21;
    delete[] A22;
    delete[] B11;
    delete[] B12;
    delete[] B21;
    delete[] B22;
    delete[] P1;
    delete[] P2;
    delete[] P3;
    delete[] P4;
    delete[] P5;
    delete[] P6;
    delete[] P7;
    delete[] Z11;
    delete[] Z12;
    delete[] Z21;
    delete[] Z22;

    return Z;
}
//////////////////////////////////////////////////////////////

//kartsoba

int make_equal_length(string &str1, string &str2) {
    while (str1.size() < str2.size())
        str1 = '0' + str1;
    while (str2.size() < str1.size())
        str2 = '0' + str2;
    return str1.size();
}

string add_bit_strings(string x, string y) {
    string result = "";
    int n = make_equal_length(x, y);
    int carry = 0;
    for (int i = n-1 ; i >= 0 ; i--) {
        int a = x[i] - '0';
        int b = y[i] - '0';
        int sum = (a ^ b ^ carry)+'0';
        result = (char)sum + result;
        carry = (a&b) | (b&carry) | (a&carry);
    }
    if (carry) {
        result = '1' + result;
    }
    return result;
}

int multiplyi_single_bit(string a, string b) {
    return (a[0] - '0')*(b[0] - '0');
}

long int multiply(string X, string Y) {
    int n = make_equal_length(X, Y);
    if (n == 0)
        return 0;
    if (n == 1)
        return multiplyi_single_bit(X, Y);

    int fh = n/2;
    int sh = (n-fh);
    string Xl = X.substr(0, fh);
    string Xr = X.substr(fh, sh);
    string Yl = Y.substr(0, fh);
    string Yr = Y.substr(fh, sh);

    long int P1 = multiply(Xl, Yl);
    long int P2 = multiply(Xr, Yr);
    long int P3 = multiply(add_bit_strings(Xl, Xr),
                           add_bit_strings(Yl, Yr));

    return P1*(1<<(2*sh)) + (P3 - P1 - P2)*(1<<sh) + P2;
}

string DecimalToBinary(int n) {
   string binaryNumber ="";
   int num=n;
   int i = 0;
   while (n > 0) {
      binaryNumber += to_string(n % 2) ;
      n = n / 2;
      i++;
}
   reverse(binaryNumber.begin(),binaryNumber.end());
   return binaryNumber ;
}

///////////////////////////////////////////////////

//fast power
float fast_power_recursive(float b, int e) {
    if (e == 0)
        return 1.0;
    if (e % 2 == 1)
        return b * fast_power_recursive(b * b, e / 2);
    else
        return fast_power_recursive(b * b, e / 2);
}

/////////////////////////////////////////////////

//matrix view

void matrix_view();

//main menu

void mainmenu(){

  cout << "**************************\n" << endl;
    cout << "                    WELCOME TO calculator\n           \n" << endl;
    cout << "**************************\n" << endl;
    cout << "\n1- matrix";
    cout << "\n2-addition numbers";
    cout << "\n3-subtriction numbers";
    cout << "\n4-multiply numbers";
    cout << "\n5-power numbers\n";
    cout << "\n5-EXIT\n\n";

    int choice ;
    cout << "please enter your choice : ";
    cin>>choice;

    if(choice==1){
        matrix_view();

    }
    else if(choice==2){
             cout << "please enter the number of the numbers you want to calc : ";
             int n , number;
             int sum=0;
             cin>>n;
             for(int i=1; i<=n ; i++)
                {

                    cout<<"enter the "<<i<<" number :";
                    cin>>number;
                    sum+=number;

                }
                cout<<"the sum of this numbers is "<<sum;
                cout<<endl;


    }
     else if(choice==3){
             cout << "please enter the number of the numbers you want to calc : ";
             int n , number;
             int sum=0;
             cin>>n;
             for(int i=1; i<=n ; i++)
                {

                    cout<<"enter the "<<i<<" number :";
                    cin>>number;
                    sum-=number;

                }
                cout<<"the sum of this numbers is "<<sum;
                cout<<endl;


    }
    else if(choice==4){
            cout << "please enter the two numbers you want to calc : ";
            int n ,m;
            cin >> n >> m;
            string n1=DecimalToBinary(n);
            string m1=DecimalToBinary(m);
            cout <<" the result is "<<multiply(n1,m1);
            cout<<endl;

    }
    else if(choice==5){
            cout << "please enter the two numbers you want to calc : ";
            int n ,m;
            cin >> n >> m;
            cout <<" the result is ";
            cout<<fast_power_recursive(n, m);
            cout<<endl;
    }

    else if(choice==6){
        exit(0);
    }

}



void matrix_view(){

  cout << "**************************\n" << endl;
    cout << "                    MATRIX VIEW\n           \n" << endl;
    cout << "**************************\n" << endl;
    cout << "\n1- add  2 matrix";
    cout << "\n2-subtrict 2 matrix ";
    cout << "\n3-multiply 2 matrix\n";
    cout << "\n4-back to mainmenu\n\n";

    int choice;
    cout << "please enter your choice : ";
    cin>>choice;
    cout << "please enter the size of the matrix: ";
    int n;
    cin >> n;

    int** X = initialize_matrix(n);
    input_matrix(X, n);
    cout << "Matrix X: " << '\n';

    int** Y = initialize_matrix(n);
    input_matrix(Y, n);
    cout << "Matrix Y: " << '\n';



    if(choice==1){
        int** m=  add_matrix(X,Y,n);
        cout << "Result of addition: " << '\n';
        display_matrix(m, n);
        cout<<endl;

    }
    else if(choice==2){
            int** g = subtract_matrix(X,Y,n);
            cout << "Result of subtraction: " << '\n';
            display_matrix(g, n);
            cout<<endl;

    }
     else if(choice==3){
             int** Z = strassen_multiply(X, Y, n);
             cout << "Result of multiplication : " << '\n';
             display_matrix(Z, n);
             cout<<endl;
     }

    else if(choice==4){
        mainmenu();
    }
}


int main() {
     while(1){

    mainmenu();

    }
    return 0;
}