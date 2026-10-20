

#define LOG_ENTRY(fileName, message, ...)            \
	{                                                           \
		FILE *gpLogFile = fopen(fileName, "a");                 \
		fprintf(gpLogFile, "INFO: " message "\n", __VA_ARGS__); \
		fclose(gpLogFile);                                      \
		gpLogFile = NULL;                                       \
	}

#define VFP(complete, percent) (complete * percent / 100.0)
