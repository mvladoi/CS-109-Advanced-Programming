#ifndef SRI_TABLE_H
#define SRI_TABLE_H
#include <string>
#include <map>
#include <vector>
using namespace std;

class Table {

  private:
    /* The string used for the key corresponds to the variable.
     * The vector corresponds to the variable's column.
     * Example:
     * A | B | C
     * =========
     * 1 | 2 | 3
     * 4 | 5 | 6
     *
     * table["A"]; returns a vector with {"1", "4"}
     */
    map<string, vector<string>> table;
  public:
    Table();
    /* var_name corresponds to the columns.
     * content corresponds to the values to add to these columns.
     * e.g. var_name = {"A","B","C"}; content = {"1","2","3"}.
     *
     * add_entry will push blanks for columns with no corresponding content
     * Note that all columns will have an entry added no matter if they have content defined for it.
     * It's up to the one implementing this to find out which columns don't have content.
     */
    void add_entry(vector<string> &var_name, vector<string> &content);
    /* grabs entry referenced by index, overwrites values needed, and then adds it to bottom of list.
     */
    void copy_add_entry(vector<string> &var_name, vector<string> &content, int index);
    /* deletes column
     */
    void delete_column(string column);
    /* delete_entry removes the row that corresponds with the index provided.
     */
    void delete_entry(int index);
    vector<string> get_columns();
    /* var_name corresponds to the column.
     * index corresponds to the row.
     */
    string get_entry(string var_name, int index);
    /* Creates a new Table where the only entry is the one referenced by the index.
     */
    Table *get_entry_subtable(int index);
    /* get a vector of strings that correspond to the index specified
     */
    vector<string> get_entry_row(vector<string> &var_name, int index);
    /* rename column
     */
    void move_column(string dest, string src);
    /* Replaces the row referenced by the index with the contents of Table replacement.
     * Does _not_ delete *replacement; you'll need to delete that yourself.
     * Also returns a integer that refers to an index that's at the end of the new table you insert.
     */
    int replace_entry(int index, Table &replacement);
    /* Appends Table input to this table.
     */
    void cat(Table &input);
    /* remove duplicates from table*/
    void remove_duplicates();
    /* output table in string form
     */
    string toString();
    /* this toString prints parameters in the order they're listed in paramList.
     * Note that this skips over anything in paramList that doesn't start with a $
     */
    string toString(vector<string> &paramList);
    /* return how many rows the table has
     */
    size_t size();
    ~Table();
};

#endif
