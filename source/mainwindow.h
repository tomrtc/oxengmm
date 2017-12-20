#ifndef GTKMM_MAINWINDOW_H
#define GTKMM_MAINWINDOW_H
#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/image.h>

class MainWindow : public Gtk::Window
{

public:
  MainWindow(Glib::RefPtr<Gtk::Application> t_application, const char*t_image_arg);
  virtual ~MainWindow();
  void			on_what();
protected:

  void			on_button_clicked();
  void			on_spin_button_clicked();

  Glib::RefPtr<Gtk::Application> _application;
  // inner widgets.
  Gtk::Box		_box {Gtk::ORIENTATION_VERTICAL};
  Gtk::Box		_buttons_box {Gtk::ORIENTATION_HORIZONTAL};
  Gtk::Button		_button     {Gtk::Button("Quit")} ;
  Gtk::SpinButton	_spin_button;
  Gtk::Image		_image;
  Gtk::ScrolledWindow	_scrolled_window;
};

#endif // GTKMM_MAINWINDOW_H
