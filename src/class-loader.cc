#include "class-loader.hh"

ClassLoader::ClassLoader(std::vector<std::string> libstr)
  : libstr_(libstr)
{}

ClassLoader::~ClassLoader()
{}

bool ClassLoader::load_libraries()
{
  for (std::string str : this->libstr_)
  {
    void *handle = dlopen(str, RTLD_LAZY);
    if (!handle)
    {
      std::cerr << "Unable to load : " << str << std::endl;
      return false;
    }
    this->libs_.push_back(handle);
    handle = NULL;
  }
  return true;
}

std::vector<void *> ClassLoader::get_libraries()
{
  return this->libs_;
}

Listener *ClassLoader::get_instance(void *classptr)
{
  create* create_listener = (create*) dlsym(classptr, "create");
  const char* dlsym_error = dlerror();
  if (dlsym_error)
  {
    cerr << "Can not create instance" << std::endl;
    return NULL;
  }
  return create_listener();
}