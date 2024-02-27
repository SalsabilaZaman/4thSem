//#include<iostream>
//#include<string>
#include<bits/stdc++.h>
using namespace std;

char table[5][5];

void constructTable(string key){
	string str="",alpha="ABCDEFGHI%KLMNOPQRSTUVWXYZ";
	string StringVariable="";
	transform(key.begin(), key.end(), key.begin(), ::toupper);
	
	for(int i=0;i<key.size();i++){
		if(key[i]=='J')
		    key[i]='I';
		StringVariable=key[i];
		if(str.find(StringVariable)== string :: npos)
			str+=StringVariable;
	}
	for(int i=0;i<key.size();i++){
		int position=key[i]-'A';
		alpha.erase(alpha.begin()+position);
		alpha.insert(position,"%");
	}
	for(int i=0;i<alpha.size();){
		if(alpha[i]=='%')
			alpha.erase(alpha.begin()+i);
		else
		    i++;	
	}
	/*if(key.find("I")!= string :: npos)
		alpha.erase(alpha.begin()+alpha.find("J"));
	else if(key.find("J")!= string :: npos)
		alpha.erase(alpha.begin()+alpha.find("I"));
	*/
		
	//cout << str <<endl;
	//cout << alpha.size()<<endl;
	
	str+=alpha;
	//cout << str <<endl;
	//cout << str.size()<<endl;
	
	int k=0;
	for(int i=0;i<5;i++)
	   for(int j=0;j<5;j++)
	   	table[i][j]=str[k++];
	   	
	for(int i=0;i<5;i++){
	   for(int j=0;j<5;j++)
	   	cout << table[i][j]<<" ";	
	   cout <<endl;
	}
} 



int lengthwithoutSpaces(string str){
	int len=str.size();
	for(int i=0;i<str.size();i++)
		if(str[i]==' ')
			len--;

	return len;
}

string charToString(char inputChar) {
    return string(1, inputChar);
}

void encrypt(string key){
	constructTable(key);
	string str,finalStr="";
	cout <<"Enter your String=";
	getline(cin,str);
	for(int i=0;i<str.size();i++)
		if(str[i]=='j')
		   str[i]='i';
	transform(str.begin(), str.end(), str.begin(), ::toupper);	   
		   
	for(int i=0;i<str.size();i+=2)
		if(str[i]==str[i+1])
			str.insert(i+1,"X");

	if(lengthwithoutSpaces(str)%2!=0)
		str+="X";
	cout << str<<endl;
	
	for(int i=0;i<str.size();i+=2){
	     string s1;
	     int r1,c1,r2,c2;
	     for(r1=0;r1<5;r1++){
	         for(c1=0;c1<5;c1++)
	              if(table[r1][c1]==str[i])
	              	break;
	     	 if(c1!=5)
	     	    break;
	     }         	
	     for(r2=0;r2<5;r2++){
	         for(c2=0;c2<5;c2++)
	              if(table[r2][c2]==str[i+1])
	              	break;
	         if(c2!=5)
	     	    break;
	    } 	         	
	
	     if(r1==r2)
	     	finalStr+=charToString(table[r1][(c1+1)%5])+charToString(table[r2][(c2+1)%5]);	
	     else if(c1==c2)	
		finalStr+=charToString(table[(r1+1)%5][c1])+charToString(table[(r2+1)%5][c2]);
	     else
		finalStr+=charToString(table[r1][c2])+charToString(table[r2][c1]); 
	}
	cout << finalStr<<endl;
}


int main(){
	string key;
	cout <<"Enter your key=";
	getline(cin,key);
	encrypt(key);

	return 0;
}
