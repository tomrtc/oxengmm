#ifndef GTKMM_MAINWINDOW_H
#define GTKMM_MAINWINDOW_H

#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/box.h>

class MainWindow : public Gtk::Window
{

public:
  MainWindow();
  virtual ~MainWindow();

protected:

  void			on_button_clicked();
  void			on_spin_button_clicked();


  // inner widgets.
  Gtk::Box		_box;
  Gtk::Box		_buttons_box;
  Gtk::Button		_button;
  Gtk::SpinButton	_spin_button;
};

#endif // GTKMM_MAINWINDOW_H
