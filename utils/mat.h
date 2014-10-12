#include <ostream>
#include <vector>
#include <assert.h>
#include <math.h>
#define M_PI 3.14
namespace math {

template <int ROWS, int COLS> 
class Matrix {
public:
    static Matrix identity() {
        static_assert(ROWS==COLS, "Identity matrix must have ROWS==COLS!!");
        Matrix<ROWS,COLS> m;
        for(int r = 0; r < ROWS; r++) {
            for(int c = 0; c < COLS; c++) {
                float value = r != c ? 0.0 : 1.0;
                m.setValue(r,c, value);
            }
        }
        return m;
    }

    Matrix() : matrix(new float[ROWS*COLS]) {
        for(int i = 0; i < ROWS * COLS; i++) {
            matrix[i] = 0.0f;
        }
    }

    Matrix(std::initializer_list<float> list) : Matrix() {
        assert(list.size() == ROWS*COLS);
        int index = 0;
        for (auto it = list.begin() ; it != list.end(); ++it) {
            matrix[index] = *it;
            index++;
        }
    }

    Matrix& operator=(Matrix&& m) {
        matrix = m.matrix;
        m.matrix = 0;
    }

    Matrix(Matrix&& m) {
        matrix = m.matrix;
        m.matrix = 0;
    }

    ~Matrix() {
        delete [] matrix;
    }

    int cols() const {
        return COLS;
    }

    int rows() const {
        return ROWS;
    }

    float* array() const {
        return matrix;
    }

    void print_array() const {
        for(int i = 0; i < ROWS * COLS; i++) {
            std::cout << matrix[i] << ",";
        }

    }

    void setValue(int row, int col, float value) {
        //matrix[COLS * row + col] = value;
        matrix[ROWS * col + row] = value;
    }

    float getValue(int row, int col) const {
        return matrix[ROWS*col + row];
    }

    template <int R1, int C1>
    Matrix<ROWS, C1> operator*(const Matrix<R1,C1>& m) const{
        Matrix<ROWS, C1> result;
        for(int row = 0; row < ROWS; row++) {
            for(int mcol = 0; mcol < C1; mcol++) {
                float sum = 0.0;
                for(int col = 0; col < COLS; col++) {
                    //std::cout << getValue(row, col) << " x " << m.getValue(col, mcol) << std::endl;
                    sum += getValue(row, col) * m.getValue(col, mcol);
                }
                result.setValue(row, mcol, sum);
            }
        }
        return result;
    }

    template <int r, int c>
    friend std::ostream& operator<< (std::ostream& out, const Matrix<r,c>& m);
private:

    float* matrix;
};

template <int r, int c>
std::ostream& operator<< (std::ostream& out, const Matrix<r,c>& m) {
    out << "Matrix " << r << "x" << c << std::endl;
    for(int i = 0; i < r; i++ ) {
        out << "| ";
        for(int j = 0; j < c; j++) {
            out << m.getValue(i, j) << " ";
        }
        out << "|" << std::endl;
    }
    return out;
};

typedef Matrix<4,4> Mat4;

static inline float toRad(float angle) {
    return angle * M_PI / 180;
}

Mat4 translate(float x, float y, float z) {
    Mat4 m = Mat4::identity();
    m.setValue(0, 3, x);
    m.setValue(1, 3, y);
    m.setValue(2, 3, z);
    return m;
}

Mat4 rotate(float angle_x, float angle_y, float angle_z) {
    Mat4 m = Mat4::identity();
    float rad_x = toRad(angle_x);
    float rad_y = toRad(angle_y);
    float rad_z = toRad(angle_z);
    m.setValue(0, 0, cos(rad_y) * cos(rad_z));
    m.setValue(0, 1, cos(rad_x) * sin(rad_z) + sin(rad_x) * sin(rad_y) * cos(rad_z));
    m.setValue(0, 2, sin(rad_x) * sin(rad_z) - cos(rad_x) * sin(rad_y) * cos(rad_z));

    m.setValue(1, 0, -cos(rad_y) * sin(rad_z));
    m.setValue(1, 1, cos(rad_x) * cos(rad_z) - sin(rad_x) * sin(rad_y) * sin(rad_z));
    m.setValue(1, 2, sin(rad_x) * cos(rad_z) + cos(rad_x) * sin(rad_y) * sin(rad_z));

    m.setValue(2, 0, sin(rad_y));
    m.setValue(2, 1, -sin(rad_x) * cos(rad_y));
    m.setValue(2, 2, cos(rad_x) * cos(rad_y));
    return m;

}

Mat4 scale(float x, float y, float z) {
    Mat4 m = Mat4::identity();
    m.setValue(0,0, x);
    m.setValue(1,1, y);
    m.setValue(2,2, z);
    return m;
}

Mat4 perspective(float fovy, float aspect, float n, float f) {
    float q = 1.0f / tan(toRad(0.5f * fovy));
    float A = q / aspect;
    float B = (n + f) / (n - f);
    float C = (2.0f * n * f) / (n - f);

    Mat4 result;
/*
    result[0] = vec4(A, 0.0f, 0.0f, 0.0f);
    result[1] = vec4(0.0f, q, 0.0f, 0.0f);
    result[2] = vec4(0.0f, 0.0f, B, -1.0f);
    result[3] = vec4(0.0f, 0.0f, C, 0.0f);*/

    result.setValue(0,0, A);
    result.setValue(1,1, q);
    result.setValue(2,2, B);
    result.setValue(2,3, C);
    result.setValue(3,2, -1.0);
    

    return result;
}
}




