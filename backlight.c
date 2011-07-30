void get_backlight_stat();
void toggle_backlight();

static Bool backlight;


void toggle_backlight()
{
  Arg arg;  
  
  get_backlight_stat();
  backlight = !backlight;

  if(backlight)
    arg.v = (const char*[]){ "/bin/sh", "-c",  "echo 1 > /proc/easy_backlight", NULL };
  else
    arg.v = (const char*[]){ "/bin/sh", "-c",  "echo 0 > /proc/easy_backlight", NULL };


  if(fork() == 0) {
    if(dpy)
      close(ConnectionNumber(dpy));
    setsid();
    execvp(((char **)arg->v)[0], (char **)arg->v);
    fprintf(stderr, "Slock: execvp %s", ((char **)arg->v)[0]);
    perror(" failed");
    exit(0);
  }

}

void get_backlight_stat()
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
  
    // read actual_brightness
    fp = fopen("/proc/easy_backlight", "r");
    if (fp == NULL){
         printf("\nfailed to read /proc/easy_backlight\n");
         return;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
      if(line[0] == '1') backlight = True;
      else backlight = False;
      break;
    }
    
    if (line) free(line);
    fclose(fp);
}
