#include <syslog.h>

int main()
{
	syslog(LOG_DEBUG,"%s is %d\n","Today",22);
	return 0;
}
