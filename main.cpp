#include <iostream>
#include <chrono>
#include <cstdio>
#include "defines.h"
#include "Scheme.h"
#include "distr.h"

#define TEST_NUM 100

#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
#define PBWIDTH 60

void printProgress(double percentage)
{
	int val = (int)(percentage * 100);
	int lpad = (int)(percentage * PBWIDTH);
	int rpad = PBWIDTH - lpad;
	printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
	fflush(stdout);
}


using namespace std;

int main() {
	
		long count = 0;
		
		double mskTime = 0.;
		double skTime = 0.;
		double encTime = 0.;
		double ipTime = 0.;
		
		int64_t ptxtResult;
		chrono::high_resolution_clock::time_point t1;
		chrono::high_resolution_clock::time_point t2;

		MasterSecretKey msk;
		EncryptedTemplate T;
		EncryptedBio B;

		Biometric X, Y;

		// Start Test
		cout << TEST_NUM << " iteration start!" << endl;
		for (long i = 0; i < TEST_NUM; i++) {
			printProgress((double)i / TEST_NUM);

			// Make template biometric
			for (long i = 0; i < K; i++) {
				X[i] = U(GEN) % 2;
				X[i] = 1 - 2 * X[i];
			}

			// Generate Master Secret Key
			t1 = chrono::high_resolution_clock::now();
			Scheme::mskGen(msk);
			t2 = chrono::high_resolution_clock::now();
			mskTime += chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
		
			// Generate Encryped Template corresponding to X
			t1 = chrono::high_resolution_clock::now();
			Scheme::templateGen(T, msk, X);
			t2 = chrono::high_resolution_clock::now();
			skTime += chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
					
			// Set random Y
			for (long j = 0; j < K; j++) {
				Y[j] = U(GEN) % 2;
				Y[j] = 1 - 2 * Y[j];
			}
			// Encrypt Bio information
			t1 = chrono::high_resolution_clock::now();
			Scheme::encryptBio(B, msk, Y);
			t2 = chrono::high_resolution_clock::now();
			encTime += chrono::duration_cast<chrono::milliseconds>(t2 - t1).count();
			// Compute Result in un-encrypted state for check
			ptxtResult = 0;
			for (long j = 0; j < K; j++) {
				ptxtResult += X[j] * Y[j];
			}
			// InnerProduct using encrypted template T and encrypted bio B
			t1 = chrono::high_resolution_clock::now();
			int64_t result = Scheme::innerProduct(T, B);
			t2 = chrono::high_resolution_clock::now();
			ipTime += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
			// Check the result
			if (ptxtResult != result) {
				cout << ptxtResult << endl;
				cout << result << endl;
				cout << "  " << endl;
				count++;
				cout << i << "-th running has ERROR!!!" << endl;
			}
		}

		cout << endl;
		cout << "- Master Secret Key Generation Time: " << mskTime / TEST_NUM << " ms" << endl;
		cout << "- Template Generation Time: " << skTime / TEST_NUM << " ms" << endl;

		if (count == 0) cout << "No error occured." << endl;
		cout << "- Average Time for Encryption: " << encTime / TEST_NUM << " ms" << endl;
		cout << "- Average Time for InnerProduct: " << ipTime / TEST_NUM << " us" << endl;
		cout << "- Error Rate: " << 100 * (double)count / TEST_NUM << "%" << endl;


		delete[] msk.S;
		delete[] msk.U;



	cout << "PRESS ENTER to EXIT" << endl;
	cin.ignore();
	return 0;
}
