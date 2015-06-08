#ifndef CLASS_LOADER_HH_
# define CLASS_LOADER_HH_

# include <vector>
# include <iostream>
# include <string>
# include <dlfcn.h>
# include "listener.hh"
# include "ai.hh"
# include "color.hh"

class ClassLoader
{
public:
  ClassLoader();
  ~ClassLoader();

  bool load_libraries(std::vector<std::string> libs);
  Ai* get_ia(std::string ia, Color color);
  std::vector<void*> get_libs();
  std::vector<ListenerExport*> get_plugins();


private:
  std::vector<ListenerExport*> plugins_;
  std::vector<void*> libs_;
};

#endif /* !CLASS_LOADER_HH_ */
