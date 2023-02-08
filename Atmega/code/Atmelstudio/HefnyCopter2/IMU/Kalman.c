/*
 * Kalman.c
 *
 * Created: 14-Sep-12 4:33:21 AM
 *  Author: M.Hefny
 */ 
//
//#include <avr/io.h>
//#include <util/delay.h>
//#include <util/atomic.h>
//
//
//#include "../Include/typedefs.h"
//#include "../Include/GlobalValues.h"
//#include "../Include/Kalman.h"
//
// --- Kalman filter module  ----------------------------------------------------------------------------
/*
double Q_angle[2]	=  {0.001,0.001}; //0.001
double Q_gyro[2]		=  {0.003,0.003};  //0.003
double R_angle[2]	=  {0.03,0.03};  //0.03

double x_angle[2]	= {0,0};
double x_bias[2]		= {0,0};
double P_00[2] = {0,0}, P_01[2] = {0,0}, P_10[2] = {0,0}, P_11[2] = {0,0};
double dtKalman[2], yKalman[2], SKalman[2];
double K_0[2], K_1[2];
*/


 /*
 * URL: http://www.x-firm.com/?page_id=191
 */
 /*
  int16_t Kalman_Calculate(int8_t index, int16_t newAngle, int16_t newRate,uint16_t looptime) {
    dtKalman [index]= (double)((looptime)/10000); //time in 100us
    x_angle[index] += dtKalman[index] * (newRate - x_bias[index]);
    P_00[index] +=  - dtKalman[index] * (P_10[index] + P_01[index]) + Q_angle[index] * dtKalman[index];
    P_01[index] +=  - dtKalman[index] * P_11[index];
    P_10[index] +=  - dtKalman[index] * P_11[index];
    P_11[index] +=  (Q_gyro[index] * dtKalman[index]);

    yKalman[index] = newAngle - x_angle[index];
    SKalman[index] = P_00[index] + R_angle[index];
    K_0[index] = P_00[index] / SKalman[index];
    K_1[index] = P_10[index] / SKalman[index];

    x_angle[index] +=  K_0[index] * yKalman[index];
    x_bias[index]  +=  K_1[index] * yKalman[index];
    P_00[index] -= K_0[index] * P_00[index];
    P_01[index] -= K_0[index] * P_01[index];
    P_10[index] -= K_1[index] * P_00[index];
    P_11[index] -= K_1[index] * P_01[index];

    return (uint16_t) (x_angle[index]);
  }
  */