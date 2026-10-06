#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Template for T data type
template <typename T>

//LinkedList class def
class LinkedList{

  public:
   //Define node struct
    struct Node{

    T data;
    Node* prev;
    Node* next;

    };

  private:
  //Define start and end of node and count of nodes
  Node* head;
  Node* tail;
  unsigned int count;
  
  public:
  LinkedList(){
    head = nullptr;
    tail = nullptr;
    count = 0;
  }                                                            //Default constructor
  Node* GetHead(){
    return head;
  }                                                            //Returns ptr to first node in list
  const Node* GetHead() const{
    return head;
  }                                                            //Returns const ptr to first node
  
  Node* GetTail(){
    return tail;
  }                                                            //Returns ptr to last node
  const Node* GetTail() const{
    return tail;
  }                                                            //Returns const ptr to last node

  unsigned int GetCount() const{
    return count;
  }                                                            //Number of nodes currently stored in list


  LinkedList(const LinkedList<T>& list){  //Copy constructor
  
    head = nullptr;                                            //Initialize new list's head, tail, count to nothing
    tail = nullptr;
    count = 0;

    Node* current = list.head;

    while(current != nullptr){                                 //Ends when the parameter list's current node moves past its last node
      Node* newNode = new Node;                                //Set ptr newNode to the address of a new Node
      newNode->data = current->data;                           //Copy data from list to new list's node
      newNode->next = nullptr;                                 //Set new node next ptr to nullptr because its currently the last node in copy
      newNode->prev = this->tail;                              //Set new node prev to tail of previous iteration
      if(tail == nullptr){                                     //No previously exisiting nodes, this is the first one
        head = newNode;                                        //the first newNode is the head and tail of the copy
        tail = newNode;
      }
      else{                                                    //There is a node already existing, its next should point to this newNode
        tail->next = newNode;                                  //Set previous node's (still the tail) next to point to current newNode
        this->tail = newNode;                                  //Set tail to current newNode to move forward        
      }
      current = current->next;                                 //Current moves to next node's location
      count+=1;                                                //count increment
    

    }

    
  }

  LinkedList<T>& operator=(const LinkedList<T>& list){         //Copy Assignment oper

    //Delete the old (*this) list
    if(this != &list){                                         //Only perform deletion if this list is not already equal to the parameter list
      Node* current = this->head;                              //current points to the node being manipulated, starting with 
        while(current != nullptr){
        Node* tempNext = current->next;                        //Set a temp ptr indicating next node equal to current node's next node
        delete current;                                        //Delete node at current
        current = tempNext;                                    //move current forward to the next node
      }
      //Reset head, tail, count of *this
      head = nullptr;
      tail = nullptr;
      count = 0;

      //Copy from parameter list
      
      current = list.head;
      while(current != nullptr){
        Node* newNode = new Node;
        newNode->data = current->data;
        newNode->next = nullptr;
        newNode->prev = this->tail;
        if(tail == nullptr){                
          head = newNode;                 
          tail = newNode;
        }
        else{                          
          tail->next = newNode;           
          this->tail = newNode;              
        }
        current = current->next;            
        count+=1;                
      }
      
    }
    return *this;
  }

  ~LinkedList(){                           //Destructor
    Node* current = this->head;            //Current node to traverse
    while(current != nullptr){

      Node* tempNext = current->next;      //Save location of next node
      delete current;                      //Delete current node starting with the head
      current = tempNext;                  //Move current forward
    }
  }

  void AddHead(const T& value){            //Adds new node to beginning of list

    Node* newHead = new Node;              //Create new node for the head
    newHead->data = value;                 //Put value into the data of newHead
    newHead->prev = nullptr;               //Head is the first element, no previous

    if(this->head == nullptr){             //If list empty
      newHead->next = nullptr;             //Only element, no next
      this->tail = newHead;                //newHead is both the head and tail
    }
    else{
      
      this->head->prev = newHead;          //Old head's prev should point to the new head
      newHead->next = this->head;          //Head's next node is the old head
      
      
      
    }
    this->head = newHead;                  //Reassign the current obj's head to the newHead
    count+=1;                              //Add 1 to count
  }

  void AddTail(const T& value){            //Adds new node to end of list
    Node* newTail = new Node;              //Create new node for the tail
    newTail->data = value;                 //Put value into newTail's data
    newTail->next = nullptr;               //Final element, no node after

    if(this->tail == nullptr){             //If originally empty
      newTail->prev = nullptr;             //Only element, no prev
      this->head = newTail;                //newTail is also head and tail
    }
    else{
      this->tail->next = newTail;          //Old tail's next should point to newTail
      newTail->prev = this->tail;          //Tail's prev node is the old tail
    }
    this->tail = newTail;                  //Reassign current obj's tail to the newTail
    count+=1;
  }

  void AddNodesHead(const T* ArrPtr, unsigned int count){       //Adds multiple arr values to front of list while preserving orig order
    for(int i = count - 1; i >= 0; i--){                        //Starting with count - 1, add elements from last to first (in order because its at the start)
      AddHead(ArrPtr[i]);                                       //AddHead with array element as parameter
    }
  }

  void AddNodesTail(const T* ArrPtr, unsigned int count){       //Adds multiple arr values to end of list while preserving orig order
    for(int i = 0; i < count; i++){                             //Add array element to the end (in order)
      AddTail(ArrPtr[i]);                                       //AddTail call
    }
  }

  void PrintForward() const{                                    //Print list from head to tail
    Node* current = this->head;                                 //Current node to traverse
    while(current != nullptr){
      cout << current->data << endl;                            //Print data at the current node
      current = current->next;                                  //Move current forward
    }
  }

  void PrintReverse() const{                                    //Prints tail to head
    Node* current = this->tail;                                 //Current node to traverse
    while(current != nullptr){
      cout << current->data << endl;                            //Print data at the current node
      current = current->prev;                                  //Move current backward
    }
  }
    
  Node* Find(const T& value) const{                             //Search first node containing given value
    Node* search = head;                                        //Declare a node to search the list
    while(search != nullptr){                                   //Keep searching list until it reaches the end
      if(search->data == value){                                //Return if search found
        return search;
      }
      search = search->next;                                    //Move search forward
    }
    return nullptr;                                             //If no matching nodes found
  }

  void FindAll(vector<Node*>& outData, const T& value) const{     //Find every node with value, stores its pointers in vector
    Node* search = head;                                          //Declare node to search list
    while(search != nullptr){                                     //Keep searching until reaches end
      if(search->data == value){                    
        outData.push_back(search);                                //Add node at search to vector if matched
      }
      search = search->next;                                      //Move search forward
    }
  }

  Node* FindAt(int index) const{                                  //Return node at an index

    if(index < 0 || index >= count){                  
      throw out_of_range("Index is out of range");                //Index out of range if negative or >= count
    }

    Node* search = head;                                          //Declare search node
    for(int i = 0; i < index; i++){                               //Loop through list until it reaches index amount of increments
      search = search->next;                                      //Move search forward
    }
    return search;                                                //Return search when it reaches index value
  }
  
  T& operator[](unsigned int index){                              //Returns data stored at given index
    if(index > count){                  
      throw out_of_range("Index Out of Range");                   //Index out of range if >= count (unsigned never negative)
    }

    Node* search = head;                                          //Declare search node
    for(int i = 0; i < index; i++){                               //Loop through list until it reaches index amount of increments
      search = search->next;                                      //Move search forward
    }
    return search->data;                                          //Return data in search when it reaches index value
  }

  const T& operator[](unsigned int index) const{                  //Returns data at an index for a constant Linked List
    if(index >= count){                  
      throw out_of_range("Index Out of Range");                   //Index out of range if >= count (unsigned never negative)
    }

    Node* search = head;                                          //Declare search node
    for(int i = 0; i < index; i++){                               //Loop through list until it reaches index amount of increments
      search = search->next;                                      //Move search forward
    }
    return search->data;                                          //Return data in search when it reaches index value
  }

  bool operator==(const LinkedList<T>& list) const{
    Node* thisCheck = head;                                       //Set a pointer starting at the *this list head to check nodes
    Node* listCheck = list.head;                                  //Set a pointer starting at the parameter list head to check nodes
    if(count == list.count){                                      //Check if same number of nodes
      while(thisCheck != nullptr){                                //Iterate through list until it reaches end
        if(thisCheck->data != listCheck->data){
          return false;                                           //False if the data isn't equal
        }
        thisCheck = thisCheck->next;                              //If equal, move forward to next node
        listCheck = listCheck->next;
      }
      return true;                                                //If made it to end of lists without differences, both lists are equal = true
    }
    else{
      return false;                                               //Different number of nodes, not equal
    }
  }

  void InsertAfter(Node* node, const T& value){
    Node* insert = new Node;                                  //Declare a pointer to the new node to be inserted 
    insert->data = value;                                     //Put parameter value into data of new node
    if(node == tail){
      tail = insert;                                          //If para node was tail, insert becomes new last node in list
      insert->next = nullptr;                                 //End of list, no next after insert
    }
    else{                                                     //If not the tail                              
      insert->next = node->next;                              //Insert next points to node previously after para node
      insert->next->prev = insert;                            //Connect node after insert' prev to insert

    }
    node->next = insert;                                      //Reassign para node's next to insert
    insert->prev = node;                                      //Change insert's prev to para node
  
    count +=1;                                                //Add 1 to count
  }
  

  

  void InsertBefore(Node* node, const T& value){              //Inserting new node w/ value before a para node's location
    Node* insert = new Node;
    insert->data = value;
    if(node == head){
      head = insert;
      insert->prev = nullptr;
    }
    else{
      insert->prev = node->prev;
      insert->prev->next = insert;
    }
    node->prev = insert;
    insert->next = node;

    count +=1;                                                //Add 1 to count
  }

  void InsertAt(const T& value, unsigned int index){          //Insert new value in node at index
    
    if(index > count){                  
      throw out_of_range("Index Out of Range");               //Index out of range if > count (unsigned never negative)
    }
    
    if(index == 0){                                           //Inserting at the head 
      InsertBefore(head, value);
    }
    else if (index == count){                                 //Insert at the tail
      InsertAfter(tail, value);
    }
    else{
      Node* insert = head;                                    //Find node at given index and insert new node before it
      for(int i = 0; i < index; i++){
        insert = insert->next;
      }
      InsertBefore(insert, value);
    }
    
  }

  bool RemoveHead(){                                          //Remove node if its a head
    if(head == nullptr){                                      //False if head is null (list empty)
      return false;
    }
    else{                                                     //If head is a node, set toRemove to first node
      Node* toRemove = head;
      head = toRemove->next;                                  //Move head ptr to node after, delete first node, return true
      if(head == nullptr){
        tail = nullptr;                                       //If head is nullptr, there was only one node, tail also nullptr
      }
      else{
        head->prev = nullptr;                                 //If not one node, Prev of new head is now null because it will be new first node
      }
      delete toRemove;
      count-=1;                                               //Decrement count by 1
      return true;
    }
  }

  bool RemoveTail(){                                          //Remove node when its a tail
    if(tail == nullptr){                                      //False if tail is null (list empty)
      return false;
    }
    else{                                                     //If tail is a node, set toRemove to last node
      Node* toRemove = tail;
      tail = toRemove->prev;                                  //Move tail ptr to node before, delete last node, return true
      if(tail == nullptr){
        head = nullptr;                                       //If tail is nullptr, there was only one node, head also nullptr
      }
      else{
        tail->next = nullptr;                                 //If not one node, next of new tail is now null because it will be new last node
      }
      delete toRemove;
      count-=1;                                               //Decrement count by 1
      return true;
    }
  }

  unsigned int Remove(const T& value){                        //Remove nodes with matching data value
    unsigned int removeCount = 0;                             //Keep count of nodes removes, set current node to beginning
    Node* current = head;
    
    while(current != nullptr){
      if(current->data == value){                             //Delete when data matches para value
        Node* next = current->next;                           //Save address of next node

        if(current == head){                                  //Function call to remove head
          RemoveHead();
        }
        else if(current == tail){                             //Function call to remove tail
          RemoveTail();
        }
        else{                                                 //Remove a middle node, rematch prev and next node ptrs
          current->prev->next = current->next;
          current->next->prev = current->prev;
          delete current;                                     //Delete current node and decrement count
          count-=1;
        }
        current = next;                                       //Move current to next node, increment remove count
        removeCount +=1;
      }
      else{
        current = current->next;                              //If didn't remove, just move current
      }
    }
    return removeCount;
  }

  bool RemoveAt(int index){                                   //Remove node at an index
  if(index < 0 || index > count){                             //Index can't be more than count of nodes or negative   
      return false;               
    }
    
    if(index == 0){                                           //Remove at the head  (index = 0)
      return RemoveHead();
    }
    else if (index == count - 1){
      return RemoveTail();                                    //Remove at the tail (index = count - 1)
      
    }
    else{                                                     //Case for any middle node
      Node* current = head;
      for(int i = 0; i < index; i++){                         //Loop through list until it reaches node at index
        current = current->next;
      }
      current->prev->next = current->next;                    //Remove a middle node, rematch prev and next node ptrs
      current->next->prev = current->prev;
      delete current;                                         //Delete current node and decrement count
      count-=1;                                               //Decrement count by 1
        
      return true;
      }
    }
  

  void Clear(){                             //Clears all nodes in this list, body derived from copy assignment oper
    if(head != nullptr){                    //If list not already empty
      Node* current = head;                 //current points to the node being manipulated, starting with 
        while(current != nullptr){
        Node* tempNext = current->next;     //Set a temp ptr indicating next node equal to current node's next node
        delete current;                     //Delete node at current
        current = tempNext;                 //move current forward to the next node
      }
      //Reset head, tail, count of *this
      head = nullptr;
      tail = nullptr;
      count = 0;
    }
  }

};

#endif 