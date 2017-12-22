#ifndef GTKMM_MAINWINDOW_H
#define GTKMM_MAINWINDOW_H
#include <gtkmm/application.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/box.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/image.h>


class MyScrolledWindow : public Gtk::ScrolledWindow
{
 public:
  MyScrolledWindow();
  virtual ~MyScrolledWindow();
 protected:
  void                  on_realize() override;
};

class MainWindow : public Gtk::Window
{

public:
  MainWindow(Glib::RefPtr<Gtk::Application> t_application, const char*t_image_arg);
  virtual ~MainWindow();
  void			on_what();
protected:
  void                  on_realize() override;
  void			on_button_clicked();
  void			on_spin_button_clicked();

protected:
  //int    _hs {0};
  //int    _ws {0};
protected:
  Glib::RefPtr<Gtk::Application>	_application;
  // inner widgets.
  Gtk::Box		                _box         {Gtk::ORIENTATION_VERTICAL};
  Gtk::Box		                _buttons_box {Gtk::ORIENTATION_HORIZONTAL};
  Gtk::Button		                _button      {Gtk::Button("Quit")} ;
  Gtk::SpinButton			_spin_button;
  Gtk::Image				_image;
  MyScrolledWindow			_scrolled_window;
  Glib::RefPtr<Gdk::Cursor>             _cursor      {Gdk::Cursor::create(Gdk::ICON)};
};

#endif // GTKMM_MAINWINDOW_H
