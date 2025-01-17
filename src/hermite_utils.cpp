// [[Rcpp::depends(BH)]]
// [[Rcpp::depends(RcppParallel)]]
#include <Rcpp.h>
#include <RcppParallel.h>
#include <boost/math/special_functions/factorials.hpp>
#include <boost/math/special_functions/erf.hpp>

using namespace Rcpp;
using namespace RcppParallel;

//' Outputs physicist version of Hermite Polynomials
//' 
//' 
//' The method calculates the physicist version of Hermite polynomials, 
//' \eqn{H_k(x)} from \eqn{k=0,\dots,N} for the vector of values, x.
//' 
//' @author Michael Stephanou <michael.stephanou@gmail.com>
//'
//' @param N An integer number.
//' @param x A numeric vector.
//' @return A numeric matrix with N+1 rows and length(x) columns.
//' @export
// [[Rcpp::export]]
NumericMatrix hermite_polynomial(int N, NumericVector x) {
  int x_size = x.size();
  NumericMatrix hermite(N + 1, x_size);
  for(int i = 0; i < x_size; ++i) {
    hermite(0,i) = 1;
  }
  if (N==0){
    return hermite;
  }
  for(int i = 0; i < x_size; ++i) {
    hermite(1,i) = 2 * x[i];
  }
  if (N==1){
    return hermite;
  }
  for(int j = 0; j < x_size; ++j) {
    for(int i = 2; i <= N; ++i) {
      hermite(i,j) = 2 * x[j] * hermite(i - 1,j) - 2 *
       (((double)i) - 1) * hermite(i - 2,j);
    }
  }
  return hermite;
}

//' Outputs Hermite normalization factors 
//' 
//' The method returns numeric normalization factors that, when multiplied by 
//' the physicist Hermite polynomials times a Gaussian factor i.e.
//' \eqn{\exp{x^2/2}H_k(x)}, yields orthonormal 
//' Hermite functions \eqn{h_k(x)} for \eqn{k=0,\dots,N}.
//'
//' @author Michael Stephanou <michael.stephanou@gmail.com>
//'
//' @param N An integer number.
//' @return A numeric vector of length N+1
//' @export
// [[Rcpp::export]]
NumericVector hermite_normalization(int N) {
  NumericVector out(N + 1);
  double sqrt_pi = sqrt(M_PI);
  for(int i = 0; i <= N; ++i) {
    out(i) = 1/sqrt(pow((double)2,(double)i) * 
      boost::math::factorial<double>((double)i) * sqrt_pi); 
  }
  return out;
}

//' Outputs orthonormal Hermite functions
//' 
//' 
//' The method calculates the orthonormal Hermite functions, \eqn{h_k(x)} 
//' from \eqn{k=0,\dots,N} for the vector of values, x.
//' 
//' @author Michael Stephanou <michael.stephanou@gmail.com>
//'
//' @param N An integer number.
//' @param x A numeric vector.
//' @return A numeric matrix with N+1 rows and length(x) columns.
//' @export
// [[Rcpp::export]]
NumericMatrix hermite_function(int N, NumericVector x) {
  int x_size = x.size();
  NumericMatrix out(N + 1, x_size);
  NumericVector expFac(x_size);
  double piConst = pow(M_PI,-0.25);
  double sqrt2 = sqrt((double) 2);
  int i = 0;
  int j = 0;
  // Uses unrolling loop optimization below
  for(i = 0; i <= x_size - 4 ; i+=4) {
    expFac(i) = exp(-1 * x[i] * x[i] / 2);
    expFac(i+1) = exp(-1 * x[i+1] * x[i+1] / 2);
    expFac(i+2) = exp(-1 * x[i+2] * x[i+2] / 2);
    expFac(i+3) = exp(-1 * x[i+3] * x[i+3] / 2);
    out(0,i) = piConst * expFac(i);
    out(0,i+1) = piConst * expFac(i+1);
    out(0,i+2) = piConst * expFac(i+2);
    out(0,i+3) = piConst * expFac(i+3);
  }
  for(; i < x_size; ++i) {
    expFac(i) = exp(-1 * x[i] * x[i] / 2);
    out(0,i) = piConst * expFac(i);
  }
  if (N==0){
    return out;
  }
  for(i = 0; i <= x_size-4; i+=4) {
    out(1,i) =  sqrt2* piConst * x(i)* expFac(i);
    out(1,i+1) = sqrt2 * piConst * x(i+1)* expFac(i+1);
    out(1,i+2) = sqrt2 * piConst * x(i+2)* expFac(i+2);
    out(1,i+3) = sqrt2 * piConst * x(i+3)* expFac(i+3);
  }
  for(; i < x_size; ++i) {
    out(1,i) = sqrt2 * piConst * x(i)* expFac(i);
  }
  if (N==1){
    return out;
  }
  for(j = 0; j <= x_size - 4; j += 4) {
    for(i = 2; i <= N; ++i) {
      out(i,j) = sqrt(2 / ((double) i)) * x[j] * out(i - 1,j) - 
        sqrt(1 - 1/((double)i)) * out(i - 2,j);
      out(i,j+1) = sqrt(2 / ((double) i)) * x[j+1] * out(i - 1,j+1) - 
        sqrt(1 - 1/((double)i)) * out(i - 2,j+1);
      out(i,j+2) = sqrt(2 / ((double) i)) * x[j+2] * out(i - 1,j+2) - 
        sqrt(1 - 1/((double)i)) * out(i - 2,j+2);
      out(i,j+3) = sqrt(2 / ((double) i)) * x[j+3] * out(i - 1,j+3) - 
        sqrt(1 - 1/((double)i)) * out(i - 2,j+3);
    }
  }
  for(; j < x_size; ++j) {
    for(int i = 2; i <= N; ++i) {
      out(i,j) = sqrt(2 / ((double) i)) * x[j] * out(i - 1,j) - 
        sqrt(1 - 1/((double)i)) * out(i - 2,j);
    }
  }
  return out;
}

//' Outputs the sum of orthonormal Hermite functions
//' 
//' 
//' The method calculates the sum of orthonormal Hermite functions, 
//' \eqn{\sum_{i} h_k(x_{i})} from \eqn{k=0,\dots,N} for the vector of values,
//' x.
//' 
//' @author Michael Stephanou <michael.stephanou@gmail.com>
//'
//' @param N An integer number.
//' @param x A numeric vector.
//' @return A numeric vector of length N+1.
//' @export
// [[Rcpp::export]]
NumericVector hermite_function_sum_serial(int N, NumericVector x) {
  int x_size = x.size();
  NumericMatrix out(N + 1, x_size);
  NumericVector expFac(x_size);
  NumericVector resultOut(N + 1);
  double piConst = pow(M_PI,-0.25);
  double sqrt2 = sqrt((double) 2);
  int i = 0;
  int j = 0;
  // Uses unrolling loop optimization below
  for(i = 0; i <= x_size - 4 ; i += 4) {
    expFac(i) = exp(-1 * x[i] * x[i] / 2);
    expFac(i+1) = exp(-1 * x[i+1] * x[i+1] / 2);
    expFac(i+2) = exp(-1 * x[i+2] * x[i+2] / 2);
    expFac(i+3) = exp(-1 * x[i+3] * x[i+3] / 2);
    out(0,i) = piConst * expFac(i);
    out(0,i+1) = piConst * expFac(i+1);
    out(0,i+2) = piConst * expFac(i+2);
    out(0,i+3) = piConst * expFac(i+3);
    resultOut(0) += out(0,i) + out(0,i+1) + out(0,i+2) + out(0,i+3);
  }
  for(; i < x_size; ++i) {
    expFac(i) = exp(-1 * x[i] * x[i] / 2);
    out(0,i) = piConst * expFac(i);
    resultOut(0) += out(0,i);
  }
  if (N==0){
    return resultOut;
  }
  for(i = 0; i <= x_size-4; i += 4) {
    out(1,i) = sqrt2 * piConst * x(i)* expFac(i);
    out(1,i+1) = sqrt2 * piConst * x(i+1)* expFac(i+1);
    out(1,i+2) = sqrt2 * piConst * x(i+2)* expFac(i+2);
    out(1,i+3) = sqrt2 * piConst * x(i+3)* expFac(i+3);
    resultOut(1) += out(1,i) +out(1,i+1) +out(1,i+2)+ out(1,i+3);
  }
  for(; i < x_size; ++i) {
    out(1,i) = sqrt2 * piConst * x(i)* expFac(i);
    resultOut(1) += out(1,i);
  }
  if (N==1){
    return resultOut;
  }
  for(j = 0; j <= x_size - 4; j += 4) {
    for(i = 2; i <= N; ++i) {
      out(i,j) = sqrt(2 / ((double) i)) * x[j] * out(i - 1,j) - 
        sqrt(1 - 1/((double)i)) * out(i - 2,j);
      out(i,j+1) = sqrt(2 / ((double) i)) * x[j+1] * out(i - 1,j+1) - 
        sqrt(1 - 1/((double)i)) * out(i - 2,j+1);
      out(i,j+2) = sqrt(2 / ((double) i)) * x[j+2] * out(i - 1,j+2) - 
        sqrt(1 - 1/((double)i)) * out(i - 2,j+2);
      out(i,j+3) = sqrt(2 / ((double) i)) * x[j+3] * out(i - 1,j+3) - 
        sqrt(1 - 1/((double)i)) * out(i - 2,j+3);
      resultOut(i) += out(i,j) +out(i,j+1) +out(i,j+2)+ out(i,j+3);
    }
  }
  for(; j < x_size; ++j) {
    for(int i = 2; i <= N; ++i) {
      out(i,j) = sqrt(2 / ((double) i)) * x[j] * out(i - 1,j) - 
        sqrt(1 - 1/((double)i)) * out(i - 2,j);
      resultOut(i) += out(i,j);
    }
  }
  return resultOut;
}

//' Outputs lower integral of the orthonormal Hermite functions
//' 
//' The method calculates \eqn{\int_{-\infty}^{x} h_k(t) dt} 
//' for \eqn{k=0,\dots,N} and the vector of values x.
//' 
//' @author Michael Stephanou <michael.stephanou@gmail.com>
//'
//' @param N An integer number.
//' @param x A numeric vector.
//' @param hermite_function_mat A numeric matrix of Hermite function values 
//' generated by the function hermite_function.
//' @return A numeric matrix with N+1 rows and length(x) columns.
//' @export
// [[Rcpp::export]]
NumericMatrix hermite_integral_val(int N, NumericVector x, 
                                   NumericMatrix hermite_function_mat) {
  int x_size = x.size();
  NumericMatrix out(N + 1, x_size);
  for(int i = 0; i < x_size; ++i) {
    out(0,i) = pow(M_PI,0.25)/sqrt((double) 2) *
     boost::math::erfc<double>((double) -1 * (1 / sqrt((double)2)) * x[i]); 
  }
  if (N == 0){
    return out;
  }
  for(int i = 0; i < x_size; ++i) {
    out(1,i) = -1 * sqrt((double) 2)/pow(M_PI,0.25) *exp(-1 * x[i] * x[i] / 2); 
  }
  if (N == 1){
    return out;
  }
  for(int i = 2; i <= N; ++i) {
    for(int j = 0; j < x_size; ++j) {
      out(i,j) = -1 * sqrt(2/((double)i)) * hermite_function_mat(i - 1,j) + 
       sqrt((((double)i) - 1)/((double)i)) * out(i - 2,j);
    }
  }
  return out;
}

//' Outputs upper integral of the orthonormal Hermite functions
//' 
//' The method calculates \eqn{\int_{x}^{\infty} h_k(t) dt} 
//' for \eqn{k=0,\dots,N} and the vector of values x.
//' 
//' @author Michael Stephanou <michael.stephanou@gmail.com>
//'
//' @param N An integer number.
//' @param x A numeric vector.
//' @param hermite_function_mat A numeric matrix of Hermite function values 
//' generated by the function hermite_function.
//' @return A numeric matrix with N+1 rows and length(x) columns.
//' @export
// [[Rcpp::export]]
NumericMatrix hermite_integral_val_upper(int N,
                         NumericVector x, NumericMatrix hermite_function_mat) {
  int x_size = x.size();
  NumericMatrix out(N + 1, x_size);
  for(int i = 0; i < x_size; ++i) {
    out(0,i) = pow(M_PI,0.25)/sqrt((double) 2) *
     boost::math::erfc<double>((double) (1 / sqrt((double) 2)) * x[i]); 
  }
  if (N == 0){
    return out;
  }
  for(int i = 0; i < x_size; ++i) {
    out(1,i) = sqrt((double) 2)/pow(M_PI,0.25) *exp(-1 * x[i] * x[i] / 2); 
  }
  if (N == 1){
    return out;
  }
  for(int i = 2; i <= N; ++i) {
    for(int j = 0; j < x_size; ++j) {
      out(i,j) = sqrt(((double)2) / ((double)i)) * hermite_function_mat(i-1,j)+ 
       sqrt((((double)i)-1)/((double)i)) * out(i-2,j);
    }
  }
  return out;
}

//' Outputs integral of the orthonormal Hermite functions on the full domain
//' 
//' The method calculates \eqn{\int_{-\infty}^{\infty} h_k(t) dt} 
//' for \eqn{k=0,\dots,N}.
//' 
//' @author Michael Stephanou <michael.stephanou@gmail.com>
//'
//' @param N An integer number.
//' @return A numeric matrix with N+1 rows and 1 columns.
//' @export
// [[Rcpp::export]]
NumericMatrix hermite_int_full_domain(int N) {
  NumericMatrix out(N + 1, 1);
  out(0,0) = pow(M_PI,0.25)*sqrt((double) 2); 
  if (N == 0){
    return out;
  }
  out(1,0) = 0; 
  if (N == 1){
    return out;
  }
  for(int i = 2; i <= N; ++i) {
      out(i,0) = sqrt((((double)i)-1)/((double)i)) * out(i-2,0);
  }
  return out;
}

//' Standardizes the observation x and updates the online moment inputs
//' 
//' @author Michael Stephanou <michael.stephanou@gmail.com>
//' 
//' @param x A numeric value.
//' @param n_obs A numeric value. The number of observations.
//' @param current_mean A numeric value. 
//' @param current_var A numeric value. 
//' @return A numeric vector. The first element is the updated mean. The
//' second element is the updated variance times n_obs. The third element is the
//' updated, standardized value of x.
//' @export
// [[Rcpp::export]]
NumericVector standardizeInputs(double x, double n_obs, double current_mean,
                                double current_var) {
  NumericVector outputVec(3);
  double prev_running_mean = current_mean;
  outputVec[0] =  (current_mean * (n_obs - 1) + x) / n_obs;
  if (n_obs < 2){
    return outputVec;
  }
  outputVec[1] = current_var + (x - prev_running_mean) * (x - outputVec[0]);
  double running_std = sqrt(outputVec[1] / (n_obs - 1));
  outputVec[2] = (x - outputVec[0]) / running_std;
  return outputVec;
}

//' Standardizes the observation x and updates the online moment inputs
//' 
//' The online moments are updated via exponential weighting.
//' 
//' @author Michael Stephanou <michael.stephanou@gmail.com>
//'
//' @param x A numeric value.
//' @param n_obs A numeric value. The number of observations.
//' @param lambda A numeric value.
//' @param current_mean A numeric value.
//' @param current_var A numeric value.  
//' @return A numeric vector. The first element is the updated mean. The
//' second element is the updated variance times n_obs. The third element is the
//' updated, standardized value of x.
//' @export
// [[Rcpp::export]]
NumericVector standardizeInputsEW(double x, double n_obs,double lambda,
                                  double current_mean, double current_var) {
  NumericVector outputVec(3);
  if (n_obs < 2){
    current_mean = x;
    current_var = 1;
    outputVec[0] =  current_mean;
    outputVec[1] = current_var;
    return outputVec;
  }
  outputVec[0] =  (1 - lambda) * current_mean + lambda * x;
  current_var = (1 - lambda) * current_var + lambda * pow((x - outputVec[0]),2);
  outputVec[1] = current_var;
  double running_std = sqrt(current_var);
  outputVec[2] = (x - outputVec[0]) / running_std;
  return outputVec;
}

// struct HermiteS : public Worker
// {
//   // Input and output
//   const std::size_t N;
//   const RVector<double> input;
//   std::vector<double> value;
//   // constructors
//   HermiteS(const std::size_t N, const NumericVector input) : N(N), input(input), value() {value.resize(N+1,0.0);}
//   HermiteS(const HermiteS& hermite_sum, Split) : N(hermite_sum.N),input(hermite_sum.input), value() {value.resize(N+1,0.0);}
//   // Hermite Sum calculation
//   void operator()(std::size_t begin, std::size_t end) {
//     double piConst = pow(M_PI,-0.25);
//     double sqrt2 = sqrt((double) 2);
//     double out_curr = 0;
//     double out_0 = 0;
//     double out_1 =0;
//     for(std::size_t j = begin; j < end; j++) {
//       out_0 = piConst * exp(-1 * input[j] * input[j] / 2);
//       value[0] += out_0;
//     }
//     if (N >= 1){
//       for(std::size_t j = begin; j < end; j++) {
//         out_1  = sqrt2 * piConst * input[j]* exp(-1 * input[j] * input[j] / 2);
//         value[1] += out_1;
//       }
//       if (N >= 2){
//         for(std::size_t j = begin; j < end; j++) {
//           for(std::size_t i = 2; i <= N; i++) {
//             out_curr = sqrt(2 / ((double) i)) * input[j] * out_1 -
//               sqrt(1 - 1/((double)i)) * out_0;
//             value[i] += out_curr;
//             out_0 = out_1;
//             out_1 = out_curr;
//           }
//         }
//       }
//     }
//   }
//   void join(const HermiteS& rhs) {
//     for(std::size_t i = 0; i <= N; i++) {
//       value[i] += rhs.value[i];
//     }
//   }
// };


struct HermiteS : public Worker
{
  // Input and output
  const size_t N;
  const RVector<double> input;
  std::vector<double> value;
  // constructors
  HermiteS(const size_t N, const NumericVector input) : N(N), input(input), value() {value.resize(N+1,0.0);}
  HermiteS(const HermiteS& hermite_sum, Split) : N(hermite_sum.N),input(hermite_sum.input), value() {value.resize(N+1,0.0);}
  // Hermite Sum calculation
  void operator()(std::size_t begin, std::size_t end) {
    double piConst = pow(M_PI,-0.25);
    double sqrt2 = sqrt((double) 2);
    double out_curr = 0;
    double out_0 = 0;
    double out_1 =0;
    for(std::size_t j = begin; j < end; j++) {
      out_0 = piConst * exp(-1 * input[j] * input[j] / 2);
      value[0] += out_0;
      out_1  = sqrt2 * piConst * input[j]* exp(-1 * input[j] * input[j] / 2);
      value[1] += out_1;
      for(size_t i = 2; i <= N; i++) {
        out_curr = sqrt(2 / ((double) i)) * input[j] * out_1 -
          sqrt(1 - 1/((double)i)) * out_0;
        value[i] += out_curr;
        out_0 = out_1;
        out_1 = out_curr;
      }
    }
  }
  void join(const HermiteS& rhs) {
    for(size_t i = 0; i <= N; i++) {
      value[i] += rhs.value[i];
    }
  }
};

// [[Rcpp::export]]
NumericVector hermite_function_sum_parallel(int N, NumericVector x) {
  HermiteS hermites(N,x);
  parallelReduce(0, x.length(), hermites);
  return wrap(hermites.value);
}

struct SeriesCalc : public Worker {
  const std::size_t N;
  const RVector<double> preFac;
  const RMatrix<double> h_input;
  // input matrix to read from
  const RVector<double> coeffs;
  // output matrix to write to
  RVector<double> rout;
  SeriesCalc(const int N, const NumericVector preFac, 
             const NumericMatrix h_input, const NumericVector coeffs, 
             NumericVector rout)
    : N(N), preFac(preFac), h_input(h_input), coeffs(coeffs), rout(rout) {}
  void operator()(std::size_t begin, std::size_t end) {
    for (std::size_t j = begin; j < end; j++) {
      RMatrix<double>::Column h_input_col = h_input.column(j);
      rout[j] = std::inner_product(h_input_col.begin(),
                                   h_input_col.begin() + N - 7,
                                   coeffs.begin(),
                                   0.0)+
                                     std::inner_product(h_input_col.begin() +
                                                        N - 7,
                                                        h_input_col.end(),
                                                        preFac.begin(),
                                                        0.0);       
    }
  }
};

// [[Rcpp::export]]
NumericVector series_calc_parallel_8_fold(NumericMatrix h_input, 
                                          NumericVector coeffs) {
  int ncol_val = h_input.ncol();
  int N = h_input.nrow() - 1;
  NumericVector rout(ncol_val);
  NumericVector preFactors(8);
  preFactors[0] = 255.0/256.0*coeffs[N-7];
  preFactors[1] = 247.0/256.0*coeffs[N-6];
  preFactors[2] = 219.0/256.0*coeffs[N-5];
  preFactors[3] = 163.0/256.0*coeffs[N-4];
  preFactors[4] = 93.0/256.0*coeffs[N-3];
  preFactors[5] = 37.0/256.0*coeffs[N-2];
  preFactors[6] = 9.0/256.0*coeffs[N-1];
  preFactors[7] = 1.0/256.0*coeffs[N];
  SeriesCalc seriesCalc(N,preFactors,h_input, coeffs,rout);
  parallelFor(0, ncol_val, seriesCalc);
  return wrap(rout);
}

// [[Rcpp::export]]
NumericVector psort(NumericVector& x, NumericVector x_idx) {
  
  // std::vector<size_t> idx(x.size());
  // iota(idx.begin(), idx.end(), 0);
  
  // sort indexes based on comparing values in v
  // using std::stable_sort instead of std::sort
  // to avoid unnecessary index re-orderings
  // when v contains elements of equal values 
  
  // NumericVector sorted_idx = clone(x_idx);
  // tbb::parallel_sort(sorted_vec.begin(), sorted_vec.end());
  // return sorted_vec;
  // 
  NumericVector sorted_idx = clone(x_idx);
  tbb::parallel_sort(x_idx.begin(), x_idx.end(),
              [&x](size_t i1, size_t i2) {return x[i1] < x[i2];});
  return x_idx;
  
  
  // NumericVector sorted_vec = clone(x);
  // tbb::parallel_sort(sorted_vec.begin(), sorted_vec.end());
  // return sorted_vec;
}