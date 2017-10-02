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

#ifndef IAD_CALIBRATE_H
#define IAD_CALIBRATE_H

/*
 * Status bits
 */
#define PROCESS_READY    0x01
#define PROCESS_RUNNING  0x02
#define PROCESS_DONE     0x04
#define PROCESS_CLOSED   0x08
#define PROCESS_SUCCESS  0x10
#define PROCESS_FAILURE  0x20

/*
 * Thresholds for counts
 */
#define THRESHOLD_COUNTS_LOW  54000     /* Best around 80-90% */
#define THRESHOLD_COUNTS_HIGH 62000
#define THRESHOLD_COUNTS_DARK 4000      /* Don't tolerate more than 4000 dark counts */

/*
 * Calibration limits
 */
#define CALIBRATION_MAX_TIME_PER_SPECTRUM 2000
#define CALIBRATION_COUNTS_TARGET         58000

/*
 * Calibration start values
 */
#define CALIBRATION_RD_START_INTEGRATION_TIME 100.0f
#define CALIBRATION_RD_START_NUM_AVERAGES     10
#define CALIBRATION_TD_START_INTEGRATION_TIME 10.0f
#define CALIBRATION_TD_START_NUM_AVERAGES     100
#define CALIBRATION_TU_START_INTEGRATION_TIME 1.05f     /* Don't change this for maximum SNR */
#define CALIBRATION_TU_START_NUM_AVERAGES     10

/**
 * @brief The 'CalibrateIAD' class
 */
class CalibrateIAD
{
public:
    /* Constructor */
    explicit CalibrateIAD(double *Rd_factor = nullptr,
                          double *Td_factor = nullptr,
                          double *Tu_factor = nullptr);

    /* Did the user run the assistant? */
    bool getIsCalibrated(void);

    /* Destructor */
    ~CalibrateIAD(void);

private:
    /* User calibrated IAD */
    bool isCalibrated = false;
};

#endif // IAD_CALIBRATE_H
