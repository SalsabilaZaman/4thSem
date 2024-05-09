#include<iostream>
#include<vector>
#include <cstdlib> 
using namespace std;
#define MAX 1000009
bool isPrime[MAX];
vector<int> primeNumbers;

void checkPrime(){
	for(int i=2;i<MAX;i++)
	    isPrime[i]=true;
	    
	for(int i=2;i*i<MAX;i++)
	  if(isPrime[i]==true)
	    for(int j=i*i;j<MAX;j+=i)
	        isPrime[j]=false;
	for(int i=2;i<MAX;i++)
	    if(isPrime[i]==true)
	    	primeNumbers.push_back(i);       
}
//public (n,e)
//private(n,d)

double e,d,n;

double generateRandomPrimeNumber(){
	int i=0;
	int upper=primeNumbers.size();
	int lower=primeNumbers.size()-100;
	double randomNumber =lower + (rand() %(upper - lower+1));
	cout <<primeNumbers.at(randomNumber)<<endl;;
	return primeNumbers.at(randomNumber);
}

void keyGeneration(){
	double p=generateRandomPrimeNumber();
	double q=generateRandomPrimeNumber();
	

}


int main(){
	srand(time(0));
	checkPrime();
	keyGeneration();
	
	return 0;
}
