#include "the3.h"

// do not add extra libraries, but you can define helper functions below.
int count_glob = 0;
int compare(char a, char b, int mismatch, int match) {
  if (a == b) 
    return match;
  else 
    return -mismatch;
}

/* 
PART 1
you are expected to call recursive_alignment (as the name suggests) recursively to find an alignment. 
initial call_count value given to you will be 0.
you should check if call_count >= 1000000, if so, set possible_alignment string to "STACK LIMIT REACHED", return INT_MIN (or anything - it will not be checked).
*/

int recursive_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment, int call_count) {
    count_glob++;
    int highest_alignment_score;
    call_count = count_glob;
    if (call_count >= 1000000) {
        possible_alignment = "STACK LIMIT REACHED";
        return INT_MIN;
    }

    if (sequence_A.empty()) {
        possible_alignment += std::string(sequence_B.length(), '_');
        return -gap * sequence_B.length();
    }

    if (sequence_B.empty()) {
        possible_alignment += std::string(sequence_A.length(), '.');
        return -gap * sequence_A.length();
    }
    
    int score_match_mismatch ;
    if(sequence_A.back() == sequence_B.back())
        score_match_mismatch = match + recursive_alignment(sequence_A.substr(0, sequence_A.length() - 1), sequence_B.substr(0, sequence_B.length() - 1), gap, mismatch, match, possible_alignment, call_count);
    else
        score_match_mismatch = -mismatch + recursive_alignment(sequence_A.substr(0, sequence_A.length() - 1), sequence_B.substr(0, sequence_B.length() - 1), gap, mismatch, match, possible_alignment, call_count);
  
    std::string alignment_match_mismatch;
    if(sequence_A.back() == sequence_B.back())
        alignment_match_mismatch = possible_alignment + sequence_A.back();
    else
        alignment_match_mismatch = possible_alignment + '!';
        

    std::string temp_align_A;
    int score_gap_A = -gap + recursive_alignment(sequence_A, sequence_B.substr(0, sequence_B.length() - 1), gap, mismatch, match, temp_align_A, call_count);
    temp_align_A += '_';

    std::string temp_align_B;
    int score_gap_B = -gap + recursive_alignment(sequence_A.substr(0, sequence_A.length() - 1), sequence_B, gap, mismatch, match, temp_align_B, call_count);
    temp_align_B += '.';
    if (count_glob > 1000000)
    {
        possible_alignment = "STACK LIMIT REACHED";
        return INT_MIN;
    }
    
    if (score_match_mismatch >= score_gap_A && score_match_mismatch >= score_gap_B) 
    {
        possible_alignment = alignment_match_mismatch;
        highest_alignment_score = score_match_mismatch;
    } 
    else if (score_gap_A >= score_gap_B) 
    {
        possible_alignment = temp_align_A;
        highest_alignment_score = score_gap_A;
    } 
    else 
    {
        possible_alignment = temp_align_B;
        highest_alignment_score = score_gap_B;
    }
    
    return highest_alignment_score;
}



/* 
PART 2
you are expected to create a dynamic programming table to find the highest alignment score. 
then you will need to reconstruct a possible alignment string from the table.
*/
int dp_table_alignment(std::string sequence_A, std::string sequence_B, int gap, int mismatch, int match, std::string &possible_alignment){

    int** dp_table;
    dp_table = new int* [sequence_A.length()+1];
    for (int i = 0; i < sequence_A.length()+1; i++) {
      dp_table [i] = new int [sequence_B.length()+1];
    }
    int highest_alignment_score;

    for(int i = 0; i <= sequence_A.length(); i++)
        dp_table[i][0] = -i * gap;
    for(int j = 0; j <= sequence_B.length(); j++)
        dp_table[0][j] = -j * gap;

    for(int i = 1; i <= sequence_A.length(); i++) 
    {
        for(int j = 1; j <= sequence_B.length(); j++) 
        {
            int temp_score;
            if(sequence_A[i-1] == sequence_B[j-1])
                temp_score = match;
            else
                temp_score = -mismatch;
                
            dp_table[i][j] = std::max({dp_table[i-1][j-1] + temp_score, dp_table[i-1][j] - gap, dp_table[i][j-1] - gap});
        }
    }

    int i = sequence_A.length(), j = sequence_B.length();
    while(i > 0 && j > 0) 
    {
        if(dp_table[i][j] == dp_table[i-1][j-1] + ((sequence_A[i-1] == sequence_B[j-1]) ? match : -mismatch)) 
        {
            if(sequence_A[i-1] == sequence_B[j-1])
                possible_alignment = sequence_A[i-1] + possible_alignment;
            else
                possible_alignment = "!" + possible_alignment;
            i--;j--;
        } 
        else if(dp_table[i][j] == dp_table[i-1][j] - gap) 
        {
            possible_alignment = "." + possible_alignment;
            i--;
        } else 
        {
            possible_alignment = "_" + possible_alignment;
            j--;
        }
    }

    for( ; i > 0; i--) 
        possible_alignment = "." + possible_alignment;
    
    for( ; j > 0; j--) 
        possible_alignment = "_" + possible_alignment;
        
    highest_alignment_score = dp_table[sequence_A.length()][sequence_B.length()];
    return highest_alignment_score;   
}
