// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// hermite_polynomial
NumericMatrix hermite_polynomial(int N, NumericVector x);
RcppExport SEXP _hermiter_hermite_polynomial(SEXP NSEXP, SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type N(NSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(hermite_polynomial(N, x));
    return rcpp_result_gen;
END_RCPP
}
// hermite_normalization
NumericVector hermite_normalization(int N);
RcppExport SEXP _hermiter_hermite_normalization(SEXP NSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type N(NSEXP);
    rcpp_result_gen = Rcpp::wrap(hermite_normalization(N));
    return rcpp_result_gen;
END_RCPP
}
// hermite_function
NumericMatrix hermite_function(int N, NumericVector x);
RcppExport SEXP _hermiter_hermite_function(SEXP NSEXP, SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type N(NSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(hermite_function(N, x));
    return rcpp_result_gen;
END_RCPP
}
// hermite_function_sum_serial
NumericVector hermite_function_sum_serial(int N, NumericVector x);
RcppExport SEXP _hermiter_hermite_function_sum_serial(SEXP NSEXP, SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type N(NSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(hermite_function_sum_serial(N, x));
    return rcpp_result_gen;
END_RCPP
}
// hermite_integral_val
NumericMatrix hermite_integral_val(int N, NumericVector x, NumericMatrix hermite_function_mat);
RcppExport SEXP _hermiter_hermite_integral_val(SEXP NSEXP, SEXP xSEXP, SEXP hermite_function_matSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type N(NSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type hermite_function_mat(hermite_function_matSEXP);
    rcpp_result_gen = Rcpp::wrap(hermite_integral_val(N, x, hermite_function_mat));
    return rcpp_result_gen;
END_RCPP
}
// hermite_integral_val_upper
NumericMatrix hermite_integral_val_upper(int N, NumericVector x, NumericMatrix hermite_function_mat);
RcppExport SEXP _hermiter_hermite_integral_val_upper(SEXP NSEXP, SEXP xSEXP, SEXP hermite_function_matSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type N(NSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    Rcpp::traits::input_parameter< NumericMatrix >::type hermite_function_mat(hermite_function_matSEXP);
    rcpp_result_gen = Rcpp::wrap(hermite_integral_val_upper(N, x, hermite_function_mat));
    return rcpp_result_gen;
END_RCPP
}
// hermite_int_full_domain
NumericMatrix hermite_int_full_domain(int N);
RcppExport SEXP _hermiter_hermite_int_full_domain(SEXP NSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type N(NSEXP);
    rcpp_result_gen = Rcpp::wrap(hermite_int_full_domain(N));
    return rcpp_result_gen;
END_RCPP
}
// standardizeInputs
NumericVector standardizeInputs(double x, double n_obs, double current_mean, double current_var);
RcppExport SEXP _hermiter_standardizeInputs(SEXP xSEXP, SEXP n_obsSEXP, SEXP current_meanSEXP, SEXP current_varSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type x(xSEXP);
    Rcpp::traits::input_parameter< double >::type n_obs(n_obsSEXP);
    Rcpp::traits::input_parameter< double >::type current_mean(current_meanSEXP);
    Rcpp::traits::input_parameter< double >::type current_var(current_varSEXP);
    rcpp_result_gen = Rcpp::wrap(standardizeInputs(x, n_obs, current_mean, current_var));
    return rcpp_result_gen;
END_RCPP
}
// standardizeInputsEW
NumericVector standardizeInputsEW(double x, double n_obs, double lambda, double current_mean, double current_var);
RcppExport SEXP _hermiter_standardizeInputsEW(SEXP xSEXP, SEXP n_obsSEXP, SEXP lambdaSEXP, SEXP current_meanSEXP, SEXP current_varSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type x(xSEXP);
    Rcpp::traits::input_parameter< double >::type n_obs(n_obsSEXP);
    Rcpp::traits::input_parameter< double >::type lambda(lambdaSEXP);
    Rcpp::traits::input_parameter< double >::type current_mean(current_meanSEXP);
    Rcpp::traits::input_parameter< double >::type current_var(current_varSEXP);
    rcpp_result_gen = Rcpp::wrap(standardizeInputsEW(x, n_obs, lambda, current_mean, current_var));
    return rcpp_result_gen;
END_RCPP
}
// hermite_function_sum_parallel
NumericVector hermite_function_sum_parallel(int N, NumericVector x);
RcppExport SEXP _hermiter_hermite_function_sum_parallel(SEXP NSEXP, SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type N(NSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(hermite_function_sum_parallel(N, x));
    return rcpp_result_gen;
END_RCPP
}
// series_calc_parallel_8_fold
NumericVector series_calc_parallel_8_fold(NumericMatrix h_input, NumericVector coeffs);
RcppExport SEXP _hermiter_series_calc_parallel_8_fold(SEXP h_inputSEXP, SEXP coeffsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericMatrix >::type h_input(h_inputSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type coeffs(coeffsSEXP);
    rcpp_result_gen = Rcpp::wrap(series_calc_parallel_8_fold(h_input, coeffs));
    return rcpp_result_gen;
END_RCPP
}
// psort
NumericVector psort(NumericVector& x, NumericVector x_idx);
RcppExport SEXP _hermiter_psort(SEXP xSEXP, SEXP x_idxSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< NumericVector& >::type x(xSEXP);
    Rcpp::traits::input_parameter< NumericVector >::type x_idx(x_idxSEXP);
    rcpp_result_gen = Rcpp::wrap(psort(x, x_idx));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_hermiter_hermite_polynomial", (DL_FUNC) &_hermiter_hermite_polynomial, 2},
    {"_hermiter_hermite_normalization", (DL_FUNC) &_hermiter_hermite_normalization, 1},
    {"_hermiter_hermite_function", (DL_FUNC) &_hermiter_hermite_function, 2},
    {"_hermiter_hermite_function_sum_serial", (DL_FUNC) &_hermiter_hermite_function_sum_serial, 2},
    {"_hermiter_hermite_integral_val", (DL_FUNC) &_hermiter_hermite_integral_val, 3},
    {"_hermiter_hermite_integral_val_upper", (DL_FUNC) &_hermiter_hermite_integral_val_upper, 3},
    {"_hermiter_hermite_int_full_domain", (DL_FUNC) &_hermiter_hermite_int_full_domain, 1},
    {"_hermiter_standardizeInputs", (DL_FUNC) &_hermiter_standardizeInputs, 4},
    {"_hermiter_standardizeInputsEW", (DL_FUNC) &_hermiter_standardizeInputsEW, 5},
    {"_hermiter_hermite_function_sum_parallel", (DL_FUNC) &_hermiter_hermite_function_sum_parallel, 2},
    {"_hermiter_series_calc_parallel_8_fold", (DL_FUNC) &_hermiter_series_calc_parallel_8_fold, 2},
    {"_hermiter_psort", (DL_FUNC) &_hermiter_psort, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_hermiter(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
