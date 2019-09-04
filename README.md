# Fermi-Dirac integral using a table method in MATLAB

This script allows one to calculate Fermi-Dirac integral and its inverse in MATLAB using a table lookup method. The tables are dervied from GNU Scientific Library (GSL): https://www.gnu.org/software/gsl/doc/html/specfunc.html#fermi-dirac-function

- **Calculate FD-Integral using table lookup.** No need to balance between speed and accuracy as in iterative methods.
- **Batteries included.** Pre-made tables for common integrals are distributed with this package.
- **Entirely in MATLAB.** No need for GSL installation if using pre-made tables.
- **C-based scripts included** for generating new tables with different orders and accuracy

## Usage
All calculations are accessed through the TBFD_integral class in MATLAB.

#### First, create a class object
This object serves as the primary gateway to all calculations. In the case below, it is named `FD_order_1`. 

Two input parameters are needed: 1. integral order, and 2. absolute path to the index file. The object will load tables according to the integral orders requested. If this object is used to calculate integral of orders other than ones specified, an error will occur.

`FD_order_1 = TBFD_integral(integral_order, path_to_index_file)`

Example:

`FD_order_1 = TBFD_integral(1, '/home/programs/fd_integral/tables/index.db')`

In the example, we state our intend to do calculations associated with Fermi Dirac integrals of order 1. The index.db file location is also given as the second argument.

#### Calculate Fermi Dirac integrals 


#### Calculate Fermi Dirac integral inverses


#### Various utilities

Display the calculation plan for the given input.

`FD_order_1.explain([-0.54])`

Output:
`Analytical`

Display the integral order and other information.

`FD_order_1.info()`

## C scripts for generating new tables

## FAQs:
1. Only part of my program requires FD integral calculation. Do I have to carry this large table-based object all the way through my program?

Answer: No, it is recommended to get rid of the object if it is no longer needed. Just like how one erase any other MATLAB variables, `clear TBFD_integral_1`
