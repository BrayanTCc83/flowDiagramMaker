#ifndef FDM_HASH_TABLE_KEYWORD
#define FDM_HASH_TABLE_KEYWORD
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../FDM_pseudo_instructions.hpp"

using namespace std;

/**
 * This namespace includes every content related with de Keywords access, the list of keywords in different 
 * languajes are in the file keywords.txt, and in this file each row, has its equivalent with the enum of 
 * instructions in @see INSTRUCTIONS
*/
namespace FDM_Keywords {
    /**
     * Languajes enum, includes the langs registereds on this program, using two letters to identificates, each
     * languaje is equivalent to a column in file keywords.txt
    */
    typedef enum {
        LANG_EN,                    // Languaje english.
        LANG_ES,                    // Languaje spanish.
        LANG_FR,                    // Languaje french.

        LANG_COUNT                  // Indicates the number of languajes registereds by the moment.
    } LANG;

    static vector<string> tables[LANG_COUNT]; // When the keywords are loaded, the contente are register here.

    /**
     * Get a quick access to the specific keyword in the seleted languaje to its created, can be more of one table
     * created at time.
    */
    class TableKeyword {
        private:
            static bool loaded;
            static void LoadContent();
            LANG lang;
            TableKeyword(LANG languaje);
        public:
            static TableKeyword *GetTable(LANG languaje);
            string GetKeyword(INSTRUCTIONS instruction);
            void ListAll();
    };
};

#endif