#include<iostream>

using namespace std;
void decrypt(string encryptedText,int key){
	string decryptedText;
	for(int i=0;i<encryptedText.size();i++){
		if(encryptedText[i]==' ')
			decryptedText+=" ";
		else 	
			decryptedText+= char(65+((encryptedText[i]-'A'-key)%26));
	}
	cout << decryptedText<<endl;
}

void encrypt(string plainText,int key){
	string encryptedText;
	for(int i=0;i<plainText.size();i++){
		if(plainText[i]==' ')
			encryptedText+=" ";
		else 	
			encryptedText+= char(65+((plainText[i]-'a'+key)%26));
	}
	cout << encryptedText<<endl;
	decrypt(encryptedText,key);
}


int main(){
	string plainText;
	int key;
	cout <<"Enter your text=";
	getline(cin,plainText);
	cout<<"Shift=";
	cin >>key;
	encrypt(plainText,key);
	return 0;
}
