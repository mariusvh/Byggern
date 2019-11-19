/**
 * @file pid.h
 * @author Magnus Haukeland, Wai-Yen Chan and Marius von Hafenbrädl 
 * @brief Driver for PID control.
 */

#ifndef PID_H
#define PID_H

#include <avr/io.h>
#define F_CPU 16000000UL //Clock speed

 
#define PID_frequence 100 // 100 Hz in frequency with 625 ticks
#define MAX_I_TERM 100
#define MAX_SPEED 70 


typedef struct PID_parameters_t PID_parameters_t;


/**
 * @brief A structure to represent the properties of the PID controller.
 * 
 */
struct PID_parameters_t
{
    double K_p; /**< The proportional gain of the PID controller. */
    double K_i; /**< The integral factor of the PID controller. */
    double K_d; /**< The dampning factor of the PID controller. */
    signed char reference; /**< The desired reference. */
    signed char error; /**< The error from the reference. */
    signed char prev_error; /**< The error from the previous iteration. */
};


/**
 * @brief Initializes the PID controller. 
 */
void PID_init();


/**
 * @brief Sets the parameters of the PID controller.
 * 
 * @param *pid Pointer to the PID regulator object.
 *
 * @param K_p The value the proprtional gain is set to.
 *
 * @param K_i The value the integral factor is set to.
 *
 * @param K_d The value the dampning factor is set to.
 */
void PID_set_parameters(PID_parameters_t *pid, double K_p, double K_i, double K_d);


/**
 * @brief Updates the desired reference.
 * 
 * @param ref The value the reference is set to.
 */
void PID_update_reference(signed char ref);


/**
 * @brief Runs one iteration of the PID controller. 
 */
void PID_regulator();

//void PID_regulator(PID_parameters_t *pid);

#endif
