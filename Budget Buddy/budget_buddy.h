//#ifndef BUDGET_BUDDY_H
//#define BUDGET_BUDDY_H

#include<iostream>
#include<string>
#include<fstream>
using namespace std;

struct user{
    string name;
    int id;
    string password;
};

struct budget{
    int id;
    float balance;
    int num_transactions;
    struct transaction* t;
};

struct transaction{
    float amount;
    string date;
    string category;
    string description;
};


user* create_user_db(int);
void get_user_info(user*,int,ifstream&);
void print_user_arr(user*,int);
bool is_id_pass_match(user*,int,string,string);
int is_match(user*,budget*,int,int,string,string);
budget* create_budgets(int);
void get_budget_data(budget*,int,ifstream&);
void print_budget_arr(budget*,int);
transaction* create_transactions(int);
void get_transaction_data(transaction*,int,ifstream&);
void print_transaction(budget*);
void user_login(string&, string&);
void prompt_option(user*,budget*,int,int);
void swap(transaction*,transaction*);
void sort_by_amount(budget*,int);
void sort_by_date(budget*,int);
void sort_by_category(budget*,int);
void print_or_write(budget*,int);
void write_to_file(budget*,int,ofstream&);
void delete_info(user*,budget*,int);
bool is_int(string);
string get_user_id();
string get_user_pass();

//#endif