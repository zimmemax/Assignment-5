/* This is a skeleton code for External Memory Sorting, you can make modifications as long as you meet 
   all question requirements*/  
#include "sortDept.h"

//defines how many blocks are available in the Main Memory 
int fileDmarker = 0;

Records buffers[buffer_size]; //use this class object of size 22 as your main memory

/***You can change return type and arguments as you want.***/

void deleteFiles(string name, int numFiles){
    for(int i = 0; i < numFiles; i++){
        //ifstream n(name + to_string(i));
        string n = name + to_string(i);
        remove(n.c_str());
    }
}

//PASS 1
//Sorting the buffers in main_memory and storing the sorted records into a temporary file (Runs) 
void Sort_Buffer(vector <Records> buffer){
    //Remember: You can use only [AT MOST] 22 blocks for sorting the records / tuples and create the runs


    
    string temp_File = "dept" + to_string(fileDmarker);
    
    fstream tempma(temp_File.c_str(), ios::out | ios::app);

   // tempma.open(temp_File, ios::out | ios::app);



    sort(buffer.begin(), buffer.end(), [](const Records& a, const Records& b) {
        return a.emp_record.salary < b.emp_record.salary;
    });

    //for (int i = 0; i < buffer.size(); i++){
    //    cout << buffer[i].emp_record.eid << endl;
    //}

    

    for (int i =0; i <buffer.size(); i++){
        //cout << "gang\n";
        tempma << buffer[i].emp_record.eid << "$" << buffer[i].emp_record.ename << "$" << buffer[i].emp_record.age << "$" << buffer[i].emp_record.salary << "$" << endl;
    }
    






    fileDmarker++;

    

}

//PASS 2
//Use main memory to Merge the Runs 
//which are already sorted in 'runs' of the relation Emp.csv 

/*Records writeRecordToFile(ifstream& inputFile, ofstream &outputFile, char delimeter){
    Records emp;

    string word;
    
    getline(inputFile, word,delimeter);               
    emp.emp_record.eid = stoi(word);
    getline(inputFile, word, delimeter);
    emp.emp_record.ename = word;
    getline(inputFile, word, delimeter);
    emp.emp_record.age = stoi(word);
    getline(inputFile, word, delimeter);
    emp.emp_record.salary = stod(word);

    return emp;
}
*/

Records getRecord(ifstream& inputFile, char delimeter ){
    
    
    Records emp;

    string word;
    
    getline(inputFile, word,delimeter);    
  //  cout << "eid " <<  word << endl;           
    emp.emp_record.eid = stoi(word);
    getline(inputFile, word, delimeter);
  //  cout << "name " <<  word << endl;
    emp.emp_record.ename = word;
    getline(inputFile, word, delimeter);
   // cout << "age " <<  word << endl;
    emp.emp_record.age = stoi(word);
    getline(inputFile, word, delimeter);
  //  cout << "salary " <<  word << endl;
    emp.emp_record.salary = stod(word);

    return emp;
    
    
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

void copyFile(const std::string& sourceFile, const std::string& destinationFile) {
    std::ifstream source(sourceFile, std::ios::binary);
    

    std::ofstream destination(destinationFile, std::ios::binary);
   

    std::string line;
    while (std::getline(source, line)) {
        destination << line << "\n";
    }
    source.close();
    destination.close();
}

int writeRestOfFile(std::ifstream& source, std::ofstream& destination) {
    std::string line;
    int lines_written = 0;
    while (std::getline(source, line)) {
        if(line ==""){
            continue;
        }
        lines_written++;
        destination << line << "\n";
    }
    return lines_written;
}

bool hasRecordsLeft(int currentLine, int targetLine){
    if(currentLine == targetLine){
        return false;
    }
    return true;
}

void Merge_Runs(){






    for (int i = 1; i < fileDmarker; i++){


        int recordCountEmpA = 0;
        int recordCountEmpB = 0;
        int totalRecordEmpA = 0;
        int totalRecordEmpB = 0;

        ofstream outfile("fileout");
        //tally up totalrecords in each file
       totalRecordEmpA = countLines("dept0");
       totalRecordEmpB = countLines("dept"+to_string(i));

        cout << "Total Records in EmpA: " << totalRecordEmpA << " Total Records in EmpB: " << totalRecordEmpB << endl;
        
        ifstream inputb("dept"+to_string(i));
        ifstream inputa ("dept0");
       
        Records empA = getRecord(inputa, '$');
        Records empB = getRecord(inputb, '$');
        bool hasInputA = true;
        bool hasInputB = true;
        int countOfRecordsWritten = 0;
        while (hasInputA && hasInputB)
        {

            if (empA.emp_record.salary < empB.emp_record.salary){
                outfile << empA.emp_record.eid << "$" << empA.emp_record.ename << "$" << empA.emp_record.age << "$" << empA.emp_record.salary << "$" << endl;
                countOfRecordsWritten++;
                recordCountEmpA++;
                hasInputA = hasRecordsLeft(recordCountEmpA, totalRecordEmpA);
                if(!hasInputA)break;
                empA = getRecord(inputa, '$');

            }
            else{
                outfile << empB.emp_record.eid << "$" << empB.emp_record.ename << "$" << empB.emp_record.age << "$" << empB.emp_record.salary << "$" << endl;
                countOfRecordsWritten++;
                recordCountEmpB++;
                hasInputB = hasRecordsLeft(recordCountEmpB, totalRecordEmpB);
                if(!hasInputB)break;
                empB = getRecord(inputb, '$');
                
            } 
        }
        cout << hasInputA << " " << hasInputB << endl;;
        if (hasInputB)
        {
           outfile << empB.emp_record.eid << "$" << empB.emp_record.ename << "$" << empB.emp_record.age << "$" << empB.emp_record.salary << "$" << endl;
           countOfRecordsWritten++;
           int x = writeRestOfFile(inputb,outfile);
           countOfRecordsWritten+=x;
            
        }

        if (hasInputA)

        {
            outfile << empA.emp_record.eid << "$" << empA.emp_record.ename << "$" << empA.emp_record.age << "$" << empA.emp_record.salary << "$" << endl;
            countOfRecordsWritten++;
            int x = writeRestOfFile(inputa,outfile);
           countOfRecordsWritten+=x;   
        }

/////////////////////idk how tf this works
        inputa.close();
        inputb.close();
        outfile.close();
        copyFile("fileout","dept0");
        remove("fileout");
    
    //copy fileout to temp0
    //outfile.close();
    //remove("temp0");
    //rename("fileout", "temp0");




        


    }

    

    

}

void PrintSorted(){

    //Store in EmpSorted.csv
    

    ofstream outfile("deptSorted.csv");
    ifstream infile("dept0");

    string line;
    while(getline(infile, line)){
        string output;
        for(int i =0; i < line.size()-1;i++){
            if(line[i] == '$'){
                output=output+',';
            }
            else{
                output+=line[i];
            }

        }
        //line[line.size()-1] = '\n';
        output+='\n';
        outfile << output;
    }
    
    //deleteFiles("temp", 1000);
    return;
}



int main() {

    deleteFiles("dept", 1000);
    //Open file streams to read and write
    //Opening out the Emp.csv relation that we want to Sort
    fstream empin;
    empin.open("Dept.csv", ios::in);

    
    
   
    //Creating the EmpSorted.csv file where we will store our sorted results
    fstream SortOut;
   // SortOut.open("DeptSorted.csv", ios::out | ios::app);

    //Grab the first 22 blocks of Emp.csv and store them in the bufferp   
    int value = 0;
    int records_read =0;
    vector <Records> buffer;
    while (value!= -1){
        Records emp;

        
        for (int i = 0; i< buffer_size; i++){
            
            emp = Grab_Emp_Record(empin);
            value = emp.no_values;
            if (value == -1){
            
                cout << "Value: \n" << value << "Records read: " << records_read<< endl;
                break;
            }
            buffer.push_back(emp);
            records_read++;
            
            //cout << emp.emp_record.age << " " <<emp.emp_record.eid << " " << emp.emp_record.ename << " " << emp.emp_record.salary << endl;

        }
        
        

        Sort_Buffer(buffer);
        buffer.clear();
        
        

    }

    
    //Merge_Runs();

    //PrintSorted();


    //1. Create runs for Emp which are sorted using Sort_Buffer()
    //create n^4 temp files


    

    






    //2. Use Merge_Runs() to Sort the runs of Emp relations 
    // and store the sorted results in EmpSorted.csv
    
    


    //Please delete the temporary files (runs) after you've sorted the Emp.csv
    // fuck no


    return 0;
}
