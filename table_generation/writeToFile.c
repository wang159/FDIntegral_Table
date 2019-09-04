// Database file generator for FD integral tool on iPhone
#include <stdio.h>
#include "writeToFile.h"
#include <gsl/gsl_sf_fermi_dirac.h>
#include <gsl/gsl_sf_exp.h>
#include <math.h>
#include <string.h>

int writeToFile(double order, double min, double max, double incre, int maxEntryPerFile, char *dirName)
{
	// Write to file
	int totalIndex = 1;
	int fileIndex = 1;

	double thisNumber = min;
	double min_y = 0;
	double max_y = 0;
	double result = 0;

	FILE *fid;
	FILE *file;

	// assign some tokens
	char fileName[25] = "t";
	char dName[250] = "t";
	
	sprintf(dName, "%s/index.db", dirName);
	file = fopen(dName, "a+");
	
	if (order == -0.5) {
		strcat(fileName, "_mhalf");
	} else if (order == 0.5) {
		strcat(fileName, "_half");
	} else if (order == 1) {
		strcat(fileName, "_1");
	} else if (order == 1.5) {
		strcat(fileName, "_3half");
	} else if (order == 2) {
		strcat(fileName, "_2");
	}

	while (thisNumber <= max) {
		// calculate the Fermi-Dirac integral
		if (order == -0.5) {
			result = gsl_sf_fermi_dirac_mhalf(thisNumber);
		} else if (order == 0.5) {
			result = gsl_sf_fermi_dirac_half(thisNumber);
		} else if (order == 1) {
			result = gsl_sf_fermi_dirac_1(thisNumber);
		} else if (order == 1.5) {
			result = gsl_sf_fermi_dirac_3half(thisNumber);
		} else if (order == 2) {
			result = gsl_sf_fermi_dirac_2(thisNumber);
		}

		// see if database grandcentral need to be updated
		if (totalIndex == maxEntryPerFile || thisNumber == max) {
			// write to the index file
			max_y = result;

			fprintf(file,"%0.1f %.8f %.8f %.8e %.8e %.8f %s \n", order, min, thisNumber, min_y, max_y, incre, dName);
			printf("%0.1f %.8f %.8f %.8e %.8e %.8f %s \n", order, min, thisNumber, min_y, max_y, incre, dName);

			// close the previous database file
			fprintf(fid,"%e ", result);
			fclose(fid);
		
			// update parameters
			min = thisNumber + incre;
			totalIndex = 0;
			fileIndex = fileIndex + 1;

		} else if (totalIndex == 1) {
			min_y = result;

			// open a new datafile
			sprintf(dName, "%s/%s_%d.db",dirName, fileName,fileIndex);
			fid = fopen(dName,"w");
			fprintf(fid,"%e ", result);
		} else {
			fprintf(fid,"%e ", result);
		}	

		thisNumber = thisNumber + incre;
		totalIndex = totalIndex + 1;

                
		if (thisNumber > max) {
			// write to the index file
			fprintf(file,"%0.1f %.8f %.8f %.8e %.8e %.8f %s \n", order, min, thisNumber, min_y, max_y, incre, dName);
			printf("%0.1f %.8f %.8f %.8e %.8e %.8f %s \n", order, min, thisNumber, min_y, max_y, incre, dName);
    }
	}

	// close the grandcentral file
	fclose(file);
}
