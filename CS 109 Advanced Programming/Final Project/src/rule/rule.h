#ifndef SRI_RULE_H
#define SRI_RULE_H
#include <list>
#include <string>
#include <vector>
#include <cstdint>
#define OR 0
#define AND 1
using namespace std;

class Predicate {
  private:
    /* Name that corresponds to either a fact or a rule.
     */
    string name;
    /* Contains the variables for this predicate.
     */
    vector<string> param;
    /* Number of variables that match up with the left-hand side
     */
    int param_match;
  public:
    Predicate(string in_name, vector<string> &in_param);
    string get_name();
    int num_params();
    vector<string> *get_param();
    int get_param_match();
    void inc_param_match();
    string toString();
    ~Predicate();
};

class Rule {
  private:
    /* Name of the rule
     */
    string name;
    /* Operation type for each rule instance
     */
    vector<uint8_t> operation;
    /* left-hand side parameters for each rule instance
     */
    vector<vector<string>> rule_param;
    /* predicates for each rule instance, preserving order specified in the rule declaration.
     */
    vector<vector<Predicate *>> rule_instance;
    /* stores pointers for the predicates, sorted in order so that predicates with more parameters
     * matching the left hand side appear closer to the left.
     */
    vector<list<Predicate *>> sorted_instance;
    vector<int> predicate_param_match_index;
  public:
    Rule(string in_name);
    /* creates a new vector<string> rule_param in the rule_instance vector
     */
    void initialize_rule(uint8_t in_operation, vector<string> &params);
    /* creates a new Predicate in one of the vector<Predicate> in the rule_instance 
     */
    void add_predicate(string name, vector<string> &param_list);
    size_t get_num_instances();
    uint8_t get_operation(size_t index);
    vector<string> *get_rule_param(size_t index);
    list<Predicate *> *get_sorted_instance(size_t index);
    /* get Rule's name
     */
    string get_name();
    /* Prints rule in a format that can be used by the parser to recreate the rule
     */
    string toString();
    string toStrung();
    /* Expands rule and returns a Table object with the results.
     * These results are not filtered for duplicates.
     */
    ~Rule();
};

#endif
