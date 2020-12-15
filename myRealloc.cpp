#include <iostream>
#include <cstdlib>


int *myReallocC(int *arr, int *len) {
	int *newArr = (int*)malloc(sizeof(int)*2*(*len));

	for(int i=0;i<(*len);i++) {
		newArr[i] = arr[i];
	}
	free(arr);
	(*len) *= 2;
	return newArr;
}

int *myReallocCpp(int *arr, int *len) {
	int *newArr = new int[(*len)*2];

	for(int i=0;i<(*len);i++) {
		newArr[i] = arr[i];
	}
	delete [] arr;
	(*len) *= 2;
	return newArr;
}

int main() {
	int lenC=2;
	int lenCpp=2;

	int *arrC = (int*)malloc(sizeof(int)*lenC);
	int *arrCpp = new int[lenCpp];

	// simdi negatif sayi girilene kadar diziye eleman ekliyelim

	int i=0;
	int num;

	while(1) {
		if(i==lenC) { arrC = myReallocC(arrC, &lenC); }
		if(i==lenCpp) { arrCpp = myReallocCpp(arrCpp, &lenCpp); }

		std::cin>>num;
		if(num <= 0) { break; }

		arrC[i] = num;
		arrCpp[i] = num;

		i++;
	}

	std::cout<<"\nC arr >> ";
	for(int z=0;z<lenC;z++) { std::cout<<arrC[z]<<"  "; }

	std::cout<<"\nCpp arr >> ";
	for(int z=0;z<lenCpp;z++) { std::cout<<arrCpp[z]<<"  "; }

	std::cout<<"\n";

	return 0;
}
