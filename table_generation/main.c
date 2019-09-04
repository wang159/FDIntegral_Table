// Database file generator for FD integral tool on iPhone
#include <stdio.h>
#include "writeToFile.h"
#include <gsl/gsl_sf_fermi_dirac.h>
#include <gsl/gsl_sf_exp.h>
#include <math.h>
main()
{
	// Ultility parameters allocations
	double result;
	double min_result;
	double max_result;

	double min;
	double max;
	double thisNumber;
	double diffNumber;
	double diffPerc;

	// Output directory
	char output_dir[] = "/home/wang159/Programs/FDIntegral_Table/table";

	// CONTROLS
	double perc = 1e-6; // Percision of the table range. Percision = (table_result - analytical_result) / table_result
	                    // The range of the table is guaranteed to cover cases that, for ones outside the table, analytical results are within the specified
	                    // percision
	                     
	int maxEntryPerFile = 500000000; // maximum number of entries per file. If desired to have smaller, but multiple data files, adjust this parameter
	
	double mhalf_incre = 0.001;
	double half_incre = 0.001;
	double one_incre = 0.005;
	double threeHalf_incre = 0.005;
	double two_incre = 0.005;

	// Looking for the boundary where analytical function and numerical function intercept

	// ---------------------------
	// Order = -1
		// Analytical formula avaliable
		// F = e^x/(1+e^x);

	// --------------------------
	// Order = -1/2
	min = -20.0;
	max = 210.0;

	printf("Order -1/2 -------------------\n");
	for (thisNumber = min; thisNumber < 0; thisNumber = thisNumber + 0.0001) {
		result = gsl_sf_fermi_dirac_mhalf(thisNumber);		
		min_result = gsl_sf_exp(thisNumber);
		
		diffNumber = result - min_result;
		diffPerc = fabs(diffNumber/result);

		if (diffPerc > perc) {
			printf("Order -1/2, min = %f, btd = %f\n", min, thisNumber);
			printf("            GSL = %.12f, ANA = %.12f\n", result, min_result);
			printf("            diff = %.12f\n", diffPerc);
			break;
		}
	}

	for (thisNumber = max; thisNumber > 0; thisNumber = thisNumber - 0.0001) {
		result = gsl_sf_fermi_dirac_mhalf(thisNumber);		
		min_result = (2.0*sqrt(thisNumber))/sqrt(3.14159265);
		
		diffNumber = result - min_result;
		diffPerc = fabs(diffNumber/result);

		if (diffPerc > perc) {
			printf("Order -1/2, max = %f, btd = %f\n", max, thisNumber);
			printf("            GSL = %.12f, ANA = %.12f\n", result, min_result);
			printf("            diff = %.12f\n", diffPerc);
			break;
		}
	}

	writeToFile(-0.5, min, max, mhalf_incre, maxEntryPerFile, output_dir);	

	// --------------------------
	// Order = 0
		// Analytical formula avaliable
		// F = ln(1+e^x);

	// --------------------------
	// Order = 1/2
	min = -20.0;
	max = 400.0;

	printf("Order 1/2 -------------------\n");
	for (thisNumber = min; thisNumber < 0; thisNumber = thisNumber + 0.0001) {
		result = gsl_sf_fermi_dirac_half(thisNumber);		
		min_result = gsl_sf_exp(thisNumber);
		
		diffNumber = result - min_result;
		diffPerc = fabs(diffNumber/result);

		if (diffPerc > perc) {
			printf("Order 1/2, min = %f, btd = %f\n", min, thisNumber);
			printf("            GSL = %.12f, ANA = %.12f\n", result, min_result);
			printf("            diff = %.12f\n", diffPerc);
			break;
		}
	}

	for (thisNumber = max; thisNumber > 0; thisNumber = thisNumber - 0.0001) {
		result = gsl_sf_fermi_dirac_half(thisNumber);		
		min_result = (4.0*pow(thisNumber,(3.0/2.0)))/(3.0*sqrt(3.14159265));

		diffNumber = result - min_result;
		diffPerc = fabs(diffNumber/result);
		if (diffPerc > perc) {
			printf("Order 1/2, max = %f, btd = %f\n", max, thisNumber);
			printf("            GSL = %.12f, ANA = %.12f\n", result, min_result);
			printf("            diff = %.12f\n", diffPerc);
			break;
		}
	}
	writeToFile(0.5, min, max, half_incre, maxEntryPerFile, output_dir);	

	// --------------------------
	// Order = 1
	min = -20.0;
	max = 700.0;

	printf("Order 1 -------------------\n");
	for (thisNumber = min; thisNumber < 0; thisNumber = thisNumber + 0.0001) {
		result = gsl_sf_fermi_dirac_1(thisNumber);		
		min_result = gsl_sf_exp(thisNumber);
		
		diffNumber = result - min_result;
		diffPerc = fabs(diffNumber/result);

		if (diffPerc > perc) {
			printf("Order 1, min = %f, btd = %f\n", min, thisNumber);
			printf("            GSL = %.12f, ANA = %.12f\n", result, min_result);
			printf("            diff = %.12f\n", diffPerc);
			break;
		}
	}

	for (thisNumber = max; thisNumber > 0; thisNumber = thisNumber - 0.0001) {
		result = gsl_sf_fermi_dirac_1(thisNumber);		
		min_result = (0.5*pow(thisNumber,2.0));
		
		diffNumber = result - min_result;
		diffPerc = fabs(diffNumber/result);

		if (diffPerc > perc) {
			printf("Order 1, max = %f, btd = %f\n", max, thisNumber);
			printf("            GSL = %.12f, ANA = %.12f\n", result, min_result);
			printf("            diff = %.12f\n", diffPerc);
			break;
		}
	}
	writeToFile(1, min, max, one_incre, maxEntryPerFile, output_dir);	

	// --------------------------
	// Order = 3/2
	min = -20.0;
	max = 800.0;

	printf("Order 3/2 -------------------\n");
	for (thisNumber = min; thisNumber < 0; thisNumber = thisNumber + 0.0001) {
		result = gsl_sf_fermi_dirac_3half(thisNumber);		
		min_result = gsl_sf_exp(thisNumber);
		
		diffNumber = result - min_result;
		diffPerc = fabs(diffNumber/result);

		if (diffPerc > perc) {
			printf("Order 3/2, min = %f, btd = %f\n", min, thisNumber);
			printf("            GSL = %.12f, ANA = %.12f\n", result, min_result);
			printf("            diff = %.12f\n", diffPerc);
			break;
		}
	}

	for (thisNumber = max; thisNumber > 0; thisNumber = thisNumber - 0.0001) {
		result = gsl_sf_fermi_dirac_3half(thisNumber);		
		min_result = (8.0*pow(thisNumber,(5.0/2.0)))/(15.0*sqrt(3.14159265));
		
		diffNumber = result - min_result;
		diffPerc = fabs(diffNumber/result);

		if (diffPerc > perc) {
			printf("Order 3/2, max = %f, btd = %f\n", max, thisNumber);
			printf("            GSL = %.12f, ANA = %.12f\n", result, min_result);
			printf("            diff = %.12f\n", diffPerc);
			break;
		}
	}
	writeToFile(1.5, min, max, threeHalf_incre, maxEntryPerFile, output_dir);	

	// --------------------------
	// Order = 2
	min = -20.0;
	max = 1000.0;

	printf("Order 2 -------------------\n");
	for (thisNumber = min; thisNumber < 0; thisNumber = thisNumber + 0.0001) {
		result = gsl_sf_fermi_dirac_2(thisNumber);		
		min_result = gsl_sf_exp(thisNumber);
		
		diffNumber = result - min_result;
		diffPerc = fabs(diffNumber/result);

		if (diffPerc > perc) {
			printf("Order 2, min = %f, btd = %f\n", min, thisNumber);
			printf("            GSL = %.12f, ANA = %.12f\n", result, min_result);
			printf("            diff = %.12f\n", diffPerc);
			break;
		}
	}

	for (thisNumber = max; thisNumber > 0; thisNumber = thisNumber - 0.0001) {
		result = gsl_sf_fermi_dirac_2(thisNumber);		
		min_result = pow(thisNumber,3.0)/6.0;
		
		diffNumber = result - min_result;
		diffPerc = fabs(diffNumber/result);

		if (diffPerc > perc) {
			printf("Order 2, max = %f, btd = %f\n", max, thisNumber);
			printf("            GSL = %.12f, ANA = %.12f\n", result, min_result);
			printf("            diff = %.12f\n", diffPerc);
			break;
		}
	}
	writeToFile(2, min, max, two_incre, maxEntryPerFile, output_dir);	
}
