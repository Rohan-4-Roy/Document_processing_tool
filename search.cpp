// Do NOT add any other includes
#include "search.h"
vector <int> bad_table_vector(string &pattern);
vector<int> boyer_moore(string &sentence, string &pattern);

SearchEngine::SearchEngine(){
    // Implement your function here  
}

SearchEngine::~SearchEngine(){
    // Implement your function here  
    long long s=text.size();
    for(long long i=0; i<s; i++){
        delete text[i];
        text[i]=nullptr;
    }
    text.clear();
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here  
    Textnode* newNode= new Textnode(book_code, page, paragraph, sentence_no, sentence);
    text.push_back(newNode);
    return;
}

Node* SearchEngine::search(string pattern, int& n_matches){
    // Implement your function here
    Node *res=new Node(); 
    Node* temp=new Node();
    res->right=temp;
    temp->left=res;
    for(long long i=0;i<text.size();i++){
        vector<int> v=boyer_moore(text[i]->sentence,pattern);
        if(v.size()==0) continue;
        for(int j=0;j<v.size();j++)
        {
            n_matches++;
            temp->book_code=text[i]->book_code;
            temp->page=text[i]->page;
            temp->paragraph=text[i]->paragraph;
            temp->sentence_no=text[i]->sentence_no;
            temp->offset=v[j];
            temp->right=new Node();
            temp->right->left=temp;
            temp=temp->right;
        }

    }
    if(temp->left==res&&temp->paragraph==-1)
    return nullptr;
    temp=temp->left;
    delete temp->right;
    temp->right=nullptr;


    Node* ans=res->right;
    ans->left=nullptr;
    return ans;
}



 vector <int> bad_table_vector(string &pattern){
        // Assumption- only english letters in lowercase and space
        int n=pattern.size();
        vector<int> bad_table(37, -1);
        // Space is 37th
        for(int i=0; i<n; i++){
            if('a'<=pattern[i] && pattern[i]<='z'){
                int index=pattern[i]-'a';
                bad_table[index]=i;
            }
            else if(pattern[i]==' '){
                bad_table[36]=i;
            }
            else if('0'<=pattern[i] && pattern[i]<='9'){
                int index=pattern[i]-'0'+26;
                bad_table[index]=i;
            }
        }
        return bad_table;
    }

    vector<int> boyer_moore(string &sentence, string &pattern){
        int m=pattern.length();
        int n=sentence.length();
        vector<int> offsets;
        if(m>n)
        return offsets;
        vector<int> bct=bad_table_vector(pattern);
        int s=0;
        while(s<=n-m){
            int j=m-1;
            while(j>=0&&pattern[j]==sentence[s+j]){
                j=j-1;
            }
            if(j<0){
                offsets.push_back(s);
                if(s+m<n){
                    int bct_value;
                    if('a'<= sentence[s+m] && sentence[s+m]<'z') bct_value=bct[sentence[s+m]-'a'];
                    else if(sentence[s+m]==' ') bct_value=bct[36];
                    else if('0'<= sentence[s+m] && sentence[s+m]<'9') bct_value=bct[sentence[s+m]-'0'+26];
                    else bct_value=-1;
                    
                    s+=m-bct_value;
                }
                else{
                    s+=1;
                }
            }
            else{
                int bct_value;
                if('a'<= sentence[s+m] && sentence[s+m]<'z') bct_value=bct[sentence[s+m]-'a'];
                else if(sentence[s+m]==' ') bct_value=bct[36];
                else if('0'<= sentence[s+m] && sentence[s+m]<'9') bct_value=bct[sentence[s+m]-'0'+26];
                else bct_value=-1;

                s+=max(1, j-bct_value);
            }            
        }
        return offsets;

    }