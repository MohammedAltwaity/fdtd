# Electromagnetic FDTD Simulation Engine

![C Language](https://img.shields.io/badge/Language-C-blue.svg)
![Python](https://img.shields.io/badge/Visualization-Python_3.x-green.svg)
![Status](https://img.shields.io/badge/Status-In_Active_Development-orange.svg)
![License](https://img.shields.io/badge/License-MIT-brightgreen.svg)

A high-performance computational electromagnetics framework developed in C based on Schneider’s FDTD architecture, 

This repository currently implements the **2D $\text{TM}_z$ core simulation module**, serving as the foundation for an expanding electromagnetic solver built to analyze plane wave scattering, boundary conditions, and complex target geometries.

---

## Current Simulation Preview

![FDTD Wave Scattering Simulation](./images/fdtd_simulation.gif)

*Figure 1: Current 2D engine snapshot showing an $E_z$ electric field wave propagating through a Total-Field/Scattered-Field (TFSF) boundary box and scattering off a Perfect Electric Conductor (PEC) target.*

## References
* **Textbook Reference:** Schneider, John B. *Understanding the Finite-Difference Time-Domain Method*