#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <dirent.h>
using namespace std;
DIR *directory;   
struct dirent *entry;  
string fname[3];
string file, file1;
string filetext;
fstream f;
void view();
void convert();
void show();
int main() {
	int num;
	cout << "\n\n\n\t\t--------------------Text to HTML Converter----------------\n\n";
	cout << "\t\t\t1. View and Select text file from directory.\n";					                 		
	cout << "\t\t\t2. Convert text file to HTML file.\n";					                               			
	cout << "\t\t\t3. View HTML file.\n";
	cout <<	"\t\t\t4. Exit.\n";			                                           										
	cout << "\t\t----------------------------------------------------------\n\n";
	do {
		cout << "\t\tPlease Enter your choice : ";
		cin >> num;
		switch (num) {
		case 1: view(); break;
		case 2: convert(); break;
		case 3: show(); break;
		case 4: cout << "\t\tExit."<<endl; exit(0);
		default: cout << "\t\tInvalid choice.\n"; 
		}
	} while (num !=4 );
	system("pause");
	return 0;
}
void view(){
	int i=1,ch;
	if(( directory= opendir ("C:\\Users\\hassa\\Desktop\\Project CC\\Text files")) == NULL){
		cout<<"Path not found.\n"<<endl;
	}else{
		cout<<"\n\t\t------------------------------------------------------------------\n";
		cout<<"\t\tInside File Path: C:\\Users\\hassa\\Desktop\\Project CC\\Text files\n\n";      
 	 	while ((entry = readdir (directory)) != NULL) {
 	     if(entry->d_name[0]!='.'){
			cout<<"\t\t\t"<<i<<". "<<entry->d_name<<endl;
			fname[i-1]=entry->d_name;	
			i++;
		  }
 		}
 		cout << "\t\tPlease select your file : ";
		cin >> ch;
		if(fname[ch-1] == ""){
			cout<<"\t\tInvalid choice.\n";
		}else{
			file=fname[ch-1];
			cout<<"\n\t\tConfriming file choice: "<<file<<endl;
			file1=file;
			file="C:\\Users\\hassa\\Desktop\\Project CC\\Text files\\"+file;
			
		}
		cout<<endl;
  		closedir (directory); 
	}
	main();
}
void convert(){
	int p, len=file.length();
	filetext="C:\\Users\\hassa\\Desktop\\Project CC\\HTML\\"+file1;
	p=filetext.find(".");
	string t=".html";
	filetext.erase(p,len);
	filetext.insert(p,t);
	string line;
	ofstream n;
	n.open(filetext.c_str());
	f.open(file.c_str());
	while(!f.eof()){
	while(getline(f,line)){
		//Analyzin input stream
		if(line[0]>=0&&line[0]<=9){
			cout<<"\t\tInvalid identifier.\n";
		}else if(line[0]==*"t"){
			cout<<"\t\t"<<line[0]<<" is a keyword.\n";
			n<<"<!DOCTYPE html>\n<html>\n<head>";
			n<<"<title>"<<line.substr(2,len)<<"</title>\n";
			n<<"</head>\n";
			n<<"<body>\n";
		}else if(line[0]==*"h"){
			cout<<"\t\t"<<line[0]<<line[1]<<" is a keyword.\n";
			n<<"<"<<line[0]<<line[1]<<">"<<line.substr(3,len)<<"</"<<line[0]<<line[1]<<">"<<endl;		
		}else if(line[0]==*"c"){
			cout<<"\t\t"<<line[0]<<" is a keyword.\n";
			n<<"<!--"<<line.substr(2,len)<<"-->"<<endl;
		}else if(line[0]==*"b"&&line[1]==*"r"){
			cout<<"\t\t"<<line[0]<<line[1]<<" is a operator.\n";
			n<<"</"<<line[0]<<line[1]<<">"<<line.substr(3,len)<<endl;
		}else if(line[0]==*"h"&&line[1]==*"r"){
			cout<<"\t\t"<<line[0]<<line[1]<<" is a operator.\n";
			n<<"</"<<line[0]<<line[1]<<">"<<line.substr(3,len)<<endl;
		}else if(line[0]==*"b"||line[0]==*"i"||line[0]==*"u"){
			cout<<"\t\t"<<line[0]<<" is a operator.\n";
			n<<"<"<<line[0]<<">"<<line.substr(2,len)<<"</"<<line[0]<<">"<<endl;
		}else if(line[0]==*"p"){
			cout<<"\t\t"<<line[0]<<" is an Keyword.\n";
			n<<"<"<<line[0]<<">"<<line.substr(2,len)<<"</"<<line[0]<<">"<<endl;
		}else if(line[1]==*"_"||line[2]==*"_"){
			//int o=line.find("_");
			cout<<"\t\t_ is a puntuactor.\n";
		}	
	}
}
	n<<"</body>\n";
	n<<"</html>\n";			
	n.close();
	f.close();
	main();
}	
void show(){
	system("cls");
	cout<<"\n\n\n";
	string line;
	f.open(filetext.c_str());
	while(!f.eof()){
		while(getline(f,line)){
			cout<<"\t\t"<<line<<endl;
		}
	}
	f.close();
	main();
}

