// 
// Compute the skewness of a set of values
// 

#include <RcppArmadillo.h>
using namespace Rcpp; 
using namespace arma; 

#define NOVAR_SKEWNESS_VAL NA_REAL


// 
//' 
//' @title Skewness
//' 
//' @description Compute the skewness of a given set of values 
//' 
//' @return Skewness as a numeric value. 
//' 
//' @details If the values provided have zero variance, then \code{NA} 
//'   is returned. 
//' 
//' @param X A vector of values
//' 
//' @seealso \code{\link[moments]{skewness}}
//' 
//'@export
//[[Rcpp::export]]
double raw_skewness(arma::vec X) { 
  
  // Number of elements in X
  int N = X.n_elem; 
  
  // if not enough elements, return early 
  if ( N < 2 ) { 
    return( NOVAR_SKEWNESS_VAL ); 
  }
  
  // else, proceed with computing skewness
  double xmean = arma::mean(X); 
  
  // Compute the upper term
  double cubesum = 0; 
  double sqsum = 0; 
  for (int i=0; i<N; i++) { 
    cubesum += (X(i) - xmean) * (X(i) - xmean) * (X(i) - xmean); 
    sqsum  += (X(i) - xmean) * (X(i) - xmean); 
  }
  cubesum = cubesum / N; 
  sqsum  = sqsum  / N; 
  
  // Compute skewness
  double skewness; 
  if ( sqsum == 0 ) { 
    return( NOVAR_SKEWNESS_VAL ); 
  } else { 
    skewness = cubesum / pow(sqsum, 1.5); 
  }
  return(skewness);
}
