/* Chain stores
 *
 * Desc:
 *   This program reads input data concerning chain stores from an input
 * file, the lines of which are of the form:
 * chain_store;store_location;product_name;product_price.
 * The program checks if each line consists of the abovementioned four
 * data fields.
 *   The data written in the file is collected into an appropriate data
 * structure consisting of STL containers and structs. After that the user
 * can make searches for the data structure by using the commands
 * chains, stores, selection, cheapest, and products. These commands
 * have a varying number of parameters, and the program checks if the
 * user gave a correct number of parameters and if the given parameters
 * (chain store, store location, product name) can be found from the data
 * structure.
 *   The program terminates with the command quit.
 *
 * Program author ( Fill with your own info )
 * Name: Huma Fatima Azmi Shaikh
 * Student number: 152757243
 * UserID: nsv323 ( Necessary due to gitlab folder naming )
 * E-Mail: humafatimaazmi.shaikh@tuni.fi
 *
 *Program author
 * Name: Vivetha Lakshmana Perumal
 * Student number: 153046791
 * UserID:hvm255
 * E-Mail: vivetha.lakshmanaperumal@tuni.fi
 *
 * Notes about the program and it's implementation (if any):
 *
 * */


#include <iostream>
#include<fstream>
#include<string>
#include<map>
#include<vector>
#include<iomanip>
#include<set>



using namespace std;

struct Product {
    string product_name;
    double price;
};
 enum FIELDS {CHAIN, LOCATION, PRODUCT, PRICE, FIELD_COUNT};

const double OUT_OF_STOCK=-0.1;
const string ERROR_FIELD = "Error: the input file has an erroneous line" ;
const string ERROR_CANT_FIND_FILE="Error: the input file cannot be opened";

using products_list = vector<Product>;
using Store = map<string, products_list>;
using Chains = map<string, map<string, vector<Product>>>;


//Functions for file reading

vector<string>split(string input,
                     const char& delimiter);
bool read_input_file(Chains& chains);
bool check_faulty_field(vector<string>& fields);
void update_product(Chains& chains,
                    const string& chain,
                    const string& location,
                    const string& product,
                    double price);



//Functions for commands
void cheapest_product(string user_product_name, const Chains& chains)
{
   double cheapest=0;
   vector<string> cheapest_chains;
   vector<string> cheapest_stores;
   bool is_product_out_of_stock=false;
   set<string> product_list_unique={ };

   for (const auto&  chain : chains )
   {
      for (const auto&  store : chain.second)
      {
          for(const auto&  product : store.second)
          {
              product_list_unique.insert(product.product_name);

              if( (product.product_name == user_product_name) and (product.price != OUT_OF_STOCK) )
              {
                  if(cheapest_stores.empty())
                  {
                      cheapest_stores.push_back(store.first);
                      cheapest_chains.push_back(chain.first);
                      cheapest = product.price;
                  }
                  else if (product.price == cheapest)
                  {
                     cheapest_stores.push_back(store.first);
                     cheapest_chains.push_back(chain.first);
                  }
                  else if (product.price < cheapest)
                  {
                    cheapest_stores.clear();
                    cheapest_stores.push_back(store.first);
                    cheapest_chains.push_back(chain.first);
                    cheapest = product.price;
                  }
               }
              else if( (product.product_name == user_product_name) and (product.price == OUT_OF_STOCK) )
              {

                is_product_out_of_stock=true;
              }
          }
      }
   }



      if(cheapest_chains.size()==0)
      {

          if( is_product_out_of_stock==true )
          {
             cout<<"The product is temporarily out of stock everywhere"<<endl;
          }
          else
          {
          cout<<"The product is not part of product selection"<<endl;
          }
      }
      else
      {
          //printing with two decimals
         cout << fixed << setprecision(2)<< cheapest <<" euros"<<endl;
         for ( vector<string>::size_type index=0;index < cheapest_stores.size();index++)
           {

           cout<<cheapest_chains.at(index)<<" "<<cheapest_stores.at(index)<<endl;
            }
       }
}

//Function for Products Unique list:
void product_list(const Chains& chains)
{

   set<string> product_list_unique={ };

   for (const auto&  chain : chains )
   {
      for (const auto&  store : chain.second)
      {
          for(const auto&  product : store.second)
          {
              product_list_unique.insert(product.product_name);

          }
      }
   }


   for (const string& item : product_list_unique)
   {
       //prints the names of all the products in alphabetical order
       cout << item <<endl;
     }

}


vector<string> split(string input,
                     const char& delimiter,
                     bool ignore_empty= false)
{
    vector <string> result;
    while ( input.find(delimiter)!= string::npos)
    {
     string word =input.substr (0, input.find(delimiter));
     input = input.substr(input.find(delimiter)+1, input.size());

     if (not (ignore_empty and word.empty()))
     {
         result.push_back(word);
     }
    }

    if (not (ignore_empty and input.empty()))
    {
        result.push_back(input);
    }

    return result;

}

//Function to check if fields are right
bool check_faulty_field(vector<string>& fields)
{


    if (fields.size() != FIELD_COUNT)
    {
                return false;
    }

   //check for field consisting of only spaces
    for (const string &field:fields)
    {
        if (field.find_first_not_of( ' ' ) == string::npos)
        {

            return false;
        }
     }
    return true;

}

//Function to update product prices
void update_product(Chains& chains,
                    const string& chain,
                    const string& location,
                    const string& product,
                    double price)
{
    if (chains.find (chain) == chains.end())
    {
        chains.insert({chain, {}});
    }
    if (chains.at(chain).find(location) == chains.at(chain).end())
    {
            chains.at(chain).insert({location, {}});
    }


    for (Product& existing_product: chains.at(chain).at(location))
    {
        if(existing_product.product_name==product)
        {
            existing_product.price = price;
            return;
        }

    }
    chains.at(chain).at(location).push_back (Product{product,price});

}


void print(const std::vector<string>& vec) {

    cout<<"output of the field"<< endl;
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}



bool read_input_file(Chains& chains)
{
    string input_file= " ";
    cout<<"Input file: " ;
    getline(cin,input_file);

    ifstream file_object(input_file);
    if (not file_object)
    {
        cout<<ERROR_CANT_FIND_FILE<< endl;
        return false;
     }

    string line = " " ;
    while (getline (file_object,line))
      {
       vector<string> fields = split(line, ';', false);

       if (not check_faulty_field (fields))
       {
        cout<<ERROR_FIELD << endl;

        return false;
       }



     double price=0.0;

     if ( fields.at(PRICE)=="out-of-stock")
      {
         price=OUT_OF_STOCK;
      }
     else
     {
         price=stod(fields.at(PRICE));
     }

     update_product(chains, fields.at(CHAIN),fields.at(LOCATION), fields.at(PRODUCT), price);
    }

    return true;
}

//Function for commands
int command_chains(const Chains& chains)
{

    string user_commands;
    while (true)
    {
        cout<<"> " ;
        getline(cin,user_commands);

       vector<string> user_command_fields = split(user_commands, ' ', false);


       if (user_command_fields.at(0)=="quit")
       {

           if (user_command_fields.size()!=1)
           {
               cout<<"Error: error in command "<< user_command_fields.at(0)<<endl;
           }
           else
           {
               break;
           }
       }
       else if (user_command_fields.at(0)=="chains")
       {

           if (user_command_fields.size()!=1)
           {
               cout<<"Error: error in command "<< user_command_fields.at(0)<<endl;
           }

           else
           {
            for (const auto&  chain : chains )
            {
               cout << chain.first  << endl;
            }

           }
       }
       else if (user_command_fields.at(0)=="stores")
       {

           if (user_command_fields.size()!=2)
           {
               cout<<"Error: error in command "<< user_command_fields.at(0)<<endl;
           }
           else if (chains.find(user_command_fields.at(1))==chains.end())
           {
               cout<<"Error: unknown chain name"<<endl;
           }
           else
           {
               for (const auto&  location : chains.at(user_command_fields.at(1)))
               {
                  cout << location.first  << endl;
               }

           }

       }
       else if (user_command_fields.at(0)=="selection")
       {

           if (user_command_fields.size()!=3)
           {
               cout<<"Error: error in command "<< user_command_fields.at(0)<<endl;
           }
           else if (chains.find(user_command_fields.at(1))==chains.end())
           {
               cout<<"Error: unknown chain name"<<endl;
           }
           else if (chains.at(user_command_fields.at(1)).find(user_command_fields.at(2))==chains.at(user_command_fields.at(1)).end())
          {
              cout<<"Error: unknown store"<<endl;
          }
           else
           {
               for (Product existing_product: chains.at(user_command_fields.at(1)).at(user_command_fields.at(2)))
               {
                   cout<<existing_product.product_name << " ";
                   if(existing_product.price==OUT_OF_STOCK)
                   {
                       cout<<"out of stock" <<endl;
                   }
                   else
                   {
                       cout<< existing_product.price<<endl;
                   }

               }

           }
       }

       else if (user_command_fields.at(0)=="cheapest")
       {

           if (user_command_fields.size()!=2)
           {
               cout<<"Error: error in command "<< user_command_fields.at(0)<<endl;
           }
           else
           {
              cheapest_product(user_command_fields.at(1), chains);
           }

       }
       else if (user_command_fields.at(0)== "products")
       {

           if (user_command_fields.size()!=1)
           {
               cout<<"Error: error in command "<< user_command_fields.at(0)<<endl;
           }
           else
           {
               product_list(chains);

           }
       }
       else
        {
       cout<<"Error: unknown command: " <<user_commands<<endl;
        }

    }

   return EXIT_SUCCESS;
}

int main()
    {
  Chains chains;

  if(not read_input_file(chains) )
  {
      return EXIT_FAILURE;
  }

  if(not command_chains(chains)){
      return EXIT_SUCCESS;
  }

       return 0;
    }
