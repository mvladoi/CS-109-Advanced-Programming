#ifndef SRI_FACT_H
#define SRI_FACT_H
#include <iostream>
#include <string>
#include <vector>


using namespace std;





class Fact {
  private:

    /* name of the fact
     */
    string name;

    /* stores the parameters for each fact instance
     * All fact instances have the same number of parameters.
     */
    vector<vector<string> *> fact_instance;

    /* retrieves the fact instance referenced by the index.
     */
    vector<string> *  get_param(size_t index);

  public:

    Fact(string in_name);

    /* returns name
     */
    string get_name();

    /* e.g. if this is Father(X,Y), this will return 2
     */
    int num_of_params();

    /* if we have 5 different Father(X,Y), this will return 5
     */
   size_t num_of_instance();

    /* Adds the *params vector to the fact_instance vector
     */
    void new_instance(vector<string> *params);

    /* Prints the facts in a format that the parse could read and convert
     * back to a fact object.
     */
    string toString();

    /* calls get_param(pos);
     */
    vector<string>* operator[] (size_t pos);
    ~Fact();
};



#endif
