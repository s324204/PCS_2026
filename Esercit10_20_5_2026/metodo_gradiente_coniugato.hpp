#pragma once
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>

// Eigen::MatrixXd vuol dire Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic>
template<typename T>
double cond(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& A) { // condizionamento di matrice simm def pos è K=|max(autoval(A))|/|min(autoval(A))|
  Eigen::JacobiSVD<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>> svd(A);
  Eigen::Vector<T, Eigen::Dynamic> singularValuesA = svd.singularValues();
  return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
}

template<typename T>                                          //la funzione ha in pasto: gradiente_coniugato(A, b, it, it_max, tol, res_tol)
Eigen::Vector<T, Eigen::Dynamic> gradiente_coniugato(const Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>& A, Eigen::Vector<T, Eigen::Dynamic>& b, unsigned int& it, const unsigned int& it_max, const double& tol, const double& res_tol) {
  std::cout.precision(2);
  std::cout << std::scientific << "Condizionamento della matrice A: "<< cond(A) << std::endl;

  int dim=A.cols();
  it = 0;
  Eigen::Vector<T, Eigen::Dynamic> x = Eigen::Vector<T, Eigen::Dynamic>::Zero(dim);
  Eigen::Vector<T, Eigen::Dynamic> res = b - A*x;
  double res_norm_0 = res.norm();
  Eigen::Vector<T, Eigen::Dynamic> p = res;

  while (it < it_max && res.norm() > res_tol*res_norm_0) {
    const double alpha_k = ((p.transpose()*res)/(p.transpose()*A*p)).value(); 
      // senza il value, il prodotto scalare genera in Eigen una matrice 1x1, non un numero
    x = x + alpha_k*p;
    res = res - alpha_k*A*p;
    const double beta_k = ((p.transpose()*A*res)/(p.transpose()*A*p)).value();
    p = res - beta_k*p;
    it++;
  }
          
  std::cout.precision(4);
  std::cout<< std::scientific << "In " << it << "/" << it_max << " iterazioni," << std::endl;
  //std::cout<< std::scientific << it<< "/" << it_max << std::endl;
  std::cout<< std::scientific << "e con res"<< "/" << "res_tol: " << res.norm() / res_norm_0 << "/" << res_tol << "," << std::endl;
  //std::cout<< std::scientific << res.norm() / res_norm_0 << "/" << res_tol << std::endl;
  
  return x;
}
//avrei potuto usare i metodi nativi delle Eigen come .dot() (trovati su video youtube e internet) per evitare .transpose() e .value() e migliorare le prestazioni, 
//ma ho voluto rispettare cioè che aveva fatto il professore in aula