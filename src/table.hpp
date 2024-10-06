#ifndef TABLE
#define TABLE
#include <string>
#include <vector>

struct TableViewColumn {
  std::string name;
  std::string value;
};

struct TableViewRow {
  std::vector<TableViewColumn> columns;
};

class TableView {
  std::vector<TableViewRow> rows;
};

class TableInputController {};

#endif
