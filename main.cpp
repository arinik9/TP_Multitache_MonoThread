#include <unistd.h>
#include <Outils.h>
int main(){
InitialiserApplication(XTERM);
sleep(10);
TerminerApplication(true);
return 0;
}
