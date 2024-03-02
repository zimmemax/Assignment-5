#include <bits/stdc++.h>
#include "record_class.h"
#include <fstream>
#include <cstdio>
#include <iostream>
using namespace std;
#define buffer_size 22


void deleteFiles(string name, int numFiles);
void Sort_Buffer(vector <Records> buffer);
Records getRecord(ifstream& inputFile, char delimeter );
int countLines(string filename);
void copyFile(const std::string& sourceFile, const std::string& destinationFile);
int writeRestOfFile(std::ifstream& source, std::ofstream& destination);
bool hasRecordsLeft(int currentLine, int targetLine);
void merge_runs();
void PrintSorted();







