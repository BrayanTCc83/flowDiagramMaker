#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include "../FDM_pseudo_instructions.hpp"
#include "FDM_TableKeyword.hpp"

using namespace FDM_Keywords;

bool TableKeyword::loaded = false;

/**
 * Returns a instance of the TableKeywords in the specified languaje
 * 
 * @param languaje  The specified language to be used @see LANG
 * @return          The class table with access to the keywords in the languaje
*/
TableKeyword *TableKeyword::GetTable(LANG languaje) {
    return new TableKeyword(languaje);
}

/**
 * Instance the table with the languaje indicated, if the tables are loaded only instance
 * the class, in other way loads the content of the tables in each languaje
 * 
 * @param languaje  The specified languaje to be used @see LANG
*/
TableKeyword::TableKeyword(LANG languaje) {
    this->lang = languaje;
    if(!TableKeyword::loaded)
        TableKeyword::LoadContent();
}

/**
 * Avaible load the content of the keywords file, to do this read the file line by line, then
 * split each line in the words that contain, as each column is a languaje @see LANG, then save
 * it in its table.
*/
void TableKeyword::LoadContent() {
    ifstream *inputFile = new ifstream("C:/Users/btell/OneDrive/Escritorio/UNAM/flowDiagramMaker/flowDiagramMaker/src/common/compilers/pseudo/lang/keywords.txt");
    string reads;
    getline(*inputFile, reads);
    while(!inputFile->eof()){
        getline(*inputFile, reads);
        stringstream ss(reads);
        string word;
        int column = 0;
        while (ss >> word)
            tables[column++].push_back(word);
    }
}

/**
 * Gets the keyword indicates in the languaje of the table @see LANG
 * 
 * @param instruction   The instruction to be getted by the method @see INSTRUCTIONS
 * @return              The string keyword requested in their languaje
*/
string TableKeyword::GetKeyword(INSTRUCTIONS instruction) {
    return tables[this->lang].at(instruction);
}

/**
 * Show in console all the keywods in its languaje @see LANG
*/
void TableKeyword::ListAll() {
    for(int i = 0; i < INSTRUCTIONS_COUNT; i++)
        cout << tables[this->lang].at(i) << endl;
}