/* This is a skeleton code for Optimized Merge Sort, you can make modifications as long as you meet 
   all question requirements*/  

#include <bits/stdc++.h>
#include "record_class.h"

using namespace std;

//defines how many blocks are available in the Main Memory 
#define buffer_size 22
int deptFileDMarker = 0;
int empFileDMarker = 0;
int total_emp_records = 0;
int total_dept_records = 0;

vector <Records> buffer; //will be maxed out at size 22

Records buffers[buffer_size]; //use this class object of size 22 as your main memory

/***You can change return type and arguments as you want.***/

//Sorting the buffers in main_memory and storing the sorted records into a temporary file (runs) 
int countFiles(string filenames){
    int count = 0;
    for(int i = 0; i < 1000; i++){
        string name = filenames + to_string(i);
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        count++;
    }    
    }
    return count;
}
int countLines(string filename){
    std::ifstream file(filename);
   

    int count = 0;
    std::string line;
    while (std::getline(file, line)) {
        count++;
    }

    file.close();
    return count;
}




//Prints out the attributes from empRecord and deptRecord when a join condition is met 
//and puts it in file Join.csv
void PrintJoin(Records dept, Records emp, ofstream &joinout) {
    
    
    string string1= to_string(emp.emp_record.eid) + "," + emp.emp_record.ename + "," + to_string(emp.emp_record.age) + "," + to_string(emp.emp_record.salary) + ",";
    string string2 = to_string(dept.dept_record.did) + "," + dept.dept_record.dname + "," + to_string(dept.dept_record.budget) + "," + to_string(dept.dept_record.managerid) + '\n';
    string ppeepoo = string1+string2;
    joinout << ppeepoo;

    return;
}

bool endOfFile(Records r){

   // cout << "r.novalues: " << r.no_values << endl;
    if(r.no_values==-1){
        return true;
    }
    else{
        return false;
    }
}


//Use main memory to Merge and Join tuples 
//which are already sorted in 'runs' of the relations Dept and Emp 
void Merge_Join_Runs(){
   
    cout << deptFileDMarker << endl;
    cout << empFileDMarker << endl;



    fstream dept0("dept0");
    fstream emp0("emp0");
    fstream emp1("emp1");


    



    bool endOfEmp0 = false;
    bool endOfEmp1 = false;
    bool endOfDept = false;
    ofstream joinout("Join.csv", ios::out | ios::app);

    // Variables to hold the current records from Emp and Dept relations

    // Read the first records from the sorted runs of Emp and Dept relations
    Records r;

    
    Records emp0_record;
    Records emp1_record;
    Records dept0_record;

    emp0_record = Grab_Emp_Record$(emp0);
    emp1_record = Grab_Emp_Record$(emp1);
    dept0_record = Grab_Dept_Record$(dept0);


    while(dept0_record.no_values !=-1){
        //dept0_record = Grab_Emp_Record$(dept0);
        if (dept0_record.no_values == -1){
            break;}
        //cout << "Did: " << emp1_record.emp_record.eid << endl;
        

        if (emp0_record.emp_record.eid == dept0_record.dept_record.managerid) {
            PrintJoin(dept0_record, emp0_record, joinout);
            emp0_record = Grab_Emp_Record$(emp0);
            dept0_record = Grab_Dept_Record$(dept0);
        }

        if (emp1_record.emp_record.eid == dept0_record.dept_record.managerid) {
            PrintJoin(dept0_record, emp1_record, joinout);
            emp1_record = Grab_Emp_Record$(emp1);
            dept0_record = Grab_Dept_Record$(dept0);
        }

        if (emp0_record.emp_record.eid < dept0_record.dept_record.managerid) {
            emp0_record = Grab_Emp_Record$(emp0);
        }
        if (emp1_record.emp_record.eid < dept0_record.dept_record.managerid) {
            emp1_record = Grab_Emp_Record$(emp1);
        }        


        if ((dept0_record.dept_record.managerid < emp0_record.emp_record.eid) && (dept0_record.dept_record.managerid < emp1_record.emp_record.eid)) {
            dept0_record = Grab_Dept_Record$(dept0);
        }
        


    }

    
    

        
    
    // join in the remainder emp0 and emp1


    
    // Close file streams
    dept0.close();
    emp0.close();
    emp1.close();
    joinout.close();

    // Delete temporary files after joining Emp.csv and Dept.csv
    
    //1.) start by opening dept0 and pulling the first record into memory

    //jump to line number 
    //compare with the first record of emp0-'emp + empFileDMarker -1'
    //iterate over current emp file until current dept0.managerid =<empX.eid
    //write matching records to join
    //update empFileArray with where we are in the file
    




    //and store the Joined new tuples using PrintJoin() 
    return;
}

int main() {
    remove("Join.csv");

    total_dept_records = countLines("Dept.csv");
    total_emp_records = countLines("Emp.csv");
    empFileDMarker = countFiles("emp");
    deptFileDMarker = countFiles("dept");

    fstream emp_file_array[empFileDMarker];
    fstream dept_file_array[deptFileDMarker];
    
    for (int i = 0; i < empFileDMarker; i++){
        emp_file_array[i] = fstream("emp" + to_string(i));
    }
    for (int i = 0; i < deptFileDMarker; i++){
        dept_file_array[i] = fstream("dept" + to_string(i));
    }
    //make arrays for all runs    

    //Open file streams to read and write
    //Opening out two relations Emp.csv and Dept.csv which we want to join
    //fstream empin;
    //fstream deptin;
   // empin.open("Emp.csv", ios::in);
   // deptin.open("Dept.csv", ios::in);
   
    //Creating the Join.csv file where we will store our joined results
    fstream joinout;
    joinout.open("Join.csv", ios::out | ios::app);
    Merge_Join_Runs();

    //1. Create runs for Dept and Emp which are sorted using Sort_Buffer()


    //2. Use Merge_Join_Runs() to Join the runs of Dept and Emp relations 


    //Please delete the temporary files (runs) after you've joined both Emp.csv and Dept.csv


    return 0;
}
