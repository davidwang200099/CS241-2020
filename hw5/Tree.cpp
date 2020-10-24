#include "Tree.h"

bool operator==(const kdNode &a, const kdNode &b){
    return (a.key[0]==b.key[0])&&(a.key[1]==b.key[1]);
}
// ==================== k-d tree ======================
kdTree::kdTree(){}

void kdTree::remove(kdNode *r){
    if(hasLChild(r)) remove(r->left);
    if(hasRChild(r)) remove(r->right);
    delete r;
}

void kdTree::insert(kdNode* p, int arr[], int dim){
    if(!root) root=new kdNode(arr);
    else {
        kdNode* &r=search(p, arr, dim);
        if(r) return;
        else{
            r=new kdNode(arr);
        }
    }
}

kdNode* &kdTree::rs(kdNode *&p, int *arr, int dim/*, kdNode* &hot*/) {
    kdNode node(arr);
    if(!p||*p==node) return p;
    //hot=p;
    return rs((node.key[dim]<p->key[dim]?p->left:p->right),arr,(dim+1)%2/*,hot*/);
}

kdNode* &kdTree::search(kdNode* &p, int arr[], int dim){
    return rs(p, arr, dim/*, hot*/);
}

void kdTree::remove(kdNode* p, int arr[], int dim){
    kdNode* &r=search(p,arr,dim);
    if(r&&(*r==kdNode(arr))) {delete r;r=nullptr;}
}

kdNode* kdTree::findMin(kdNode* p, int dimCmp, int dim){
    if(!p) return nullptr;
    kdNode *min=findMin(p->left,dimCmp,(dim+1)%2);
    if(dimCmp!=dim){
        kdNode *rightMin=findMin(p->right, dimCmp, (dim+1)%2);
        if(min&&rightMin)
            min=(min->key[dimCmp]<rightMin->key[dimCmp])?min:rightMin;
        else{
            min=(min?min:rightMin);
        }
    }
    return (min&&min->key[dimCmp]<p->key[dimCmp])?min:p;
}

void kdTree::RS(kdNode *p, int dim, int *lower_bound, int *upper_bound, vector<kdNode *> &v) {
    if(!p) return;
    if(p->key[dim]>=lower_bound[dim]&&p->key[dim]<=upper_bound[dim]){
        if(p->key[1-dim]>=lower_bound[1-dim]&&p->key[1-dim]<=upper_bound[1-dim]) v.push_back(p);
        if(p->left) RS(p->left, 1-dim, lower_bound, upper_bound, v);
        if(p->right) RS(p->right, 1-dim, lower_bound, upper_bound, v);
    }else{
        if(p->key[dim]<lower_bound[dim]&&p->right) RS(p->right, 1-dim, lower_bound, upper_bound, v);
        else if(p->key[dim]>upper_bound[dim]&&p->left) RS(p->left, 1-dim, lower_bound, upper_bound, v);
    }
}

vector<struct kdNode*> kdTree::rangeSearch(kdNode* p, int dim, int lower_bound[], int upper_bound[]){
    vector<struct kdNode*> v;
    //if((p->key[0]<lower_bound[0]||p->key[0]>upper_bound[0])||(p->key[1]<lower_bound[1]||p->key[1]>upper_bound[1]))
    RS(p,dim, lower_bound, upper_bound, v);
    return v;
}


// ==================== trie (prefix tree) ======================
Trie::Trie() {
    root=new TrieNode;
}

void Trie::insert(const string &word) {
    bool found=Search(word,hot);
    if(found) return;
    auto iter=hot->next.find(word[hot->rank]);
    if(iter==hot->next.end())
        hot->next[word[hot->rank]]=new TrieNode(word);
    else{
        TrieNode *tmp=iter->second;
        TrieNode *n=new TrieNode(word);

        int len1,len2;
        int minlen=((len1=tmp->str.length())<(len2=word.length()))?len1:len2;
        const string &longstr=(len1<len2)?word:tmp->str;

        for(int i=hot->rank;i<minlen&&tmp->str[i]==word[i];i++){
            TrieNode *p=new TrieNode(i+1);
            hot->next[word[hot->rank]]=p;
            hot=p;
        }
        hot->next['$']=(len1<len2)?tmp:n;
        hot->next[longstr[minlen]]=(len1<len2)?n:tmp;
    }
}


bool Trie::Search(const string &word, TrieNode* &hot) {
    TrieNode *r=root;
    for(auto i:word){
        auto iter=r->next.find(i);
        if(iter!=r->next.end()){
            if(iter->second->flag) {hot=r;return iter->second->str==word;}
            else{
                hot=r;
                r=iter->second;
            }
        }else{
            hot=r;
            return false;
        }
    }
    auto iter=r->next.find('$');
    return iter!=r->next.end();
}

bool Trie::search(const string &word) {
    return Search(word, hot);
}

bool Trie::startsWith(const string &prefix) {
    if(!root) return false;
    TrieNode *r=root;
    for(auto i:prefix){
        auto iter=r->next.find(i);
        if(iter==r->next.end()) return false;
        if(!iter->second->flag) r=iter->second;
        else{
            auto len1=prefix.size();
            auto len2=iter->second->str.length();
            if(len1>len2) return false;
            for(auto j=r->rank;j<len1;j++){
                if(iter->second->str[j]!=prefix[j]) return false;
            }
            return true;
        }
    }
    return true;
}

void Trie::remove(TrieNode *p) {
    if(!p) return;
    for(auto i:p->next) remove(i.second);
    delete p;
}

void Trie::traverse(TrieNode *p) {
    if(!p) return;
    if(p->flag) cout<<p->str<<endl;
    else {
        for(auto i:p->next){
            cout<<i.first<<":"<<endl;
            traverse(i.second);
        }
    }
}