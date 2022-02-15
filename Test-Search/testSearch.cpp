#include "pch.h"

#include "../Test-Search/isearch.h"

TEST(SearchCase, SearchByName) {
  
  //input...
  vector <Employee> employees;
  employees.push_back({ "12345678","KIM","GILDONG","CL1","010-2000-0000","000101","ADV" });
  
  //SCH »ý¼º
  ISearch * finder = NaiveSearcher(employees)


  employees.push_back({ "12345678","HONG","GILDONG","CL2","010-2000-0000","000101","ADV" });
  employees.push_back({ "12345678","CHOI","GILDONG","CL3","010-2000-0000","000101","ADV" });


  NaiveSearch finder(employees);
  vector <Employee*> result;

  result = finder.searchByFirstName("KIM");
  EXPECT_EQ(result[0]->firstName, "KIM");

  result = finder.searchByLastName("GILDONG");
  EXPECT_EQ(result.size(), 3);

  result = finder.searchByFirstName("PARK");
  EXPECT_EQ(result.size(), 0);

}