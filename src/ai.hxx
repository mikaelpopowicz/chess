# define AI_EXPORT(TYPE)                                \
  extern "C"                                            \
  {                                                     \
    Ai* ai_create(Color color)                          \
    {                                                   \
      return new TYPE(color);                           \
    }                                                   \
  }
