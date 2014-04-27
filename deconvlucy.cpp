// deconvlucy.cpp : Defines the entry point for the console application.
//
// ===================================================================================================================================
// ========================================================Lucy-Richardson algorithm ===================================
//
// Author: Tinniam V Ganesh
// Developed 14 May 2012
// File: deconvlucy.cpp
//=====================================================================================================================================
#include "stdafx.h"
#include "math.h"
#include <cxcore.h>
#include <cv.h>
#include <highgui.h>

#define kappa 10000
int main(int argc, char ** argv)
{
IplImage* im;
IplImage* im_conv_kernel;
IplImage* im_correction;
IplImage* im_new;
IplImage* im_new_est;
IplImage* im1;

char str[80];
int i;
CvMat* cvShowDFT1(IplImage*, int, int,char*);
IplImage* cvShowInvDFT1(IplImage*, CvMat*, int, int,char*);

im1 = cvLoadImage("kutty-1.jpg");
cvNamedWindow("Original-Color", 0);
cvShowImage("Original-Color", im1);
im = cvLoadImage("kutty-1.jpg", CV_LOAD_IMAGE_GRAYSCALE );
if( !im )
return -1;

cvNamedWindow("Original-Gray", 0);
cvShowImage("Original-Gray", im);

// fk+1(x,y) = fk(x,y)

for(i=0;i < 10;i++) {

// Convolve f0(x,y)= g(x,y) with blur kernel
// f0(x,y) ** kernel

// Create a blur kernel
//double a[9]={-1,200,1,-1,200,1,-1,200,1};
//double a[9]={0,-1,0,-1,4,-1,0,-1,0};
//double a[9]={-4,40,4,-4,40,4,-4,40,4};
//double a[9]={-1,2,-1,-1,2,-1,-1,2,-1};
double a[9] = {0,40,0,0,40,0,0,40,0};
CvMat kernel1 = cvMat(3,3,CV_32FC1,a);

// Convolve the kernel with the blurred image as the seed i0(x,y) ** k(x,y)
im_conv_kernel= cvCloneImage(im);
cvFilter2D(im,im_conv_kernel,&kernel1,cvPoint(-1,-1));

cvNamedWindow("conv", 0);
cvShowImage("conv", im_conv_kernel);

// Subtract from blurred image. Error correction = b(x,y) - ik(x,y) ** k(x.y)
im_correction = cvCreateImage(cvSize(383,357),8,1);;
cvSub(im,im_conv_kernel,im_correction, 0);
cvNamedWindow("Sub", 0);
cvShowImage("Sub", im_correction);

// Add ik(x,y) with imCorrection - ik(x,y) + b(x,y) - ik(x,y) ** k(x,y)
im_new_est = cvCreateImage(cvSize(383,357),8,1);;
cvAdd(im,im_correction,im_new_est,NULL);

cvNamedWindow("Add", 0);
cvShowImage("Add", im_new_est);
sprintf(str,"Iteration - %d",i);
cvNamedWindow(str, 0);
cvShowImage(str, im_new_est);

//Set the estimate as the previous estimate and repeat
im = im_new_est;
im = cvCloneImage(im_new_est);
}
cvWaitKey(-1);
return 0;
}
