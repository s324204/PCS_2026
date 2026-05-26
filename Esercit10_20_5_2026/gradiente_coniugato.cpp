#include "metodo_gradiente_coniugato.hpp"
#include <Eigen/Dense>
#include <Eigen/SVD>

// !!! per la compilazione con Eigen: g++ -std=c++20 test_gc.cpp -I /usr/include/eigen3 -o test !!!

int main(int argc, char **argv) {
    const double tol = 1.0e-15;
    unsigned int it = 0;
    const unsigned int it_max = 10000;
    const double res_tol = 1.0e-12;
    
    //ciclo su dimensioni
    for (int dim=2; dim<=20; dim++) {
        Eigen::MatrixXd B = Eigen::MatrixXd::Random(dim, dim);
        if (std::abs(B.determinant()) < tol){
            throw std::invalid_argument("ERRORE: la matrice è singolare! Fornire un'altra matrice");
        }

        // rendiamo simm e def pos la matrice B (nel caso non lo sia) creando una nuova matrice A
        Eigen::MatrixXd A = B.transpose()*B;
        Eigen::VectorXd x_esatta = Eigen::VectorXd::Ones(dim);
        Eigen::VectorXd b = A*x_esatta;

        Eigen::VectorXd x = gradiente_coniugato<double>(A, b, it, it_max, tol, res_tol);
        std::cout << "La soluzione a cui converge la matrice B di dimensione " << dim << " è x = " << "[" << x << "]" << std::endl;
            
        auto err_rel = 0.0;
        if (x_esatta.norm()==0.0) {
            err_rel = (x - x_esatta).norm();
        }
        else {
            err_rel = (x - x_esatta).norm()/x_esatta.norm();
        }
        std::cout << "Mentre l'errore relativo è " << err_rel << std::endl;

    }

    return 0;
}