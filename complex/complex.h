#ifndef COMPLEX_H
#define COMPLEX_H

typedef struct {
	float re;
	float im;
	}complex;

void foo();
complex addCom (complex x, complex y){
	complex result;
	result.re = x.re + y.re;
	result.im = x.im + y.im;
	printf ("<%2f> <%2f>\n",result.re,result.im);
	return result;
}

complex subCom(complex x, complex y){
	complex result;
	result.re = x.re - y.re;
	result.im = x.im - y.im;
	printf ("<%2f> <%2f>\n",result.re,result.im);
	return result;
}

complex mulCom (complex x, complex y){
	complex result;
	result.re = x.re * y.re - x.im * y.im;
	result.im = x.re + y.im + x.im * y.re;
	printf ("<%2f> <%2f>\n",result.re,result.im);
	return result;
}

complex divCom (complex x, complex y){
	if (y.re == 0 && y.im == 0){
		return;
//		return EXIT_FAILURE;
		}
	complex result;
	result.re = (x.re * y.re + x.im * y.im)/(y.re * y.re + y.im * y.im);
	result.im = (x.im * y.re - x.re * y.im)/(y.re * y.re + y.im * y.im);
	printf ("<%2f> <%2f>\n",result.re,result.im);
	return result;
}

#endif
