// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    // Implement your function here
    root= new TrieNode();
}

Dict::~Dict(){
    // Implement your function here 
    delete root;
    root=nullptr;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    string separators= ". , - : ! \" \' ( ) ? — [ ] “ ” ‘ ’ ˙ ; @";
    string word="";
    int s=sentence.size();
    for(int i=0; i<s ; i++){
        if(separators.find(sentence[i])!=string :: npos){
            if(word!="") insert_word(word);
            word="";
        }
        else if('a'<=sentence[i] && sentence[i]<='z') word+=sentence[i];
        else if('A'<=sentence[i] && sentence[i]<='Z') word+=sentence[i]-'A'+'a';
        else if('0'<=sentence[i] && sentence[i]<='9') word+=sentence[i];
    }
    insert_word(word);
    return;
}

int Dict::get_word_count(string word){
    // Implement your function here
    string w="";
    //ASK IF THE WORD IS VALID OR NOT IE DOES NOT HAVE ANY PUNCTUATION MARKS
    int s=word.size();
    for(int i=0; i<s ;i++){
        char ch=word[i];
        //////////////////////////////
        if(ch<'a'&&ch>='A')
        ch=tolower(ch);
        w=w+ch;
    }
    word=w;
    //ASSUMING WORD IS IN LOWERCASE
    TrieNode* temp=root;
    for(int i=0;i<word.length();i++){
        int pos;
        if('a'<=word[i] && word[i]<='z')
         pos=word[i]-'a';
        else if('0'<=word[i] && word[i]<='9')
         pos=word[i]-'0'+26;
        if(temp->alphabets[pos]==nullptr){
            return -1;//Check this once on piazza
        }
        temp=temp->alphabets[pos];
    }
    if(temp->endofword==false)
    return -1;//Check this once on piazza
    else
    return temp->count;

}

void Dict::dump_dictionary(string filename){
    // Implement your function here
    TrieNode *temp=root;
    recursive_print(temp, "", filename);
    // for(int i=0;i<36;i++){
    //     if(temp->alphabets[i]!=nullptr)
    //     if(temp->)
    //     recursive_print(temp->alphabets[i],"",filename);
    // }
    return;
}

void Dict::insert_word(string &word){
    // pre processed word
    TrieNode* node=root;
    int s=word.size();
    for(int i=0; i<s; i++){
        int index;
        if('a'<=word[i] && word[i]<='z') index=word[i]-'a';
        else index=word[i]-'0'+26;
        if(node->alphabets[index]==nullptr){
            node->alphabets[index]=new TrieNode();
        }
        node=node->alphabets[index];
    }
    node->endofword=true;
    node->count++;
}

void Dict:: recursive_print(TrieNode* node, string currword, string &filename){
    if(node->endofword){
        fstream file(filename, ios::app);
        file<<currword<<", "<<node->count<<'\n';//ASK IF THE FILE MUST BE EMPTY BEFORE FUNC CALL
        file.close();
    }
    for(int i=0;i<36;i++){
        if(node->alphabets[i]!=nullptr){
            char ch;
            if(0<=i && i<=25) ch=i+'a';
            else ch=i-26+'0';
            string newword=currword+ch;
            recursive_print(node->alphabets[i], newword, filename);
            newword.clear();
        }
    }
    currword.clear();
}

///// [a]