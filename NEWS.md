# hermiter v2.2.0

## Breaking changes

* The interface of `hermiter` has been simplified. The `update_batch` method 
has been removed in favor of providing the ability to initialize the 
`hermite_estimator` with an initial batch of observations. Several internal 
methods are no longer exported in the interests of simplicity.
* The default value of N for univariate estimators has been changed from N = 30
to N = 50.

## Major enhancements

* Parallel implementation of batch updating using RcppParallel provides 
significant performance improvements on multicore systems.

## Minor improvements and bug fixes

* Updated citation information.
* Additional test cases have been added.
* Bug fixes for series acceleration algorithm.

# hermiter v2.1.0

## New features

* A method has been added for estimating the Kendall rank correlation 
coefficient in the bivariate setting.
* The univariate quantile estimation method has been significantly enhanced in
accuracy using series acceleration techniques. Series acceleration is enabled
by default.
* The univariate pdf and cdf methods have been significantly enhanced in
accuracy using series acceleration techniques. Series acceleration is enabled
by default.
* The new default method for the univariate quantile estimation method, 
'interpolate' is much faster than the alternate method, 'bisection' with nearly
the same accuracy.
* Added print and summary methods for both the univariate and bivariate 
hermite_estimator objects.
* Convenience function added to calculate sums of Hermite functions.

## Documentation improvements

* The vignette `hermiter`, namely `vignette("hermiter")` has been extended to 
included examples pertaining to estimation of the Kendall Tau nonparametric
correlation coefficient in the bivariate setting.

# hermiter v2.0.3

## Minor improvements and bug fixes

* Minor update to test cases.

# hermiter v2.0.2

## Breaking changes

* `get_coefficients` has been removed as it is redundant.
* `combine_hermite` has been renamed to `merge_hermite` for clarity.
* `combine_pair` has been renamed to `merge_pair` for clarity.
* `hermite_integral_val_quantile_adap` has been renamed to 
`hermite_integral_val_upper` for clarity.

## New features

* Bivariate Hermite estimators have been added with methods for estimating 
bivariate probability density functions and cumulative distribution functions 
along with Spearman's rank correlation coefficients.
* The bivariate estimators include methods to batch update or sequentially 
update.
* Methods are also provided to consistently merge bivariate hermite_estimators.
* Convenience methods have been added for calculating normalized Hermite 
functions, along with upper, lower and full domain integrals of the 
normalized Hermite functions. 

## Documentation improvements

* The vignette `hermiter`, namely `vignette("hermiter")` has been extended to 
included examples pertaining to the bivariate Hermite series based estimators.

## Minor improvements and bug fixes
  
* The method for merging univariate Hermite series based estimators has been
improved, yielding greater accuracy when the hermite_estimators are 
standardized.
* The method for estimating quantiles with the univariate Hermite series based
estimator has been improved and is now consistent with the estimator in the
literature.
* Vectorized the univariate quantile estimation method.
* Added further error trapping and other minor enhancements (also for C++
routines).

# hermiter v1.0.0

## INITIAL RELEASE