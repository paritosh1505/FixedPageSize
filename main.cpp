#include "Page.hpp"
int main() {
  PageSize page = CreatePageInit();
  PageSize content = AddFileInit(page);
  insert_Record(content, "hello");
  insert_Record(content, "Beautiful");
  insert_Record(content, "World");
  print_page_records(content);
}