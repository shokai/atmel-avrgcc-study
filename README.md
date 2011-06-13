AVR-GCC study
=============


Dependencies
------------

* [CrossPack for AVR](http://www.obdev.at/products/crosspack/index.html)
* avrdude


Install USB enabled avrdude
---------------------------

    % sudo port install avrdude
    % sudo cp /opt/local/etc/avrdude.conf /opt/local/etc/avrdude.conf.bak
    % sudo cp ./avrdude.conf /opt/local/etc/avrdude.conf


Set PATH
--------

~/.profile

    export PATH=$PATH:/opt/local/bin
    export PATH=$PATH:/usr/local/CrossPack-AVR/bin

