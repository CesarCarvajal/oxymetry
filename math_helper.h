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

#ifndef MATH_HELPER_H
#define MATH_HELPER_H

/* Linear 1D interpolation */
double *interp1(double *x, double *v, double *xq, unsigned int numel, unsigned int numinterp);

/* Get minimum/mean/maximum of array */
double getMinimum(double *x, unsigned int numValues);
double getMean(double *x, unsigned int numValues);
double getMaximum(double *x, unsigned int numValues);

#endif // MATH_HELPER_H
