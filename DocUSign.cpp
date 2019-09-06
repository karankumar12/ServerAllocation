#include <iostream> 
#include <vector>
#include <algorithm>
#include <random>
using namespace std; 

//1. The following program takes in the name and the size of the server in the format "Name:Size"
//2. Each server info will be treated as a single argument and the name and size of each will be parsed into two parallel arrays
//3. The program will then use the sizes of servers as weights and generate weighted random indices that will correspond to the respective server names
//4. Finally the program will output of the name of the server that was generated based on the size

//Functionality
// The program can take in multiple server names and sizes
// The program can take in multi-letter server names, such as "Server1" etc.
// The program checks if the server size entered is a valid number or not. The program terminates if an invalid size is passed, such as 'a'
// The program can read server sizes of multiple digits, for example 10001 etc.

int IndexGenerator(int [], int);
int main(int argc, char** argv) 
{
    //A count of the number of servers
    const int num_servers = argc - 1;
    
    //Array to hold the names of the server
    string server_name[num_servers];
    
    //Array to hold the size of the server
    int server_size[num_servers];
    
    //Parsing the names and sizes into the arrays from the argument
    for(int i = 0; i < num_servers; i++){
        
        //Parsing the server name, the name and sized are parsed by usign ':' as the delimiting character
        char character;
        server_name[i] = "";
        int j = 0;
        character = argv[i+1][j];
        while(character != ':' && character != '\n'){
            server_name[i] += character;
            j++;
            character = argv[i+1][j];
        }

        //The program now moves on to parse the size of the given server and puts it in a parallel array of sizes
        j++;
        server_size[i] = 0;
        character = argv[i+1][j];
        while(character != '\0'){
            //If the size passed is invalid, the program will terminate after the error message
            if((int)(character - '0') > 9){
                 cout << "Invalid Size. Please check the server size entered for " << server_name[i] << endl;
                 return 0;
            }
            server_size[i] = server_size[i]*10 + (character - '0');
            j++;
            character = argv[i+1][j];
        }
        
    }

    //Generating the random index using server size as weights
    int randomIndex = IndexGenerator(server_size, num_servers);
 
    //Outputting the server name that corresponds to the given index generated
    cout << server_name[randomIndex] << endl;
  
    return 0; 
} 


//Function to generate a weighted random index
int IndexGenerator(int weights[], int num){
    vector<int> temp(weights, weights+num);
    random_device rd;
    
    for (int i = 1; i < num; ++i){
         temp[i] += temp[i-1];
    }

    return lower_bound(temp.begin(), temp.end(), rd() % temp.back() + 1) - temp.begin();
}