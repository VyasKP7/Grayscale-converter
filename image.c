
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "image.h"

ImagePPM *readPPM(char *filename){
	FILE *fp = fopen(filename, "r");
	int r;
	int c;
	int max;
	char Magic[3];

	if(fp == NULL)
	{
		return NULL;
	}

	fscanf(fp, "%s", Magic);
	fscanf(fp, "%d", &c);
	fscanf(fp, "%d", &r);
	fscanf(fp, "%d", &max);

	ImagePPM *pImagePPM = (ImagePPM*)malloc(sizeof(ImagePPM));
	pImagePPM->pixels = (Pixel**)malloc(sizeof(Pixel*)*(r));

	for (int x = 0; x < r; x++) {
		pImagePPM->pixels[x] = (Pixel*)malloc(sizeof(Pixel)*c);
	}

	strcpy(pImagePPM->magic, Magic);
	pImagePPM->width = c;
	pImagePPM->height = r;
	pImagePPM->max_value = max;

	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			fscanf(fp, "%d", &pImagePPM->pixels[i][j].red);
			fscanf(fp, "%d", &pImagePPM->pixels[i][j].green);
			fscanf(fp, "%d", &pImagePPM->pixels[i][j].blue);
		}
	}

	return pImagePPM;

}

int writePGM(ImagePGM *pImagePPM, char *filename){
	FILE *fp = NULL;

	fp = fopen(filename, "w");
	if(fp == NULL)
		return 0;

	fprintf(fp, "%s\n", pImagePPM->magic);
	fprintf(fp, "%d %d %d\n", pImagePPM->width, pImagePPM->height, pImagePPM->max_value);

	for(int i = 0; i < pImagePPM->height; i++) {
		for(int j = 0; j < pImagePPM->width; j++) {
			fprintf(fp, "%d ", pImagePPM->pixels[i][j]);
	}
		fprintf(fp, "\n");
	}

	return 1;



}

ImagePGM *extractRed(ImagePPM *pImagePPM){
	ImagePGM *PGM = (ImagePGM*)malloc(sizeof(ImagePGM));
	PGM->pixels = (int **)malloc(sizeof(int*)*(pImagePPM->height));
	for (int i = 0; i < pImagePPM->height; i++){
		PGM->pixels[i]=(int*)malloc(sizeof(int)*pImagePPM->width);
	}

	strcpy(PGM->magic, "P2");
	PGM->width = pImagePPM->width;
	PGM->height = pImagePPM->height;
	PGM->max_value = pImagePPM->max_value;

	for (int i = 0; i < pImagePPM->height; i++){
		for (int j=0; j < pImagePPM->width; j++){
			PGM->pixels[i][j] = pImagePPM->pixels[i][j].red;
		}
	}
	return PGM;
}

ImagePGM *extractGreen(ImagePPM *pImagePPM){
	ImagePGM *PGM = (ImagePGM*)malloc(sizeof(ImagePGM));
        PGM->pixels = (int **)malloc(sizeof(int*)*(pImagePPM->height));
        for (int i = 0; i < pImagePPM->height; i++){
                PGM->pixels[i]=(int*)malloc(sizeof(int)*pImagePPM->width);
        }

        strcpy(PGM->magic, "P2");
        PGM->width = pImagePPM->width;
        PGM->height = pImagePPM->height;
        PGM->max_value = pImagePPM->max_value;

        for (int i = 0; i < pImagePPM->height; i++){
                for (int j=0; j < pImagePPM->width; j++){
                        PGM->pixels[i][j] = pImagePPM->pixels[i][j].green;
                }
        }
        return PGM;

}


ImagePGM *extractBlue(ImagePPM *pImagePPM){
        ImagePGM *PGM = (ImagePGM*)malloc(sizeof(ImagePGM));
        PGM->pixels = (int **)malloc(sizeof(int*)*(pImagePPM->height));
        for (int i = 0; i < pImagePPM->height; i++){
                PGM->pixels[i]=(int*)malloc(sizeof(int)*pImagePPM->width);
        }

        strcpy(PGM->magic, "P2");
        PGM->width = pImagePPM->width;
        PGM->height = pImagePPM->height;
        PGM->max_value = pImagePPM->max_value;

        for (int i = 0; i < pImagePPM->height; i++){
                for (int j=0; j < pImagePPM->width; j++){
                        PGM->pixels[i][j] = pImagePPM->pixels[i][j].blue;
                }
        }
        return PGM;

}

ImagePGM *computeAverage(ImagePPM *pImagePPM){
	int average = 0;
	double avg = 0.0;
        ImagePGM *PGM = (ImagePGM*)malloc(sizeof(ImagePGM));
        PGM->pixels = (int **)malloc(sizeof(int*)*(pImagePPM->height));
        for (int i = 0; i < pImagePPM->height; i++){
                PGM->pixels[i]=(int*)malloc(sizeof(int)*pImagePPM->width);
        }

        strcpy(PGM->magic, "P2");
        PGM->width = pImagePPM->width;
        PGM->height = pImagePPM->height;
        PGM->max_value = pImagePPM->max_value;

        for (int i = 0; i < pImagePPM->height; i++){
                for (int j=0; j < pImagePPM->width; j++){
			avg = (double)(pImagePPM->pixels[i][j].red + pImagePPM->pixels[i][j].green + pImagePPM->pixels[i][j].blue) / 3.0;
			average = round(avg);
			PGM->pixels[i][j] = average;
                }

        }
        return PGM;

}


ImagePGM *computeLightness(ImagePPM *pImagePPM){

	ImagePGM *PGM = (ImagePGM*)malloc(sizeof(ImagePGM));
        PGM->pixels = (int **)malloc(sizeof(int*)*(pImagePPM->height));
        for (int i = 0; i < pImagePPM->height; i++){
                PGM->pixels[i]=(int*)malloc(sizeof(int)*pImagePPM->width);
        }

        strcpy(PGM->magic, "P2");
        PGM->width = pImagePPM->width;
        PGM->height = pImagePPM->height;
        PGM->max_value = pImagePPM->max_value;

        for (int i = 0; i < pImagePPM->height; i++){
                for (int j=0; j < pImagePPM->width; j++){
                        int light = 0;
			double light1 = 0;

			int max = pImagePPM->pixels[i][j].blue;

			if(max < pImagePPM->pixels[i][j].green)
				max = pImagePPM->pixels[i][j].green;
			if(max < pImagePPM->pixels[i][j].red)
				max = pImagePPM->pixels[i][j].red;

			int min = pImagePPM->pixels[i][j].blue;

			if(min> pImagePPM->pixels[i][j].green)
				min = pImagePPM->pixels[i][j].green;
			if(min> pImagePPM->pixels[i][j].red)
				min = pImagePPM->pixels[i][j].red;

			light1 = (double)(max + min)/2.00;
			light = round(light1);

			PGM->pixels[i][j] = light;
                }
        }
        return PGM;

}

ImagePGM *computeLuminosity(ImagePPM *pImagePPM)
{

        ImagePGM *PGM1=(ImagePGM*)malloc(sizeof(ImagePGM));
        PGM1->pixels=(int **)malloc(sizeof(int*)*(pImagePPM->height));
        for(int i=0;i<pImagePPM->height;i++)
        {
                PGM1->pixels[i]=(int*)malloc(sizeof(int)*pImagePPM->width);	//returns martix of average luminosity
        }

        strcpy(PGM1->magic,"P2");
        PGM1->width=pImagePPM->width;
        PGM1->height=pImagePPM->height;
        PGM1->max_value=pImagePPM->max_value;

        for(int i=0;i<pImagePPM->height;i++)
        {
                for(int j=0;j<pImagePPM->width;j++)
                {
                        int cLum=0;
                        double lumC=0;
                        lumC=(0.21*(double)pImagePPM->pixels[i][j].red)+(0.72*(double)pImagePPM->pixels[i][j].green)+(0.07*(double)pImagePPM->pixels[i][j].blue);
                        cLum=round(lumC);
                        PGM1->pixels[i][j]=cLum;
                }
        }

        return PGM1;

}

void freeSpacePPM(ImagePPM *pImagePPM){
	int rows = pImagePPM->height;

	for(int i = 0; i < rows; i++)
		free(pImagePPM->pixels[i]);

	free(pImagePPM->pixels);
	free(pImagePPM);

}

void freeSpacePGM(ImagePGM *pImagePGM){
	int rows = pImagePGM->height;

	for(int i = 0; i < rows; i++)
		free(pImagePGM->pixels[i]);

	free(pImagePGM->pixels);
	free(pImagePGM);
}
