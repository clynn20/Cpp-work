/*********************************************************************
 *Program : Budget buddy
 *Author : Chia-Ling Hu
 *********************************************************************/

#include "./budget_buddy.h"

int main(int argc, char* argv[]){
    
    int user_db_num, budget_num, budget_idx;
    ifstream file;
    file.open(argv[1],ios::in);
    if(file.fail()){
        cout << "Error user file cannot be opened " << endl;
    }
    else if(file.is_open()){
        cout << "Success open user file " << endl;
    }
    file >> user_db_num;
    user* u_arr = create_user_db(user_db_num);
    get_user_info(u_arr,user_db_num,file);
    //print_user_arr(u_arr,user_db_num);
    file.close();

    file.open(argv[2],ios::in);
    if(file.fail()){
        cout << "Error budget file cannot be opened " << endl;
    }
    else if(file.is_open()){
        cout << "Success open budget file " << endl;
    }
    file >> budget_num;
    budget* b_arr = create_budgets(budget_num);
    get_budget_data(b_arr,budget_num,file);
    //print_budget_arr(b_arr,budget_num);
    file.close();

    string id,pass;
    int count = 1;
    do {
        user_login(id, pass);
        if(is_id_pass_match(u_arr,user_db_num,id,pass)==false){
            cout << "No matched user id and password pair!" << endl;
            count++;
        }
        if(count>3){
            cout << "Failed to login after three tries!" << endl;
            delete_info(u_arr,b_arr,budget_num);
            exit(1);
        }
    }while(is_id_pass_match(u_arr,user_db_num,id,pass)==false);

    if(is_id_pass_match(u_arr,user_db_num,id,pass)==true){
        budget_idx = is_match(u_arr,b_arr,user_db_num,budget_num,id,pass);
    }
    prompt_option(u_arr,b_arr,budget_idx,budget_num);
    return 0;

}