======
libift
======

About
=====

This is a library for incremental failure test.

Install
=======

::

  $ ./configure --prefix=/where/to/install
  $ make
  $ sudo make install

Usage
=====

Write white box test (see "sample" directory) and link libift.

::

  $ PKG_CONFIG_DIR=/where/to/install/lib/pkgconfig:$PKG_CONFIG_DIR
  $ g++ your_test.cpp -o your_test $(pkg-config libift --cflags --libs)

Then, run test, like this.

::

  $ runift your_test

