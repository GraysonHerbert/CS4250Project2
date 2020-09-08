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
#include <string>
#include <cctype>

//This class defines the nodes for the game. They hold the stacks of dollars and form the connections between them.
class Node{
  private:
    int dollars; //Holds the number of dollars the node has.
    std::vector<Node*> connected_nodes; //Holds pointers to all nodes connected to.
  
  public:
  //Constructs a node with passed number of dollars.
  Node(int Dollars){
    dollars = Dollars;
  }
  
  //Takes a pointer to a node passed to it and forms the connection.
  void connect_node(Node* to_connect){
    
    //Checking to make sure the nodes aren't already connected, and that the passed node isn't itself.
    if(!connected(to_connect) && to_connect != this){
      //Connecting the nodes
      connected_nodes.push_back(to_connect);
      to_connect->connected_nodes.push_back(this);
    }
    //Checking if itself was passed into the function.
    else if(to_connect == this){
      //Throwing the exception
      throw self_connect_error();
    }
    //Catching the case where the nodes are already connected
    else{
      //Throwing the exception
      throw already_connected_error();
    }
  }
  
  //Gives a dollar to all connected nodes.
  void give(){
    dollars -= connected_nodes.size();
    
    //Iterates through the list of connected nodes giving them each a dollar
    for(auto node : connected_nodes){
      node->dollars++;
      }
  }
  
  //Takes a dollar from all connected nodes.
  void take(){
    dollars += connected_nodes.size();
    
    //Iterates through the nodes taking a dollar from each.
    for(auto node : connected_nodes){
      node->dollars--;
    }
  }
  
  //Checks if the node passed in is already connected. If so returns true, else false
  bool connected(Node* to_check) const{
    //Iterates through the nodes searching for a matching node
    for(auto node : connected_nodes){
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

bool valid(int, char, char);

int main(){

  std::vector<Node> nodes;
  int num_of_nodes, dollars;
  bool running = true;
  std::string connector = "";
  
  do{
  std::cout << "How many nodes would you like to create? (2-7) ";
  std::cin >> num_of_nodes;
  
  if(num_of_nodes < 2 || num_of_nodes > 7){
      std::cout << "You must enter an integer between 2 and 7.\n";
  }
  } while(num_of_nodes < 2 || num_of_nodes > 7);
  
  for(int i = 0; i < num_of_nodes; i++){
      std::cout << "How many dollars should node " << i + 1 << " have? ";
      std::cin >> dollars;
      
      nodes.push_back(Node(dollars));
  }
  
while(running){
    //Prompts the user to input the connection command and repeats until both letters are valid
    do{
        std::cout << "Please input the two nodes you would like to connect: ";
        std::cin >> connector;
        if(connector == "quit"){
            running = false;
            break;
        }
    }while(!valid(nodes.size(), connector[0], connector[1]));
    
        //If one of the letters is invalid prints an error message
        if(!valid(nodes.size(), connector[0], connector[1]) && connector != "quit"){
        std::cout << "One of your node letters is invalid. Please Try again.\n";
      
        continue;
    
  
        //Attempts to connect the nodes in the commands. If an error is thrown it will be caught.
        try{
            nodes[static_cast<int>(connector[0]) - 97].connect_node(&nodes[static_cast<int>(connector[1]) - 97]);
        }
        //Prints an error message for a self connection error.
        catch(Node::self_connect_error){
        std::cout << "You cannot connect a node to itself. Please try again.\n";
        }
        //Prints an error message for a redundant connection error
        catch(Node::already_connected_error){
        std::cout << "You cannot have more than one connection between two nodes. Please try again.\n";
      
        }
    }
}
    
  return EXIT_SUCCESS;
}

//Tests the validity of the two node letters. Returns true if they are valid, false if they are not
bool valid(int num_of_nodes, char node_1, char node_2){
  //Converting all letters to lowercase
   node_1 = tolower(node_1);
   node_2 = tolower(node_2);
  
  //If one of them is not a letter it returns false.
  if(!isalpha(node_1) || !isalpha(node_2)){
       return false;
   }
  
  //If they are both letters within the valid set of letters it returns true, else returns false;
  return static_cast<int>(node_1) - 97 < num_of_nodes && static_cast<int>(node_2) - 97 < num_of_nodes;
}
