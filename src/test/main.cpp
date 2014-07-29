#include <gtk/gtk.h>
#include "../atlantis/atlantis.h"

int main(int argc, char *argv[]) {
	GtkWidget *window;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 1200, 600);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show_all(window);

	load("test.gba");

	gtk_main();

	return 0;
}


//#include "../atlantis/atlantis.h"
//#include "System.h"
//#include <cstring>
//#include <cstdio>
//
//void tests() {
//	printf("Startup Callback\n");
//}
//
//int main(int argc, char **argv) {
//
//	//test::System sys;
//
////init((atlantis::Emulator*) &sys);
//
//	atlantisOnStartup(tests);
//
//	char image[50];
//	strcpy(image, "./test.gba");
//	char *args[2] =  {argv[0], image};
//
//	atlantis_init("test.gba");
//
//	return 0;
//}
//
//
//
