//Program Title: The Dollar Game
//File Name: Main.cpp
//External Files: N/A
//Names: Grayson Herbert, Jacob Esswein
//Email: gdhxnw@umsystem.edu, TODO
//Course: 4250-001
//Date: TBD
//Description: A game to play including a graph and stacks of dollars. The goal is to get every stack with positive dollars.
//Resources: N/A

#include <iostream>
#include <vector>

class Node{
  private:
    int dollars;
    std::vector<Node*> nodes;
  
  public:
  
  Node(int Dollars){
    dollars = Dollars;
  }
  
  void connect_node(Node* to_connect){
    nodes.push_back(to_connect);
    to_connect->nodes.push_back(this);
  }
  
  void give(){
      dollars -= nodes.size();
      
      for(auto node : nodes){
          node->dollars++;
      }
  }
  
  void print_amount() const{
      std::cout << dollars << std::endl;
  }
};

int main(){


  std::vector<Node*> nodes;
  
 
  return EXIT_SUCCESS;
}
