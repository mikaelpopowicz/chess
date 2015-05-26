# define AI_EXPORT(TYPE)                                \
  extern "C"                                            \
  {                                                     \
    EXPORT Ai* ai_create(Color color)                   \
    {                                                   \
      return new TYPE(color);                           \
    }                                                   \
  }
