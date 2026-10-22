#include <iostream>
#include <fstream>
#include <functional>
#include "llrec.h"
using namespace std;

/**
 * Reads integers (separated by whitespace) from a file
 * into a linked list.
 *
 * @param[in] filename
 *  The name of the file containing the data to read
 * @return
 *  Pointer to the linked list (or NULL if empty or the
 *  file is invalid)
 */
Node* readList(const char* filename);

/**
 * Prints the integers in a linked list pointed to
 * by head.
 */
void print(Node* head);

/**
 * Deallocates the linked list nodes
 */
void dealloc(Node* head);


Node* readList(const char* filename)
{
    Node* h = NULL;
    ifstream ifile(filename);
    int v;
    if( ! (ifile >> v) ) return h;
    h = new Node(v, NULL);
    Node *t = h;
    while ( ifile >> v ) {
        t->next = new Node(v, NULL);
        t = t->next;
    }
    return h;
}

void print(Node* head)
{
    while(head) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

void dealloc(Node* head)
{
    Node* temp;
    while(head) {
        temp = head->next;
        delete head;
        head = temp;
    }
}

// -----------------------------------------------
//   Add any helper functions or
//   function object struct declarations
// -----------------------------------------------

struct IsOdd{
  bool operator()(int val)const {
    return val % 2 != 0;
  }
};


int main(int argc, char* argv[])
{
    if(argc < 2) {
        cout << "Please provide an input file" << endl;
        return 1;
    }

    // -----------------------------------------------
    // Feel free to update any code below this point
    // -----------------------------------------------
    Node* head1 = readList(argv[1]);
    cout << "=== Testing llpivot ===" << endl;
    cout << "Original List: ";
    print(head1);

    Node* smaller = NULL;
    Node* larger = NULL;
    int pivot = 10; // You can change this pivot value to test different splits

    llpivot(head1, smaller, larger, pivot);

    cout << "Pivot value: " << pivot << endl;
    cout << "Smaller list (<= " << pivot << "): ";
    print(smaller);
    cout << "Larger list (> " << pivot << "): ";
    print(larger);
    cout << "Original head (should be 0/NULL): " << head1 << endl;

    // Clean up memory from llpivot test
    dealloc(smaller);
    dealloc(larger);

    cout << endl;

    // -----------------------------------------------
    // TEST 2: Testing llfilter
    // -----------------------------------------------
    Node* head2 = readList(argv[1]); // Re-read original list from file
    cout << "=== Testing llfilter ===" << endl;
    cout << "Original List: ";
    print(head2);

    IsOdd pred;
    Node* filteredHead = llfilter(head2, pred);

    cout << "Filtered List (odds removed): ";
    print(filteredHead);

    // Clean up memory from llfilter test
    dealloc(filteredHead);

    return 0;

}
