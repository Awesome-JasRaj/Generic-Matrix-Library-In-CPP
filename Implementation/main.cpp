#include "matrix_library.h"
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;



void init(){
	ifstream fin;
	fin.open("initializations_input.txt");
	int r1,c1,r2,c2,n;
	fin>>r1;
	fin>>c1;
	fin>>r2;
	fin>>c2;
	fin>>n;
	cout<<"Initialization by specifying rows, cols and an optional default value" << endl;
	Matrix<int> m(r1,c1,5);
	m.display();
	cout<<"Initialization of an identity matrix" << endl;
	Matrix<int> m3(n);
	cout<<m3;
	cout<<"Initialization by using a vector" << endl;
	vector<vector<int> > v(r2, vector<int>(c2));
	int k=0;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++)
			fin>>v[i][j];
	}
	Matrix<int> m1(v);
	cout<<m1;
	cout<<"Initialization by using a copy constructor" << endl;
	Matrix<int> m2(m1);
	cout<<m2;
	int rit,cit;
	fin>>rit;
	fin>>cit;
	cout<<"Row Iterator for Row "<<rit<<endl;
	for(auto it=m2.begin_row(rit-1);it!=m2.end_row(rit-1);it++)
    {
        cout<<*it<<" ";
    }
    cout<<"\n\n";

    cout<<"Coloumn Iterator for Coloumn "<<cit<<endl;
	for(auto it=m2.begin_col(cit-1);it!=m2.end_col(cit-1);it++)
    {
        cout<<*it<<"\n";
    }
    cout<<"\n\n";
    
    fin.close();
}

void opr(){
	ifstream fin;
	int row,col,row1,col1,crow,ccol,resizerow,resizecol,element;
	fin.open("operations_input.txt");
	fin>>row;
	fin>>col;
	Matrix<int> m1(row,col);
	for(int i=0;i<row;i++){
		for(int j=0;j<col;j++)
			fin>>m1[i][j];
	}
	fin>>crow;
	fin>>ccol;
	cout<<m1;
	cout<<"No of rows: "<<m1.rows()<<endl;
	cout<<"No of coloumns: "<<m1.cols()<<endl;
	cout<<"No of elements: "<<m1.no_of_elements()<<endl;
	cout<<"The value present at matrix["<<crow<<"]["<<ccol<<"]: "<<m1[crow-1][ccol-1]<<endl;
	Matrix<int> X(row,col);
	X = m1;
	cout<<"\n\nAppend Row"<<endl;
    vector<int> v2(3);
    int ele = 1;
    for(int i=0;i<3;i++)
    	v2[i] = ele++;
    X.Append(v2,1);
    X.display();
    cout<<"\nAppend Coloumn"<<endl;
    X.Append(v2,0);
    X.display();
	/* A second matrix to perform binary operations */
	cout<<endl;
	fin>>row1;
	fin>>col1;
	Matrix<int> m2(row1,col1);
	for(int i=0;i<row1;i++){
		for(int j=0;j<col1;j++)
			fin>>m2[i][j];
	}
	cout<<"Second matrix: "<<endl;
	cout<<m2;
	cout<<"Binary operations on matrices: "<<endl;
	cout<<"Addition of matrices: "<<endl;
	m1.display();
	cout<<"\tAND\n"<<endl;
	m2.display();
	cout<<(m1+m2);


	cout<<"Subtraction of matrices: "<<endl;
	m1.display();
	cout<<"\tAND\n"<<endl;
	m2.display();
	cout<<(m1-m2);


	cout<<"Multiplication of matrices: "<<endl;
	m1.display();
	cout<<"\tAND\n"<<endl;
	m2.display();
	cout<<(m1*m2);

	cout<<"\nOperations based on scalar quantities: \n"<<endl;
	
	fin>>element;
	cout<<"Adding "<<element<<" to all the elements of the matrix: "<<endl;
	m2+=element;
	m2.display();
	cout<<"Subtracting "<<element<<" from all the elements of the matrix: "<<endl;
	m2-=element;
	m2.display();
	cout<<"Multiplying "<<element<<" to all the elements of the matrix: "<<endl;
	m2*=element;
	m2.display();
	cout<<"Dividing by "<<element<<" to all the elements of the matrix: "<<endl;
	m2/=element;
	m2.display();

	cout<<"\nOperations on the matrix: \n"<<endl;
	m2.display();
	cout<<"Transpose of the matrix: \n"<<endl;
	m2.Transpose();
	m2.display();

	cout<<"New Matrix\n";
	Matrix<double> m3(3,3,2.5);
	m3[0][0] = 4;
	m3[1][1] = 6;
	m3.display();
	cout<<"\nDeterminant of the matrix: "<<m3.Determinant()<<endl;

	fin>>resizerow;
	fin>>resizecol;
	m3.resize(resizerow,resizecol);
	cout<<"\nMatrix after resizing it to "<<resizerow<<" rows and "<<resizecol<<" coloumns: \n"<<endl;
	m3.display();
	cout<<endl;

	int inr,inc;
	fin>>inr;
	fin>>inc;
	Matrix<double> inverse(inr,inc,1.0);
	for(int i=0;i<inr;i++){
		for(int j=0;j<inc;j++)
			fin>>inverse[i][j];
	}
	inverse.display();
	cout<<"\nInverse of the matrix: \n"<<endl;
	cout<<inverse.Inverse();
	int pow;
	fin>>pow;
	cout<<"Matrix to the power of "<<pow<<"\n\n";
	cout<<m2;
	cout<<m2.Power(pow);
	fin.close();
}