/*********************************************
 *Program:Palindrome Dector and Word Frequency
 *Author: Chia-Ling Hu
 *********************************************/

#include<iostream>
#include<string>
#include<cstring>
#include<string.h>
#include<cstdlib>
#include<cmath>

using namespace std;

// print the string
void print(char* str){
	cout << str <<endl;
}

// convert upper char to lower char
void uppertolower(char* str){
	for(int i=0;i<strlen(str);i++){
		if(str[i]>=65 && str[i]<=90){
			str[i]=str[i]+32;
		}
	}
}

// remove space in the string
void remove_space(char* str){
	for(int i=0;i<strlen(str);i++){
		if(str[i]==' '){
			memmove(&str[i],&str[i+1],strlen(str)-1);
			i--;
		}
	}
}

// remove multiple space in the string
void remove_mutispace(char* str){
	for(int i=0;i<strlen(str);i++){
		if(str[i]==' '&& str[i+1]==' '){
			memmove(&str[i],&str[i+1],strlen(str)-1);
			i--;
		}
	}
}

// remove number in the string
void remove_number(char* str){
	for(int i=0;i<strlen(str);i++){
		if(str[i]>47 && str[i]<58){
			memmove(&str[i],&str[i+1],strlen(str)-1);
			i--;
		}
	}
}

//remove character other than space
void remove_chara(char* str){
	for(int i=0;i<strlen(str);i++){
		if((str[i]>32 && str[i]<48)|| (str[i]>57 && str[i]<65) || (str[i]>90 && str[i]<97)||str[i]>122){
			memmove(&str[i],&str[i+1],strlen(str)-1);
			i--;
		}
	}
}

// check if string is palindrome
bool is_palindrome(char* str){
	int length = strlen(str);
	bool isbad = false;
	for(int i=0;i<length;i++){
		if(str[i]!=str[length-1-i]){
			isbad = true;
			break;
		}
	}
	if(isbad){
		return false;
	}
	else{
		return true;
	}
}

// purge string 
char *purge_string1(char* str){
	char *copy_str = new char[1025];
	strcpy(copy_str,str);
	uppertolower(copy_str);
	remove_space(copy_str);
	remove_chara(copy_str);
	return copy_str;
}

// purge string
char *purge_string2(char* str){
	char *copy_str = new char[1025];
	strcpy(copy_str,str);
	uppertolower(copy_str);
	remove_chara(copy_str);
	remove_number(copy_str);
	remove_mutispace(copy_str);
	return copy_str;
}

// count how many words in a string
int  count_words(char *str){
	int words = 0;
	for(int i=0; str[i]!='\0';i++){
		if(str[i]==' '){
			words++;
		}
	}
	return words+1;
}

// count the words of frequent in a string
void all_words_freq(char *str){	
	int index = 0;
	int newindex = 0;
	int words = count_words(str);
	string copystr[256];
	string compstr[256];
	int countarr[256] = {0};
	string temp="";	
	for(int i=0;i<strlen(str);i++){
		if(str[i]!=' '&& str[i]!='\0'){
			temp = temp + str[i];
		}
		else{
			temp="";
			index++;
		}
		copystr[index]=temp;
	}
	for(int i=0;i<words;i++){
		bool found = false;
		for(int j=0;j<newindex;j++){
			if(copystr[i]==compstr[j]){
				countarr[j]++;
				found = true;
			}
		}
		if(found==false){
			compstr[newindex]=copystr[i];
			countarr[newindex]=1;
			newindex++;
		}
	}
	for(int i=0;i<newindex;i++){
		cout << compstr[i] << " occur " << countarr[i] <<" time " <<endl;
	}
}
// count words of frequent in a string
void given_words_freq(char *str){
	int num;
	int words = count_words(str);
	cout << "Enter the number of words: ";
	cin >> num;
	cin.ignore(1024,'\n');
	string *ptr = new string[num];
	string copystr[256];
	string temp="";
	int numarr[256] = {0};
	cout <<"Enter the words you want to count:  ";
	for(int i=0;i<num;i++){
		getline(cin,ptr[i]);
	}
	int index=0;	
	for(int i=0;i<strlen(str);i++){
		if(str[i]!=' '&& str[i]!='\0'){
			temp = temp + str[i];
		}
		else{
			temp="";
			index++;
		}
		copystr[index]=temp;
	}
	for(int i=0;i<num;i++){
		for(int j=0;j<words;j++){
			if(ptr[i]==copystr[j]){
				numarr[i]++;
			}
		}
	}
	for(int i=0;i<num;i++){
		cout <<ptr[i] << " occur " << numarr[i] << " in the sentence."<<endl;
	}
	delete [] ptr;
	

}

// palindrome
void case_one(char* str){
	char *modistr = purge_string1(str);
	(is_palindrome(modistr))? cout <<"It is palindrome."<<endl : cout <<"It is not palindrome."<<endl;
	delete [] modistr;
}

// all words frequent
void case_two(char* str){
	char *modistr = purge_string2(str);
	all_words_freq(modistr);
	delete []modistr;

}

// given word frequent
void case_three(char* str){
	char *modistr = purge_string2(str);
	given_words_freq(modistr);
	delete []modistr;

}
int main(){
	int play = 0;
	do{
		char input[1025];
		int number = 0 ;
		cout <<"Enter a sentence: ";
		cin.getline(input,1024);
		cout <<"Choose 1(Palindrome Dector) or 2(Frequency of all words) or 3(Frequency of given words): ";
		cin >>number;
		switch(number){
			case 1:{
				case_one(input);
				break;
			}
			case 2:{

				case_two(input);	
				break;
			}
			case 3:{
				case_three(input);
				break;
			}

		}
		cout << "Do you want to play again?(0-no, 1-yes): ";
		cin >> play;
		cin.ignore();
		}while(play==1);
	return 0;
}
