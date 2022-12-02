/*********************************************************************
 *Program : Budget buddy
 *Author : Chia-Ling Hu
 *********************************************************************/
#include <iostream>
#include <string>
#include <cstring>
#include "./budget_buddy.h"

using namespace std;


// dynamically allocate an array of user
user* create_user_db(int num){
    user* u = new struct user[num];
    return u;
}
// fill in user struct with info read in from user txt file 
void get_user_info(user* arr,int num,ifstream& file){
    for(int i=0;i<num;i++){
        file >> arr[i].name;
        file >> arr[i].id;
        file >> arr[i].password;
    }
}

// print the filled in user struct 
void print_user_arr(user* arr,int num){
    cout << num << endl;
    for(int i=0;i<num;i++){
        cout << arr[i].name << " ";
        cout << arr[i].id << " ";
        cout << arr[i].password << endl;
    }
}

// dynamically allocate an array of budget
budget* create_budgets(int num){
    budget* b = new struct budget[num];
    return b;
}

// fill in budget struct with info read from budget file 
void get_budget_data(budget* arr,int num,ifstream& file){
    for(int i=0;i<num;i++){
        file >> arr[i].id;
        file >> arr[i].balance;
        file >> arr[i].num_transactions;
        arr[i].t = create_transactions(arr[i].num_transactions);
        get_transaction_data(arr[i].t,arr[i].num_transactions,file);
    }
}

// dynamically allocate an array of transaction
transaction* create_transactions(int num){
    transaction* t = new struct transaction[num];
    return t;
}

// fill in transaction struct with info read from budget file
void get_transaction_data(transaction* arr,int num,ifstream& file){
    for(int i=0;i<num;i++){
        file >> arr[i].date;
        file >> arr[i].amount;
        file >> arr[i].description;
        file >> arr[i].category;
    }
}

void print_budget_arr(budget* arr,int num){
    cout << num << endl;
    for(int i=0;i<num;i++){
        cout << arr[i].id << " ";
        cout << arr[i].balance << " ";
        cout << arr[i].num_transactions << endl;
        for(int j=0;j<arr[i].num_transactions;j++){
            cout << arr[i].t[j].date << " ";
            cout << arr[i].t[j].amount << " ";
            cout << arr[i].t[j].description << " ";
            cout << arr[i].t[j].category << endl;
        }
    }
}

// check if string only contains integer
bool is_int(string str){
    for(int i=0;i<str.size();i++){
        if(str[i]<48 || str[i]>57){
            return false;
        }
    }
    return true;
}

// get id from user
string get_user_id(){
    string id;
    do{
        cout << "Enter user id (integer only): ";
        getline(cin,id);
        if(!is_int(id)){
            cout << "Invalid id format, id must be all integers! Try again! " << endl;
        }
    }while(!is_int(id));
    return id;
}

// get password from user
string get_user_pass(){
    string pass;
    cout << "Enter password: ";
    getline(cin,pass);
    return pass;
}

// get user login 
void user_login(string& id, string& pass){
    id = get_user_id();
    pass = get_user_pass();
}

// check if user's input id and password match the info 
bool is_id_pass_match(user* u_arr,int u_num,string id,string pass){
    int id_num = atoi(id.c_str());
    for(int i=0;i<u_num;i++){
        if((u_arr[i].id==id_num) && (pass.compare(u_arr[i].password)==0)){
            return true;
        }
    }
    return false;
}


// find the index of matched id in budget arr
int is_match(user* u_arr,budget* b_arr,int u_num,int b_num,string id,string pass){
    int idx;
    int id_num = atoi(id.c_str());
    for(int i=0;i<u_num;i++){
        if(u_arr[i].id == id_num && (pass.compare(u_arr[i].password)==0)){
            cout << "User name: " << u_arr[i].name << endl;
            cout << "User id: " << u_arr[i].id << endl;
        }
    }
    for(int j=0;j<b_num;j++){
        if(b_arr[j].id == id_num){
            cout << "Account balance: " << b_arr[j].balance << endl;
            idx = j;
        }
    }
    return idx;
}

// swap function
void swap(transaction* x, transaction* y){
    transaction temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

// sort the transaction by amount 
void sort_by_amount(budget* b_arr,int b_idx){
    for(int i=0;i<b_arr[b_idx].num_transactions-1;i++){
        for(int j=0;j<b_arr[b_idx].num_transactions-i-1;j++){
            if(b_arr[b_idx].t[j].amount > b_arr[b_idx].t[j+1].amount){
                swap(&b_arr[b_idx].t[j],&b_arr[b_idx].t[j+1]);
            }
        }
    }
}

// sort by the first alphabet 
void sort_by_category(budget* b_arr,int b_idx){
    for(int i=0;i<b_arr[b_idx].num_transactions-1;i++){
        for(int j=0;j<b_arr[b_idx].num_transactions-i-1;j++){
            if(b_arr[b_idx].t[j].category[0] < b_arr[b_idx].t[j+1].category[0]){
                swap(&b_arr[b_idx].t[j],&b_arr[b_idx].t[j+1]);
            }
        }
    }
}


 // sort the transaction by date
 void sort_by_date(budget* b_arr,int b_idx){
     for(int i=0;i<b_arr[b_idx].num_transactions-1;i++){
        for(int j=0;j<b_arr[b_idx].num_transactions-i-1;j++){
            if(b_arr[b_idx].t[j].date.substr(6,4)<b_arr[b_idx].t[j+1].date.substr(6,4)){
                swap(&b_arr[b_idx].t[j],&b_arr[b_idx].t[j+1]);
            }
            if(b_arr[b_idx].t[j].date.substr(6,4) == b_arr[b_idx].t[j+1].date.substr(6,4)){
                if(b_arr[b_idx].t[j].date.substr(0,2)<b_arr[b_idx].t[j+1].date.substr(0,2)){
                    swap(&b_arr[b_idx].t[j],&b_arr[b_idx].t[j+1]);
                }
                else if(b_arr[b_idx].t[j].date.substr(0,2) == b_arr[b_idx].t[j+1].date.substr(0,2)){
                    if(b_arr[b_idx].t[j].date.substr(3,2) < b_arr[b_idx].t[j+1].date.substr(3,2)){
                        swap(&b_arr[b_idx].t[j],&b_arr[b_idx].t[j+1]);
                    }
                }
            }
        }
     }
 }


// print the transaction of given budget index
void print_transaction(budget* b_arr,int b_idx){
    for(int i=0;i<b_arr[b_idx].num_transactions;i++){
        cout << b_arr[b_idx].t[i].date << " ";
        cout << b_arr[b_idx].t[i].amount << " ";
        cout << b_arr[b_idx].t[i].description << " ";
        cout << b_arr[b_idx].t[i].category << endl;
    }
}

// write the transaction to the file
void write_to_file(budget* b_arr,int b_idx,ofstream& file){
    for(int i=0;i<b_arr[b_idx].num_transactions;i++){
        file << b_arr[b_idx].t[i].date << " ";
        file << b_arr[b_idx].t[i].amount << " ";
        file << b_arr[b_idx].t[i].description << " ";
        file << b_arr[b_idx].t[i].category << endl;
    }
}

// ask user if they want to print the transaction on screen or write them into file
void print_or_write(budget* b_arr,int b_idx){
    int i=0;
    cout << "Do you want to print out on screen(press 1) or write to file(press 2)? "<< endl;
    cout << "Enter your choice ( 1 or 2 ): ";
    cin >> i;
    switch(i){
        case 1:{
                print_transaction(b_arr,b_idx);
                break;
        }
        case 2:{
                ofstream outf;
                string filename;
                cout << "Enter file name: ";
                cin.ignore();
                getline(cin,filename);
                outf.open(filename,ios::out|ios::app);
                if(outf.fail()){
                    cout << "Error cannot open file to write" << endl;
                }
                else if(outf.is_open()){
                    cout << "Information is written into " << filename << endl;
                    write_to_file(b_arr,b_idx,outf);
                }
                outf.close();
                break;
        }
    }
}


// prompt user four option
void prompt_option(user* u_arr,budget* b_arr,int b_idx,int b_num){
    int i = 0;
    do{
        cout <<"Choose one way to display the sorted transaction:" << endl;
	    cout <<"Sort by category(press 1)" << endl;
	    cout <<"Sort by date(press 2)" << endl;
	    cout <<"Sort by dollar amount(press 3)" << endl;
	    cout <<"Quit the program(press 4)" << endl;
	    cout <<"Enter your choice number: ";
	    cin >> i;
        switch (i){
            case 1:{
                    cout << "Sort by category " << endl;
                    sort_by_category(b_arr,b_idx);
                    print_or_write(b_arr,b_idx);
                    
                    break;
            }
            case 2:{
                    cout << "Sort by date " << endl;
                    sort_by_date(b_arr,b_idx);
                    print_or_write(b_arr,b_idx);
                    break;
            }
            case 3:{
                    cout << "Sort by dollar amount " << endl;
                    sort_by_amount(b_arr,b_idx);
                    print_or_write(b_arr,b_idx);
                    break;
            }
            case 4:{
                    delete_info(u_arr,b_arr,b_num);
                    exit(0);
            }
        }
    }while(i!=4);
}

// free the allocate memory
void delete_info(user* u_arr,budget* b_arr,int num){
    delete [] u_arr;
    for(int i=0;i<num;i++){
        delete [] b_arr[i].t;
    }
    delete [] b_arr;
}
