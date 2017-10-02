/*
 * Hemoxymetrie in non-hemolyzed human whole blood
 * Copyright (C) 2016-2017 Benjamin Redmer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* Internal includes */
#include "math_helper.h"

/**
 * @brief Linear 1D interpolation
 * @param x Sample points
 * @param v Corresponding values
 * @param xq Query points
 * @return Interpolated values or nullptr if failed
 */
double *interp1(double *x, double *v, double *xq, unsigned int numel, unsigned int numinterp)
{
    double *vq = new double[numinterp];

    if (nullptr == vq)
    {
        return nullptr;
    }

    unsigned int i = 0, j = 0;

    for (i = 0; i < numinterp; i++)
    {
        for (j = 0; j < numel; j++)
        {
            if ((x[j] < xq[i]) && (x[j+1] > xq[i]))
                break;
        }

        if (j >= sizeof(x))
            vq[i] = 0.0;

        double x_diff = x[j+1] - x[j];
        double v_diff = v[j+1] - v[j];

        vq[i] = v[j] + ((v_diff / x_diff) * (xq[i] - x[j]));
    }
    return vq;
}

/**
 * @brief Get minimum of array
 * @param x Array
 * @param numValues Array length
 * @return Minimum of array
 */
double getMinimum(double *x, unsigned int numValues)
{
    double minimum = x[0];

    unsigned int i = 0;

    /* Loop through values */
    for (i = 1; i < numValues; i++)
    {
        /* New maximum found? */
        if (x[i] < minimum)
        {
            minimum = x[i];
        }
    }
    return minimum;
}

/**
 * @brief Get mean of array
 * @param x Array
 * @param numValues Array length
 * @return Mean of array
 */
double getMean(double *x, unsigned int numValues)
{
    double mean = x[0];

    unsigned int i = 0;

    /* Loop through values */
    for (i = 0; i < numValues; i++)
    {
        mean += x[i];
    }
    return (mean / numValues);
}

/**
 * @brief Get maximum of array
 * @param x Array
 * @param numValues Array length
 * @return Maximum of array
 */
double getMaximum(double *x, unsigned int numValues)
{
    double maximum = x[0];

    unsigned int i = 0;

    /* Loop through values */
    for (i = 1; i < numValues; i++)
    {
        /* New maximum found? */
        if (x[i] > maximum)
        {
            maximum = x[i];
        }
    }
    return maximum;
}
