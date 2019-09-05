# Fermi-Dirac integral using a table method in MATLAB

This script allows one to calculate Fermi-Dirac integral and its inverse in MATLAB using a table lookup method. The tables are dervied from GNU Scientific Library (GSL): https://www.gnu.org/software/gsl/doc/html/specfunc.html#fermi-dirac-function

- **Calculate FD-Integral using table lookup.** No need to balance between speed and accuracy as in iterative methods.
- **Batteries included.** Pre-made tables for common integrals are distributed with this package.
- **Automatic switch between table and analytical formulas.** A single large list of numbers can be passed on to the function, and the function will decide which ones within the list shall be calculated using table-based method. The rest will be calculated using analytical formulas.  
- **Entirely in MATLAB.** No need for GSL installation if using pre-made tables.
- **C-based scripts included** for generating new tables with different orders and accuracy.

## Usage
All calculations are accessed through the TBFD_integral class in MATLAB.

### First, create a class object
This object serves as the primary gateway to all calculations. In the case below, it is named `FD_order_1`. 

Two input parameters are needed: 1. integral order, and 2. absolute path to the index file. The object will load tables according to the integral orders requested. If this object is used to calculate integral of orders other than ones specified, an error will occur.

`FD_order_1 = TBFD_integral(integral_order, path_to_index_file)`

Example:

`FD_order_1 = TBFD_integral(1, '/home/programs/fd_integral/tables/index.db')`

In the example, we state our intend to do calculations associated with Fermi Dirac integrals of order 1. The index.db file location is also given as the second argument.

### Calculate Fermi Dirac integrals 
```
x=[0, 0.1, 0.2];
y = FD_order_1.get(x)
```
output
```
ans =
    0.7651    0.8275    0.8938
```

### Calculate Fermi Dirac integral inverses
```
x=[0.7651, 0.8275, 0.8938];
y = FD_order_1.get(x)
```
output
```
ans =
   -0.0000    0.1000    0.1999
```

### C scripts for generating new tables
All c scripts needed for making new Fermi Dirac intergral tables are included in folder 'table_generation'. GNU Scientific Liabray is needed to compile and run the program.

main.c: main program calculating intergrals of various orders
writeToFile.c: program used to write data into tables
writeToFile.h: Header for writeToFile.c
compile.run: shell script for compiling the program. Edit the file to setup correct paths to GSL

### Benchmark and speed tests
![GitHub Logo](/images/logo.png)
![GitHub Logo](/images/logo.png)
![GitHub Logo](/images/logo.png)


## FAQs:
1. Only part of my program requires FD integral calculation. Do I have to carry this large table-based object all the way through my program?

Answer: No, it is recommended to get rid of the object if it is no longer needed. Just like how one erase any other MATLAB variables, `clear TBFD_integral_1`
