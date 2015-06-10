#include "class-loader.hh"

ClassLoader::ClassLoader()
{}

ClassLoader::~ClassLoader()
{
  for (auto lib : this->libs_)
  {
    dlclose(lib);
    lib = nullptr;
  }
}

bool ClassLoader::load_libraries(std::vector<std::string> libs)
{
  for (auto str : libs)
  {
    void* lib = dlopen(str.c_str(), RTLD_NOW);
    if (!lib)
    {
      std::cerr << dlerror() << std::endl;
      return false;
    }
    ListenerExport* plugin = (ListenerExport*) dlsym(lib, "listener_plugin");
    if (!plugin)
    {
      std::cerr << "Can't load symbol : " << dlerror() << std::endl;
      dlclose(lib);
      lib = nullptr;
      return false;
    }
    this->libs_.push_back(lib);
    this->plugins_.push_back(plugin);
  }
  return true;
}

Ai* ClassLoader::get_ia(std::string ia, Color color)
{
  void* handle = dlopen(ia.c_str(), RTLD_NOW);
  if (!handle)
  {
    std::cerr << dlerror() << std::endl;
    return nullptr;
  }
  typedef Ai* create_t(Color);
  create_t* function = (create_t*) dlsym(handle, "ai_create");
  if (!function)
  {
    std::cerr << "Can't load constructor :" << dlerror() << std::endl;
    return nullptr;
  }
  this->libs_.push_back(handle);
  return function(color);
}

std::vector<void*> ClassLoader::get_libs()
{
  return this->libs_;
}

std::vector<ListenerExport*> ClassLoader::get_plugins()
{
  return this->plugins_;
}
