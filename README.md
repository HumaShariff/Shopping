# **Chain Stores Data Management System**  


### **Authors**

- **Huma Fatima Azmi Shaikh**

  - Email: [humafatimaazmi.shaikh@tuni.fi](mailto:humafatimaazmi.shaikh@tuni.fi)

- **Vivetha Lakshmana Perumal**

  - Email: [vivetha.lakshmanaperumal@tuni.fi](mailto:vivetha.lakshmanaperumal@tuni.fi)

## **Description**  
This program processes and manages data related to chain stores from an input file. The input file contains entries in the format:  
chain_store;store_location;product_name;product_price


The program validates each line to ensure it follows the correct format. It then organizes the data using efficient STL containers and structs. Users can interact with the system using various commands to retrieve information about stores, products, and pricing.  

---

## **Features**  
- **Data Validation:** Ensures input data integrity.  
- **Structured Storage:** Uses maps and vectors for efficient data management.  
- **User Commands:**  
  - `chains` → Lists all available chain stores.  
  - `stores <chain_store>` → Lists all store locations of a specific chain.  
  - `selection <chain_store> <store_location>` → Displays products available in a given store.  
  - `cheapest <product_name>` → Finds the cheapest price for a given product across all stores.  
  - `products` → Lists all available products in alphabetical order.  
  - `quit` → Terminates the program.  

---

## **Getting Started**  

### **Prerequisites**  
Ensure you have a C++ compiler installed, such as:  
- **GCC** (MinGW for Windows)  
- **Clang**  
- **MSVC** (for Visual Studio users)
  
## **Acknowledgement**
This project was developed using an initial template provided by the Programming 2 course at Tampere University. The template included the basic structure and input handling. The remaining implementation, including data structures, command processing, and functionality, was developed by the authors.
### **Compiling the Program**  
To compile the program, use:  

```sh
g++ -o chain_stores main.cpp 





