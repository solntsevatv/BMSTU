#include <iostream>
#include "matrix.hpp"
#define _CRT_SECURE_NO_WARNINGS


int main() {
    // Test constructor
    std::cout << "Test constructors:" << "\n\n";

    size_t q = 3, z = 5;
    std::cout << "Test constructor with two size_t numbers:\n";
    Matrix<int> matrix(q, z);
    std::cout << matrix << "\n\n";

    std::cout << "Test constructor with c-matrix:\n";
    int **c_matrix = new int*[2];
    for (int i = 0; i < 2; ++i) {
        c_matrix[i] = new int[2];
        for (int j = 0; j < 2; ++j)
            c_matrix[i][j] = i + j;
    }

    Matrix<int> matr { 2, 2, c_matrix };
    std::cout << matr << "\n\n";
    for (int i = 0; i < 2; ++i)
        delete []c_matrix[i];
    delete []c_matrix;

    std::cout << "Test constructor with one zero size:\n";
    Matrix<int> zero_mat(0, 3);
    std::cout << "Sizes of matrix: " << zero_mat.GetRows() << " and " << zero_mat.GetColumns() << "\n";
    std::cout << "insert row with filler 2 in this matrix: \n";
    zero_mat.insertRow(0, 2);
    std::cout << zero_mat << "\n\n";

    std::cout << "Test constructor with initialization list c({ { 1., 2. }, { 3., 4. } }):\n";
    Matrix<double> c({ { 1., 2. }, { 3., 4. } });
    std::cout << c << "\n\n";
    
    try {
        std::cout << "Test negative size" << std::endl;
        Matrix<int> err_m(-2, 2);
    }
    catch (ExceptionMatrix& err) {
        std::cerr << err.what() << "\n\n";
    }

    std::cout << "==========\n\n\n";

    // Test insert delete resize
    std::cout << "Test insert delete resize:\n\n";
    std::cout << "Working with matrix c:\n";
    std::cout << c << "\n\n";

    std::cout << "Test insertRow(1, 3.33);\n";
    c.insertRow(1, 3.33);
    std::cout << c << "\n\n";

    std::cout << "Test insertCol(1, 4.321);\n";
    c.insertCol(1, 4.321);
    std::cout << c << "\n\n";

    std::cout << "Test deleteCol(1);\n";
    c.deleteCol(1);
    std::cout << c << "\n\n";

    std::cout << "Test deleteRow(0);\n";
    c.deleteRow(0);
    std::cout << c << "\n\n";

    std::cout << "Test resizeRows(c.GetRows() + 1);\n";
    c.resizeRows(c.GetRows() + 1);
    std::cout << c << "\n\n";

    std::cout << "Test resizeCols(c.GetColumns() + 1);\n";
    c.resizeCols(c.GetColumns() + 1);
    std::cout << c << "\n\n";

    std::cout << "Test resizeRows(c.GetRows() + 1, 34);\n";
    c.resizeRows(c.GetRows() + 1, 34);
    std::cout << c << "\n\n";

    std::cout << "Test resizeCols(c.GetColumns() + 1, 43);\n";
    c.resizeCols(c.GetColumns() + 1, 43);
    std::cout << c << "\n\n";

    std::cout << "Test resize(c.GetRows() + 2, c.GetColumns() + 1);\n";
    c.resize(c.GetRows() + 2, c.GetColumns() + 1);
    std::cout << c << "\n\n";

    std::cout << "Test resize(c.GetRows() - 2, c.GetColumns() - 1);\n";
    c.resize(c.GetRows() - 2, c.GetColumns() - 1);
    std::cout << c << "\n\n";

    std::cout << "===========\n\n\n";

    std::cout << "Test of transpose method on matrix c (but first - resize (+ 2 rows)):\n";
    std::cout << "Test c.resizeRows(c.GetRows() + 2, 32.10);\n";
    c.resizeRows(c.GetRows() + 2, 32.10);
    std::cout << "Result: \n" << c << "\n\n";
    std::cout << "Test c.transpose();\n";
    c.transpose();
    std::cout << "Result: \n" << c << "\n\n";

    // Test get elements methods
    std::cout << "Test elements method:\n\n";
    Matrix<string> new_m = { { "a1", "a2", "a3" }, { "b1", "b2", "b3" }, { "c1", "c2", "c3" } };
    std::cout << "Test matrix new_m: \n" << new_m << "\n\n";

    std::cout << "Test new_m[1][1] and new_m.at(1, 1)\n";
    std::cout << new_m[1][1] << " / " << new_m.at(1, 1) << "\n\n";

    std::cout << "Test new_m[1][1] = new1 and new_m.at(1, 2) = new2\n";
    new_m[1][1] = "new1"; new_m.at(1, 2) = "new2";
    std::cout << "new_m[1][1] = " << new_m[1][1] << ", new_m[1][2] = " << new_m[1][2] << "\n\n";
    std::cout << "==========\n\n\n";

    // Test iterators
    std::cout << "Test iterators\n\n";
    std::cout << "Test new_m matrix from previous section:\n";
    std::cout << new_m << "\n\n";

    std::cout << "Test range-based for cycle (const elem &), ' ' as delimiter\n";
    for (const auto &elem: new_m)
        std::cout << elem << ' ';
    std::cout << "\n\n";

    size_t cnt = 0;
    std::cout << "Range-based for filling matrix with string \"new_test<number>\":\n";
    for (auto &elem: new_m)
        elem = "new_test" + std::to_string(++cnt);
    std::cout << new_m << "\n\n";

    std::cout << "Test fill [from, to, filler]:\n";
    new_m.fill(new_m.end() - static_cast<int>(new_m.GetColumns()), new_m.end(), "filler_for_last_line");
    std::cout << new_m << "\n\n";

    std::cout << "Test fill from another matrix container via iterators:\n";
    Matrix<string> test_m = {{"test1", "test2", "test3"}, {"test4", "test5", "test6"}};
    new_m.fill(new_m.end() - static_cast<int>(new_m.GetColumns()), test_m.begin(), test_m.end());
    std::cout << new_m << "\n\n";

    std::cout << "==========\n\n";

    // Test const iterators and objects
    std::cout << "Test const iterators and objects\n\n";

    std::cout << "Create const matrix = { { '11', '12', '13' }, { '21', '22', '23' } }\n";
    const Matrix<string> const_m = { { "11", "12", "13" }, { "21", "22", "23" } };
    std::cout << "Range-based for cycle for const matrix:\n";
    for (const auto &elem: const_m)
        std::cout << elem << "; ";
    std::cout << "\n\n";

    std::cout << "Insert in new_m matrix from const matrix:\n";
    std::cout << "new_m matrix:\n" << new_m << "\n\n";
    std::cout << "Test new_m.fill(new_m.begin(), const_m.begin(), const_m.begin() + 3);\n";
    new_m.fill(new_m.begin(), const_m.begin(), const_m.begin() + 3);
    std::cout << "new_m matrix after insertion: \n" << new_m << "\n\n";

    std::cout << "Check of cbegin and cend methods of non-constant object (new_m matrix):\n";
    for (auto it = new_m.cbegin(); it < new_m.cend(); it++)
        std::cout << *it << "; ";
    std::cout << "\n\n";
    std::cout << "==========\n\n";

    // Test math operations
    std::cout << "Test math operations\n\n";
    Matrix<double> math_matrix = { { 1, 2, 3, 4 }, {5, 6, 7, 8}, {-9, 10, -11, 12}, {13, -14, 15, -16} };
    std::cout << "Test matrix: \n";
    std::cout << math_matrix << "\n\n";

    std::cout << "Test math_matrix += 2.5;\n";
    math_matrix += 2.5;
    std::cout << "result:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Test math_matrix -= 2.5;\n";
    math_matrix -= 2.5;
    std::cout << "result:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Test *= 2.5;\n";
    math_matrix *= 2.5;
    std::cout << "result:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Test /= 2.5;\n";
    math_matrix /= 2.5;
    std::cout << "result:\n";
    std::cout << math_matrix << "\n\n";

    std::cout << "Using methods:\n";
    std::cout << "Test addEqElem(2.5);\n";
    math_matrix.addAssigElem(2.5);
    std::cout << "result:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Test subEqElem(2.5);\n";
    math_matrix.subAssigElem(2.5);
    std::cout << "result:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Test mulEqElem(2.5);\n";
    math_matrix.mulAssigElem(2.5);
    std::cout << "result:\n";
    std::cout << math_matrix << "\n\n";
    std::cout << "Test divEqElem(2.5);\n";
    math_matrix.divAssigElem(2.5);
    std::cout << "result:\n";
    std::cout << math_matrix << "\n\n";

    Matrix<double> tmp;

    std::cout << "Test operators:\n";
    std::cout << "Test tmp = math_matrix + 2.5;\n";
    tmp = math_matrix + 2.5;
    std::cout << "result:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Test tmp = math_matrix - 2.5;\n";
    tmp = math_matrix - 2.5;
    std::cout << "result:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Test tmp = math_matrix * 2.5;\n";
    tmp = math_matrix * 2.5;
    std::cout << "result:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Test tmp = math_matrix / 2.5;\n";
    tmp = math_matrix / 2.5;
    std::cout << "result:\n";
    std::cout << tmp << "\n\n";

    std::cout << "Using methods\n";
    std::cout << "Test tmp = math_matrix.addElem(2.5);\n";
    tmp = math_matrix.addElem(2.5);
    std::cout << "result:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Test tmp = math_matrix.subElem(2.5);\n";
    tmp = math_matrix.subElem(2.5);
    std::cout << "result:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Test tmp = math_matrix.mulElem(2.5);\n";
    tmp = math_matrix.mulElem(2.5);
    std::cout << "result:\n";
    std::cout << tmp << "\n\n";
    std::cout << "Test tmp = math_matrix.divElem(2.5);\n";
    tmp = math_matrix.divElem(2.5);
    std::cout << "result:\n";
    std::cout << tmp << "\n\n";

    std::cout << "Negative matrix operator: \n" << -math_matrix <<
        "\nwith method:\n" << math_matrix.neg() << '\n';

    Matrix<double> det_matrix = { { 38, 382, 21, 9 }, { 21, 1, 9, 11 }, { 118, 5, 85, 2 }, { 10, 8, 22, 13 } };
    std::cout << "Determinant test matrix:\n" << det_matrix << "\n\n";
    std::cout << "Test matrix.determinant();\n";
    std::cout << "result: " << det_matrix.determinant() << "\n";
    std::cout << "Test matrix.inverse();\n";
    det_matrix.inverse();
    std::cout << "result: \n" << det_matrix << "\n";
    det_matrix.inverse();
    std::cout << "\nInverse one more time\nResult: \n" << det_matrix << "\n";

    // Check multiplication
    std::cout << "Matrix multiplication test: \n";
    Matrix<double> res;
    Matrix<double> m1 = { { 1 }, { 2 }, { 3 } }, m2 = { { 1, 2 } };
    std::cout << "Operation: m1 * m2 (m1 = { { 1 }, { 2 }, { 3 } }, m2 = { { 1, 2 } })\n";
    res = m1 * m2;
    std::cout << "result:\n" << res << "\n\n";
    std::cout << "Using method: m1 * m2 (m1 = { { 1 }, { 2 }, { 3 } }, m2 = { { 1, 2 } })\n";
    res = m1.mulMatrix(m2);
    std::cout << "result:\n" << res << "\n\n";

    // Check division
    std::cout << "Matrix division test: \n";
    Matrix<double> m3 = { { 1, 2 }, { 3, 4 } };
    Matrix<double> m4 = { { 1, 2 }, { 3, 4 } };
    std::cout << "Test m3 / m4 (m4 = m3, sizes: 2x2)\n";
    res = m3 / m4;
    std::cout << "result:\n" << res << "\n\n";
    std::cout << "Using method: m3 / m4 (m4 = m3, sizes: 2x2)\n";
    res = m3.divMatrix(m4);
    std::cout << "result:\n" << res << "\n\n";

    std::cout << "==========\n\n";

    // Test errors
    std::cout << "Test error operators\n\n";

    std::cout << "Test attempt to read expired iterator\n";
    try {
        Iterator<double> it_tmp = res.begin();
        {
            Matrix<double> tmp = { { 1, 2 }, { 3, 4 } };
            it_tmp = tmp.begin();
        }
        std::cout << *it_tmp;
    } catch (ExceptionMatrix &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "Test call operator* for iterator out of the bounds:\n";
    try {
        Iterator<double> it_tmp = res.end();
        std::cout << *it_tmp;
    } catch (ExceptionMatrix &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "Test operator + for incompatible matrices:\n";
    try {
        Matrix<int> m1 = { { 1, 2, 3 } };
        Matrix<int> m2 = { { 1, 2 }, { 3, 4 } };
        std::cout << m1 + m2;
    } catch (ExceptionMatrix &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "Test operator * for incompatible matrices:\n";
    try {
        Matrix<int> m1 = { { 1, 2, 3 } };
        Matrix<int> m2 = { { 1, 2, 3 } };
        std::cout << m1 * m2;
    } catch (ExceptionMatrix &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "Test all of constructor with invalid argument:\n";
    try {
        Matrix<int> matrix_inv = { { 1, 2 }, { 3 } };
    } catch (ExceptionMatrix &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "Test all of operator= with init list (correct and incorrect):\n";
    try {
        Matrix<int> matrix_inv = { { 1, 2 }, { 3, 4 } };
        matrix_inv = { { 3, 4, 5 }, {1, 2, 3} };
        std::cout << "Correct init-list done:\n" << matrix_inv << "\n";
        matrix_inv = { { 4, 5 }, {1, 2, 3} };
    } catch (ExceptionMatrix &err) {
        std::cout << err.what() << "\n\n\n";
    }

    std::cout << "Test all or constructor which is working with c_matrix\n";
    try {
        int **ec_matrix = NULL;
        Matrix<int> matr_er { 2, 2, ec_matrix };
        std::cout << matr << "\n\n";
    } catch (ExceptionMatrix &err) {
        std::cout << err.what() << "\n\n";
    }
    std::cout << "==========\n\n";
    return 0;
}