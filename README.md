# Real-Time PID Motor Simulator (Embedded)

A real-time PID control system implemented on a microcontroller that simulates a second-order motor and visualizes system behavior using LEDs. The system supports live tuning of control gains via potentiometers and demonstrates how timing affects control stability in embedded environments.

---

## Overview

This project implements a discrete-time control loop running on embedded hardware. A virtual motor model is updated in real time using measured loop timing (Δt), while a PD controller computes control effort based on error and rate of change.

The system is fully interactive:

* A potentiometer sets the **target position**
* Two potentiometers adjust **kP** and **kD** in real time
* LEDs visualize system error and convergence behavior

## Demo

[![Watch Demo](https://img.youtube.com/vi/3ZNK2iobQUw/0.jpg)](https://youtube.com/shorts/3ZNK2iobQUw?feature=share)
---

## Key Features

* **Real-Time Control Loop**

  * Uses measured Δt (`millis()`) instead of fixed timing
  * Handles variable loop execution safely

* **Second-Order Motor Simulation**

  * Models position, velocity, and acceleration
  * Includes damping to simulate friction

* **PD Controller with Filtering**

  * Proportional + Derivative control
  * Exponential Moving Average (EMA) applied to derivative term to reduce noise

* **Live Gain Tuning**

  * kP and kD adjusted via hardware potentiometers
  * Immediate visual feedback from system response

* **Error Visualization**

  * 5-LED system indicates magnitude and direction of error
  * Provides intuitive view of system stability and convergence

* **Non-Ideal System Behavior**

  * Output saturation (±1.0)
  * Minimum power threshold (simulated stiction)
  * Δt clamping to prevent instability from timing spikes

---

## System Architecture

Control loop flow:

1. Read inputs (target, kP, kD from potentiometers)
2. Measure elapsed time (Δt)
3. Compute error:
   `error = target - position`
4. Compute derivative:
   `d(error)/dt` with smoothing
5. Compute control output:
   `power = kP * error + kD * derivative`
6. Apply constraints (clamping + deadband)
7. Update motor model using real-time Δt
8. Update LEDs based on error

---

## Hardware Setup

* Microcontroller (Arduino-compatible)
* 3 potentiometers:

  * Target position
  * kP tuning
  * kD tuning
* 5 LEDs:

  * Left Red (large negative error)
  * Left Yellow
  * Center Blue (near target)
  * Right Yellow
  * Right Red (large positive error)

---

## What This Demonstrates

* THis demostrates the use of kP and kD varibale in the PID equation, allow the user to set the kP to any value , while allow the kD to stay at 0 , allow the user to visually see the osicaltion of the virtual motor, and when slowlu adding kD to the equation allows the user to see the the system begins to settle down, and eventully reachs crital dampness.

---

## Example Observations

* Increasing kP:

  * Faster response
  * Increased overshoot and oscillation

* Increasing kD:

  * Reduced overshoot
  * Smoother convergence

* Removing timing control:

  * Unstable or inconsistent behavior

---

## Future Work

* Add Integral term (kI) with anti-windup
* Replace virtual motor with real DC motor + encoder
* Implement fixed-frequency control loop option
* Add serial telemetry or data logging
* Tune system under real-world disturbances

---

## Project Purpose

This project was built to bridge the gap between:

* theoretical control systems
* real-time embedded implementation

It focuses on understanding system behavior, not just implementing equations.

---

## Status

* Fully functional real-time PD control system

[ ]Awaiting hardware integration (motor + encoder)

---
