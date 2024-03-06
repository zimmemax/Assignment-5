/* This is a skeleton code for Optimized Merge Sort, you can make modifications as long as you meet 
   all question requirements*/  

#include <bits/stdc++.h>
#include "record_class.h"
#include <vector>

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
void deleteFiles(string name, int numFiles){
    for(int i = 0; i < numFiles; i++){
        //ifstream n(name + to_string(i));
        string n = name + to_string(i);
        remove(n.c_str());
    }
}

int countFiles(string filenames){
    int count = 0;
    for(int i = 0; i < 1000; i++)
    {
        string name = filenames + to_string(i);
        if (FILE *file = fopen(name.c_str(), "r"))
        {
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

/*
bool deptsLeft(string *dept_file_array, int deptFileDMarker){
    for(int i = 0; i < deptFileDMarker; i++){
        fstream deptFile = fstream(dept_file_array[i]);
        Records r = Grab_Dept_Record$(deptFile);
        if(dept != -1){
            return false;
        }
    }
    return true;
    
}
*/


bool inArray(const std::vector<int> v, int seek) {
    for (int i = 0; i < v.size(); i++) {
        //cout << "Seek: " << seek << " v[i] "  <<v[i];
        if (seek == v[i]) {
            return true;
        }
    }

   return false;
}


Records getSmallestRecord(vector<int> vistedDeptManagerID, string*dept_file_arr){
    Records currDept;
    Records smallestDept;
    fstream currFile;
    int smallestManagerID = 10000000;

    for(int i =0; i < deptFileDMarker; i++){
        string fileName = "dept" + to_string(i);
        currFile = fstream(fileName);
        currDept = Grab_Dept_Record$(currFile);
        while(currDept.no_values != -1){
            int currManagerID = currDept.dept_record.managerid;
            if((currManagerID< smallestManagerID) && !inArray(vistedDeptManagerID, currDept.dept_record.did))
            {
                smallestDept = currDept;
                smallestManagerID = currManagerID;
            }
        currDept = Grab_Dept_Record$(currFile);

        }
        
    }

    return smallestDept;
}
void Merge_Join_Runs(string *emp_file_array, string *dept_file_array){
   
    // find the lowest dept file manager id
   

    vector<int> vistedDeptDID;
    //visit lowest dept = currDeptmanagerid
    //check if currDeptmanagerid in vistedDeptManagerID
    //if not check if it has any join in all emp
    //add currentDeptManagerid to vistedDeptManagerID
    
    ofstream joinout;
    joinout.open("Join.csv", ios::out | ios::app);

    //count total deptrecords
   total_dept_records = 0;
   for(int i = 0; i < deptFileDMarker; i++){
    
    total_dept_records+=countLines(dept_file_array[i]);
   }
    
    
    Records smallestDeptRecord;
   
    while(vistedDeptDID.size() != total_dept_records){
        smallestDeptRecord = getSmallestRecord(vistedDeptDID, dept_file_array);
        vistedDeptDID.push_back(smallestDeptRecord.dept_record.did);
        
        for(int i = 0; i < empFileDMarker; i++){
            Records r;
            fstream empFile = fstream(emp_file_array[i]);
            while(r.no_values != -1){
                r = Grab_Emp_Record$(empFile);
                if(r.emp_record.eid == smallestDeptRecord.dept_record.managerid)
                {
                    PrintJoin(smallestDeptRecord, r, joinout);
                }
            }
        }
    }

    return;
}
int main() {
    remove("Join.csv");

    total_dept_records = countLines("Dept.csv");
    total_emp_records = countLines("Emp.csv");
    empFileDMarker = countFiles("emp");
    deptFileDMarker = countFiles("dept");

    string emp_file_array[empFileDMarker];
    string dept_file_array[deptFileDMarker];
    
    stringstream sstm;
    for (int i=0;i<empFileDMarker ;i++)
    {
        string currStr = "emp" + to_string(i);
        emp_file_array[i] = currStr;
    }
    for (int i=0;i<deptFileDMarker ;i++)
    {
        string currStr = "dept" + to_string(i);
        dept_file_array[i] = currStr;
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
    //Merge_Join_Runs(emp_file_array, dept_file_array);
    cout << "Max o clock" << endl;
    Merge_Join_Runs(emp_file_array, dept_file_array);
    
    //Close file streams
    joinout.close();
    
    //1. Create runs for Dept and Emp which are sorted using Sort_Buffer()


    //2. Use Merge_Join_Runs() to Join the runs of Dept and Emp relations 


    //Please delete the temporary files (runs) after you've joined both Emp.csv and Dept.csv
    deleteFiles("emp", 1000);
    deleteFiles("dept", 1000);

    return 0;
}
