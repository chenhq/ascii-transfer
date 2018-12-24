#include <stdio.h>
#include <unistd.h>
#include <string.h>


const char SOF=0x01;
const char ETX=0x03;
const char EOT=0x04;
const char ACK=0x07;
const char NACK=0x18;

/** Simple ASCII file transmission
 * Intended for use over a reliable connection
 *
 * Protocol:
 * 1a. Client initiates send, wait for SOF
 * 1b.
 */
int main() {
  FILE *fp;
  char file[1024];
  char buf[1024];
  char cwd[1024];
  int i = 0;

  // instruct server to start sending
  putc(SOF, stdout);
  fflush(stdout);
  // get the filename
  char c = getc(stdin);
  while (c != '\n' && i < 1024) {
    file[i++] = c;
    c = getc(stdin);
  }
  getcwd(cwd, 1024);
  if (cwd == NULL) {
    fprintf(stderr, "error getting cwd\n");
    fputc(NACK, stdout);
  } else {
    fprintf(stderr, "Saving <%s> to <%s>\n", file, cwd);
    // Attempt to open local file with same name for writing
    if ((fp = fopen(file, "w")) != NULL) {
      fputc(ACK, stdout);
      // read and save characters until EOT sent
      char c = getc(stdin);
      while (c != EOT) {
        fputc(c, fp);
        c = getc(stdin);
        if (c == '\n') fputc('.', stderr);
      }
      fclose(fp);
      fputs("\nDownload complete.", stderr);
    } else {
      fprintf(stderr, "error opening %s\n", buf);
      fputc(NACK, stdout);
    }
  }
}
