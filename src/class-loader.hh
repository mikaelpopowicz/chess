#ifndef CLASS_LOADER_HH_
# define CLASS_LOADER_HH_

# include <vector>
# include <string>
# include <dlfcn.h>
# include "listener.hh"

class ClassLoader
{
public:
  ClassLoader(std::vector<string> libs);
  ~ClassLoader();
  
  bool load_libraries();
  std::vector<void *> get_libraries();
  listener *get_instance(void *class);
  
  
private:
  std::vector<std::string> libstr_;
  std::vector<void *> libs_;
};

#endif /* !CLASS_LOADER_HH_ */