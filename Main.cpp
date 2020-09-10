//Program Title: The Dollar Game
//File Name: Main.cpp
//External Files: N/A
//Names: Grayson Herbert, Jacob Esswein
//Email: gdhxnw@umsystem.edu, essweinjacob@gmail.com
//Course: 4250-001
//Date: 9/10/2020
//Description: A game to play including a graph and stacks of dollars. The goal is to get every stack with positive dollars.
//Resources: N/A
//Language: C++

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

    int get_dollars() const{
        return dollars;
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

bool valid(int, char); //Checks for validity of the character for a node
bool won(std::vector<Node>); //Checks if the player has won
void print_info(std::vector<Node>); //Prints the information on node values
int max_edges(int); //Calculates the maximum number of edges

int main(){

    std::vector<Node> nodes; //Holds the nodes the user creates
    int num_of_nodes; //Stores the number of nodes
    int dollars; //Holds the input for how many dollars should be in each node
    int turn_counter = 0; //Counts the total number of turns taken.
    int num_of_edges = 0; //Holds the number of edges
    std::string connector = ""; //Holds the input for which nodes to connect
    std::string numeric_input = "";
    char input, input_2; //These hold input characters for selecting nodes and giving and taking.

    std::cout << "This is a game called the dollar game. You will give instructions to construct a graph, then assign" <<
                 "values to each node. Your goal is to get all nodes to have 0 or more dollars by giving and taking " <<
                 "from nodes. Good luck!\n";


    //This loop repeats until the user enters a proper number of nodes (2-7)
    do{
        std::cout << "How many nodes would you like to create? (2-7) ";
        std::cin >> numeric_input;
        try {
            num_of_nodes = stoi(numeric_input);
        }
        catch(std::invalid_argument){
            std::cout << "Your input is not an integer, it must be an integer. Please try again.\n";
            continue;
        }

        if(num_of_nodes < 2 || num_of_nodes > 7){
            std::cout << "You must enter an integer between 2 and 7.\n";
        }
    } while(num_of_nodes < 2 || num_of_nodes > 7);

    do{
        std::cout << "How many edges do you want? You must use at least " << num_of_nodes - 1 << " and at most " << max_edges(num_of_nodes) << ' ';
        std::cin >> numeric_input;
        try {
            num_of_edges = stoi(numeric_input);
        }
        catch(std::invalid_argument){
            std::cout << "Your input is not an integer, it must be an integer. Please try again.\n";
            continue;
        }
    } while(num_of_edges < num_of_nodes - 1);

    //Iterates through the nodes and prompts the user for the number of dollars for each.
    for(int i = 0; i < num_of_nodes; i++){
        std::cout << "How many dollars should node " << i + 1 << " have? ";
        std::cin >> numeric_input;
        try {
            dollars = stoi(numeric_input);
        }
        catch(std::invalid_argument){
            std::cout << "Your input is not an integer, it must be an integer. Please try again.\n";
            continue;
        }

        //Constructs the node with the given dollars and pushes it onto the back of the vector
        nodes.push_back(Node(dollars));
    }

    //Handles node connection selection stops when user inputs "quit"
    for(int i = 0; i < num_of_edges; i++){
        //Prompts the user to input the connection command and repeats until both letters are valid
        do{
            std::cout << "Please input the two nodes you would like to connect: ";
            std::cin >> connector;
            if(connector == "quit" && num_of_nodes > num_of_edges){
                break;
            }

            //If one of the letters is invalid prints an error message
            if(!valid(nodes.size(), connector[0]) || !valid(nodes.size(), connector[1])/* && connector != "quit"*/){
                std::cout << "One of your node letters is invalid. Please Try again.\n";
                i--;
            }
        }while(!valid(nodes.size(), connector[0]) || !valid(nodes.size(), connector[1]));

        //Attempts to connect the nodes in the commands. If an error is thrown it will be caught.
        try{
            nodes[static_cast<int>(connector[0]) - 97].connect_node(&nodes[static_cast<int>(connector[1]) - 97]);
        }
            //Prints an error message for a self connection error.
        catch(Node::self_connect_error){
            std::cout << "You cannot connect a node to itself. Please try again.\n";
            i--;
        }
            //Prints an error message for a redundant connection error
        catch(Node::already_connected_error){
            std::cout << "You cannot have more than one connection between two nodes. Please try again.\n";
            i--;
        }

    }

    //This is the game loop. Ends when the user inputs "q" or "Q"
    do{
        std::cout << "Select a node (a-" << static_cast<char>(num_of_nodes + 96) << ") or input q to quit. ";
        std::cin >> input;

        if(valid(num_of_nodes, input)){
            std::cout << "Would you like that node to give (g) or take (t)? ";
            std::cin >> input_2;

            if(input_2 == 'g'){
                nodes[static_cast<int>(input) - 97].give();
            }
            else if(input_2 == 't'){
                nodes[static_cast<int>(input) - 97].take();
            }
            else{
                std::cout << "Your input was invalid. The valid options are g and t. To try again select the same node and input g or t.\n";
            }
        }

        print_info(nodes);

        if(won(nodes)){
            std::cout << "Congratulations! You won! You may continue to play or input q to quit.\n";
        }

        turn_counter++;
    } while(tolower(input) != 'q');

    std::cout << "Final node amounts:\n";
    print_info(nodes);
    std::cout << "You took " << turn_counter << " moves.\n";
    std::cout << (won(nodes) ? "You won!\n" : "You did not win.\n");

    return EXIT_SUCCESS;
}

//Tests the validity of the node letter. Returns true if valid, false if invalid
bool valid(int num_of_nodes, char node_char){
    //Converting lowercase
    node_char = tolower(node_char);

    //If not a letter returns false.
    if(!isalpha(node_char)){
        return false;
    }

    //If within the valid set of letters returns true, else returns false;
    return static_cast<int>(node_char) - 97 < num_of_nodes;
}

//Checks to see if the user won.
bool won(std::vector<Node> nodes){
    //Iterates through the nodes making sure they are all >= 0
    for(auto node : nodes)
    {
        if(node.get_dollars() < 0){
            return false;
        }
    }
    return true;
}

//Prints each node and the number of dollars they have.
 void print_info(std::vector<Node> nodes){
    //Iterates through the nodes printing information for each
    for(int i = 0; i < nodes.size(); i++){
        std::cout << "Node " << static_cast<char>(i + 97) << " has " << nodes[i].get_dollars() << " dollars.\n";
    }
}

//Calculates the maximum number of edges based on number of nodes
int max_edges(int n){
    int total = 1;

    //Sums up the total
    for(int i = 2; i < n; i++){
        total += i;
    }

    return total;
}
