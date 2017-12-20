#include "mainwindow.h"

#include <fmt/format.h>


int main (int argc, char *argv[])
{
  setlocale (LC_ALL, "");
  setlocale (LC_NUMERIC, "C"); // to set decimal point to "."
  if (argc)
    {
      fmt::print("hello world from {}!", argv[0]);
    }
#if GTK_APPLICATION_RECEIVES_COMMAND_LINE_ARGUMENTS
  // The command line arguments must be checked before Gtk::Application::run()
  // is called. The Gio::APPLICATION_HANDLES_COMMAND_LINE flag and the
  // on_command_line() signal handler are not necessary. This program is simpler
  // without them, and with argc = 1 in the call to Gtk::Application::create().
  // They are included to show a program with Gio::APPLICATION_HANDLES_COMMAND_LINE.
  // Gio::APPLICATION_NON_UNIQUE makes it possible to run several instances of
  // this application simultaneously.
  auto app = Gtk::Application::create(argc, argv,
    "org.gtkmm.example", Gio::APPLICATION_HANDLES_COMMAND_LINE | Gio::APPLICATION_NON_UNIQUE);

  // Note after = false.
  // Only one signal handler is invoked. This signal handler must run before
  // the default signal handler, or else it won't run at all.
  app->signal_command_line().connect(sigc::bind(sigc::ptr_fun(&on_command_line), app), false);
#else
  // Gio::APPLICATION_NON_UNIQUE makes it possible to run several instances of
  // this application simultaneously.
  int argc1 = 1; // Don't give the command line arguments to Gtk::Application.
  auto application = Gtk::Application::create(argc1, argv, "com.al-enterprise.oxeng");
#endif




  // Glib::RefPtr<Gtk::IconTheme> defaultIconTheme = Gtk::IconTheme::get_default();
  // defaultIconTheme->append_search_path (".");

  MainWindow a_main_window {application, argv[1]};

  // sigcore !! a_main_window.on_what();
  return application->run(a_main_window);
}
