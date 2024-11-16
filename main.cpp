#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

void erase (int microseconds) {
  usleep(microseconds); 
  std::cout << "\033[2J\033[1;1H";
}

class node {
  public: 
    string data;
    node* next;
    bool flipped;    

    node(string data) {
      this->data = data;
      this->next = nullptr;
      this->flipped = false;
    }
};

class list {
  public: 
    node* head;

    list () {
      head = nullptr;
    }

    void add (string data) {
      node* new_node = new node (data);

      if (head == nullptr) {
        head = new_node;
      }

      else {
        node* current = head;

        while (current->next != nullptr) {
          current = current->next;
        }

        current->next = new_node;
      }
    }		

    void print () {
      cout << "\n";
      node* current = head;
      while (current != nullptr){
        if(current->flipped == false){
          cout<< "🟥 ";
        }
        else {
          cout << current->data << " ";
        }
        current = current->next;
      }
      cout << "\n";
    }

    node* get_node (int position) {
      node* current = head;
      
      for(int i = 0; i < position; i++) {
        current = current->next;
      }

      return current;
    }

    bool check_match (node* first, node* second) {
      if (first->data == second->data) {
        return true;
      } else {
        return false;
      }
    }

    void flip_card (node* card) {
      if(card->flipped == true){
        card->flipped = false;
      }
      else{
        card->flipped = true;
      }
    }

    bool check_win () {
      node* current = head;
      int counter = 0;
      
      for(int i = 0; i < 8; i++){
        if(current->flipped == false){
          counter += 1;
        }
        current = current->next;
      }
      
      if(counter == 0){
        cout<<"\nyou win📺🥊🎙️🫅❓🤔👑🎭\n";
        return true;
      }
      else{
        cout<<"\nwrong answer buddy🤵‍♂️\n";
        return false;
      }   
    } // check win function is wrong maybe !!!!

    void shuffle () {
      for(int j = 0; j < 204; j++){
        int random1 = rand() % 8;
        int random2 = rand() % 8;

        node* card1 = get_node (random1);
        node* card2 = get_node (random2);

        string value1 = card1->data;
        string value2 = card2->data;

        card1->data = value2;
        card2->data = value1;
      }
    }

    void print_flipped (int position1, int position2) {
      cout << "\n";
      node* current = head;
      for (int i = 0; i < 8; i++) {
        if(current->flipped == false && position1 != i && position2 != i){
          cout<< "🟥 ";
        }
        else {
          cout << current->data << " ";
        }
        current = current->next;
      }
      cout << "\n";
    }
};

int main () { 
  srand (time (0));

  list l;
  l.add("🫃");
  l.add("🫃");
  l.add("👬");
  l.add("👬");
  l.add("🌍");
  l.add("🌍");
  l.add("👨‍🦼");
  l.add("👨‍🦼");
  
  l.shuffle();

  while (true) {
    erase (2000000);
    l.print();
  
    int ask1;
    std::cout << "\npick ur first card? ";
    std::cin >> ask1;
  
    int ask2;
    std::cout << "pick ur first card? ";
    std::cin >> ask2;

    ask1 -= 1;
    ask2 -= 1;
  
    l.print_flipped(ask1, ask2);
  
    if(l.check_match(l.get_node (ask1), l.get_node (ask2)) == true){
      l.flip_card(l.get_node (ask1));
      l.flip_card(l.get_node (ask2));
    }
  
    if(l.check_win() == true){
      break;
    }
  }

}
