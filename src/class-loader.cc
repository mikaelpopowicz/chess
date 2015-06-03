#include "class-loader.hh"

ClassLoader::ClassLoader()
{}

ClassLoader::~ClassLoader()
{
  for (auto lib : this->libs_)
    dlclose(lib);
}

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
      dlclose(lib);
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
