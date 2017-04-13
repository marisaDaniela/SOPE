
void signalHandler (int);

/* Search file in a directory by its full name */
void searchByName(const char*,const char*,const char*);

void searchByType(const char*,const char,const char*);

void searchByPermissions(const char*,const char*,const char*);

int comparePermissions(const char*, const char*);

void executeAction(const char*,const char*,const char*);

void printAllFilesInDir(const char*);

int isRegularFile(const char *);

int isDirectory(const char *);

int isSymbolicLink(const char *);
