#include "class-loader.hh"

ClassLoader::ClassLoader()
{}

ClassLoader::~ClassLoader()
{}

bool ClassLoader::load_libraries(std::vector<std::string> libs)
{
  for (auto str : libs)
  {
    void* lib = dlopen(str.c_str(), RTLD_NOW);
    if (!lib)
    {
      std::cerr << "Can't load lib " << str << ": " << dlerror() << std::endl;
      return false;
    }
    ListenerExport* plugin = (ListenerExport*) dlsym(lib, "listener_plugin");
    if (!plugin)
    {
      std::cerr << "Can't load symbol : " << dlerror() << std::endl;
      return false;
    }
    this->libs_.push_back(lib);
    this->plugins_.push_back(plugin);
  }
  return true;
}

std::vector<void*> ClassLoader::get_libs()
{
  return this->libs_;
}

std::vector<ListenerExport*> ClassLoader::get_plugins()
{
  return this->plugins_;
}
/*
Listener* ClassLoader::get_instance(void* classptr)
{
  ListenerExport* test = static_cast<ListenerExport*>(dlsym(classptr, "listener_plugin"));
  if (!test)
    std::cerr << "Merde !" << std::endl;
  //std::cout << "ListenerExport created ! -> " << test->name << std::endl;
  const char* dlsym_error = dlerror();
  if (dlsym_error)
  {
    std::cerr << "Can not create instance" << std::endl;
    return NULL;
  }
  std::cout << "Return a Listener !" << std::endl;
  Listener* toto = test->create();
  return toto;
}
*/
