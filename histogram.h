/***********************************
 * Simple histogramming library in C
 * Programmer: Selezenev A.D.
 * March 2024
 **********************************/

#ifndef __HISTOGRAM_H__
#define __HISTOGRAM_H__

#include <stddef.h>

/**
 * One dim histogram type
 */
typedef struct Histogram1D_s {
    size_t nbins;
    float* edges;
    int*   sumw;
    int*   sumw2;
} Histogram1D;

/**
 * Func parameters for Histogram1D__apply
 */
typedef struct FuncParams_s {
    size_t n;
    float* params;
} FuncParams;

/**
 * Function with FuncParams type
 */
typedef float (*Func)(float, FuncParams);

/**
 * Enum for histogram consistency check
 */
typedef enum HistogramConsistency_e {
    HISTOGRAM_DIFF_NBINS,
    HISTOGRAM_DIFF_BINS,
    HISTOGRAM_CONSISTENT
} HistogramConsistency;

/**
 *  Initialize histogram with number of bins and range
 */
int Histogram1D__init(Histogram1D* h, size_t nbins, float xlow, float xhigh);

/**
 * Destroy/deinitialize histogram
 */
void Histogram1D__destroy(Histogram1D* h);

/** 
 * Find histogram bin for parameter \ref x
 */
size_t Histogram1D__find_bin(Histogram1D* h, float x);

/**
 * Fill histogram with x
 */
void Histogram1D__fill(Histogram1D* h, float x);

/**
 * Apply function of type \ref Func to histogram 
 * with parameters \ref of type FuncParams
 */
void Histogram1D__apply(Histogram1D* h, Func f, FuncParams pars);

/**
 * Scale histogram by a scalar
 */
void Histogram1D__scale(Histogram1D* h, float scale);

/**
 * Get integral of histogram in specified range
 */
size_t Histogram1D__integral(Histogram1D* h, size_t low_bin, size_t high_bin);

/**
 * Check consistency of two histograms
 */
HistogramConsistency Histogram1D__check_consistency(Histogram1D* h1, Histogram1D* h2) ;

/**
 * Add another histogram to this
 */
void Histogram1D__add(Histogram1D* h1, Histogram1D* h2, float scale);

/**
 * Copy to histogram
 */
void Histogram1D__copy(Histogram1D* to, Histogram1D* from);

/**
 * Print histogram
 */
void Histogram1D__print(Histogram1D* h);


#endif //__HISTOGRAM_H__
