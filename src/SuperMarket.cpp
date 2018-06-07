#include <iostream>
#include <Catalog.h>
#include <memory>
using namespace SuperStore;
int main()
{
  auto catalog = std::make_unique<Catalog>("Joes");
  std::cout<<"Welcome to " << catalog->getName() << " super market\n";
  return 0;  
}

