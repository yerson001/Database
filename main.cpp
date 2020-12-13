#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <utility>
#include <fstream>
#include <cstdio>
#include <ctime>
#include <algorithm>


#define SMALLER <
#define EQUAL ==
#define GREATER >
template <class T>
class AVLnode {
public:
    T key;
    int balance;
    std::vector< std::string > m_str;
    AVLnode *left, *right, *parent;


    AVLnode(T k, std::string st, AVLnode *p) : key(k), balance(0), parent(p),
                        left(NULL), right(NULL) { m_str.push_back(st); left = 0; right = 0; }

    ~AVLnode() {
        delete left;
        delete right;
    }
};

#include <fstream>
#include <iterator>

template <class T>
class AVLtree {
public:
    AVLtree(std::string mmi, std::string mmc, std::string mmt);
    ~AVLtree(void);
  AVLnode<T> *root;

    std::string m_name_index;
    std::string m_name_col;
    std::string m_name_table;
    bool insert(T key, std::string st);
    void deleteKey(const T key);
    void printBalance();
    void inOrder() ;
    void writeFile(std::ofstream& file);
    void writeFile2(std::ofstream& file,std::string);

    std::vector< std::string > find (T tem);
  AVLnode<T>* build_from_vec(std::vector<std::string> values, AVLnode<T>*& cur);
  AVLnode<T>* build_from_vec2(std::vector<std::string> values, int start, int end);
  void printPreorder(AVLnode<T>* cur);

private:

    AVLnode<T>* rotateLeft          ( AVLnode<T> *a );
    AVLnode<T>* rotateRight         ( AVLnode<T> *a );
    AVLnode<T>* rotateLeftThenRight ( AVLnode<T> *n );
    AVLnode<T>* rotateRightThenLeft ( AVLnode<T> *n );
    void rebalance                  ( AVLnode<T> *n );
    int height                      ( AVLnode<T> *n );
    void setBalance                 ( AVLnode<T> *n );
    void printBalance               ( AVLnode<T> *n );
    void clearNode                  ( AVLnode<T> *n );
    void inOrder                    ( AVLnode<T> *n );
    void writeFile                  (std::ofstream& file, AVLnode<T> *n);
    std::vector< std::string > find (T tem, AVLnode<T> *n);
};

///----------------------------------CPP--------------
#include <sstream>
  std::vector<std::string> valores_t;
void writeFile4(std::string file){

  std::string value, real_value;
  std::ifstream index_file;
  index_file.open(file);
  getline(index_file, value);
    if (index_file.is_open()) {
        while (index_file >> value){
            /*real_value.clear();
            auto it = value.find(";");
            for(int i=0; i<it; i++ ){
                real_value += value[i];
            }*/

            //std::cout << real_value<<std::endl;
            valores_t.push_back(value);
            /*if(real_value != valor){
                values.push_back(value);
           }*/
        }
    }
    index_file.close();

   // for(int i=0; i<valores_t.size(); i++ ){
  //      std::cout <<valores_t[i]<<std::endl;    } 
}


int stringToInt2(std::string a){
  int ret;
  std::stringstream convi(a);
  convi >> ret;
  return ret;
}

/* AVL class definition */

template <class T>
void AVLtree<T>::rebalance(AVLnode<T> *n) {
    setBalance(n);

    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }

    if (n->parent != NULL) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateLeft(AVLnode<T> *a) {
    AVLnode<T> *b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != NULL)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateRight(AVLnode<T> *a) {
    AVLnode<T> *b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != NULL)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateLeftThenRight(AVLnode<T> *n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}

template <class T>
AVLnode<T>* AVLtree<T>::rotateRightThenLeft(AVLnode<T> *n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}

template <class T>
int AVLtree<T>::height(AVLnode<T> *n) {
    if (n == NULL)
        return -1;
    return 1 + std::max(height(n->left), height(n->right));
}

template <class T>
void AVLtree<T>::setBalance(AVLnode<T> *n) {
    n->balance = height(n->right) - height(n->left);
}

template <class T>
void AVLtree<T>::printBalance(AVLnode<T> *n) {
    if (n != NULL) {
        printBalance(n->left);
        std::cout << n->balance << " ";
        printBalance(n->right);
    }
}

template <class T>
AVLtree<T>::AVLtree(std::string mmi, std::string mmc, std::string mmt) : root(NULL) {
    m_name_index = mmi;
    m_name_col = mmc;
    m_name_table = mmt;
    std::cout << ">"<<m_name_index <<"  "<< m_name_col <<" "<<m_name_table <<std::endl;
  root = 0;
}

template <class T>
AVLtree<T>::~AVLtree(void) {
    delete root;
}

template <class T>
bool AVLtree<T>::insert(T key, std::string st) {
    if (root == NULL) {
        root = new AVLnode<T>(key, st, NULL);
    }
    else {
        AVLnode<T>*n = root,*parent;

        while (true) {
            if (n->key == key)
            {
                n->m_str.push_back(st);
                return false;
            }

            parent = n;

            bool goLeft = n->key > key;
            n = goLeft ? n->left : n->right;

            if (n == NULL) {
                if (goLeft) {
                    parent->left = new AVLnode<T>(key, st, parent);
                }
                else {
                    parent->right = new AVLnode<T>(key, st, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }
  if (stringToInt2(key) % 10000 == 0)
     std::cout << "Value " << key << " inserted.\n";
  //printBalance();
  //inOrder();
    return true;
}

template <class T>
void AVLtree<T>::deleteKey(const T delKey) {
    if (root == NULL)
        return;

    AVLnode<T>
        *n       = root,
        *parent  = root,
        *delNode = NULL,
        *child   = root;

    while (child != NULL) {
        parent = n;
        n = child;
        child = delKey >= n->key ? n->right : n->left;
        if (delKey == n->key)
            delNode = n;
    }

    if (delNode != NULL) {
        delNode->key = n->key;

        child = n->left != NULL ? n->left : n->right;

        if (root->key == delKey) {
            root = child;
        }
        else {
            if (parent->left == n) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }

            rebalance(parent);
        }
    }
}

template <class T>
void AVLtree<T>::printBalance() {
    printBalance(root);
    std::cout << std::endl;
}

template <class T>
void AVLtree<T>::inOrder()
{
    inOrder(root);
    std::cout << std::endl;
}

template <class T>
void AVLtree<T>::inOrder(AVLnode<T> *n)
{
    if(n != NULL)
    {
        inOrder(n->left);
        std::cout << n->key << " " <<n->m_str.size() << std::endl;
        inOrder(n->right);
    }
}
#include <unordered_set>
void remove(std::vector<std::string> &v){
	std::vector<std::string>::iterator itr = v.begin();
	std::unordered_set<std::string> s;
	for (auto curr = v.begin(); curr != v.end(); ++curr) {
		if (s.insert(*curr).second)
			*itr++ = *curr;
	}
	v.erase(itr, v.end());
}
bool sortinrev(const std::pair<int,std::string> &a,const std::pair<int,std::string> &b){ 
       return (a.first < b.first); 
} 
  
std::vector<std::pair<int,std::string> > real;
void all_fun(std::string file){

  std::string value, real_value;
  std::ifstream index_file;
  index_file.open(file);
  getline(index_file, value);
    if (index_file.is_open()) {
        while (index_file >> value){
            real_value.clear();
            auto it = value.find(";");
            for(int i=0; i<it; i++ ){
                real_value += value[i];
            }

            //std::cout << real_value<<"------"<<value<<std::endl;
            real.push_back(make_pair(stringToInt2(real_value),value));
            sort(real.begin(), real.end(), sortinrev); 
      //      if(real_value != value){
      //          valores_t.push_back(value);
       //    }
        }
    }
    index_file.close();

    for(int i=0; i<real.size(); i++ ){
        std::cout <<real[i].first<<"   "<<real[i].second<<std::endl;    } 

}
template <class T>
void AVLtree<T>::writeFile(std::ofstream& file){
  file << m_name_table << ',' << m_name_col << '\n';
    writeFile(file, root);
}


template <class T>
void AVLtree<T>::writeFile2(std::ofstream& file,std::string name_index){
  std::ofstream ofs;
  writeFile4(name_index);
    ofs.open(name_index, std::ofstream::out | std::ofstream::trunc);
    ofs.close(); 
    std::cout << "ACTUALIZANDO"<<std::endl;
    file << m_name_table << ',' << m_name_col << '\n';
    writeFile(file, root);
    //remove(valores_t);
    for(int i=0; i<valores_t.size(); i++){
        file << valores_t[i] <<std::endl;
    }
    valores_t.clear();
    writeFile4(name_index);
    ofs.open(name_index, std::ofstream::out | std::ofstream::trunc);
    ofs.close(); 
    remove(valores_t);
     file << m_name_table << ',' << m_name_col << '\n';
    for(int i=0; i<valores_t.size(); i++){
        file << valores_t[i] <<std::endl;
    }
    valores_t.clear();
    all_fun(name_index);
    ofs.open(name_index, std::ofstream::out | std::ofstream::trunc);
    ofs.close(); 
    file << m_name_table << ',' << m_name_col << '\n';
    for(int i=0; i<real.size(); i++){
        file << real[i].second<<std::endl;
    }
    real.clear();
}


template <class T>
void AVLtree<T>::writeFile(std::ofstream& file, AVLnode<T> *n){
    if(n != NULL){
        writeFile(file, n->left);
        file << n->key;
        for (int i = 0; i < n->m_str.size(); i++){
            file << ';' << n->m_str[i];
        }
        file << '\n';
        writeFile(file, n->right);
    }
  
}

template <class T>
std::vector< std::string > AVLtree<T>::find(T tem) {
    //std::cout << "root value: " << this->root->key << '\n';
    return find(tem, this->root);
}

template <class T>
std::vector< std::string > AVLtree<T>::find(T tem, AVLnode<T> *n) {
    std::vector< std::string > r;
    r.push_back("-1"); //change if wanting to cheat because stupid crap fails with small id's for some reason
  //std::cout << "cur key: " << n->key << ", looking for: " << tem << std::endl;
    while (n != NULL) {
    //std::cout << "cur key: " << n->key << ", looking for: " << tem << std::endl;
        //std::cout << n->key << std::endl;
        if (n->key == tem) {
            return n->m_str;
        }
        else if(n->key > tem) {
            n = n->left;
        }
        else
            n = n->right;
    }
  //std::cout << "column: " << r.at(0);
    return r;
}

template <class T>
AVLnode<T>* AVLtree<T>::build_from_vec(std::vector<std::string> values, AVLnode<T>*& cur){
  //std::cout << "values size: " << values.size() << std::endl;
  if (values.size() <= 0){
  //	std::cout << "null\n";
    return NULL;
  }
  if (values.size() == 1){
    return (new AVLnode<T>(values.at(0), values.at(0), 0));
  }
  //std::vector<std::string> left_values, right_values;

  int mid = values.size() / 2;
  //int mid = (values.size()) >> 1;
  cur = new AVLnode<T>(values.at(mid),values.at(mid), 0);

  //std::copy(values.begin(), values.begin() + mid, std::back_inserter(left_values));
  /*for (int i = 0; i < mid; i++){
    left_values.push_back(values.at(i));
  }*/

  std::vector<std::string> left_values(values.begin(), values.begin() + mid);
  cur->left = build_from_vec(left_values, cur->left);

  /*for (int i = mid + 1; i < values.size(); i++){
    right_values.push_back(values.at(i));
  }*/

  //std::copy(values.begin() + mid + 1, values.end(), std::back_inserter(right_values));
  std::vector<std::string> right_values(values.begin() + mid + 1, values.end());
  cur->right = build_from_vec(right_values, cur->right);

  return cur;

  return root;
}

template <class T>
AVLnode<T>* AVLtree<T>::build_from_vec2(std::vector<std::string> values, int start, int end){
  if (start > end) return NULL;
  AVLnode<T>* cur;
  int mid = (start + end)/2;
  if (start == 0 && end == values.size() - 1){
    root = cur;
  }
  if (mid%10000 == 0) std::cout << "cur_mid: " << mid << std::endl;
  cur = new AVLnode<T>(values.at(mid), values.at(mid), 0);

  cur->left = build_from_vec2(values, start, mid-1);

  cur->right = build_from_vec2(values, mid+1, end);

  return cur;
}

template class AVLtree<std::string>;

template <class T>
void AVLtree<T>::printPreorder(AVLnode<T>* cur){
  if (cur){
    std::cout << "current node: " << cur->key << ' ';
    int a;
    std::cin >> a;
    if (cur->left) std::cout << "left: " << cur->left->key << ' ';
    if (cur->right) std::cout << "right: " << cur->right->key << ' ';
    printPreorder(cur->left);
    printPreorder(cur->right);
  }
}

///--------------------------------------------------

//previous definitions of future implementations

class Table;
struct VCHAR;

//types

typedef std::string str;
typedef long long LL;
typedef unsigned int u_int;
typedef unsigned short u_short;
typedef std::pair <str, str> str_pair; //pair: type, name
typedef std::pair <str, u_int> char_name; //pair: name_of_VARCHAR, bytes
typedef std::vector<str_pair> strp_vec;
typedef std::vector<char_name> char_name_vec;
typedef std::vector<Table*> table_vec;
typedef std::vector<u_int> uint_vec;
typedef std::vector<VCHAR*> vchar_vec;
typedef std::vector<str> str_vec;
typedef std::vector<int> int_vec;
typedef std::stringstream ss;
typedef std::ofstream txt_file;
typedef std::ifstream read_file;
typedef AVLtree<std::string> str_tree;
typedef std::vector<str_tree*> tree_vec;

//-----------la clase functions---------------
u_int stringToUint(str a);
int rdtsc();
int rand_between(int a, int b);
int stringToInt(str a);
str intToString(int a);
LL stringToLL(str a);
void print_vec(strp_vec vec, char_name_vec cvec);
void writeInsert(txt_file& file, str_vec t);
void write_multiple(txt_file& file, read_file& file2, str_vec t);
int findInArray(char to_be_found, char* to_look, int size);
str updateRow(str temp, uint_vec position, str_vec values);
//-------------cpp of function--------------------
#define ROWS_TO_INSERT 20

int rdtsc(){
  __asm__ __volatile__("rdtsc");
}

u_int stringToUint(str a){
  u_int ret;
  ss convi(a);
  convi >> ret;
  return ret;
}

int stringToInt(str a){
  int ret;
  ss convi(a);
  convi >> ret;
  return ret;
}

str intToString(int a){
  str ret;
  ss leString;
  leString << a;
  return leString.str();
}

LL stringToLL(str a){
  LL ret;
  ss convi(a);
  convi >> ret;
  return ret;
}

int rand_between(int a, int b){
  srand( rdtsc() );
  return rand() % b + a;
}

void print_vec(strp_vec vec, char_name_vec cvec){
  int j = 0;
  for(int i = 0; i < vec.size(); i++){
    std::cout << "Tipo de dato: " << vec.at(i).first << '\n';
    std::cout << "Nombre de la columna: " << vec.at(i).second << '\n';
    if (vec.at(i).first == "VARCHAR" ){
      std::cout << "El VARCHAR es de " << cvec.at(j).second << std::endl;
      j++;
    }
    std::cout << std::endl;
  }

}

void writeInsert(txt_file& file, str_vec t){
  str temp;
  temp.clear();
  for (int i = 0; i < t.size(); i++){
    if (i != t.size() - 1) temp += (t.at(i) + ',');
      //file << t.at(i) << ',';
    else temp += (t.at(i) + ' ');
      //file << t.at(i) << ' ';
  }
  while (temp.size() <= 59) temp += ' ';
  temp += '\n';
  file << temp;
  //file << '\n';
}

//INSERTAR VARIOS EN persona I/R1,100/id nombre ; funciona
void write_multiple(txt_file& file, read_file& file2, str_vec t){
 //***********************************************
  for(int i=0; i<t.size(); i++){
    std::cout <<t[i];
  }std::cout<<std::endl;std::cout << "1-------------------"<<std::endl;
  //**********************************************

  int_vec a, b; //random numbers
  int rands = 0, j, k, num_char = 0;
  str num, le_text;
  str_vec chars;
  uint_vec what_to_insert; //0: Incrementer, 1: Random, 2: char
  bool char_inserted;
  for(int i = 0; i < t.size(); i++){
    if (t.at(i)[0] == 'I')
       what_to_insert.push_back(0);
    else if (t.at(i)[0] == 'R'){
          rands++;
          what_to_insert.push_back(1);
    }
     else what_to_insert.push_back(2);
  }




  rands = 0;
  for (int i = 0; i < t.size(); i++){ //getting random numbers
    if (t.at(i)[0] == 'R'){
      num.clear();
      j = 1;
      while (t.at(i)[j] != ','){ //Rnum1,num2
        num += t.at(i)[j++];
      }
      j++;
      a.push_back( stringToInt(num) );
      num.clear();
      while (j < t.at(i).size() ){
        num += t.at(i)[j++];
      }
      b.push_back( stringToInt(num) );
    }
  }
  getline(file2, num);
  std::cout <<"this-> num : " <<num <<std::endl;
  j = 0;
  for (int i = 0; i < what_to_insert.size(); i++){
    char_inserted = 0;
    if (what_to_insert.at(i) == 2){
      k = 0;
      j = 0;
      le_text.clear();
      while((j) < num.size() ){
        if (num[j] == ',' || num[j] == '\n'){
          if (k == i){
            chars.push_back(le_text);
            char_inserted = 1;
          }
          k++;
          j++;
          le_text.clear();
        }
        le_text += num[j];
        j++;
      }
      if (!char_inserted) {
        chars.push_back(le_text);
      }
    }
  }
  for (int i = 0; i < ROWS_TO_INSERT; i++){ //modify this
    rands = 0;
    num_char = 0;
    str lel;
    lel.clear();
    for (j = 0; j < what_to_insert.size(); j++){
      if (what_to_insert.at(j) == 0){
        if (j != what_to_insert.size() - 1) {
          lel += intToString(i+1) + ',';
          //file << i+1 << ',';
        }
        else{
          //file << i+1 << '\n';
          lel += intToString(i+1) + ' ';
        }
      }
      else if (what_to_insert.at(j) == 1){
        if (j != what_to_insert.size() - 1){
          //file << rand_between(a.at(rands), b.at(rands)) << ',';
          lel += intToString(rand_between(a.at(rands), b.at(rands))) + ',';
        }
        else {
          //file << rand_between(a.at(rands), b.at(rands)) << '\n';
          lel += intToString(rand_between(a.at(rands), b.at(rands))) + ' ';
        }
        rands++;
      } else {
        if (j != what_to_insert.size() - 1){
          //file << chars.at(num_char) << i+1 << ',';
          lel += chars.at(num_char) + intToString(i+1) + ',';
        }
        else {
          //file << chars.at(num_char) << i+1 << '\n';
          lel += chars.at(num_char) + intToString(i+1) + ' ';
        }
        num_char++;
      }
    }

    while (lel.size() <= 59)
             lel += ' ';
    lel += '\n';
    file << lel;
    /*if (i != 1000 - 1) file << ',';
    else file << '\n';*/
  }
}


int findInArray(char to_be_found, char* to_look, int size){
  int index;
  for(index = 0; index < size; index++){
    if (to_be_found == to_look[index]) return index;
  }
  return -1; //if it wasn't found
}

str updateRow(str temp, uint_vec position, str_vec values){
  str ret, temp2, temp3;
  bool last_col;
  for (int i = 0; i < position.size(); i++){
    last_col = 1;
    int j = 0, k = 0;
    temp2.clear();
    temp3.clear();
    while (k < temp.size()){
      temp3 += temp[k];
      if (temp[k] == ',' || k == temp.size() - 1){

        if (position.at(i) == j){
          temp2 += values.at(i);
          temp2 += ',';
          last_col = 0;
          //break;
        } else {
          temp2 += temp3;
        }
        //temp2 += ',';
        j++; k++;
        temp3.clear();
        continue;
      }

      k++;
    }
    if (last_col){
      k = temp.size() - 1;
      while (temp[k] != ','){
        k--;
      }
      temp3 += values.at(i);
    }
    temp = temp2;
  }
  while (temp.size() <= 59){
    temp += ' ';
  }
  return temp;
}

//------------struct.h--------------------

struct VCHAR{
  u_int n; //size of char
  char* V_CHAR;
  VCHAR(){
    this->n = 0;
    this->V_CHAR = new char[0];
  }
  VCHAR(u_int n){
    this->n = n;
    this->V_CHAR = new char[n+1];
    V_CHAR[n] = '\0';
  }
};

struct Data{
  LL* NUMBER;
  VCHAR* VARCHAR;
  strp_vec names; //pair: type, name
  char_name_vec vchars;
  u_int n, v,d;
  Data(){
    ;
  }
  Data( u_int n, u_int v,u_int d ,strp_vec names, char_name_vec vchars ){ //n = amount of numbers, v = amount of chars, d = amount of dates
    this->NUMBER = new LL[n];
    this->VARCHAR = new VCHAR[v];
    this->names = names;
    this->vchars = vchars;
    this->n = n;
    this->v = v;
    this->d = d;
  }
  void print_info(){
    print_vec(names, vchars);
  }
};
//----------------table-------------
class Table{
private:
  str name;
  Data* t_data;
public:
  Table(str name, strp_vec& vec, uint_vec nums, char_name_vec& cvec);
  str getName();
  void desc();
  friend void writeTable(txt_file& file, Table* t);
  friend void writeHeaderTable(txt_file& file, Table* t);
};
//-------------table.cpp--------------
Table::Table(str name, strp_vec& vec, uint_vec nums, char_name_vec& cvec){
  this->name = name;
  Data *temp = new Data(nums.at(0), nums.at(1),nums.at(2), vec, cvec);
  this->t_data = temp;
}

str Table::getName(){
  return this->name;
}

void Table::desc(){
  int camps;
  camps = this->t_data->n + this->t_data->v;
  std::cout << "Tabla: " << this->name << '\n';
  std::cout << "TIENE " << camps << " CAMPOS.\n";
  print_vec(this->t_data->names, this->t_data->vchars);
}


void writeTable(txt_file& file, Table* t){
  int j = 0;
  file << t->name << '\n';
  for(int i = 0; i < t->t_data->names.size(); i++){
    file << t->t_data->names.at(i).second << ' '; //STORED: DATA_NAME DATA_TYPE ENDL
    if (t->t_data->names.at(i).first == "VARCHAR" ){
      file << "VARCHAR(" << t->t_data->vchars.at(j).second << ")" << '\n';
      j++;
    } else file << t->t_data->names.at(i).first << '\n'; //TIPO DE DATO
  }
  file << "-----------------------------------------"; //SEPARATION BETWEEN TABLES
  file << '\n' << std::endl;  //so the next one starts at the next line
}

void writeHeaderTable(txt_file& file, Table* t){
  int j = 0;
  str alg;
  alg.clear();
  for(int i = 0; i < t->t_data->names.size(); i++){
    //alg += (t->t_data->names.at(i).second + ',');
    if (i != t->t_data->names.size()-1){
      //file << t->t_data->names.at(i).second << ','; //STORED: DATA_NAME,DATA_NAME,... ENDL
      alg += (t->t_data->names.at(i).second + ',');
    }
    else {
      //file << t->t_data->names.at(i).second;
      alg += t->t_data->names.at(i).second;
    }
  }
  //while (alg.size() <= 59) alg += ' ';
  alg += '\n'; //SEPARATION FOR THE DATA TO BE STORED
  file << alg;
}
//--------------------bd.cpp-----------------

class db{
private:
  table_vec tables;
  tree_vec indices;
  bool query_index, query_where, to_insert, index_eval, id_index;
  str_vec values_to_compare;
  int comparator; //0: EQUAL, 1: GREATER, 2: EQUAL

  bool interpret_query(str query, str& name, strp_vec& vec, char_name_vec& cvec, uint_vec& num);
  bool interpret_query_index(str query, str& name_index, str& name_table, str& name_col);
  bool interpret_query_aRam(str query, str& name_index);
  bool interpret_query_i(str query, str& name, str_vec& values);
  bool interpret_query_s(str query, str& name, str_vec& values, str& column);
  bool interpret_query_d(str query, str& name, str_vec& values, str& column);
  bool interpret_query_u(str query, str& name, str_vec& values, str& column, str_vec& columns);
  bool interpret_query_i_m(str query, str& name, str_vec& values);
  bool interpret_query_i_index(str query, str& name, str_vec& values, str_vec& name_indices, int_vec& num_col, str& num_fila);
  bool interpret_query_d_index(str query, str& name, str_vec& values, str& column, str& name_index, str& num_col);
  bool interpret_query_u_index(str query, str& name, str_vec& values, str_vec& name_indices, str& column, str_vec& columns);

  //str_vec select_query(read_file& file, str_vec columns, str name, str column); //each position at the vec returned is a row of data
  void select_query2(read_file& file, str_tree* m_tree, str column);
  void read_index(read_file& file, str_tree* m_tree);
  void delete_query(read_file& file, txt_file& outfile, str_vec columns, str name, str column);
  void update_query(read_file& file, txt_file& outfile, str_vec columns, str_vec values, str name, str column);

  u_int finding_atribute_type(str type_name, str table_name, int& pos);

public:
  db();
  void i_query(str query); //general interpret query
  void createTable(str query);
  void createIndex(str query);
  void insert_row(str query);
  void insert_row_index(str query);
  void select_data(str query);
  void delete_data(str query);
  void delete_data_index(str query);
  void update_data(str query);
  void update_data_index(str query);
  void insert_multiple(str query);
  void aRam(str query);
  str_vec id_values(char* name);
  str_vec select_query(read_file& file, str_vec columns, str name, str column); //each position at the vec returned is a row of data
};
//**************************************************************
//*************************************************************

str create_tab = "CREATE TABLA ";
str insert_into = "INSERTAR EN "; //11
str insert_index = "INSERTAR CON INDICE EN ";
str select_q = "SELECT * FROM ";
str select_q_ = "SELECT_ * FROM ";
str del = "DELETE FROM ";
str delete_index = "ELIMINAR CON INDICE EN ";
str upd = "UPDATE FROM ";
str upd_index = "UPDATE CON INDICE EN ";
str multi_insert = "INSERTAR VARIOS EN ";
str create_index = "CREATE INDEX ";
str a_ram = "A RAM (";

txt_file tables_txt;
read_file tables_txt2;
unsigned t0, t1,t2,t3;

bool index_query;

db::db(){
  ;
}



bool db::interpret_query(str query, str& name, strp_vec& vec, char_name_vec& cvec, uint_vec& num){
  str temp, type, type_name, char_num;
  int i, int_count, char_count,date_count;
  int_count = char_count = date_count= 0;
  vec.clear();
  temp.clear();
  temp = query.substr(0, 13); //temp = "CREATE TABLE "
  if (temp != create_tab){
    std::cout << "Sintaxis incorrecta 1. Vuelva a intentarlo.\n";
    return 0;
  }
  i = 13;
  name.clear();
  while (query[i] != ' '){
    name += query[i];
    i++;
  }
  i++; //so query[i] != ' '
  while (query[i] != ';' && query[i] != ' '){
    type.clear();
    type_name.clear();
    str_pair data_name_pair; //pair of str(type), str(name)
    char_name char_name_pair;
    while (query[i] != ' ' && query[i] != '('){ //filling with type
      type += query[i];
      i++;
    }
    i++;
    if (type == "INTEGER"){
      int_count++; //i++ because next is a space
      while (query[i] != ' ' && query[i] != ';'){ //filling with the name chosen
        type_name += query[i];
        i++;
      }
      data_name_pair.first = type;
      data_name_pair.second = type_name;
      vec.push_back(data_name_pair);
      i++;
    } else if (type == "VARCHAR") {
      char_count++;
      char_num.clear();
      while (query[i] != ')' && query[i] != ';'){ //filling with the amount of bytes chosen
        char_num += query[i];
        i++;
      }
      i++; //i is now ' '
      i++; //i is now the letter
      while (query[i] != ' ' && query[i] != ';'){
        type_name += query[i];
        i++;
      }
      data_name_pair.first = type;
      data_name_pair.second = type_name;
      
      char_name_pair.first = type_name;
      char_name_pair.second = stringToUint(char_num); //n chars

      vec.push_back(data_name_pair);
      cvec.push_back(char_name_pair);
      i++; 
    } 
     else if (type == "DATE"){                   //verificamos si es intero o varchar
      date_count++;                            //buscamos el siguiente espacio
      while (query[i] != ' ' && query[i] != ';'){ //verificamos si esque termina o sigue
        type_name += query[i];
        i++;
      }
      data_name_pair.first = type; // asignamos  como primer elemento de nuestro par al tipo
      data_name_pair.second = type_name; // y el segundo que es el nombre
      vec.push_back(data_name_pair); // lo insertamos al vector
      i++;
    }    
    else {
      std::cout << "Sintaxis incorrecta 2. Vuelva a intentarlo.\n";
      return 0;
    }
  }
  num.at(0) = (int_count);
  num.at(1) = (char_count);
  num.at(2) = (date_count);
  return 1;
}

bool db::interpret_query_index(str query, str& name_index, str& name_table, str& name_col){
  str temp, type, type_name, char_num;
  int i, int_count, char_count;
  int_count = char_count = 0;

  temp.clear();

  //CREATE INDEX indi2 ON persona (dpto);
  //CREATE INDEX indi1 ON persona (id);
  //optiene en nombre del index
  i = 13;
  name_index.clear();
  while (query[i] != ' '){
    name_index += query[i];
    i++;
  }
  i++; //so query[i] != ' '
  //end

  temp += query[i];
  temp += query[i+1];
  //std::cout << " temp: " << temp << '\n';
  if(temp != "ON")
  {
    std::cout << "Sintaxis incorrecta 3. Vuelva a intentarlo.1\n";
    return 0;
  }
  i += 3;

  name_table.clear();
  while (query[i] != ' '){
    name_table += query[i];
    i++;
  }
  i++; //so query[i] != ' '

  if (query[i] != '(')
  {
    std::cout << "Sintaxis incorrecta 4. Vuelva a intentarlo.2\n";
    return 0;
  }
  i++;
  name_col.clear();
  while (query[i] != ')'){
    name_col += query[i];
    i++;
  }
  //std::cout << ">>>>>>>>>>>>>>>>>>>>>   "<< name_col << std::endl;
  i++;
  if (query[i] != ';')
  {
    std::cout << "Sintaxis incorrecta 5. Vuelva a intentarlo.3\n";
    return 0;
  }

  return 1;
}

bool db::interpret_query_aRam(str query, str& name_index) {
  str temp, temp_name_table, temp_name_col;
  u_int i;

  i = 7;
  name_index.clear();
  while (query[i] != ')'){
    name_index += query[i];
    i++;
  }


  if (query[i+1] != ';')
  {
    std::cout << "Sintaxis incorrecta 6. Vuelva a intentarlo.3\n";
    return 0;
  }

  if (name_index[0] == 'i' && name_index[1] == 'd'){
    this->id_index = 1; //id tree
    std::cout << "index name: " << name_index << '\n';
  }

  return 1;
}

bool db::interpret_query_i(str query, str& name, str_vec& values){
  str temp, temp2;
  int i;
  values.clear();
  temp = query.substr(0, 12); //temp = "INSERTAR EN "
  if (temp != insert_into){
    std::cout << "Sintaxis incorrecta 7. Vuelva a intentarlo.\n";
    return 0;
  }
  i = 12;
  name.clear();
  while (query[i] != ' '){ //getting the name of the table
    name += query[i];
    i++;
  }
  i++; //so query[i] != ' '
  for (int j = 0; j < 8; j++){
    temp2 += query[i++];
  }
  if (temp2 != "VALORES "){
    std::cout << "Sintaxis incorrecta 8. Vuelva a intentarlo.\n";
    return 0;
  }
  while (query[i] != ';' && query[i] != ' '){
    temp.clear();
    while (query[i] != ' ' && query[i] != ';'){ //filling with type
      temp += query[i];
      i++;
    }
    i++;
    values.push_back(temp);
  }
  return 1;
}

bool db::interpret_query_i_index(str query, str& name, str_vec& values, str_vec& name_indices, int_vec& num_col, str& num_fila){
  str temp, temp2, temp3, _num;
  int i;
  values.clear();
  temp = query.substr(0, 23); //temp = "INSERTAR CON INDICE EN "

  if (temp != insert_index){
    std::cout << "Sintaxis incorrecta 9. Vuelva a intentarlo.1\n";
    return 0;
  }
  i = 23;
  name.clear();
  while (query[i] != ' '){ //getting the name of the table
    name += query[i];
    i++;
  }
  i++; //so query[i] != ' '
  for (int j = 0; j < 8; j++){
    temp2 += query[i++];
  }
  if (temp2 != "VALORES "){
    std::cout << "Sintaxis incorrecta 10. Vuelva a intentarlo.2\n";
    return 0;
  }
  while (query[i] != 'I' && query[i] != ' '){
    temp.clear();
    while (query[i] != ' ' && query[i] != ';'){ //filling with type
      temp += query[i];
      i++;
    }
    i++;
    values.push_back(temp);
  }

  ///INSERTAR CON INDICE EN alumnos_maz_nah VALORES 1001 nombre1001 apellido1001 99 INDICE prueba_edad.idx(3) prueba_idx.idx(0) S1001 ;
  ///SELECT * FROM alumnos_maz_nah WHERE id = 1001 IDX = prueba_idx.idx ;
  temp3 = "";
  for (int j = 0; j < 7; j++){
    temp3 += query[i++];
  }
  if (temp3 != "INDICE "){
    std::cout << "Sintaxis incorrecta 11. Vuelva a intentarlo.3\n";
    return 0;
  }
  //"INSERTAR CON INDICE nombre VALUES val1 INDICE ind.idx(2) ind"
  while (query[i] != 'S' && query[i] != ' '){
    temp.clear();
    while (query[i] != ' ' && query[i] != ';'){ //filling with type
      if(query[i] == '(')
      {
        i++;
        _num.clear();
        while (query[i] != ')')
        {
          _num += query[i];
          i++;
        }
        num_col.push_back(stringToInt(_num));
        i++;
        break;
      }
      temp += query[i];
      i++;
    }
    i++;
    name_indices.push_back(temp);
  }
  i++;
  num_fila.clear();
  while (query[i] != ' ' && query[i] != ';')
  {
    num_fila += query[i];
    i++;
  }
  return 1;
}

bool db::interpret_query_d_index(str query, str& name, str_vec& values, str& column, str& name_index, str& num_col){
  str temp, temp2,temp3;
  int i;
  values.clear();
  temp = query.substr(0, 23); //temp = "DELETE FROM "
  if (temp != delete_index){
    std::cout << "Sintaxis incorrecta 12. Vuelva a intentarlo.\n";
    return 0;
  }
  i = 23;
  name.clear();
  while (query[i] != ' '){ //getting the name of the table
    name += query[i];
    i++;
  }
  i++; //so query[i] != ' '
  //WHERE clause
  temp.clear();
  for(int j = 0; j < 6; j++){
    temp += query[i++];
  }
  if (temp != "WHERE "){
    std::cout << "Sintaxis incorrecta 13. Vuelva a intentarlo.\n";
    return 0;
  }
  this->query_where = 1; //WHERE SYNTAX ENABLED
  this->values_to_compare.clear(); //where the values to compare will be added
  char comp;
  column.clear();
  while (query[i] != ' '){
    column += query[i++]; //column name is being stored
  }
  i++; //i should now be the comparator
  comp = query[i++]; //comp is the comparator, and i is a space
  this->comparator = 0;
  //if comp is not in comparisons std::cout << "Comparador no permitido.\n";
  i++;
  temp.clear(); //this should be inside another loop
  //Will be fixed when I have to do boolean operators
  while (query[i] != ' '){ //getting the value of the atribute
    temp += query[i];
    i++;
  }
  num_col = temp;
  this->values_to_compare.push_back(temp);
  i++;
  //std::cout<<i<<std::endl;
  temp3 = "";
  for (int j = 0; j < 7; j++){
    temp3 += query[i++];
  }

  if (temp3 != "INDICE "){
    std::cout << "Sintaxis incorrecta 14. Vuelva a intentarlo.3\n";
    return 0;
  }

  while (query[i] != ';'){ //getting the name of the table
    name_index += query[i];
    i++;
  }

  return 1;
}

bool db::interpret_query_s(str query, str& name, str_vec& values, str& column){
  str temp, temp2;
  int i;
  values.clear();
  temp = query.substr(0, 14); //temp = "SELECT * FROM "
  if (temp != select_q){
    std::cout << "Sintaxis incorrecta 15. Vuelva a intentarlo.\n";
    return 0;
  }
  i = 14;
  name.clear();
  while (query[i] != ' '){ //getting the name of the table
    name += query[i];
    i++;
  }
  i++;


  if (query[i] == ';')
     return 1;

  //WHERE clause
  //WHERE clause should begin here
  temp.clear();
  for(int j = 0; j < 6; j++){
    temp += query[i++];
  }		   //IDX =
  if (temp != "WHERE "){
    std::cout << "Sintaxis incorrecta 16. Vuelva a intentarlo.\n";
    return 0;
  }
  this->query_where = 1; //WHERE SYNTAX ENABLED
  this->values_to_compare.clear(); //where the values to compare will be added
  char comp;
  column.clear();
  while (query[i] != ' '){
    column += query[i++]; //column name is being stored
  }
  i++; //i should now be the comparator
  comp = query[i++]; //comp is the comparator, and i is a space
  //this->comparator = findInArray(comp, comparisons, 3);
  this->comparator = 0;
  //if comp is not in comparisons std::cout << "Comparador no permitido.\n";
  i++;
  temp.clear(); //this should be inside another loop
  //Will be fixed when I have to do boolean operators
  while (query[i] != ' '){ //getting the value of the atribute
    temp += query[i];
    i++;
  }
  this->values_to_compare.push_back(temp);

  //index
  i++;
  if (query[i] == ';')
  {
    this->query_index = 0;
    return 1;
  }

/***********sin indices****************************/

  this->query_index = 1;
  temp.clear();
  for(int j = 0; j < 6; j++){//"IDX = ""
    temp += query[i++];
  }
  if (temp != "IDX = "){
    std::cout << "Sintaxis incorrecta 17. Vuelva a intentarlo.\n";
    return 0;
  }

  temp.clear(); //this should be inside another loop
  //Will be fixed when I have to do boolean operators
  while (query[i] != ' '){ //getting the value of the atribute
    temp += query[i];
    i++;
  }
  //std::cout<<"<<<<<<<<<<<<<<<<<<<<<<<"<<temp<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<std::endl;

  this->values_to_compare.push_back(temp);

  return 1;
}

bool db::interpret_query_d(str query, str& name, str_vec& values, str& column){
  str temp, temp2;
  int i;
  values.clear();
  temp = query.substr(0, 12); //temp = "DELETE FROM "
  if (temp != del){
    std::cout << "Sintaxis incorrecta 18. Vuelva a intentarlo.\n";
    return 0;
  }
  i = 12;
  name.clear();
  while (query[i] != ' '){ //getting the name of the table
    name += query[i];
    i++;
  }
  i++; //so query[i] != ' '
  //WHERE clause
  temp.clear();
  for(int j = 0; j < 6; j++){
    temp += query[i++];
  }
  if (temp != "WHERE "){
    std::cout << "Sintaxis incorrecta 19. Vuelva a intentarlo.\n";
    return 0;
  }
  this->query_where = 1; //WHERE SYNTAX ENABLED
  this->values_to_compare.clear(); //where the values to compare will be added
  char comp;
  column.clear();
  while (query[i] != ' '){
    column += query[i++]; //column name is being stored
  }
  i++; //i should now be the comparator
  comp = query[i++]; //comp is the comparator, and i is a space
  this->comparator = 0;
  //if comp is not in comparisons std::cout << "Comparador no permitido.\n";
  i++;
  temp.clear(); //this should be inside another loop
  //Will be fixed when I have to do boolean operators
  while (query[i] != ' '){ //getting the value of the atribute
    temp += query[i];
    i++;
  }
  this->values_to_compare.push_back(temp);
  return 1;
}

bool db::interpret_query_u(str query, str& name, str_vec& values, str& column, str_vec& columns){
  str temp, temp2;
  int i;
  values.clear();
  temp = query.substr(0, 12); //temp = "UPDATE FROM "
  if (temp != upd){
    std::cout << "Sintaxis incorrecta 20. Vuelva a intentarlo.\n";
    return 0;
  }
  i = 12;
  name.clear();
  while (query[i] != ' '){ //getting the name of the table
    name += query[i];
    i++;
  }
  i++; //so query[i] != ' '
  for (int j = 0; j < 4; j++){
    temp2 += query[i++];
  }
  if (temp2 != "SET "){
    std::cout << "Sintaxis incorrecta 21. Vuelva a intentarlo.\n";
    return 0;
  }
  while ( /*query[i] != 'W' && */query[i] != ' '){
    temp.clear();
    if (query[i] == 'W'){
      temp2.clear();
      for (int j = 0; j < 6; j++){
        temp2 += query[i+j];
      }
      if (temp2 == "WHERE ") break;
    }
    temp2.clear();
    while (query[i] != ' ' && query[i] != ';'){ //filling with type
      temp += query[i];
      i++;
    }
    i++;
    columns.push_back(temp);
    if (query[i] != '=') {
      std::cout << "Sintaxis incorrecta 22. Vuelva a intentarlo.\n";
      return 0;
    }
    i++;
    i++; //i is not empty now
    temp2.clear();
    while (query[i] != ' '){ //value
      temp2 += query[i++];
    }
    values.push_back(temp2);
    i++; //space omitted
  }
  i += 6; //ommitting "WHERE "
  this->query_where = 1; //WHERE SYNTAX ENABLED
  this->values_to_compare.clear(); //where the values to compare will be added
  char comp;
  column.clear();
  while (query[i] != ' '){
    column += query[i++]; //column name is being stored
  }
  i++; //i should now be the comparator
  comp = query[i++]; //comp is the comparator, and i is a space
  //this->comparator = findInArray(comp, comparisons, 3);
  this->comparator = 0;
  //if comp is not in comparisons std::cout << "Comparador no permitido.\n";
  i++;
  temp.clear(); //this should be inside another loop
  //Will be fixed when I have to do boolean operators
  while (query[i] != ' '){ //getting the value of the atribute
    temp += query[i];
    i++;
  }
  this->values_to_compare.push_back(temp);
  return 1;
}

bool db::interpret_query_u_index(str query, str& name, str_vec& values, str_vec& name_indices, str& column, str_vec& columns){
  str temp, temp2, temp3, _num;
  int i;
  values.clear();              //UPDATE CON INDICE EN tabla SET atributo = valor WHERE atributo = valor INDICE index1-name.idx ;
  temp = query.substr(0, 21); //temp = "UPDATE CON INDICE EN "
  //UPDATE CON INDICE EN alumnos_maz_nah SET edad = 4 WHERE edad = 1 INDICE prueba_edad.idx ;
  if (temp != upd_index){
    std::cout << "Sintaxis incorrecta 23. Vuelva a intentarlo.1\n";
    return 0;
  }
  i = 21;
  name.clear();
  while (query[i] != ' '){ //getting the name of the table
    name += query[i];
    i++;
  }
  i++; //so query[i] != ' '
  for (int j = 0; j < 4; j++){
    temp2 += query[i++];
  }
  if (temp2 != "SET "){
    std::cout << "Sintaxis incorrecta 24. Vuelva a intentarlo.2\n";
    return 0;
  }
  while ( /*query[i] != 'W' && */query[i] != ' '){
    temp.clear();
    if (query[i] == 'W'){
      temp2.clear();
      for (int j = 0; j < 6; j++){
        temp2 += query[i+j];
      }
      if (temp2 == "WHERE ") break;
    }
    temp2.clear();
    while (query[i] != ' ' && query[i] != ';'){ //filling with type
      temp += query[i];
      i++;
    }
    i++;
    columns.push_back(temp);
    if (query[i] != '=') {
      std::cout << "Sintaxis incorrecta 25. Vuelva a intentarlo.\n";
      return 0;
    }
    i++;
    i++; //i is not empty now
    temp2.clear();
    while (query[i] != ' '){ //value
      temp2 += query[i++];
    }
    values.push_back(temp2);
    i++; //space omitted
  }
  i += 6; //ommitting "WHERE "
  this->query_where = 1; //WHERE SYNTAX ENABLED
  this->values_to_compare.clear(); //where the values to compare will be added
  char comp;
  column.clear();
  while (query[i] != ' '){
    column += query[i++]; //column name is being stored
  }
  i++; //i should now be the comparator
  comp = query[i++]; //comp is the comparator, and i is a space
  //this->comparator = findInArray(comp, comparisons, 3);
  this->comparator = 0;
  //if comp is not in comparisons std::cout << "Comparador no permitido.\n";
  i++;
  temp.clear(); //this should be inside another loop
  //Will be fixed when I have to do boolean operators
  while (query[i] != ' '){ //getting the value of the atribute
    temp += query[i];
    i++;
  }
  this->values_to_compare.push_back(temp);
  i++;
  temp3 = "";
  for (int j = 0; j < 7; j++){
    temp3 += query[i++];
  }
  if (temp3 != "INDICE "){
    std::cout << "Sintaxis incorrecta 26. Vuelva a intentarlo.3\n";
    return 0;
  }
  //"INSERTAR CON INDICE nombre VALUES val1 INDICE ind.idx(2) ind"
  temp.clear();
  while (query[i] != ' ' && query[i] != ';'){ //filling with type
    temp += query[i];
    i++;
  }
  name_indices.push_back(temp);
  return 1;
}

bool db::interpret_query_i_m(str query, str& name, str_vec& values){
  str temp, temp2;
  int i;
  values.clear();
  temp = query.substr(0, 19); //temp = "INSERTAR EN "
  if (temp != multi_insert){
    std::cout << "Sintaxis incorrecta 27. Vuelva a intentarlo.\n";
    return 0;
  }
  i = 19;
  name.clear();
  while (query[i] != ' '){ //getting the name of the table
    name += query[i];
    i++;
  }
  i++; //so query[i] != ' '
  /*for (int j = 0; j < 8; j++){
    temp2 += query[i++];
  }
  if (temp2 != "VALORES "){
    std::cout << "Sintaxis incorrecta. Vuelva a intentarlo.\n";
    return 0;
  }*/
  while (query[i] != ';' && query[i] != ' '){
    temp.clear();
    while (query[i] != ' ' && query[i] != ';'){ //filling with I; Rnum1,num2 or C
      temp += query[i];
      i++;
    }
    i++;
    values.push_back(temp);
  }
  return 1;
}

void db::createTable(str query){
  str name;
  strp_vec vec;
  char_name_vec cvec;
  uint_vec num (3);
  int i;

  if (!interpret_query(query, name, vec, cvec, num)) return;
  Table* temp = new Table(name, vec, num, cvec);
  //add_table(temp);

  tables_txt.open("tables.ggwp", std::fstream::app); //adding to the file in hdd
  writeTable(tables_txt, temp);
  tables_txt.close();

  name += ".table";
  char* file_name = new char[name.size() + 1];
  for (i = 0; i < name.size(); i++){
    file_name[i] = name.at(i);
  }
  file_name[i] = '\0';

  tables_txt.open(file_name);
  writeHeaderTable(tables_txt, temp);
  tables_txt.close();

  delete [] file_name;

  std::cout << "Tabla " << temp->getName() << " creada.\n";
  temp->desc();
}

void db::createIndex(str query){
  str name_index, name_table, name_col, tex, temp_name_table;
  str_vec vec_data, vec_filas, vec_col;
  int i;

  if (!interpret_query_index(query, name_index, name_table, name_col))
                     return;
  //std::cout << ">>>>>>>>>>>>>>>>>>>>>   "<< name_col << std::endl;


  name_index += ".idx";
  char* file_name = new char[name_index.size() + 1];
  for (i = 0; i < name_index.size(); i++){
    file_name[i] = name_index.at(i);
  }
  file_name[i] = '\0';

  temp_name_table = name_table;
  name_table += ".table";

  char* file_tabe = new char[name_table.size() + 1];
  for (i = 0; i < name_table.size(); i++){
    file_tabe[i] = name_table.at(i);
  }
  file_tabe[i] = '\0';

  str_tree *m_tree =  new str_tree(name_index, name_col, temp_name_table);
  //std::cout << ">>>>>>>>>>>>>>>>>>>>>despues del tree   "<< name_col << std::endl;


//el arbol recive el nombre del archivo ,la columna , 
std::cout <<"FILE_table: "<<file_tabe<<" "<<"name_colu : "<<name_col<<std::endl;
  tables_txt2.open(file_tabe, std::fstream::app);
  this->select_query2(tables_txt2, m_tree, name_col); // inserta los valores al arbol solo el valor colum y un key id
  //enviamos los valores de la columna y un indidce de numeros 
  tables_txt2.close();
  //m_tree->printPreorder(m_tree->root);
std::cout <<"FILE_name: "<<file_name<<std::endl;
  tables_txt.open(file_name, std::fstream::app);
  m_tree->writeFile(tables_txt);
  tables_txt.close();

  indices.push_back(m_tree);
  
    real.clear();
    all_fun(file_name);
    std::ofstream ofs;
    ofs.open(file_name, std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    std::ofstream file;
    file.open(file_name,std::fstream::app);
    file<<name_table<<","<<name_col<<std::endl;
    for(int i=0; i<real.size(); i++){
        file << real[i].second<<std::endl;
    }
    real.clear();

  std::cout << "Se creo el INDEX\n";
   delete [] file_name;
}

void db::aRam(str query) {
  str name_index, temp, temp_name_table, temp_name_col;
  u_int i;
using namespace std;
//********************************************
//cout <<"QUERY: "<< query <<endl;
//*********************************************
  if (!interpret_query_aRam(query, name_index)) return;// retorna lo del parentesis name_idx
  //cout << "QUERY: "<<query<<" name:_index: "<< name_index << endl;
  
  /*
  for (int i = 0; i < indices.size(); i++){ // recorrer el vector de arbolres indices
    if(indices[i]->m_name_index == name_index) // buscamos nuestro index
      return ;
  }
*/
  temp.clear();
  char* file_name = new char[name_index.size() + 1];
  for (i = 0; i < name_index.size(); i++){
    file_name[i] = name_index.at(i);
  }
  file_name[i] = '\0';

  tables_txt2.open(file_name, std::fstream::app);// para abrir el archivo index

  i=0;
  getline(tables_txt2, temp);


  temp_name_table.clear();
  while (temp[i] != ','){
    temp_name_table += temp[i];
    i++;
  }

  i++;
  temp_name_col.clear();
  while (i < temp.size()){
    temp_name_col += temp[i];
    i++;
  }
// hasta esta parte obtenemos el nombre y la comunva de nuestro archivo que esta en la primera fila
  str_tree *m_tree =  new str_tree(name_index, temp_name_col, temp_name_table);
  std::cout << "INIT READ" << std::endl;
  if (this->id_index){
    //std::cout << "id index\n";
    str_vec values;
    values.clear();
    values = this->id_values(file_name);
    //std::cout << "id index. values read. starting to build tree\n";
    values.erase(values.begin() + values.size()-1);
    //std::cout << "amount of values: " << values.size() << std::endl;
    //std::cout << "first value: " << values.at(0) << ", last: " << values.at(values.size()-1) << std::endl;
    m_tree->build_from_vec(values, m_tree->root);
    //m_tree->build_from_vec2(values,0,values.size()-1);
    std::cout << "root value: " << m_tree->root->key << std::endl;
  }
  else this->read_index(tables_txt2, m_tree);
  std::cout << "end read" << std::endl;
  tables_txt2.close();
  //m_tree->printPreorder(m_tree->root);
  indices.push_back(m_tree);
  //m_tree->inOrder();
  cout << "TERMINA RAM: "<< endl;
  this->id_index = 0;
}

void db::i_query(str query){
  str temp;
  temp = query.substr(0, 13); //temp = "CREATE TABLE "
  if (temp == create_tab){
    //std::cout<<"entra en crear tabla"<<std::endl;
    createTable(query);
     return;
  }
  temp = query.substr(0, 13); //temp = "CREATE INDEX "
  if (temp == create_index){
    createIndex(query);
    return;
  }
  temp = query.substr(0, 7); //temp = "A RAM ("
  if (temp == a_ram){
    aRam(query);
    return;
  }
  temp = query.substr(0, 12); //temp = "INSERTAR EN "
  if (temp == insert_into){
    insert_row(query);
    return;
  }
  temp = query.substr(0, 23); //temp = insert_index = "INSERTAR CON INDICE EN nombre_tabla VALORES ;"
  if (temp == insert_index){
    insert_row_index(query);
    return;
  }
  temp = query.substr(0, 23); //temp = insert_index = "ELIMINAR CON INDICE EN nombre_tabla VALORES ;"
  if (temp == delete_index){
    delete_data_index(query);
    return;
  }
  temp = query.substr(0, 21); //"UPDATE CON INDICE EN "
  if (temp == upd_index){
    update_data_index(query);
    return;
  }
  temp = query.substr(0, 14); //temp = "SELECT * FROM "
  if (temp == select_q) {
        t0=clock();
            select_data(query);
        t1 = clock();
            #include<time.h>
            double time = (double(t1-t0)/CLOCKS_PER_SEC);
            std::cout << "Execution Time: " << time << std::endl;
  std::cout <<"##########################################################"<<std::endl;
    return;
  }
  temp = query.substr(0, 12); //temp = "DELETE FROM "
  if (temp == del){
    delete_data(query);
    return;
  }
  temp = query.substr(0, 12); //temp = "DELETE FROM "
  if (temp == upd){
    update_data(query);
    return;
  }
  temp = query.substr(0, 19); //temp = "INSERTAR VARIOS EN "
  if (temp == multi_insert){
    insert_multiple(query);
    return;
  }
  std::cout << "Sintaxis incorrecta 0. Vuelva a intentarlo\n";
  return;
}

void db::insert_row(str query){
  str name;
  str_vec vec;
  int i;

  if (!interpret_query_i(query, name, vec)) return;
  name += ".table";
  char* file_name = new char[name.size() + 1];
  for (i = 0; i < name.size(); i++){
    file_name[i] = name.at(i);
  }

  file_name[i] = '\0';
  tables_txt.open(file_name, std::fstream::app);
  //write the info retrieved to file_name
  writeInsert(tables_txt, vec);
  tables_txt.close();

  delete [] file_name;
  std::cout << "Datos insertados.\n";
}




void db::insert_row_index(str query){
  ///INSERTAR CON INDICES EN nombre_tabla VALUES value_1 caluer2 INDICES name.idx(2) nameidx(1)
  str name;
  str_vec vec;// contiene los datos a insertar 
  str_vec name_index;
  int_vec num_col;
  str num_fila;
  int i;

  if (!interpret_query_i_index(query, name, vec, name_index, num_col, num_fila)) return;
  name += ".table";
  char* file_name = new char[name.size() + 1];
  for (i = 0; i < name.size(); i++){
    file_name[i] = name.at(i);
  }

  file_name[i] = '\0';
  tables_txt.open(file_name, std::fstream::app);
  //write the info retrieved to file_name
  
  /*std::cout << "<<<<<<<<<<<<<<<name index>>><<<<<<<<<<<<<"<< std::endl;
  for(int i=0; i<name_index.size(); i++){
    std::cout << name_index[i] << std::endl;
  }

   std::cout << "<<<<<<<<<<<<<<<INDICES>>><<<<<<<<<<<<<"<< std::endl;
  for(int i=0; i<indices.size(); i++){
    std::cout << indices[i]->m_name_index << std::endl;
  }

  std::cout << "<<<<<<<<<<<<<<<INTO INDICES>>><<<<<<<<<<<<<"<< std::endl;
  for(int i=0; i<indices.size(); i++){
    for(int j=0; j<indices.size(); j++){
      std::cout << indices[i]<< std::endl;
    }
  }*/

  writeInsert(tables_txt, vec);
  tables_txt.close();

  delete [] file_name;

  for (int i = 0; i < indices.size(); i++){
    for(int j = 0; j < name_index.size(); j++){
      if(indices[i]->m_name_index == name_index[j]){
        std::cout << "ENCONTRO EL INDICE <insert>" << std::endl;
        indices[i]->insert(vec[num_col[j]], num_fila);
          
          tables_txt.open(name_index[j], std::fstream::app);
          indices[i]->writeFile2(tables_txt,name_index[j]);
          tables_txt.close();
      }
    } 
  }






  std::cout << "Datos insertados.\n";
}

void db::insert_multiple(str query){ //INSERTAR VARIOS EN tabla I/Rnum1,num2/C ;
  str name;
  str_vec vec;
  int i;

  if (!interpret_query_i_m(query, name, vec)) return;
  std::cout << "Insertando varias filas en " << name << std::endl;
  name += ".table";
  char* file_name = new char[name.size() + 1];
  for (i = 0; i < name.size(); i++){
    file_name[i] = name.at(i);
  }

  file_name[i] = '\0';
  tables_txt.open(file_name, std::fstream::app);
  tables_txt2.open(file_name);
  //write the info retrieved to file_name
  //writeInsert(tables_txt, vec);
  write_multiple(tables_txt, tables_txt2, vec);
  tables_txt.close();

  delete [] file_name;
  std::cout << " M Datos insertados.\n";
}

str_vec db::select_query(read_file& file, str_vec columns, str name, str column){
  str temp, temp2, temp3, temp_name, vchar_value_found, vchar_val_to_compare;
  str_vec res;
   std::cout <<"##########################################################"<<std::endl;
  //A RAM (indi1.idx);
  //A RAM (indi2.idx);
  //SELECT * FROM persona WHERE id = 7933 ;
  //SELECT * FROM persona WHERE id = 7933 IDX = indi1.idx ;
  //SELECT * FROM persona WHERE dpto = 5 ;
  //SELECT * FROM persona WHERE dpto = 5 IDX = indi2.idx ;
  this->query_index = 0;

  if (this->query_index) {
    //t2=clock();

    // budcamos el valor del indice en los vectores indice
    u_int pos_index = indices.size()+1;
    for (int i = 0; i < indices.size(); i++){
      if(indices[i]->m_name_index == values_to_compare[1]){
        pos_index = i;
        break;
      }
    }
    
    if(pos_index == indices.size()+1) {
      std::cout << "No existe el indice" << std::endl;
      return res;
    }
    if(indices[pos_index]->m_name_table != name) {
      std::cout << "No coincide la tabla del indice" << std::endl;
      return res;
    }

    //indices[pos_index]->inOrder();
    index_query = 1;
    this->index_eval = 1;
    return indices[pos_index]->find(values_to_compare[0]);// fin fucion del arbol le pasamos el indice
    /*
        t3 = clock();
        #include<time.h>
        double times = (double(t3-t2)/CLOCKS_PER_SEC);
        std::cout << "Execution Time INDEX: " << times << std::endl;*/
  }




  uint_vec types (columns.size() );
  u_int type;
  int pos = -1, i; //so if there's not a WHERE clause, the IF will never begin
  LL value_found, val_to_compare;
  read_file getting_columns;
  bool broke = 0, last_col = 0;

  temp_name = name + ".table";
  char* file_name = new char[temp_name.size() + 1];
  for (i = 0; i < temp_name.size(); i++){
    file_name[i] = temp_name.at(i);
  }
  file_name[i] = '\0';

  getting_columns.open(file_name); //copy of file

  delete [] file_name;
  temp_name.clear();
  temp.clear();

  if (this->query_where){ //finding the atributes
    getline(getting_columns, temp2);
    for(i = 0; i < temp2.size(); i++){
      if (temp2.at(i) == ',') {
        if (temp == column ){
          type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->VARCHAR(N), 2->DATE
          broke = 1;
          break;
          //pos will store the number of column we have to check at the table
        } //else
        temp.clear();
      } else {
        temp += temp2.at(i);
      }
    }
    if (!broke){
      if (temp == column ){
        type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->VARCHAR(N), 2->DATE
      }
    }
  }
  bool first_line = true;
  while (! file.eof() ){
    temp2.clear();
    getline(file, temp2);
    temp.clear();
    int position = 0;
    temp_name.clear();
    last_col = 0;
    for(i = 0; i < temp2.size(); i++){
      if ( temp2.at(i) == ',' ) {
        temp3 = temp_name;
        temp3.erase(std::remove_if(temp3.begin(), temp3.end(), isspace), temp3.end());
        if (pos == position){
          last_col = 1;
          if (type == 0){ //do the cast to the type it is
            value_found = stringToLL(temp3);
            //value_found.erase(std::remove_if(value_found.begin(), value_found.end(), isspace), value_found.end())
            val_to_compare = stringToLL(values_to_compare.at(0) );
            this->query_where = 1;
            if (this->comparator == 0){
              if (value_found == val_to_compare) to_insert = 1;
            }
            else if (this->comparator == 1){
              if (value_found > val_to_compare) to_insert = 1;
            }
            else {
              if (value_found == val_to_compare){
                to_insert = 1;
              }
            }
          } else if (type == 1){
            vchar_value_found = temp3;
            //vchar_value_found.erase(std::remove_if(vchar_value_found.begin(), vchar_value_found.end(), isspace), vchar_value_found.end())
            vchar_val_to_compare = values_to_compare.at(0);
            if (this->comparator == 0){
              if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
            }
            else if (this->comparator == 1){
              if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
            }
            else {
              if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
            }
          } else {
            ; //same as above but with date
          }

          //do the respective comparison with this->comparator and the value
          //THIS COMPARATOR: 0 <, 1 >, 2 =
          //for now, the value is only this->values_to_compare.at(0)
        }
        position++;
        temp += ' ';
        temp3.clear();
        temp_name.clear();
      } else { //storing values
        temp += temp2.at(i);
        temp_name += temp2.at(i);
      }
    }
    if (! last_col ){ //doing one last iteration
      temp3 = temp_name;
      temp3.erase(std::remove_if(temp3.begin(), temp3.end(), isspace), temp3.end());
      if (pos == position){
        last_col = 1;
        if (type == 0){ //do the cast to the type it is
          value_found = stringToLL(temp3);
          //value_found.erase(std::remove_if(value_found.begin(), value_found.end(), isspace), value_found.end())
          val_to_compare = stringToLL(values_to_compare.at(0) );
          this->query_where = 1;
          if (this->comparator == 0){
            if (value_found == val_to_compare) to_insert = 1;
          }
          else if (this->comparator == 1){
            if (value_found > val_to_compare) to_insert = 1;
          }
          else {
            if (value_found == val_to_compare){
              to_insert = 1;
            }
          }
        } else if (type == 1){
          vchar_value_found = temp3;
          //vchar_value_found.erase(std::remove_if(vchar_value_found.begin(), vchar_value_found.end(), isspace), vchar_value_found.end())
          vchar_val_to_compare = values_to_compare.at(0);
          if (this->comparator == 0){
            if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
          }
          else {
            if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
          }
        }
      }

    }
    if (temp.empty() ){
      first_line = false;
      continue;
    }
    if (! this->query_where || first_line) res.push_back(temp);
    if (this->query_where && this->to_insert) res.push_back(temp);
    this->to_insert = 0;
    first_line = false;
  }
  return res;
}

void db::select_data(str query){ // SELECT * FROM pruebita
  str name, result, column, temp_name;
  str_vec vec;
  char* index_q;
  int i;
  result.clear();

  if (!interpret_query_s(query, name, vec, column)) return;

  temp_name = name;
  name += ".table";
  char* file_name = new char[name.size() + 1];
  for (i = 0; i < name.size(); i++){
    file_name[i] = name.at(i);
  }
  file_name[i] = '\0';
  tables_txt2.open(file_name, std::fstream::app);
  //get the info from the select clause
  vec = select_query(tables_txt2, vec, temp_name, column);
  //tables_txt2.close();

  delete [] file_name;
//std::cout << "column: " << vec.at(i) << std::endl;
  //if (true){
  if (this->index_eval){
    char* first_row = new char[24];
    tables_txt2.seekg(0);
    tables_txt2.read(first_row, 24);
    std::cout.write(first_row, 24);
    delete[] first_row;
    if (vec.size() == 1 && vec.at(0) == "-1"){
      std::cout << "No se encontro el valor buscado.\n";
    } else {
      for (int i = 0; i < vec.size(); i++){
        index_q = new char[61];
        //std::cout << "iter: " << i << std::endl;
        //std::cout << "column: " << vec.at(i) << std::endl;
        //std::cout << "seekg: " << 24 + i + 60 * (stringToInt(vec.at(i))-1) << std::endl;
        tables_txt2.seekg(24 + (61 * (stringToInt(vec.at(i))-1)), std::ios_base::beg);
        tables_txt2.read(index_q, 61);
        //std::cout << index_q << '\n';
        std::cout.write(index_q,61);
        delete[] index_q;
      }
    }
    index_query = 0;
    std::cout << "**********************************************************************"<<std::endl;
  }
  //}
   else {
    for (int i = 0; i < vec.size(); i++){
      std::cout << vec.at(i) << '\n';
    }
  }
  this->query_where = 0;
  index_query = 0;
  this->index_eval = 0;
  tables_txt2.close();
}

void db::delete_data(str query){
  str name, result, column, temp_name;
  str_vec vec;
  txt_file outfile;
  int i;
  result.clear();

  if (!interpret_query_d(query, name, vec, column)) return;
  temp_name = name;
  temp_name = temp_name + "_temp.table"; //to create name_temp.table

  char* file_temp = new char[temp_name.size() + 1]; //data will be temporarily stored there
  char* file_name = new char[name.size() + 1];
  for (i = 0; i < temp_name.size(); i++){
    file_temp[i] = temp_name.at(i);
  }
  file_temp[i] = '\0';
  outfile.open(file_temp);

  temp_name = name;

  name += ".table";
  for (i = 0; i < name.size(); i++){
    file_name[i] = name.at(i);
  }
  file_name[i] = '\0';
  tables_txt2.open(file_name, std::fstream::app);
  //copy to a temp file all values but deleted one
  this->delete_query(tables_txt2, outfile, vec, temp_name, column); //PRETTY MUCH the same as select_query
  tables_txt2.close();
  outfile.close();

  remove(file_name); //removing old data
  std::rename(file_temp, file_name); //renaming so name.table still exists with the new data
  //std::rename(file_name, file_temp); //renaming so name.table still exists with the new data

  delete [] file_name;
  delete [] file_temp;

  std::cout << "Valores eliminados.\n";

  this->query_where = 0;
}

void writeFile3(std::string file,std::string valor){
  std::vector<std::string> values;
  values.push_back("alumnos2,edad");
  std::string value, real_value;
  std::ifstream index_file;
  index_file.open(file);
  getline(index_file, value);
    if (index_file.is_open()) {
        while (index_file >> value){
            real_value.clear();
            auto it = value.find(";");
            for(int i=0; i<it; i++ ){
                real_value += value[i];
            }
            if(real_value != valor){
                values.push_back(value);
           }
        }
    }
    index_file.close();
    std::ofstream ofs;
    ofs.open(file, std::ios::out | std::ios::trunc);
    ofs.close(); 

  std::ofstream r_index_file;
  r_index_file.open(file);
  for(int i=0; i<values.size(); i++){
      r_index_file<<values[i]<<std::endl;
  }
  index_file.close(); 
}

void db::delete_data_index(str query){
  str name, result, column, temp_name, name_index, num_col;
  str_vec vec;
  txt_file outfile;
  int i;
  result.clear();

  if (!interpret_query_d_index(query, name, vec, column, name_index, num_col)) return;

  //std::cout<<"NAME: "<<name<<std::endl;
  //std::cout<<"column: "<<column<<std::endl;
  //std::cout<<"NAME_INDEX: "<<name_index<<std::endl;
  //std::cout<<"NUM COL: "<<num_col<<std::endl;


  temp_name = name;
  temp_name = temp_name + "_temp.table"; //to create name_temp.table

  char* file_temp = new char[temp_name.size() + 1]; //data will be temporarily stored there
  char* file_name = new char[name.size() + 1];
  for (i = 0; i < temp_name.size(); i++){
    file_temp[i] = temp_name.at(i);
  }
  file_temp[i] = '\0';
  outfile.open(file_temp);

  temp_name = name;

  name += ".table";
  for (i = 0; i < name.size(); i++){
    file_name[i] = name.at(i);
  }
  file_name[i] = '\0';
  tables_txt2.open(file_name, std::fstream::app);
  //copy to a temp file all values but deleted one
  this->delete_query(tables_txt2, outfile, vec, temp_name, column); //PRETTY MUCH the same as select_query
  tables_txt2.close();
  outfile.close();

  remove(file_name); //removing old data
  std::rename(file_temp, file_name); //renaming so name.table still exists with the new data
  //std::rename(file_name, file_temp); //renaming so name.table still exists with the new data

  delete [] file_name;
  delete [] file_temp;

  for(int i=0; i<values_to_compare.size(); i++){
      std::cout <<"VALUES TO :: "<< values_to_compare[i] <<std::endl;
  }




  int numcol = stringToInt(num_col);
  std::cout<<numcol<<std::endl;

  std::cout  << "INDICE::SIZE() = "<<indices.size()<<std::endl;



  for (int i = 0; i < indices.size(); i++) {
    std::cout<<"NAME DELETE: "<<indices[i]->m_name_index<< " | "<< name_index<<std::endl;
    std::cout << (indices[i]->m_name_index == name_index) <<std::endl;

    if(indices[i]->m_name_index ==  "idx_edad.idx"){// && vec[numcol] == num_col){
      std::cout << "ENCONTRO EL INDICE <Delete> "<<std::endl;
      indices[i]->deleteKey(values_to_compare.at(0));
      writeFile3(name_index,num_col);
    }
  }


  std::cout << "Valores ELIMINADOS.\n";

  this->query_where = 0;

}

void db::update_data(str query){
  str name, result, column, temp_name;
  str_vec columns, values;
  txt_file outfile;
  int i;
  result.clear();

  if (!interpret_query_u(query, name, values, column, columns)) return;
  temp_name = name;
  temp_name = temp_name + "_temp.table"; //to create name_temp.table

  char* file_temp = new char[temp_name.size() + 1]; //data will be temporarily stored there
  char* file_name = new char[name.size() + 1];
  for (i = 0; i < temp_name.size(); i++){
    file_temp[i] = temp_name.at(i);
  }
  file_temp[i] = '\0';
  outfile.open(file_temp);

  temp_name = name;

  name += ".table";
  for (i = 0; i < name.size(); i++){
    file_name[i] = name.at(i);
  }
  file_name[i] = '\0';
  tables_txt2.open(file_name, std::fstream::app);
  this->update_query(tables_txt2, outfile, columns, values, temp_name, column); //PRETTY MUCH the same as delete_query
  tables_txt2.close();
  outfile.close();

  remove(file_name); //removing old data
  std::rename(file_temp, file_name); //renaming so name.table still exists with the new data

  delete [] file_name;
  delete [] file_temp;

  std::cout << "Valores actualizados.\n";

  this->query_where = 0;
}

void db::update_data_index(str query){
  str name, result, column, temp_name;
  str_vec columns, values, name_indices;
  txt_file outfile;
  std::vector< std::string > temp;
  int i;
  result.clear();

  if (!interpret_query_u_index(query, name, values, name_indices, column, columns)) return;
  temp_name = name;
  temp_name = temp_name + "_temp.table"; //to create name_temp.table

  char* file_temp = new char[temp_name.size() + 1]; //data will be temporarily stored there
  char* file_name = new char[name.size() + 1];
  for (i = 0; i < temp_name.size(); i++){
    file_temp[i] = temp_name.at(i);
  }
  file_temp[i] = '\0';
  outfile.open(file_temp);

  temp_name = name;

  name += ".table";
  for (i = 0; i < name.size(); i++){
    file_name[i] = name.at(i);
  }
  file_name[i] = '\0';
  tables_txt2.open(file_name, std::fstream::app);
  this->update_query(tables_txt2, outfile, columns, values, temp_name, column); //PRETTY MUCH the same as delete_query
  tables_txt2.close();
  outfile.close();

  remove(file_name); //removing old data
  std::rename(file_temp, file_name); //renaming so name.table still exists with the new data

  delete [] file_name;
  delete [] file_temp;

  std::cout << "Valores actualizados.\n";

  this->query_where = 0;

  for (int i = 0; i < indices.size(); i++)
  {
    if(indices[i]->m_name_index == name_indices[0])
    {
      temp=indices[i]->find(values_to_compare.at(0));
      indices[i]->deleteKey(values_to_compare.at(0));
      for(int o=0; o < temp.size(); o++){
        std::cout<<temp[o]<<std::endl;
        indices[i]->insert(values[0], temp[o]);
      }
    }

  }
}

u_int db::finding_atribute_type(str type_name, str table_name, int& pos){
  //pos will store the number of the column at the file
  //say we're looking for the "ABCD" column, and data is stored like "AHD,ACB,ABCD,AHD"
  //pos will save the value 2
  read_file tables_file;
  tables_file.open("tables.ggwp");
  str temp, temp2;
  while(! tables_file.eof() ){
    getline(tables_file, temp);
    if (temp == table_name) break; //we've found the table we want to look at
  }
  pos = 0;
  while(! tables_file.eof() ){
    temp2.clear();
    int i = 0;
    getline(tables_file, temp);
    if (temp[0] == '-') return -1;
    //for(i = 0; i < type_name.size(); i++){
    while(temp[i] != ' '){
      temp2 += temp[i++];
    }
    if (temp2 == type_name){
      i++; //temp[i] should be the letter of the type
      if (temp[i] == 'I') return 0; //it is an integer!
      else if (temp[i] == 'V') return 1; //it is a varchar!
    }
    pos++;
  }
}

void db::select_query2(read_file& file, str_tree* m_tree, str column){
  str temp_fila, temp;
  u_int pos_column, j, i;

  j = 0;
  pos_column = 0;
  temp.clear();
  getline(file, temp_fila);
  int tam = temp_fila.size();

  std::vector<str > aea;
  for(int i=0; i<tam; i++){
      if(temp_fila[i] != ','){ 
         temp += temp_fila[i];
          if(temp_fila[i-1]==','){
             temp = temp_fila.substr(0,i-1);
             temp_fila = temp_fila.erase(0,i-1);
             temp_fila = temp_fila.erase(0,1);
             aea.push_back(temp);
           }
         }
     temp.clear();
    }

   for(int i=0; i<aea.size(); i++){
          if(column == aea[i]){
            pos_column = i;
            break;
          }
    }


  //std::cout <<"pos_colum : "<< pos_column<<std::endl;
  int id_fila = 1;
  //pos_column = 1;

  while (! file.eof() ){
    j = 0;
    i = 0;
    temp_fila.clear();
    temp.clear();
    getline(file, temp_fila);
    //std::cout << "select_q2 in while  "<< temp_fila << std::endl;
    while(j <= temp_fila.size())
    {
      if(temp_fila[j] != ',' && j != temp_fila.size()){
        temp += temp_fila[j];
      }
      else if(i != pos_column){
        temp.clear();
        i++;
      }
      else
      {
        temp.erase(std::remove_if(temp.begin(), temp.end(), isspace), temp.end());
        //std::cout <<"temp : "<< temp<<std::endl;
        m_tree->insert(temp, intToString(id_fila));
        break;
      }
      j++;
    }
    id_fila++;
  }

}

void db::read_index(read_file& file, str_tree* m_tree) {
  str temp_fila, temp_data, temp_f;
  u_int size_fila, j, i;
  j=1;

  while (! file.eof() ){
    getline(file, temp_fila);
    i = 0;
    size_fila = temp_fila.size();
    temp_data.clear();
    temp_f.clear();

    if(size_fila == 0)
      break;

    while(temp_fila[i] != ';')
    {
      temp_data += temp_fila[i];
      i++;
    }
    i++;

    temp_f.clear();
    while(i < size_fila)
    {
      if (temp_fila[i] != ';')
        temp_f += temp_fila[i];
      else
      {
        m_tree->insert(temp_data, temp_f);
        temp_f.clear();
      }
      i++;
    }
    m_tree->insert(temp_data, temp_f);
  }
}

void db::delete_query(read_file& file, txt_file& outfile, str_vec columns, str name, str column){
  str temp, temp2, temp3, temp_name, vchar_value_found, vchar_val_to_compare;
  str_vec res;
  uint_vec types (columns.size() );
  u_int type;
  int pos = -1, i; //so if there's not a WHERE clause, the IF will never begin
  LL value_found, val_to_compare;
  read_file getting_columns;
  bool broke = 0, last_col = 0;

  temp_name = name + ".table";
  char* file_name = new char[temp_name.size() + 1];
  for (i = 0; i < temp_name.size(); i++){
    file_name[i] = temp_name.at(i);
  }
  file_name[i] = '\0';

  getting_columns.open(file_name); //copy of file

  delete [] file_name;
  temp_name.clear();
  temp.clear();

  //if (this->query_where){ //finding the atributes
  getline(getting_columns, temp2);
  for(i = 0; i < temp2.size(); i++){
    if (temp2.at(i) == ',') {
      //std::cout << "values_to_compare.at(0) is: " << this->values_to_compare.at(0) << std::endl;
      if (temp == column ){
        type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->VARCHAR(N), 2->DATE
        broke = 1;
        break;
        //pos will store the number of column we have to check at the table
      } //else
      temp.clear();
    } else {
      temp += temp2.at(i);
    }
  }
  if (!broke){
    if (temp == column ){
      type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->VARCHAR(N), 2->DATE
    }
  }
  //}
  bool first_line = true;
  while (! file.eof() ){
    temp2.clear();
    getline(file, temp2);
    temp.clear();
    int position = 0;
    temp_name.clear();
    last_col = 0;
    for(i = 0; i < temp2.size(); i++){
      if ( temp2.at(i) == ',' ) {
        temp3 = temp_name;
        temp3.erase(std::remove_if(temp3.begin(), temp3.end(), isspace), temp3.end());
        if (pos == position){
          last_col = 1;
          if (type == 0){ //do the cast to the type it is
            value_found = stringToLL(temp3);
            val_to_compare = stringToLL(values_to_compare.at(0) );
            this->query_where = 1;
            if (this->comparator == 0){
              if (value_found == val_to_compare) to_insert = 1;
            }
            else if (this->comparator == 1){
              if (value_found > val_to_compare) to_insert = 1;
            }
            else {
              if (value_found == val_to_compare){
                to_insert = 1;
              }
            }
          } else if (type == 1){
            vchar_value_found = temp3;
            vchar_val_to_compare = values_to_compare.at(0);
            if (this->comparator == 0){
              if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
            }
            else if (this->comparator == 1){
              if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
            }
            else {
              if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
            }
          } else {
            ; //same as above but with date
          }

          //do the respective comparison with this->comparator and the value
          //THIS COMPARATOR: 0 <, 1 >, 2 =
          //for now, the value is only this->values_to_compare.at(0)
        }
        position++;
        temp += ',';
        temp3.clear();
        temp_name.clear();
      } else {
        temp += temp2.at(i);
        temp_name += temp2.at(i);
      }
    }
    if (! last_col ){
      temp3 = temp_name;
      temp3.erase(std::remove_if(temp3.begin(), temp3.end(), isspace), temp3.end());
      if (pos == position){
        last_col = 1;
        if (type == 0){ //do the cast to the type it is
          value_found = stringToLL(temp3);
          val_to_compare = stringToLL(values_to_compare.at(0) );
          this->query_where = 1;
          if (this->comparator == 0){
            if (value_found == val_to_compare) to_insert = 1;
          }
          else if (this->comparator == 1){
            if (value_found > val_to_compare) to_insert = 1;
          }
          else {
            if (value_found == val_to_compare){
              to_insert = 1;
            }
          }
        } else if (type == 1){
          vchar_value_found = temp3;
          vchar_val_to_compare = values_to_compare.at(0);
          if (this->comparator == 0){
            if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
          }
          else if (this->comparator == 1){
            if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
          }
          else {
            if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
          }
        } else {
          ; //same as above but with date
        }
      }

    }
    if (first_line)outfile << temp << std::endl;
    if ( ! this->to_insert && !first_line) outfile << temp << std::endl;
    else{
      if (!first_line){
        temp.clear();
        while (temp.size() <= 59){
          temp += ' ';
        }
        temp += '\n';
        outfile << temp;
      }
    }
    this->to_insert = 0;
    first_line = false;
  }
}

void db::update_query(read_file& file, txt_file& outfile, str_vec columns, str_vec values, str name, str column){
  str temp, temp2, temp3, temp_name, vchar_value_found, vchar_val_to_compare;
  str_vec res;
  uint_vec types (columns.size() ); //types: if boolean operators are used
  uint_vec positions (columns.size()); //positions: positions of the columns in the table
  u_int type, j;
  u_int it;
  int pos = -1, i; //so if there's not a WHERE clause, the IF will never begin
  LL value_found, val_to_compare;
  read_file getting_columns;
  bool broke = 0, last_col = 0;

  temp_name = name + ".table";
  char* file_name = new char[temp_name.size() + 1];
  for (i = 0; i < temp_name.size(); i++){
    file_name[i] = temp_name.at(i);
  }
  file_name[i] = '\0';

  getting_columns.open(file_name); //copy of file

  delete [] file_name;
  temp_name.clear();
  temp.clear();

  //if (this->query_where){ //finding the atributes
  getline(getting_columns, temp2);
  for(i = 0; i < temp2.size(); i++){
    if (temp2.at(i) == ',') {
      if (temp == column ){
        type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->VARCHAR(N)
        broke = 1;
        break;
        //pos will store the number of column we have to check at the table
      } //else
      if (broke) {
        break;
      }
      temp.clear();
    } else {
      temp += temp2.at(i);
    }
  }
  if (!broke){
    if (temp == column ){
      type = finding_atribute_type(temp, name, pos);//finding atribute type: 0->INTEGER, 1->VARCHAR(N), 2->DATE
    }
  }
  temp.clear();
  for (it = 0; it < columns.size(); it++){ //getting positions of columns to update
    broke = 0;
    int k = 0;
    for(j = 0; j < temp2.size(); j++){
      if (temp2.at(j) == ',') {
        if (temp == columns.at(it) ){
          positions.at(it) = k; //keeping a relation: columns[it] position is in positions[it]
          broke = 1;
          break;
          //pos will store the number of column we have to check at the table
        } //else
        temp.clear();
        k++;
      } else {
        temp += temp2.at(j);
      }
    }
    if (!broke){
      if (temp == columns.at(it) ){
        positions.at(it) = k;
      }
    }
  }
  bool first_line = true;
  while (! file.eof() ){
    temp2.clear();
    getline(file, temp2);
    temp.clear();
    int position = 0;
    temp_name.clear();
    last_col = 0;
    for(i = 0; i < temp2.size(); i++){ //getting the lines of data
      if ( temp2.at(i) == ',' ) {
        temp3 = temp_name;
        temp3.erase(std::remove_if(temp3.begin(), temp3.end(), isspace), temp3.end());
        if (pos == position){
          last_col = 1;
          if (type == 0){ //do the cast to the type it is
            value_found = stringToLL(temp3);
            val_to_compare = stringToLL(values_to_compare.at(0) );
            this->query_where = 1;
            if (this->comparator == 0){ //in this case: to_insert = to_update
              if (value_found == val_to_compare) to_insert = 1;
            }
            else if (this->comparator == 1){
              if (value_found > val_to_compare) to_insert = 1;
            }
            else {
              if (value_found == val_to_compare){
                to_insert = 1;
              }
            }
          } else if (type == 1){
            vchar_value_found = temp3;
            vchar_val_to_compare = values_to_compare.at(0);
            if (this->comparator == 0){
              if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
            }
            else if (this->comparator == 1){
              if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
            }
            else {
              if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
            }
          } else {
            ; //same as above but with date
          }

          //do the respective comparison with this->comparator and the value
          //THIS COMPARATOR: 0 <, 1 >, 2 =
          //for now, the value is only this->values_to_compare.at(0)
        }
        position++;
        temp += ',';
        temp3.clear();
        temp_name.clear();
      } else {
        temp += temp2.at(i);
        temp_name += temp2.at(i);
      }
    }
    if (! last_col ){ //lines to 579 to 620 (aprox)
      temp3 = temp_name;
      temp3.erase(std::remove_if(temp3.begin(), temp3.end(), isspace), temp3.end());
      if (pos == position){
        last_col = 1;
        if (type == 0){ //do the cast to the type it is
          value_found = stringToLL(temp3);
          val_to_compare = stringToLL(values_to_compare.at(0) );
          this->query_where = 1;
          if (this->comparator == 0){
            if (value_found == val_to_compare) to_insert = 1;
          }
          else if (this->comparator == 1){
            if (value_found > val_to_compare) to_insert = 1;
          }
          else {
            if (value_found == val_to_compare){
              to_insert = 1;
            }
          }
        } else if (type == 1){
          vchar_value_found = temp3;
          vchar_val_to_compare = values_to_compare.at(0);
          if (this->comparator == 0){
            if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
          }
          else if (this->comparator == 1){
            if (vchar_value_found > vchar_val_to_compare) to_insert = 1;
          }
          else {
            if (vchar_value_found == vchar_val_to_compare) to_insert = 1;
          }
        } else {
          ; //same as above but with date
        }
      }

    }
    if (first_line)outfile << temp << std::endl;
    if ( this->to_insert && !first_line){
      temp = updateRow(temp, positions, values);
      outfile << temp << std::endl;
    } else if (!first_line) outfile << temp << std::endl;

    this->to_insert = 0;
    first_line = false;
  }
}

str_vec db::id_values(char* name){
  str_vec values;
  str value, real_value;
  int i;
  std::ifstream index_file;
  index_file.open(name);
  getline(index_file, value);
    if (index_file.is_open()) {
        while (index_file >> value){
            i=0;
            real_value.clear();
            //std::cout << value << "\n";
            while (value[i] != ';'){
                real_value += value[i];
                i++;
            }
         values.push_back(real_value);
        }
    }
    index_file.close();
  return values;
}



int main () {
  db DB;
  
  while (true){
    str query;
    std::cout<<"gbd=# ";
    getline(std::cin, query);
    DB.i_query(query);
  }


  return 0;
}


//CREATE INDEX idx_edad ON persona (edad);
//SELECT * FROM persona WHERE edad = 13 IDX = idx_edad ;
//INSERTAR VARIOS EN persona 1/R1,100/i usuario ;


//CREATE TABLA alumnos INTEGER id INTEGER edad VARCHAR(15) nombre VARCHAR(15) apellido DATE fecha ;
//CREATE TABLA alumnos INTEGER id INTEGER edad VARCHAR(15) nombre VARCHAR(15) apellido ;



//INSERTAR CON INDICE EN alumnos2 VALORES 21 100 ALumno_101 Apellido_101 24/01/2020 INDICE idx_edad.idx(1) S21 ;

//ELIMINAR CON INDICE EN alumnos2 WHERE edad = 52 INDICE idx_edad.idx ;

// 

//A RAM (indi1.idx);
