#if defined BUILDMAINLIB
 #define TEST_COMMON_DLLSPEC Q_DECL_EXPORT
#else
 #define TEST_COMMON_DLLSPEC Q_DECL_IMPORT
#endif

int _main(int argc, char *argv[]);
