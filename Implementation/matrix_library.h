#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

template<typename T>
class Matrix {

private:
	T** mat;
	int row,col;


public:

	class iterator {
	
	private:
		int __row, __col,__crow,__ccol, __traverse; //Traverse 1 = row-wise and 0 = col-wise
		T **__mat;
	

	public:
		explicit iterator(T** _mat, int _row, int _col, int _crow, int _ccol,int _traverse): __mat(_mat), __row(_row), __col(_col),__crow(_crow),__ccol(_ccol), __traverse(_traverse)
		{

		}
        iterator operator++(int a)
        {
			iterator temp = (*this);
            if(__traverse)
            {
                if(__ccol==__col)
                {
                    __ccol=0;
                    __crow++;
                }
                else
                __ccol++;
                return temp;
                
            }
            else
            {
                if(__crow==__row)
                {
                    __crow=0;
                    __ccol++;
                }
                else
                __crow++;
                return temp;

            }
            
        }
        T operator*(){
            return __mat[__crow][__ccol];
        }

        iterator& operator++()
        {
            if(__traverse)
            {
                if(__ccol==__col)
                {
                    __ccol=0;
                    __crow++;
                }
                else
                __ccol++;
                return (*this);
                
            }
            else
            {
                if(__crow==__row)
                {
                    __crow=0;
                    __ccol++;
                }
                else
                __crow++;
                return (*this);

            }
            
        }
        bool operator==(const iterator& rhs) const
		{
			return (__crow == rhs.__crow && __ccol == rhs.__ccol);
		}
		bool operator!=(const iterator& rhs) const
		{
			return !((*this)==rhs);
		}
	};
	int rows(){
		return row;
	}
	int cols(){
		return col;
	}
    int no_of_elements(){
        return row*col;
    }
	iterator begin(int traverse=1) 
    {
        return iterator(mat,row-1,col-1,0,0,traverse);
    }
    iterator begin_row(int r) 
    {
        return iterator(mat,row-1,col-1,r,0,1);
    }
    iterator end(int traverse=1)
    {
        if(traverse)
        	return iterator(mat,row-1,col-1,row,0,traverse);
        return iterator(mat,row-1,col-1,0,col,traverse);
    }
    iterator end_row(int r) 
    {
        return iterator(mat,row-1,col-1,r+1,0,1);
    }
    iterator begin_col(int c) 
    {
        return iterator(mat,row-1,col-1,0,c,0);
    }
    iterator end_col(int c) 
    {
        return iterator(mat,row-1,col-1,0,c+1,0);
    }

    template<typename T1>
    Matrix(T1& m){		//Initialization for vector
    	row = m.size();
    	col = m[0].size();
		mat=new T*[row];
        for(int i=0;i<row;i++)
        {
            mat[i]=new T[col];
        }
		 for(int i=0;i<row;i++){
		 	for(int j=0;j<col;j++){
		 		mat[i][j] = m[i][j];
		 	}
		 }
    }
    Matrix(int nrows, int ncols, T val=0){		//Initialization when rows,cols and a default value(optional) is given
    	 row = nrows;
    	 col = ncols;  			
		 mat=new T*[row];
        for(int i=0;i<row;i++)
        {
            mat[i]=new T[col];
        }
		 for(int i=0;i<nrows;i++){
		 	for(int j=0;j<ncols;j++){
		 		mat[i][j] = val;
		 	}
		 }
    }
    Matrix(Matrix& mat1){ 		//Copy constructor
    	row = mat1.row;
    	col = mat1.col;
    	mat=new T*[row];
        for(int i=0;i<row;i++)
        {
            mat[i]=new T[col];
        }
		 for(int i=0;i<row;i++){
		 	for(int j=0;j<col;j++){
		 		mat[i][j] = mat1[i][j];
		 	}
		 }
    }
    Matrix(int n){		//Identity matrix of order n
    	row = n;
    	col = n;
    	mat=new T*[row];
        for(int i=0;i<row;i++)
        {
            mat[i]=new T[col];
        }
		 for(int i=0;i<row;i++){
		 	for(int j=0;j<col;j++){
		 		if(i==j){
		 			mat[i][j] = 1;
		 			continue;
		 		}
		 		mat[i][j] = 0;
		 	}
		 }
    }
    auto& operator[](int ind){
        return mat[ind];
    }
    Matrix& resize(int m,int n, T val=0){
        T **t = new T*[m];
        for(int i=0;i<m;i++){
            t[i] = new T[n];
        }
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++)
                t[i][j] = val;
        }
        for(int i=0;i<min(m,row);i++){
            for(int j=0;j<min(n,col);j++)
                t[i][j] = mat[i][j];
        }
        mat = t;
        row = m;
        col = n;
    }
    Matrix& operator=(const Matrix& rhs){
        (*this).resize(rhs.row,rhs.col);
        for(int i=0;i<(*this).row;i++){
            for(int j=0;j<(*this).col;j++)
                (*this)[i][j] = rhs.mat[i][j];
        }
        return (*this);
    }
    friend bool operator==(Matrix& lhs,Matrix& rhs){
    	if((lhs.rows()!=rhs.rows()) || (lhs.cols()!=rhs.cols()))
    		return false;
    	int nr = lhs.rows(), nc = lhs.cols();
    	for(int i=0;i<nr;i++){
    		for(int j=0;j<nc;j++){
    			if(lhs[i][j]!=rhs[i][j])
    				return false;
    		}
    	}
    	return true;
    }
    friend bool operator!=(Matrix& lhs,Matrix& rhs){
        return !(lhs==rhs);
    }
    friend Matrix operator+(Matrix<T>& lhs,Matrix& rhs){
    	if((lhs.row!=rhs.row || (lhs.col!=rhs.col)))
    		throw "Addition not possible";
    	int nr = lhs.row, nc = rhs.col;
    	Matrix<T> m3(nr,nc,0);
		for(int i=0;i<nr;i++){
    		for(int j=0;j<nc;j++){
    			m3[i][j] = lhs[i][j] + rhs[i][j];
    		}
    	}
    	return m3;
    }
    friend Matrix operator+(Matrix<T> &m1, auto& val){		//Addition with a scalar
    	Matrix<T> m3(m1.row,m1.col);
    	for(int i=0;i<m1.row;i++){
    		for(int j=0;j<m1.col;j++){
    			m3[i][j] = m1[i][j] + val;
    		}
    	}
    	return m3;
    }
    
    friend Matrix operator-(Matrix<T>& m1,Matrix& m2){	
    	if((m1.rows()!=m2.rows()) || (m1.cols()!=m2.cols()))
    		throw "Subtraction not possible";
    	int nr = m1.rows(), nc = m2.cols();
    	Matrix<T> m3(nr,nc);
		for(int i=0;i<nr;i++){
    		for(int j=0;j<nc;j++){
    			m3[i][j] = m1[i][j] - m2[i][j];
    		}
    	}
    	return m3;
    }
    friend Matrix operator-(Matrix<T> &m1, auto val){ 		//Subtraction with a scalar
    	Matrix<T> m3(m1.rows(),m1.cols());
    	for(int i=0;i<m1.rows();i++){
    		for(int j=0;j<m1.cols();j++){
    			m3[i][j] = m1[i][j] - val;
    		}
    	}
    	return m3;
    }

    friend Matrix operator*(Matrix<T>& m1,Matrix& m2){
    	if(m1.cols()!=m2.rows())
    		throw "Multiplication of the given matrices is not possible";
    	Matrix<T> m3(m1.rows(),m2.cols());
    	for(int i=0;i<m1.rows();i++){
    		for(int j=0;j<m2.cols();j++){
    			m3[i][j] = 0;
    			for(int k=0;k<m1.cols();k++){
    				m3[i][j] += (m1[i][k]*m2[k][j]);
    			}
    		}
    	}
    	return m3;
    }
    friend Matrix operator*(Matrix<T> &m1, auto val){ //Multiplication with a scalar
    	Matrix<T> m3(m1.rows(),m1.cols());
    	for(int i=0;i<m1.rows();i++){
    		for(int j=0;j<m1.cols();j++){
    			m3[i][j] = m1[i][j] * val;
    		}
    	}
    	return m3;
    }
    friend Matrix operator/(Matrix<T> &m1, auto val){ //Division with a scalar
    	Matrix<T> m3(m1.rows(),m1.cols());
    	for(int i=0;i<m1.rows();i++){
    		for(int j=0;j<m1.cols();j++){
    			m3[i][j] = m1[i][j]/val;
    		}
    	}
    	return m3;
    }

    Matrix operator+=(Matrix<T> &m1){
    	(*this) = (*this) + m1;
    	return (*this);
    }
    Matrix operator+=(auto& val){
       (*this) = (*this) + val;
        return (*this);
    }
    Matrix operator-=(Matrix<T> &m1){
    	*this = (*this) - m1;
    	return (*this);
    }
    Matrix operator-=(auto val){
        *this = (*this) - val;
        return (*this);
    }
    Matrix operator*=(Matrix<T> &m1){
    	*this = (*this) * m1;
    	return (*this);
    }
    Matrix operator*=(auto val){
        *this = (*this) * val;
        return (*this);
    }
    Matrix& operator/=(auto val){
    	*this = (*this)/val;
    	return (*this);
    }

    Matrix& Transpose(){
        int r = row,c=col;
    	T** t = new T*[c];
        for(int i=0;i<c;i++){
            t[i] = new T[row];
        }
    	for(int i=0;i<r;i++){
    		for(int j=0;j<c;j++){
    			t[j][i] = mat[i][j];
    		}
    	}
    	mat = t;
        row = c;
        col = r;
    }
    Matrix cofactor(int nr,int nc){
        if((*this).row!=(*this).col)
            throw "Cofactor of the given matrix not possible";
    	Matrix<T> m3((*this).row-1,(*this).row-1);
    	int r=0,c=0;
    	for(int i=0;i<row;i++){
    		if(i==nr)
    			continue;
    		for(int j=0;j<col;j++){
    			if(j==nc)
    				continue;
    			m3[r][c++] = mat[i][j];
    			if(c==(*this).row-1){
    				c = 0;
    				r++;
    			}
    		}
    	}
    	return m3;
    }
    
    double Determinant(){
    	if((*this).row!=(*this).col)
    		throw "Determinant of the given matrix not possible";
    	if((*this).row==1){
    		return (*this)[0][0];
    	}
    	double val = 0.0;
    	int sign = 1;
    	for(int i=0;i<(*this).row;i++){
    		val += ((*this)[0][i] * sign) * ((*this).cofactor(0,i)).Determinant();
    		sign = (-1)*sign;
    	}
    	return val;
    }
     Matrix adjoint(){
        if((*this).row!=(*this).col){
            throw "Adjoint of the given matrix not possible";
        }
        int n = (*this).row;
        Matrix<T> ad(n,n);
        int rsign = 1,sign;
        for(int i=0;i<n;i++){
            sign = rsign;
            for(int j=0;j<n;j++){
                ad[i][j] = (((*this).cofactor(i,j)).Determinant())*sign;
                sign = (-1)*sign;
            }
            rsign = (-1)*rsign;
        }
        ad.Transpose();
        return ad;
    }
    Matrix Inverse(){
        double determinant = (*this).Determinant();
        Matrix<T> inv((*this).row,(*this).row);  
        inv = (*this).adjoint();
        inv/=determinant;
        return inv;

    }
    template<typename T1>
    Matrix Append(T1 &m,int type=1){
    	int r = (*this).row,c = (*this).col,k=0;
    	if(type){
    	(*this).resize(r+1,c);
    	for(int i=0;i<c;i++){
    			(*this)[r][i] = m[k++];
    			row = r+1;
    		}
    	}
    	else{
    	    	(*this).resize(r,c+1);
    	    	for(int i=0;i<r;i++){
    			(*this)[i][c] = m[k++];
    			col = c+1;
    			}
    	    }
    	return (*this);


    }
    Matrix Power(int n){
    	if(n==1)
    		return (*this);
    	Matrix<T> t((*this).row,(*this).col);
    	t = (*this);
    	for(int i=0;i<n-1;i++){
    		t*=t;
    	}
    	return t;
    }
    bool isIdentity(Matrix& m){
    	if(m.row!=m.col)
    		return false;
    	Matrix t(m.row);
    	return (t==m);
    }
    bool square(Matrix &m){
    	return (m.row==m.col);
    }
    void display() 
	{

    cout <<endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << mat[i][j] << "\t";
        	}
        cout << endl;
    	}
        cout<<"\n\n";
	}
	friend ostream& operator<<(ostream& os,const Matrix &M)
	{
	os << "Matrix: " << endl;
   	for(int i=0;i<M.row;i++) {
     for(int j=0;j<M.col;j++)
        os <<M.mat[i][j] << "\t";
     os << endl;
    }
    os<<"\n\n";
    return os;
	}	
};