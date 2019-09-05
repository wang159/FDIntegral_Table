# Fermi-Dirac integral using a table method in MATLAB

This script allows one to calculate Fermi-Dirac integral and its inverse in MATLAB using a table lookup method. The tables are dervied from GNU Scientific Library (GSL): https://www.gnu.org/software/gsl/doc/html/specfunc.html#fermi-dirac-function. This is a script in support of the Notes on Fermi-Dirac Integrals: https://arxiv.org/abs/0811.0116

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
y = FD_order_1.get_reverse(x)
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
The integral and its inverse are calculated using the same set of tables. The benchmark below shows the values for FD integral of orders supported in default. The lines are forward calculations of Fermi Dirac integrals, and the circles are results obtained in reverse.

![Benchmark](/test/benchmark.png)

It is highly recommended to pass input in a single batch list, instead of calling "get" and "get_inverse" individually on each number. Plot below shows the calculation time vs. batch size for order 1/2.

![Time vs. batch size](/test/time_vs_batch_size.png)

The plot below shows the calculation time vs. number of function calls for order 1/2. This illustrates the amount of slow down if the data has no choice but to be passed individually.

![Time vs. function calls](/test/time_vs_function_calls.png)


## FAQs:
1. Only part of my program requires FD integral calculation. Do I have to carry this large table-based object all the way through my program?

Answer: No, it is recommended to get rid of the object if it is no longer needed. Just like how one erase any other MATLAB variables, `clear FD_order_1`

2. How does the program handle a list mixed with numbers that shall be handled by table-based and analytical methods?

Answer: The program sorts the input and records the sorted index. The input is then segmented into three blocks: ones above, below, and within the table range. Each block is then solved analytically or using the table. The results are then merged into a single list, and the list is subsequently returned to original, pre-sorted order.

## Contacts:
For any question, please contact Xufeng Wang (wang159@purdue.edu) and Prof. Mark Lundstrom (lundstro@purdue.edu)
