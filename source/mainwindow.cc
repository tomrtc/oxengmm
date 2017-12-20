#include "mainwindow.h"
#include <iostream>

#include <gtkmm/icontheme.h>
#include "icon.cc"


MainWindow::MainWindow()
  : _box(Gtk::ORIENTATION_VERTICAL),
    _buttons_box(Gtk::ORIENTATION_HORIZONTAL),
    _button("load") ,
    _spin_button()
{
  Glib::RefPtr<Gtk::IconTheme> defaultIconTheme = Gtk::IconTheme::get_default();
  
  set_title("Ubik");
  Glib::RefPtr<Gdk::Pixbuf> image = Gdk::Pixbuf::create_from_xpm_data(ubik);
  
  set_icon(image);
  set_default_size(1024, 860);
  add(_box);
  
  _spin_button.set_range(0, 100);
  _spin_button.set_value(50);
  _spin_button.set_increments(1, 10);
  _spin_button.signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_spin_button_clicked));
  _box.pack_start(_buttons_box, false, true);
  _buttons_box.pack_start(_button, true, true);
  _buttons_box.pack_start(_spin_button, true, true);



  // Sets the border width of the window.
  set_border_width(10);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  _button.signal_clicked().connect(sigc::mem_fun(*this,
						  &MainWindow::on_button_clicked));

  // This packs the button into the Window (a container).
  add(_box);
  show_all_children();
 
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_button_clicked()
{
  std::cout << "Loader" << std::endl;
}
void MainWindow::on_spin_button_clicked()
{
  int value = _spin_button.get_value_as_int();
  std::cout << "spin button is " << value << std::endl;
}
