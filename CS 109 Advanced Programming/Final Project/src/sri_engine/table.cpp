#include <iostream>
#include <sstream>
#include "table.h"
#include <algorithm>

Table::Table() {
}

void Table::add_entry(vector<string> &var_name, vector<string> &content) {
  if (table.begin() != table.end()) {
    int old_size = table.begin()->second.size();
    {
      auto var_iter = var_name.begin();
      auto con_iter = content.begin();
      while (var_iter != var_name.end()) {
	while (table[*var_iter].size() < old_size) {
	  table[*var_iter].push_back("");
	}
	table[*var_iter].push_back(*con_iter);
	++var_iter;;
	++con_iter;;
      }
    }
    for (auto iter = table.begin(); iter != table.end(); ++iter) {
      if (iter->second.size() == old_size) {
	iter->second.push_back("");
      }
    }
  } else {
    {
      auto var_iter = var_name.begin();
      auto con_iter = content.begin();
      while (var_iter != var_name.end()) {
	table[*var_iter].push_back(*con_iter);
	++var_iter;
	++con_iter;
      }
    }
  }
}

void Table::copy_add_entry(vector<string> &var_name, vector<string> &content, int index) {
  vector<string> ins_var_name = get_columns();
  vector<string> ins_content = get_entry_row(ins_var_name, index);
  {
    auto var_iter = ins_var_name.begin();
    auto con_iter = ins_content.begin();
    while (var_iter != ins_var_name.end()) {
      {
	auto var_iter2 = var_name.begin();
	auto con_iter2 = content.begin();
	while (var_iter2 != var_name.end()) {
	  if (var_iter->compare(*var_iter2) == 0) {
	    *con_iter = *con_iter2;
	  }
	  ++var_iter2;
	  ++con_iter2;
	}
      }
      ++var_iter;
      ++con_iter;
    }
  }
  {
    auto var_iter = var_name.begin();
    auto con_iter = content.begin();
    while (var_iter != var_name.end()) {
      if (find(ins_var_name.begin(), ins_var_name.end(), *var_iter) == ins_var_name.end()) {
	ins_var_name.push_back(*var_iter);
	ins_content.push_back(*con_iter);
      }
      ++var_iter;
      ++con_iter;
    }
  }
  add_entry(ins_var_name, ins_content);
}

void Table::delete_column(string column) {
  table.erase(column);
}

void Table::delete_entry(int index) {
  for (auto iter = table.begin(); iter != table.end(); ++iter) {
    iter->second.erase(iter->second.begin() + index);
  }
}

vector<string> Table::get_columns() {
  vector<string> retval = vector<string>();
  for (auto iter = table.begin(); iter != table.end(); ++iter) {
    retval.push_back(iter->first);
  }
  return retval;
}

string Table::get_entry(string var_name, int index) {
  return table[var_name][index];
}

vector<string> Table::get_entry_row(vector<string> &var_name, int index) {
  vector<string> retval = vector<string>();
  for (auto iter = var_name.begin(); iter != var_name.end(); ++iter) {
    if (table.find(*iter) != table.end()) {
      retval.push_back(table[*iter][index]);
    } else {
      retval.push_back("");
    }
  }
  return retval;
}

Table *Table::get_entry_subtable(int index) {
  Table *retval = new Table();
  vector<string> columns = get_columns();
  vector<string> content = get_entry_row(columns, index);
  retval->add_entry(columns, content);
  return retval;
}

/*
void Table::replace_entry(int index, Table &replacement) {
  for (auto iter = table.begin(); iter != table.end(); ++iter) {
    iter->second.erase(iter->second.begin() + index);
    for (size_t i = replacement.table[iter->first].size(); i >= 0; --i) {
      iter->second.insert(iter->second.begin() + index, replacement.table[iter->first][i]);
    }
  }
}
*/

void Table::move_column(string dest, string src) {
  if (dest.compare(src) != 0) {
    table[dest] = table[src];
    table.erase(src);
  }
}

int Table::replace_entry(int index, Table &replacement) {
  size_t old_size = table.begin()->second.size() - 1;
  size_t new_size = table.begin()->second.size() + replacement.table.begin()->second.size() - 1;
  for (auto iter = table.begin(); iter != table.end(); ++iter) {
    iter->second.erase(iter->second.begin() + index);
  }
  for (auto iter = table.begin(); iter != table.end(); ++iter) {
    for (auto iter2 = replacement.table.begin(); iter2 != replacement.table.end(); ++iter2) {
      if (iter->first.compare(iter2->first) == 0) {
	if (iter->second.size() == old_size) {
	  for (size_t i = iter2->second.size(); i > 0; --i) {
	    iter->second.insert(iter->second.begin() + index, (iter2->second)[i - 1]);
	  }
	}
      }
    }
  }
  for (auto iter = table.begin(); iter != table.end(); ++iter) {
    while (iter->second.size() != new_size) {
      iter->second.insert(iter->second.begin() + index, "");
    }
  }
  for (auto iter = replacement.table.begin(); iter != replacement.table.end(); ++iter) {
    if (table[iter->first].size() < new_size) {
      for (int i = 0; i < index; ++i) {
	table[iter->first].push_back("");
      }
      for (size_t i = 0; i < iter->second.size(); ++i) {
	table[iter->first].push_back(iter->second[i]);
      }
      for (size_t i = table[iter->first].size(); i < new_size; ++i) {
	table[iter->first].push_back("");
      }
    }
  }
  return index - 1 + (int) replacement.table.begin()->second.size();
}

void Table::cat(Table &input) {
  if (table.begin() != table.end()) {
    size_t init = table.begin()->second.size();
    size_t final_size = init + input.table.begin()->second.size();
    for (auto iter = table.begin(); iter != table.end(); ++iter) {
      for (auto iter2 = input.table.begin(); iter2 != input.table.end(); ++iter2) {
	if (iter->first.compare(iter2->first) == 0) {
	  for (size_t i = 0; i < iter2->second.size(); ++i) {
	    iter->second.push_back(iter2->second[i]);
	  }
	}
      }
    }
    for (auto iter = input.table.begin(); iter != input.table.end(); ++iter) {
      if (table[iter->first].size() < init) {
	for (size_t i = 0; i < init; ++i) {
	  table[iter->first].push_back("");
	}
	for (size_t i = 0; i < iter->second.size(); ++i) {
	  table[iter->first].push_back(iter->second[i]);
	}
      }
    }
    for (auto iter = table.begin(); iter != table.end(); ++iter) {
      if (iter->second.size() < final_size) {
	for (size_t i = 0; i < final_size - iter->second.size(); ++i) {
	  iter->second.push_back("");
	}
      }
    }
  } else {
    for (auto iter = input.table.begin(); iter != input.table.end(); ++iter) {
      table[iter->first] = vector<string>();
      for (size_t i = 0; i < iter->second.size(); ++i) {
	table[iter->first].push_back(iter->second[i]);
      }
    }
  }
}

string Table::toString() {
  ostringstream output;
  for (int i = 0; i < table.begin()->second.size(); ++i) {
    for (auto iter = table.begin(); iter != table.end(); ++iter) {
      output << iter->first << ":" << iter->second[i] << ", ";
    }
    output << endl;
  }
  return output.str();
}

size_t Table::size() {
  return table.begin()->second.size();
}

string Table::toString(vector<string> &paramList) {
  ostringstream output;
  for (int i = 0; i < table.begin()->second.size(); ++i) {
    for (auto iter = paramList.begin(); iter != paramList.end(); ++iter) {
      if (iter->find('$') == 0) {
	output << *iter << ":" << table[*iter][i] << ", ";
      }
    }
    output << endl;
  }
  return output.str();
}

void Table::remove_duplicates(){
  if (size() == 0) {
    return;
  }
  vector <string> var_name;
  vector<vector<string>>temp1;
  vector<vector<string>>temp2;
  // create first vector of vectors
  for(auto it = table.begin(); it != table.end(); ++it){
    var_name.push_back(it->first);
    temp1.push_back(it->second);
  }
  //create second vector of vectors
  vector<string> x;
  for (int j = 0; j < temp1.at(0).size(); j++){
    for(int i = 0; i < temp1.size(); i++){
      x.push_back(temp1[i][j]);
    }
    temp2.push_back(x);
    x.clear();
  }
  // sort and erase the duplicates
  std::sort(temp2.begin(), temp2.end());
  temp2.erase(std::unique(temp2.begin(), temp2.end()), temp2.end());
  // empty the table
  table.clear();
  // reinitialize the table
  for(size_t i = 0; i < temp2.size(); i++){
   add_entry(var_name,temp2.at(i));
  }
}

Table::~Table() {
}
