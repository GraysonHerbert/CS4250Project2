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

//This class defines the nodes for the game. They hold the stacks of dollars and form the connections between them.
class Node{
  private:
    int dollars; //Holds the number of dollars the node has.
    std::vector<Node*> nodes; //Holds pointers to all nodes connected to.
  
  public:
  //Constructs a node with passed number of dollars.
  Node(int Dollars){
    dollars = Dollars;
  }
  
  //Takes a pointer to a node passed to it and forms the connection.
  void connect_node(Node* to_connect){
    if(!connected(to_connect) && to_connect != self){
      nodes.push_back(to_connect);
      to_connect->nodes.push_back(this);
    }
    else{
      throw Already_connected_error();
    }
  }
  
  //Gives a dollar to all connected nodes.
  void give(){
      dollars -= nodes.size();
      
      for(auto node : nodes){
          node->dollars++;
      }
  }
  
  //Takes a dollar from all connected nodes.
  void take(){
    dollars += nodes.size();
    
    for(auto node : nodes){
      node->dollars--;
    }
  }
  
  //Checks if the node passed in is already connected. If so returns true, else false
  bool connected(Node* to_check) const{
    for(auto node : nodes){
      if(node == to_check){
        return true; 
      }
    }
    return false;
  }
  
  //Prints the amount of dollars held by the node.
  void print_amount() const{
      std::cout << dollars << std::endl;
  }
  
  class already_connected_error{};
  class self_connect_error{};
};

int main(){


  std::vector<Node*> nodes;
  
 
  return EXIT_SUCCESS;
}
