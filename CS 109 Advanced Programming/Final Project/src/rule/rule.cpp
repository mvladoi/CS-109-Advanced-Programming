#include "rule.h"
#include <sstream>
#include <iostream>
#include <map>

Predicate::Predicate(string in_name, vector<string> &in_param) {
  name = in_name;
  param = in_param;
  param_match = 0;
}

string Predicate::get_name() {
  return name;
}

vector<string> *Predicate::get_param() {
  return &param;
}

int Predicate::num_params(){
  return param.size();
}

int Predicate::get_param_match() {
  return param_match;
}

void Predicate::inc_param_match() {
  ++param_match;
}

string Predicate::toString() {
  ostringstream output;
  output << name << "(";
  for (auto iter = param.begin(); iter != param.end() - 1; ++iter) {
    output << *iter << ",";
  }
  output << param.back() << ")";
  return output.str();
}

Predicate::~Predicate() {
}

Rule::Rule(string in_name) {
  name = in_name;
}

void Rule::initialize_rule(uint8_t in_operation, vector<string> &params) {
  operation.push_back(in_operation);
  rule_param.push_back(vector<string>(params));
  rule_instance.push_back(vector<Predicate *>());
  sorted_instance.push_back(list<Predicate *>());
  for (size_t i = 0; i <= params.size(); ++i) {
    predicate_param_match_index.push_back(-1);
  }
}

void Rule::add_predicate(string name, vector<string> &param_list) {
  //Push a new Predicate object onto the most recently created rule instance
  rule_instance.back().push_back(new Predicate(name, param_list));
  //Create a pointer to this new Predicate object for eaiser direct access later.
  //Called "insert" since it's the most recently inserted Predicate
  Predicate *insert = rule_instance.back().back();
  //Get a pointer to the most recently created rule instance's parameters, which we'll use for comparison
  vector<string> *params = &(rule_param.back());
  //We will now begin checking how many parameters in the predicate match up with the rule's parameters.

  //Create a map for all the param variables that have been considered as "matched"
  //We'll use this map to check if a matched variable was already matched before so that duplicate variables don't get counted
  map<string, int> existing;
  //iter = pointing to predicate's parameter vector. We are using the param_list passed by the function call since Predicate's vector is private.
  //iter2 = pointing to the rule instance's parameter vector.
  for (auto iter = param_list.begin(); iter != param_list.end(); ++iter) {
    for (auto iter2 = params->begin(); iter2 != params->end(); ++iter2) {
      //check if the parameters match
      if (iter->compare(*iter2) == 0) {
	//if they match, check if the parameter value is in the map already.
	//We'll skip adding it to the map and incrementing the parameter match value if it's in the map already.
	if (existing.find(*iter) == existing.end()) {
	  //Add a value of 1 to the map with the key being the parameter variable.
	  //Doesn't matter if it's a 1, a -1, 4535345, etc. We just need find() to result in a match--it's the key value that matters.
	  existing[*iter] = 1;
	  insert->inc_param_match();
	}
      }
    }
  }
  //Now, we need to insert the pointer of the predicate into the right spot in sorted_instance.
  //sorted_instance will be used during rule expansion, since the order of the parameter pointers helps ensure that--
  //(i'm guessing we all know how it works, so I'll omit this for now. Will expand on this before turning it in for the graders)

  //predicate_param_match_index is a vector that stores indexes in sorted_instance that correspond to insertion points for Predicates
  //with certain values of param_match. (e.g. predicate_param_match_index[2] will return which index in sorted_instance to insert your
  //pointer for the Predicate that has 2 of the same parameters as the rule.)

  //All the values in predicate_param_match_index are initialized with a -1, which just means that the index to insert hasn't actually
  //been found yet.

  //We want to grab the index we should insert our newly made Predicate pointer at, but we need to see if it's even been found yet.

  //If param_match is 0, then we just need to push onto the back regardless.
  if (insert->get_param_match() != 0) {
    if (predicate_param_match_index[insert->get_param_match()] == -1) {
      //Index hasn't been found yet, so we start actually finding it.
      int i = 0;
      //Iterate through the list of sorted instances to try and find where the insertion index would be at.
      for (auto iter = sorted_instance.back().begin(); iter != sorted_instance.back().end(); ++iter, ++i) {
	if ((*iter)->get_param_match() <= insert->get_param_match()) {
	  predicate_param_match_index[insert->get_param_match()] = i;
	  break;
	}
      }
    }

    //Index either already exists, or has been found. We now need an iterator that points to the index in question.
    //lists do not have random-access iterators unlike vectors, so we'd need to manually increment the iterator
    //to achieve the same effect.
    auto iterator_index = sorted_instance.back().begin();
    for (int i = 0; i < predicate_param_match_index[insert->get_param_match()]; ++i) {
      ++iterator_index;
    }
    //Insert the Predicate pointer in the right spot.
    sorted_instance.back().insert(iterator_index, insert);
    //Now, increment the index values by 1 for all the other param_match values where the number of matched parameters
    //is fewer than the current one.
    for (int i = insert->get_param_match() - 1; i >= 0; --i) {
      //cerr << "Stop 1: " << i << endl;
      ++predicate_param_match_index[i];
    }
  } else {
    sorted_instance.back().push_back(insert);
  }
}

size_t Rule::get_num_instances() {
  return operation.size();
}

uint8_t Rule::get_operation(size_t index) {
  return operation[index];
}

vector<string> *Rule::get_rule_param(size_t index) {
  return &rule_param[index];
}

list<Predicate *> *Rule::get_sorted_instance(size_t index) {
  return &sorted_instance[index];
}

string Rule::get_name() {
  return name;
}

string Rule::toStrung() {
  ostringstream output;
  for (size_t i = 0; i < operation.size(); ++i) {
    output << "RULE " << name << "(";
    for (auto iter = rule_param[i].begin(); iter != rule_param[i].end() - 1; ++iter) {
      output << *iter << ",";
    }
    output << rule_param[i].back() << "):- " << (operation[i] == 0 ? "OR " : "AND ");
    for (auto iter = sorted_instance[i].begin(); iter != sorted_instance[i].end(); ++iter) {
      output << (*iter)->toString() << " ";
    }
  }
  return output.str();
}

string Rule::toString() {
  ostringstream output;
  for (size_t i = 0; i < operation.size(); ++i) {
    output << "RULE " << name << "(";
    for (auto iter = rule_param[i].begin(); iter != rule_param[i].end() - 1; ++iter) {
      output << *iter << ",";
    }
    output << rule_param[i].back() << "):- " << (operation[i] == AND ? "AND " : "OR ");
    for (auto iter = rule_instance[i].begin(); iter != rule_instance[i].end() - 1; ++iter) {
      output << (*iter)->toString() << " ";
    }
    output << rule_instance[i].back()->toString() << endl;
  }
  return output.str();
}

Rule::~Rule() {
}
