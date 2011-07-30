void backlight_of();
void backlight_on();


void backlight_of()
{
  popen("echo 0 > /proc/easy_backlight","w");
}

void backlight_on()
{
  popen("echo 1 > /proc/easy_backlight","w");
}