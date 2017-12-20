

#include "mainwindow.h"
#include <gtkmm/application.h>
#include <fmt/format.h>


int main (int argc, char *argv[])
{
  setlocale (LC_ALL, "");
  setlocale (LC_NUMERIC, "C"); // to set decimal point to "."
if (argc)
    {
        fmt::print("hello world from {}!", argv[0]);
    }
  auto application = Gtk::Application::create(argc, argv, "com.al-enterprise.oxeng");
 
  // Glib::RefPtr<Gtk::IconTheme> defaultIconTheme = Gtk::IconTheme::get_default();
  // defaultIconTheme->append_search_path (".");
  
  MainWindow a_main_window;

  return application->run(a_main_window);
}
