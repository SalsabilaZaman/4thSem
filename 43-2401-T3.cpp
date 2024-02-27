#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;


void encrypt(string key){
	string plainText,encryptedText;
	cout<<"Enter plain text=";
	getline(cin,plainText);
	int len1=key.size();
	int len2=plainText.size();
	if(len2>len1){
		string str=key;
		int times=len2/len1;
		int remainder=len2%len1;
		for(int i=0;i<times;i++)
			key+=str;
		for(int i=0;i<remainder;i++)	
			key+=str[i];
	}		
	for(int i=0;i<len2;i++){
		int ind=(key[i]-'a'+plainText[i]-'a')%26;
		encryptedText+=char(ind+65);
	}
	cout <<"Encrypted text="<<encryptedText;
}

int main(){
	string key;
	cout<<"Enter you key=";
	getline(cin,key);	
	encrypt(key);
	
	return 0;
}
