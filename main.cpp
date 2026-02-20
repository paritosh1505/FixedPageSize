#include "Page.hpp"
#include <iostream>
int main() {
  PageSize page = CreatePageInit();
  PageSize content = AddFileInit(page);
  insert_Record(content, "hello");
  insert_Record(content, "wolrd");
  // std::cout << "Page ID: " << content.header.page_id << "\n";
  // std::cout << "Record count: " << content.header.record_count << "\n";
}