#ifndef DEF_WIFI
#define DEF_WIFI

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);
void run_curl_test(char *addurl, char *filename);
int connect_to_apctl(int config);
int net_thread(SceSize args, void *argp);

#endif
