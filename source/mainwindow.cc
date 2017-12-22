#include "mainwindow.h"
#include <iostream>
#include <fmt/format.h>
#include <gtkmm/icontheme.h>

#include "icon.cc"

MyScrolledWindow::MyScrolledWindow()
  :Gtk::ScrolledWindow{}
{

}

MyScrolledWindow::~MyScrolledWindow()
{

}
void MyScrolledWindow::on_realize()
{
  this->Gtk::ScrolledWindow::on_realize();
  std::cout << "MyScrolledWindow realize called" << std::endl;
  auto window {this->get_window()};
  auto cursor{ Gdk::Cursor::create(Gdk::ICON)};
  window->set_cursor(cursor);
}

MainWindow::~MainWindow()
{

}

MainWindow::MainWindow(Glib::RefPtr<Gtk::Application> t_application, const char*image_filename)
  : _application{t_application},
  //_box(Gtk::ORIENTATION_VERTICAL),
    //_buttons_box(Gtk::ORIENTATION_HORIZONTAL),
    //_button{Gtk::manage(new Gtk::Button("Quit"))},
    _spin_button(),
    _image(image_filename),
    _scrolled_window()

{
  Glib::RefPtr<Gtk::IconTheme> defaultIconTheme = Gtk::IconTheme::get_default();
  set_title("Ubik");
  Glib::RefPtr<Gdk::Pixbuf> icon = Gdk::Pixbuf::create_from_xpm_data(ubik);
  set_icon(icon);

  _spin_button.set_range(0, 100);
  _spin_button.set_value(50);
  _spin_button.set_increments(1, 10);
  _spin_button.signal_changed().connect(sigc::mem_fun(*this, &MainWindow::on_spin_button_clicked));
  _box.pack_start(_buttons_box, false, true);
  _buttons_box.pack_start(_button, true, true);
  _buttons_box.pack_start(_spin_button, true, true);
  _box.pack_end(_scrolled_window);
  _scrolled_window.add(_image);

  // Sets the border width of the window.
  set_border_width(10);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  _button.signal_clicked().connect(sigc::mem_fun(*this,
						  &MainWindow::on_button_clicked));

  // This packs the button into the Window (a container).
  add(_box);

  Glib::RefPtr<Gdk::Pixbuf> pix = _image.get_pixbuf();
  fmt::print(" pix-width {} pix-height {}",
	     pix->get_width(),
	     pix->get_height());
  set_default_size(pix->get_width () + 30, 60  + pix->get_height());

  show_all_children();


}



void MainWindow::on_what()
{
  std::cout << "Cursor ..." << std::endl;
  auto window {_scrolled_window.get_window()};
  //  auto cursor{ Gdk::Cursor::create(Gdk::ICON)};
  window->set_cursor(_cursor);
}


void MainWindow::on_button_clicked()
{
  std::cout << "Quitting ..." << std::endl;
  _application->quit();

}
void MainWindow::on_spin_button_clicked()
{
  int value = _spin_button.get_value_as_int();
  on_what();
  std::cout << "spin button is " << value << std::endl;
}

void MainWindow::on_realize()
{
  this->Gtk::Window::on_realize();

  int  bh {_box.get_allocated_height()};
  fmt::print("box_height {}", bh);
  				//
}
