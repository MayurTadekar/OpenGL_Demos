
#define LOG_ERROR(fileName, error)                \
	{                                             \
		FILE *gpLogFile = fopen(fileName, "a");   \
		fprintf(gpLogFile, "ERROR: %s\n", error); \
		fclose(gpLogFile);                        \
		gpLogFile = NULL;                         \
		exit(1);                                  \
	}

#define LOG_ENTRY(fileName, message)               \
	{                                              \
		FILE *gpLogFile = fopen(fileName, "a");    \
		fprintf(gpLogFile, "INFO: %s\n", message); \
		fclose(gpLogFile);                         \
		gpLogFile = NULL;                          \
	}

#define LOG_ENTRY_WITH_PARAM(fileName, message, ...)            \
	{                                                           \
		FILE *gpLogFile = fopen(fileName, "a");                 \
		fprintf(gpLogFile, "INFO: " message "\n", __VA_ARGS__); \
		fclose(gpLogFile);                                      \
		gpLogFile = NULL;                                       \
	}
