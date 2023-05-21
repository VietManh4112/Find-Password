#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <ctime>

using namespace std;

const int DO_DAI = 150;
const int SO_CA_THE = 900;
const int CA_THE_BEST = 45;
const int CA_THE_RAND = 15;
const float XS_DOT_BIEN = 0.08f;

// Lop luu tru mot ca the duy nhat
class Ca_the {
  string word;
  float fitness_value;
public:
  Ca_the(const string& word, const string& password) : word(word) {
    fitness_value = this->fitness(password);
  }
  Ca_the(const Ca_the& indiv) {
    this->word = indiv.word;
    this->fitness_value = indiv.fitness_value;
  }

  // Tinh toan muc do phu hop dua tren so luong ky tu giong voi mat khau
  // Neu ki tu giong nhau va o cung 1 vi tri thi tang diem
  float fitness(const string& password) {
    int score = 0;
    for (unsigned int i = 0; i < DO_DAI; i++){
      if (password[i] == this->word[i]) {
            score++;
        }
    }
    this->fitness_value = (float)score / DO_DAI * 100;
    return this->fitness_value;
  }

  const string& getWord() const {
    return this->word;
  }
  string& getWord() {
    return this->word;
  }
  const float getFitness() const {
    return this->fitness_value;
  }
  bool operator<(const Ca_the& inv) const {
    if (this->fitness_value <= inv.fitness_value)
      return false;
    return true;
  }
};

// Tao mot tu nhan gia tri ASSCII tu 32-126
string random(const int length) {
    string ret;
    ret.reserve(length);
    for (int i = 0; i < length; i++)
        ret.push_back(rand() % 95 + 32);
    return ret;
}

// Ham tao the he dau tien
void first(vector<Ca_the>& pop, const int size, const string& password) {
    pop.reserve(size);
    for (int i = 0; i < size; i++) {
        pop.emplace_back(random(150), password);
    }
}

// Kiem tra do trung lap co phai 100% k
bool check(const vector<Ca_the>& n, const string& password) {
    //Kiem tra ca the dau tien
    if (n[0].getFitness() == 100.0f)
        return true;
    return false;
}

// Chon cac cap bo me
void select(const vector<Ca_the>& n, vector<Ca_the>& o) {
  o.reserve(CA_THE_BEST + CA_THE_RAND);
  // Cac ca the toi uu nhat
  for (unsigned int i = 0; i < CA_THE_BEST; i++) {
        o.push_back(n[i]);
  }

  // Cac ca the ngau nhien
  for (unsigned int i = 0; i < CA_THE_RAND; i++)
    o.push_back(n[rand() % 900]);
}

// Dot bien
void mutate(Ca_the& child) {
  for (unsigned int i = 0; i < child.getWord().size(); i++) {
    if ((float)rand()/RAND_MAX < XS_DOT_BIEN) {
      child.getWord()[i] = (char)(rand() % 95 + 32);
    }
  }
}

// Ham nhan 2 ca the va tao ra cac ca the con
Ca_the create_child(const Ca_the& parent1, const Ca_the& parent2, const string& password) {
    string child_word;
    // Lai ghep 2 ca the bo me bang cach chon 1 diem danh dau
     // int ran = rand() % DO_DAI;
     // for (int i = 0; i < ran; i++) {
     //    child_word.push_back(parent1.getWord()[i]);
     // }
     // for (int i = ran; i < DO_DAI; i++) {
     //    child_word.push_back(parent2.getWord()[i]);
     // }

    // Lai ghep bang cach random thu tu cua cac ki trong ca the bo me
  //  for (unsigned int i = 0; i < DO_DAI; i++) {
  //  int ran = rand() % 2;
  //  if (ran == 0) child_word.push_back(parent1.getWord()[i]);
  //  else child_word.push_back(parent2.getWord()[i]);
  // }
  
  // Lai ghep bang cach lay ki tu cua bo hoac me giong voi ki tu password 
  for (int i = 0; i < DO_DAI; i++) {
       if(parent1.getWord()[i] == password[i]) {
            child_word.push_back(parent1.getWord()[i]);
       } else if (parent2.getWord()[i] == password[i]) {
            child_word.push_back(parent2.getWord()[i]);
       } else {
            int ran = rand() % 2;
            if (ran == 0) child_word.push_back(parent1.getWord()[i]);
            else child_word.push_back(parent2.getWord()[i]);
       }
  }

  // Tạo con
  Ca_the child(child_word, password);
  // Dot bien
  mutate(child);
  // Tinh ti le trung lap
  child.fitness(password);
  return child;
}

// Xoa quan the cu va tao ra quan the moi voi so luong bang quan the cu
void create_children(vector<Ca_the>& n, const vector<Ca_the>& o, const string& password) {
  n.erase(n.begin(), n.end());// Xoa toan bo ca the cu
  // Tao so luong quan the moi = SO_CA_THE
  for (unsigned int i = 0; i < o.size()/2; i++) {
    for (int j = 0; j < 30; j++) {
      n.push_back(create_child(o[i], o[o.size() - i - 1], password));
    }
  }
}

int main() {
  srand(time(NULL));
  string pass = random(DO_DAI);

  vector<Ca_the> n;

  // Tao the he dau
  int gen = 0;
  first(n, SO_CA_THE, pass);
  sort(n.begin(), n.end());
  
  // Lap toi khi ti le trung lap la 100%
  while (!check(n, pass)) {
    gen++;
    // Cac ca the bo me the he truoc
    vector<Ca_the> o;
    
    // Chon cac ca the bo me the he moi
    select(n, o);
    
    // Tao ra cac ca the con
    create_children(n, o, pass);
    sort(n.begin(), n.end());
    cout << n[0].getWord() << endl;
  }

  cout << "password can tim: " << pass << endl;
  cout << "So the he can thiet: " << gen << endl;
  cout << "password tot nhat: " << n[0].getWord() << endl; 
  return 0;
}